#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>
#include <string>
#include <bitset>
#include <unordered_map>


//------====== Structs ======------

struct arguments {
    size_t maxDictSize = 4096;
    char operation = 'c';
    std::string outputPath;
    std::string inputPath;
    std::string dictPath = "dict.bin";
    bool writeDict = false;
    bool readDict = false;
};

struct symbol {
    size_t value;
    unsigned numberOfBits;
};


//------====== Auxiliary Functions ======------

unsigned getMinimumNumberOfBits(unsigned number, bool decrement) {
    unsigned n = number-decrement;
    unsigned result = 0;

    while (n > 0) {
        n >>= 1;
        ++result;
    }

    return result < 8 ? 8 : result;
}

double getBitsPerSymbol(const std::vector<symbol>& symbols, size_t n_symbols){
    size_t bits = 0;
    for (const symbol s : symbols)
        bits += s.numberOfBits;
    return (double)bits/n_symbols;
}

std::string concatenateBinary(const std::vector<symbol>& symbols) {
    std::string result;
    for (symbol s : symbols)
        result += std::bitset<32>(s.value).to_string().substr(32 - s.numberOfBits, s.numberOfBits);
    return result;
}

std::string toBinaryString(const std::vector<char>& bin){
    std::string binaryString;

    for (const char byte : bin)
        binaryString += std::bitset<8>(byte).to_string();

    return binaryString;
}


//------====== Read/write Functions ======------

void writeEncodedFile(std::string path, const std::vector<symbol>& encoded) {
    std::ofstream output(path, std::ofstream::binary);

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

void writeDecodedFile(std::string path, const std::string& decoded) {
    std::ofstream output(path, std::ofstream::binary);

    // We won't write the last byte as it is an EOF signal.
    output.write(decoded.c_str(), decoded.size()-1);

    output.close();
}

static std::vector<char> readFile(std::string path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        std::cerr << "\nERROR: Could not open the file at the provided path.\n";
        exit(1);
    }

    std::ifstream::pos_type pos = file.tellg();

    std::vector<char> result(pos);

    file.seekg(0, std::ios::beg);
    file.read(&result[0], pos);

    return result;
}


//------====== Dictionary File Handling Functions ======------

void dictToFile(const std::unordered_map<std::string, size_t>& dictionary, const std::string& path) {
    std::ofstream output(path, std::ios::binary);

    if (!output.is_open()) {
        std::cerr << "\nERROR: Unable to open file for writing.\n";
        exit(1);
    }
    
    // Write the size of the map first
    size_t dictSize = dictionary.size();
    output.write((char *)(&dictSize), sizeof(size_t));

    // Write each key-value pair to the file
    for (const auto& pair : dictionary) {
        size_t keySize = pair.first.size();
        output.write((const char *)(&keySize), sizeof(size_t));
        output.write(pair.first.c_str(), keySize);
        output.write((const char *)(&pair.second), sizeof(size_t));
    }

    output.close();
}

std::unordered_map<std::string, size_t> dictFromFile(const std::string& path) {
    std::unordered_map<std::string, size_t> dictionary;
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "\nERROR: Could not open the file at the provided path.\n";
        exit(1);
    }
    
    // Read the size of the map first
    size_t mapSize;
    file.read((char*)(&mapSize), sizeof(size_t));

    // Read each key-value pair from the file
    for (size_t i = 0; i < mapSize; ++i) {
        size_t keySize;
        file.read((char*)(&keySize), sizeof(size_t));
        std::string key;
        key.resize(keySize);
        file.read(&key[0], keySize);
        size_t value;
        file.read((char*)(&value), sizeof(size_t));
        dictionary[key] = value;
    }

    file.close();

    return dictionary;
}


//------====== Encoding/Decoding Functions ======------

std::vector<symbol> encode(const std::string &original, arguments &args) {
    size_t dictSize = 256;
    std::unordered_map<std::string, size_t> dictionary;
    std::string w;
    std::vector<symbol> result;

    if(args.readDict)
        dictionary = dictFromFile(args.dictPath);
    else
        for (unsigned i = 0; i < 256; i++) // Filling the dict with each byte value
            dictionary[std::string(1, i)] = i;

    for (size_t i = 0; i < original.size(); i++) {
        std::string wc = w + original[i];

        if (dictionary.count(wc)) // Checking if the current sequence is in the dict
            w = wc;
        else {  // If not, inserts it in the result
            result.push_back({dictionary[w], getMinimumNumberOfBits(dictSize, true)});

            if(dictionary.size() <= args.maxDictSize)
                dictionary[wc] = dictSize++;
            w = original[i];
        }
    }

    if (!w.empty())
        result.push_back({dictionary[w], getMinimumNumberOfBits(dictSize, true)});

    if(args.writeDict)
        dictToFile(dictionary, "dict.bin");

    printf("Average length: %fb/symbol\n", getBitsPerSymbol(result, original.size()));

    return result;
}

std::string decode(const std::string &compressed, arguments &args) {
    size_t dictSize = 256;
    std::unordered_map<size_t, std::string> dictionary;
    for (unsigned i = 0; i < 256; i++)
        dictionary[i] = std::string(1, i);

    size_t currentSymbol =  std::bitset<32>(compressed.substr(0, 8)).to_ulong();
    std::string w(1, currentSymbol); //Decoding the first symbol directly
    std::string result = w;
    std::vector<symbol> symbols = {{currentSymbol, 8}};
    unsigned numberOfBits;
    std::string entry;
    
    for (size_t i = 8; i < compressed.size(); i += numberOfBits) {
        numberOfBits = getMinimumNumberOfBits(dictSize, false);
        currentSymbol = std::bitset<32>(compressed.substr(i, numberOfBits)).to_ulong();
        symbols.push_back({currentSymbol, numberOfBits});

        if (dictionary.count(currentSymbol))
            entry = dictionary[currentSymbol];
        else if (currentSymbol == dictSize)
            entry = w + w[0];
        else{
            char errorStr[256];
            sprintf(errorStr, "Badly compressed symbol \"%ld\" (dictSize = %ld)\n", currentSymbol, dictSize);
            throw std::runtime_error(errorStr);
        }
        
        result += entry;
        
        if(dictionary.size() <= args.maxDictSize)
            dictionary[dictSize++] = w + entry[0];

        w = entry;
    }


    return result;
}


//------====== Main ======------

arguments argParse(int argc, char** argv){
    arguments args;

    if (argc < 2) {
        std::cerr << "\nERROR: Missing parameters! Usage:\n"
                  << " " << argv[0] << " file_path [-c or -d number of n for 2^n bits for the dict] [-o output_path]\n";
        exit(1);
    }

    // First argument will always be the input file  path
    args.inputPath = argv[1];

    for(int i = 2; i < argc; i++){
        if(!strcmp(argv[i], "-o"))
            args.outputPath = argv[i+1];

        if(!strcmp(argv[i], "-c") || !strcmp(argv[i], "-d")){
            size_t dictPow = std::atoi(argv[i+1]);

            if(dictPow >= 32 || dictPow < 8){
                std::cerr << "\nERROR: Invalid dict size! min: 8; max: 31\n";
                exit(1);
            }

            args.operation = argv[i][1];
            args.maxDictSize = 1 << dictPow;
        }


        if(!strcmp(argv[i], "-e"))
            args.writeDict = true;

        if(!strcmp(argv[i], "-i")){
            args.dictPath = argv[i+1];
            args.readDict = true;
        }
    }

    if(args.outputPath.empty())
        if(args.operation == 'c')
            args.outputPath = "encoded.lzw";
        else
            args.outputPath = "decoded";

    return args;
}

int main(int argc, char *argv[]) {
    arguments args = argParse(argc, argv);

    std::vector<char> fileContent = readFile(args.inputPath);
    std::string fileContentStr(fileContent.begin(), fileContent.end());

    if(args.operation == 'c'){
        printf("Compressing file (%ldb) with a %ldb dict at path: %s\n", fileContent.size(), args.maxDictSize, args.inputPath.c_str());
        std::vector<symbol> compressed = encode(fileContentStr, args);
        writeEncodedFile(args.outputPath, compressed);
        return 0;
    }

    if(args.operation == 'd'){
        printf("Decompressing file (%ldb) with a %ldb dict at path: %s\n", fileContent.size(), args.maxDictSize, args.inputPath.c_str());
        std::string decompressed = decode(toBinaryString(fileContent), args);
        writeDecodedFile(args.outputPath, decompressed);
        return 0;
    }   
}