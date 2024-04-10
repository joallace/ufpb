#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>
#include <string>
#include <unordered_map>

static std::vector<char> read_file(char const *path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    std::ifstream::pos_type pos = file.tellg();

    std::vector<char> result(pos);

    file.seekg(0, std::ios::beg);
    file.read(&result[0], pos);

    return result;
}

std::vector<int> encode(const std::string &original, int maxDictSize) {
    int dictSize = 256;
    std::unordered_map<std::string, int> dictionary;
    for (int i = 0; i < 256; i++) {
        dictionary[std::string(1, i)] = i;
    }

    std::string w;
    std::vector<int> result;

    for (const char c : original) {
        std::string wc = w + c;
        if (dictionary.count(wc))
            w = wc;
        else {
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

    int dict_max_size = 1 << std::atoi(argv[2]);
    std::vector<char> file_content = read_file(argv[3]);
    std::string file_content_str(file_content.begin(), file_content.end());

    if(!strcmp(argv[1], "-c")){
        printf("Compressing file with a %db dict at path: %s\n", dict_max_size, argv[3]);
        std::vector<int> compressed = encode(file_content_str, dict_max_size);
        std::ofstream output("out3.lzw", std::ofstream::binary);
        for(const int c : compressed)
            output.write(std::to_string(c).c_str(), sizeof(int));

        return 0;
    }

    if(!strcmp(argv[1], "-d")){
        printf("Decompressing file at path: %s\n", argv[3]);
        std::vector<int> decompressed = encode(file_content_str, dict_max_size);
        return 0;
    }   
}