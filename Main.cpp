#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
    std::fstream file_in_stream;
    file_in_stream.open("./res/warpeace.txt");
    if (!file_in_stream.is_open()) {
        std::cout << "couldn't open file" << std::endl;
    } else {
        std::cout << "opened file" << std::endl;
    }

    std::unordered_map<std::string, uint32_t> dictionary;

    // initialize table with single char strings
    char c = 0;
    uint32_t code = 0;
    std::string str = "";
    while (file_in_stream.get(c)) {
        str = "";
        str += c;
        if (dictionary.find(str) == dictionary.end()) {
            dictionary.insert(std::make_pair(str, code));
            code++;
        }
    }

    file_in_stream.seekg(0, file_in_stream.beg);
    file_in_stream.close();
    file_in_stream.open("./res/warpeace.txt");

    std::vector<uint32_t> encoded;
    std::fstream file_out_stream;
    file_out_stream.open("./res/warpeace.lzw", std::fstream::out | std::fstream::binary);

    std::string p = "";
    file_in_stream.get(c);
    p = c;
    while (file_in_stream.get(c)) {
        if (dictionary.find(p + c) != dictionary.end()) {
            p += c;
        } else {
            encoded.push_back(dictionary[p]);
            // file_out_stream << dictionary[p] << std::endl;
            // file_out_stream.write((char*)(&dictionary[p]), sizeof(uint32_t));
            dictionary.insert(std::make_pair(p + c, code));
            code++;
            p = c;
        }
    }
    encoded.push_back(dictionary[p]);
    // file_out_stream << dictionary[p] << std::endl;

    for (auto it = encoded.begin(); it != encoded.end(); it++) {
        file_out_stream.write((char*)(&it), sizeof(uint32_t));
    }

    std::cout << "size of encoded: " << encoded.size() * sizeof(encoded[0]) << std::endl;

    // std::unordered_map<std::string, int>::iterator itr;
    // for (itr = dictionary.begin(); itr != dictionary.end(); itr++) {
    //     file_out_stream<< itr->first << " " << itr->second << std::endl;
    // }
    file_in_stream.close();
    file_out_stream.close();

    return 0;
}
