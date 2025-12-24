#ifndef CHECKER_HPP
#define CHECKER_HPP

#include <vector>
#include <string>
#include <unordered_set>

class PlagiarismChecker {
private:
    int k; // Shingle size
    std::unordered_set<std::string> stopWords;
    
    std::string cleanWord(std::string word);
    std::vector<std::string> tokenize(std::string filePath);
    std::unordered_set<size_t> generateGrams(const std::vector<std::string>& tokens);

public:
    PlagiarismChecker(int shingleSize = 3);
    double check(std::string file1, std::string file2);
};

#endif