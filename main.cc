// Huffman Compression
// Thomas Odysseus Huber

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <map>
using namespace std;

int main(int argc, char** argv) {
    // Read Text From Arg as String
    ifstream in(argv[1]);
    string contents((istreambuf_iterator<char>(in)),
    istreambuf_iterator<char>());

    // Sort String of Full Text
    sort(contents.begin(), contents.end());

    // Make Array of Alphabet
    string alphabet = contents;
    auto ip = unique(alphabet.begin(), alphabet.end());
    alphabet.resize(distance(alphabet.begin(), ip));

    for (ip = alphabet.begin(); ip != alphabet.end(); ++ip) {
        //cout << *ip << endl;
    }

    // Map of Unique Chars and Their Frequencies
    map<char, unsigned long> counts;
    for (unsigned long i = 0; i < contents.length(); i++) {
        counts[contents[i]]++;
    }

    for (size_t i = 0; i < alphabet.length(); i++) {
        cout << alphabet[i] << ' ' << counts[i] << '\n';
    }


    return 0;
}
