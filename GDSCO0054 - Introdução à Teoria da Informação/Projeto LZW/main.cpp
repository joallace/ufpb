#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>
#include <string>
#include <bitset>
#include <unordered_map>


unsigned getMinimumNumberOfBits(unsigned number) {
    unsigned n = number-1;
    unsigned result = 0;

    while (n > 0) {
        n >>= 1;
        ++result;
    }

    return result < 8 ? 8 : result;
}

std::string concatenateBinary(const std::vector<unsigned>& numbers) {
    std::string result;
    for (unsigned num : numbers) {
        // Convert number to binary string with fixed number of bits
        int numberOfBits = getMinimumNumberOfBits(num);
        result += std::bitset<32>(num).to_string().substr(32 - numberOfBits, numberOfBits);
    }
    return result;
}

void writeFile(const std::vector<unsigned>& encoded) {
    std::ofstream output("out.lzw", std::ofstream::binary);

    // Pad the bit string to make its length a multiple of 8
    std::string paddedBitString = concatenateBinary(encoded);
    while (paddedBitString.length() % 8 != 0)
        paddedBitString += "0";

    // Convert the padded bit string to bytes and write them to the output stream
    for (size_t i = 0; i < paddedBitString.length(); i += 8) {
        char byte = 0;
        for (size_t j = 0; j < 8; ++j) {
            byte <<= 1;
            byte |= (paddedBitString[i + j] == '1') ? 1 : 0;
        }
        output.put(byte);
    }

    output.close();
}

static std::vector<char> readFile(char const *path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    std::ifstream::pos_type pos = file.tellg();

    std::vector<char> result(pos);

    file.seekg(0, std::ios::beg);
    file.read(&result[0], pos);

    return result;
}

std::vector<unsigned> encode(const std::string &original, unsigned maxDictSize) {
    unsigned dictSize = 256;
    std::unordered_map<std::string, unsigned> dictionary;
    std::string w;
    std::vector<unsigned> result;

    // Filling the dict with each byte value
    for (unsigned i = 0; i < 256; i++)
        dictionary[std::string(1, i)] = i;


    for (const char c : original) {
        std::string wc = w + c;

        // Checking if the current sequence is in the dict
        if (dictionary.count(wc))
            w = wc;
        else {  // If not, inserts it in the result
            result.push_back(dictionary[w]);
            if(dictionary.size() <= maxDictSize)
                dictionary[wc] = dictSize++;
            w = c;
        }
    }

    if (!w.empty())
        result.push_back(dictionary[w]);

    return result;
}

std::string decode(const std::vector<int> &compressed, int maxDictSize) {
    int dictSize = 256;
    std::unordered_map<int, std::string> dictionary;
    for (int i = 0; i < 256; i++)
        dictionary[i] = std::string(1, i);

    std::string w(1, compressed[0]);
    std::string result = w;
    std::string entry;
    
    for (int i = 1; i < compressed.size(); i++) {
        int k = compressed[i];
        if (dictionary.count(k))
            entry = dictionary[k];
        else if (k == dictSize)
            entry = w + w[0];
        else
            throw std::runtime_error("Bad compressed k");

        result += entry;

        dictionary[dictSize++] = w + entry[0];

        w = entry;
    }

    return result;
}

int main(int argc, char *argv[]) {
    if(argc < 4){
        printf("Missing parameters! Usage:\n./lzw -[c or d] [number of n for 2^n bits for the dict] [file path]\n");
        return 1;
    }

    unsigned dict_max_size = 1 << std::atoi(argv[2]);
    std::vector<char> file_content = readFile(argv[3]);
    std::string file_content_str(file_content.begin(), file_content.end());

    if(!strcmp(argv[1], "-c")){
        printf("Compressing file with a %db dict at path: %s\n", dict_max_size, argv[3]);
        std::vector<unsigned> compressed = encode(file_content_str, dict_max_size);
        writeFile(compressed);
        return 0;
    }

    // if(!strcmp(argv[1], "-d")){
    //     printf("Decompressing file at path: %s\n", argv[3]);
    //     std::vector<int> decompressed = encode(file_content_str, dict_max_size);
    //     return 0;
    // }   
}