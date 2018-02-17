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

    sort(alphabet.begin(), alphabet.end());



    // Map of Unique Chars and Their Frequencies
    map<char, unsigned long> counts;
    for (unsigned long i = 0; i < contents.length(); ++i) {
        counts[contents[i]]++;
    }

    // This Prints the Alphabet and Frequencies
    ip = alphabet.begin();
    for (size_t i = 0; i < alphabet.length(); ++i) {
        cout << alphabet[i] << ' ' << counts[*ip] << endl;
        ++ip;
    }


    return 0;
}
