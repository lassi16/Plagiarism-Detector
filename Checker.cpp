#include "Checker.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>

PlagiarismChecker::PlagiarismChecker(int shingleSize) : k(shingleSize) {
    stopWords = {"a", "an", "the", "and", "or", "is", "are", "to", "of", "in"};
}

std::string PlagiarismChecker::cleanWord(std::string word) {
    std::string cleaned = "";
    for (char c : word) if (isalnum(c)) cleaned += tolower(c);
    return cleaned;
}

std::vector<std::string> PlagiarismChecker::tokenize(std::string filePath) {
    std::ifstream file(filePath);
    std::vector<std::string> tokens;
    std::string word;
    while (file >> word) {
        std::string cleaned = cleanWord(word);
        if (!cleaned.empty() && stopWords.find(cleaned) == stopWords.end()) {
            tokens.push_back(cleaned);
        }
    }
    return tokens;
}

std::unordered_set<size_t> PlagiarismChecker::generateGrams(const std::vector<std::string>& tokens) {
    std::unordered_set<size_t> grams;
    if (tokens.size() < k) return grams;
    for (size_t i = 0; i <= tokens.size() - k; ++i) {
        std::string sequence = "";
        for (int j = 0; j < k; ++j) sequence += tokens[i + j];
        grams.insert(std::hash<std::string>{}(sequence));
    }
    return grams;
}

double PlagiarismChecker::check(std::string f1, std::string f2) {
    auto tokens1 = tokenize(f1);
    auto tokens2 = tokenize(f2);
    if (tokens1.empty() || tokens2.empty()) return 0.0;

    auto grams1 = generateGrams(tokens1);
    auto grams2 = generateGrams(tokens2);

    int matches = 0;
    for (size_t h : grams1) if (grams2.count(h)) matches++;

    size_t unionSize = grams1.size() + grams2.size() - matches;
    return (unionSize == 0) ? 0 : (double)matches / unionSize * 100;
}