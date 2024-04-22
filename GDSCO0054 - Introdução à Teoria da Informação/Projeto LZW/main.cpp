#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>
#include <string>
#include <bitset>
#include <unordered_map>

struct arguments {
    size_t maxDictSize = 4096;
    char operation = 'c';
    char strategyId = 2;
    std::string outputPath;
    std::string inputPath;
    bool collectAnalysis = false;
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

double getBitsPerSymbol(const std::vector<symbol>& symbols){
    size_t bits = 0;
    for (const symbol s : symbols)
        bits += s.numberOfBits;
    return (double)bits/symbols.size();    
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
        std::cerr << "\nERROR: Could not open the file at the provided path." << std::endl;
        exit(1);
    }

    std::ifstream::pos_type pos = file.tellg();

    std::vector<char> result(pos);

    file.seekg(0, std::ios::beg);
    file.read(&result[0], pos);

    return result;
}


//------====== Strategy Functions ======------

void keepStatic(size_t& dictSize, std::unordered_map<std::string, size_t>& dict, std::vector<double>& compressionRatios) {
    return;
}

void keepStatic(size_t& dictSize, std::unordered_map<size_t, std::string>& dict, std::vector<double>& compressionRatios) {
    return;
}


void reset(size_t& dictSize, std::unordered_map<std::string, size_t>& dict, std::vector<double>& compressionRatios) {
    dict.clear();

    dictSize = 256;
    for (unsigned i = 0; i < 256; i++)
        dict[std::string(1, i)] = i;
}

void reset(size_t& dictSize, std::unordered_map<size_t, std::string>& dict, std::vector<double>& compressionRatios) {
    dict.clear();

    dictSize = 256;
    for (unsigned i = 0; i < 256; i++)
        dict[i] = std::string(1, i);
}


void resetIfUnderperforming(size_t& dictSize, std::unordered_map<std::string, size_t>& dict, std::vector<double>& compressionRatios) {
    double compressionRatioMean = 0;
    size_t dataSize = compressionRatios.size();
    size_t windowSize = dataSize < 400 ? dataSize/4 : 100;

    for(size_t i = dataSize-windowSize-1; i < dataSize-1; i++)
        compressionRatioMean += compressionRatios[i];

    if((compressionRatioMean/windowSize - compressionRatios[dataSize-1]) < -0.5){
        printf("Dicionário resetado\n");
        reset(dictSize, dict, compressionRatios);
    }
}

void resetIfUnderperforming(size_t& dictSize, std::unordered_map<size_t, std::string>& dict, std::vector<double>& compressionRatios) {
    double compressionRatioMean = 0;
    size_t dataSize = compressionRatios.size();
    size_t windowSize = dataSize < 400 ? dataSize/4 : 100;

    for(size_t i = dataSize-windowSize-1; i < dataSize-1; i++)
        compressionRatioMean += compressionRatios[i];

    if((compressionRatioMean/windowSize - compressionRatios[dataSize-1]) < -0.5){
        printf("Dicionário resetado\n");
        reset(dictSize, dict, compressionRatios);
    }
}


//------====== Encoding/Decoding Functions ======------

std::vector<symbol> encode(const std::string &original, arguments &args) {
    size_t dictSize = 256;
    std::unordered_map<std::string, size_t> dictionary;
    std::string w;
    std::vector<symbol> result;
    std::vector<double> compressionRatio;
    void (*strategies[3])(size_t&, std::unordered_map<std::string, size_t>&, std::vector<double>&) = {&keepStatic, &reset, &resetIfUnderperforming};

    // Filling the dict with each byte value
    for (unsigned i = 0; i < 256; i++)
        dictionary[std::string(1, i)] = i;


    for (size_t i = 0; i < original.size(); i++) {
        std::string wc = w + original[i];

        // Checking if the current sequence is in the dict
        if (dictionary.count(wc))
            w = wc;
        else {  // If not, inserts it in the result
            result.push_back({dictionary[w], getMinimumNumberOfBits(dictSize, true)});

            if(!(result.size()%256))
                compressionRatio.push_back(getBitsPerSymbol(result));

            if(dictionary.size() <= args.maxDictSize)
                dictionary[wc] = dictSize++;
            else
                strategies[args.strategyId](dictSize, dictionary, compressionRatio);
            w = original[i];
        }
    }

    if (!w.empty())
        result.push_back({dictionary[w], getMinimumNumberOfBits(dictSize, true)});

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
    std::vector<double> compressionRatio;
    unsigned numberOfBits;
    std::string entry;
    void (*strategies[3])(size_t&, std::unordered_map<size_t, std::string>&, std::vector<double>&) = {&keepStatic, &reset, &resetIfUnderperforming};
    
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
        
        if(!(symbols.size()%256))
            compressionRatio.push_back(getBitsPerSymbol(symbols));

        if(dictionary.size() <= args.maxDictSize)
            dictionary[dictSize++] = w + entry[0];
        else
            strategies[args.strategyId](dictSize, dictionary, compressionRatio);

        w = entry;
    }

    return result;
}


//------====== Main ======------

arguments argParse(int argc, char** argv){
    arguments args;

    if (argc < 2) {
        std::cerr << "\nERROR: Missing parameters! Usage:\n"
                  << " ./lzw file_path [-c or -d number of n for 2^n bits for the dict] [-o output_path]\n";
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

        if(!strcmp(argv[i], "-s")){
            args.strategyId = std::atoi(argv[i+1]);
            if(args.strategyId > 3 || args.strategyId < 1){
                std::cerr << "\nERROR: Invalid strategy id! min: 1; max: 3\n";
                exit(1);
            }
        }

        if(!strcmp(argv[i], "-b"))
            args.collectAnalysis = true;
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