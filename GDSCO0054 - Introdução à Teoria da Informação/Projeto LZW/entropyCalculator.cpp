#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <map>

static std::vector<char> readFile(std::string path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        std::cerr << "\nERROR: Could not open the file at the provided path." << std::endl;
        exit(1);
    }

    std::ifstream::pos_type pos = file.tellg();

    std::vector<char> result(pos);

    file.seekg(0, std::ios::beg);
    file.read(&result[0], pos);

    return result;
}

double calculateEntropy(const std::vector<char>& data) {
    std::map<char, int> frequencyMap;
    for (char byte : data) {
        ++frequencyMap[byte];
    }

    double entropy = 0.0;
    double dataSize = (double)(data.size());

    for (auto& pair : frequencyMap) {
        double probability = pair.second / dataSize;
        entropy -= probability * std::log2(probability);
    }

    return entropy;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    std::string filePath = argv[1];
    std::vector<char> fileData = readFile(filePath);
    double entropy = calculateEntropy(fileData);

    std::cout << "Entropy of the file '" << filePath << "' is " << entropy << " bits per symbol." << std::endl;

    return 0;
}
