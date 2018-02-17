// Huffman Compression
// Thomas Odysseus Huber

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <bits/stdc++.h>
using namespace std;

struct Node {
    char c;
    unsigned freq;

    Node *left, *right;

    Node(char c, unsigned freq) {
        left = right = NULL;
        this -> c = c;
        this -> freq = freq;
    }
};

struct compare {
    bool operator()(Node* l, Node* r) {
        return (l -> freq > r -> freq);
    }
};

void printCodes(struct Node* root, string str) {
    if (!root)
        return;

    if (root -> c != '$')
        cout << root -> c << ": " << str << "\n";

    printCodes(root -> left, str + "0");
    printCodes(root -> right, str + "1");
}

void HuffmanCodes(char c[], int freq[], int size) {
    struct Node *left, *right, *top;

    priority_queue<Node*, vector<Node*>, compare> minHeap;

    for (int i = 0; i < size; ++i) {
        minHeap.push(new Node(c[i], freq[i]));
    }

    while (minHeap.size() != 1) {

        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        top = new Node('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    printCodes(minHeap.top(), "");
}

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

    return 0;
}
