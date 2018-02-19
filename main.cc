// Huffman Compression
// Thomas Odysseus Huber

#include "encode.h"
#include "decode.h"

int main(int argc, char** argv) {
    remove("freqs.txt");
    // Read Text From Arg as String
    ifstream path(argv[1]);
    string contents((istreambuf_iterator<char>(path)),
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

    // Turn Counts into Array of Frequencies
    ip = alphabet.begin();
    int freq[alphabet.length()];
    for (size_t i = 0; i < alphabet.length(); ++i) {
        freq[i] = counts[*ip];
        ++ip;
    }

    // Alphabet String to Alph Char Array
    char alph[alphabet.length()];
    strcpy(alph, alphabet.c_str());

    int size = sizeof(alph) / sizeof(alph[0]);

    HuffmanCodes(alph, freq, size);

    int choice;
    cout << "1) compress\n2) decompress\n3) exit" << '\n';
    while (true) {
        cin >> choice;
        if (choice == 1) {
            writeCompressed(argv[1]);
        } else if (choice == 2) {
            writeDecompressed("compressed.bin", "freqs.txt");
        } else {
            return 0;
        }
    }

    return 0;
}
