#include <iostream>
#include <fstream>
#include <iomanip>
#include "Checker.hpp"

using namespace std;

int main() {
    PlagiarismChecker pc(3); // k=3 shingle size
    
    string f1, f2;
    cout << "Enter Filename 1 (e.g., doc1.txt): "; cin >> f1;
    cout << "Enter Filename 2 (e.g., doc2.txt): "; cin >> f2;

    double result = pc.check(f1, f2);

    // Create and write to the output text file
    ofstream outFile("report.txt");

    if (outFile.is_open()) {
        outFile << "==========================================" << endl;
        outFile << "       PLAGIARISM DETECTION REPORT        " << endl;
        outFile << "==========================================" << endl;
        outFile << "File 1: " << f1 << endl;
        outFile << "File 2: " << f2 << endl;
        outFile << "------------------------------------------" << endl;
        outFile << "Similarity Percentage: " << fixed << setprecision(2) << result << "%" << endl;
        outFile << "------------------------------------------" << endl;
        
        if (result > 70.0) outFile << "STATUS: CRITICAL (Direct Plagiarism)" << endl;
        else if (result > 30.0) outFile << "STATUS: WARNING (Significant Overlap)" << endl;
        else outFile << "STATUS: CLEAR (Low Similarity)" << endl;
        
        outFile << "==========================================" << endl;
        outFile.close();

        cout << "\nAnalysis Complete! Please open 'report.txt' to see the results." << endl;
    } else {
        cerr << "Error: Could not create the report file." << endl;
    }

    // This prevents the terminal from closing instantly on Windows
    cout << "\nPress Enter to exit...";
    cin.ignore();
    cin.get();

    return 0;
}