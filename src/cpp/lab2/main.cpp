cd c#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <utility>
#include <algorithm>
#include <iomanip>

template<class K, class V>
std::vector<std::pair<V, K>> reverseMap(std::map<K, V> initMap) {
    std::vector<std::pair<V, K>> pairVector(0);
    for (const auto&[key, value] : initMap) {
        pairVector.push_back({value, key});
    }
    std::sort(pairVector.begin(), pairVector.end());
    return pairVector;
}

int main() {
    std::fstream file;
    file.ignore('\n');
    std::string word;
    std::map<std::string, int> wordCount;

    file.open("../text.txt");

    while (!file.eof()) {
        file >> word;
        word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); }), word.end());
        if (!word.empty()) {
            wordCount[word]++;
        }
    }

    auto countWord = reverseMap(wordCount);

    for (auto it = countWord.rbegin(); it != countWord.rend(); ++it) {
        std::cout << std::setw(5) << std::left << it->first << it->second << std::endl;
    }
    file.close();
}
