#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>
#include <string>
#include <bitset>
#include <unordered_map>

struct symbol {
    unsigned value;
    unsigned numberOfBits;
};


unsigned getMinimumNumberOfBits(unsigned number, bool decrement) {
    unsigned n = number-decrement;
    unsigned result = 0;

    while (n > 0) {
        n >>= 1;
        ++result;
    }

    return result < 8 ? 8 : result;
}

std::string concatenateBinary(const std::vector<symbol>& symbols) {
    std::string result;
    for (symbol s : symbols)
        result += std::bitset<32>(s.value).to_string().substr(32 - s.numberOfBits, s.numberOfBits);
    return result;
}

void writeEncodedFile(const std::vector<symbol>& encoded) {
    std::ofstream output("encoded.lzw", std::ofstream::binary);

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

void writeDecodedFile(const std::string& decoded) {
    std::ofstream output("decoded", std::ofstream::binary);

    // We won't write the last byte as it is an EOF signal.
    output.write(decoded.c_str(), decoded.size()-1);

    output.close();
}

static std::vector<char> readFile(char const *path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return std::vector<char>();
    }

    std::ifstream::pos_type pos = file.tellg();

    std::vector<char> result(pos);

    file.seekg(0, std::ios::beg);
    file.read(&result[0], pos);

    return result;
}

std::string toBinaryString(const std::vector<char>& bin){
    std::string binaryString;

    for (const char byte : bin)
        binaryString += std::bitset<8>(byte).to_string();

    return binaryString;
}

std::vector<symbol> encode(const std::string &original, unsigned long long maxDictSize) {
    unsigned dictSize = 256;
    std::unordered_map<std::string, unsigned> dictionary;
    std::string w;
    std::vector<symbol> result;

    // Filling the dict with each byte value
    for (unsigned i = 0; i < 256; i++)
        dictionary[std::string(1, i)] = i;


    for (const char c : original) {
        std::string wc = w + c;

        // Checking if the current sequence is in the dict
        if (dictionary.count(wc))
            w = wc;
        else {  // If not, inserts it in the result
            result.push_back({dictionary[w], getMinimumNumberOfBits(dictSize, true)});
            if(dictionary.size() <= maxDictSize)
                dictionary[wc] = dictSize++;
            w = c;
        }
    }

    if (!w.empty())
        result.push_back({dictionary[w], getMinimumNumberOfBits(dictSize, true)});

    return result;
}

std::string decode(const std::string &compressed, unsigned long long maxDictSize) {
    unsigned dictSize = 256;
    std::unordered_map<unsigned, std::string> dictionary;
    for (unsigned i = 0; i < 256; i++)
        dictionary[i] = std::string(1, i);

    unsigned currentSymbol =  std::bitset<32>(compressed.substr(0, 8)).to_ulong();
    std::string w(1, currentSymbol); //Decoding the first symbol directly
    std::string result = w;
    unsigned numberOfBits;
    std::string entry;
    
    for (unsigned i = 8; i < compressed.size(); i += numberOfBits) {
        numberOfBits = getMinimumNumberOfBits(dictSize, false);
        currentSymbol = std::bitset<32>(compressed.substr(i, numberOfBits)).to_ulong();

        if (dictionary.count(currentSymbol))
            entry = dictionary[currentSymbol];
        else if (currentSymbol == dictSize)
            entry = w + w[0];
        else{
            char errorStr[256];
            sprintf(errorStr, "Badly compressed symbol \"%d\" (dictSize = %d)\n", currentSymbol, dictSize);
            throw std::runtime_error(errorStr);
        }
        
        result += entry;

        if(dictionary.size() <= maxDictSize)
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

    int dictPow = std::atoi(argv[2]);

    if(dictPow >= 32 || dictPow < 1){
        printf("Invalid dict size! Max: 31");
        return 1;
    }

    unsigned long long dict_max_size = 1 << std::atoi(argv[2]);
    std::vector<char> file_content = readFile(argv[3]);
    std::string file_content_str(file_content.begin(), file_content.end());

    if(!strcmp(argv[1], "-c")){
        printf("Compressing file with a %lldb dict at path: %s\n", dict_max_size, argv[3]);
        std::vector<symbol> compressed = encode(file_content_str, dict_max_size);
        writeEncodedFile(compressed);
        return 0;
    }

    if(!strcmp(argv[1], "-d")){
        printf("Decompressing file with a %lldb dict at path: %s\n", dict_max_size, argv[3]);
        std::string decompressed = decode(toBinaryString(file_content), dict_max_size);
        writeDecodedFile(decompressed);
        return 0;
    }   
}