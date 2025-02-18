// g++ -std=c++17 -o 1_tsv_to_csv 1_tsv_to_csv.cpp
// ./1_tsv_to_csv eng_sentences.tsv eng_sentences.csv

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cctype>

using namespace std;

// Helper: Convert a string to lowercase.
string toLowerCase(const string &s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(),
            [](unsigned char c) { return tolower(c); });
    return result;
}

// Helper: Escape a CSV field by wrapping it in quotes and escaping internal quotes.
string escapeCSV(const string &field) {
    string escaped = "\"";
    for (char c : field) {
        if (c == '\"') {
            escaped += "\"\""; // Escape double quotes
        } else {
            escaped.push_back(c);
        }
    }
    escaped += "\"";
    return escaped;
}

// Extract words from a sentence using regex.
vector<string> extractWords(const string &sentence) {
    vector<string> words;
    regex wordRegex(R"(\b[A-Za-z0-9']+\b)");
    auto begin = sregex_iterator(sentence.begin(), sentence.end(), wordRegex);
    auto end = sregex_iterator();
    for (auto it = begin; it != end; ++it) {
        words.push_back(toLowerCase(it->str()));
    }
    return words;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <input_tsv> <output_csv>" << endl;
        return 1;
    }
    
    string inputFile = argv[1];
    string outputFile = argv[2];

    ifstream inFile(inputFile);
    if (!inFile) {
        cerr << "Error opening input file: " << inputFile << endl;
        return 1;
    }
    
    ofstream outFile(outputFile);
    if (!outFile) {
        cerr << "Error opening output file: " << outputFile << endl;
        return 1;
    }
    
    // Write CSV header
    outFile << "Word,Sentence\n";
    
    // Use an unordered_set to ensure each "word|sentence" pair is only written once.
    unordered_set<string> seenPairs;
    
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string id, lang, sentence;
        if (!getline(ss, id, '\t')) continue;
        if (!getline(ss, lang, '\t')) continue;
        if (!getline(ss, sentence, '\t')) continue;
        
        // Process only English sentences.
        if (lang != "eng") continue;
        
        // Extract words from the sentence.
        vector<string> words = extractWords(sentence);
        for (const string &word : words) {
            // Construct a unique key for this word/sentence pair.
            string pairKey = word + "|" + sentence;
            if (seenPairs.find(pairKey) != seenPairs.end()) continue;
            seenPairs.insert(pairKey);
            
            outFile << escapeCSV(word) << "," << escapeCSV(sentence) << "\n";
        }
    }
    
    inFile.close();
    outFile.close();
    
    cout << "TSV to CSV conversion completed successfully." << endl;
    return 0;
}