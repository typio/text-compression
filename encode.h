#include <iostream>
#include <algorithm>
#include <fstream>
#include <streambuf>
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

stringstream codes;
void printCodes(struct Node* root, string str) {
    ofstream o("freqs.txt", ios::app);
    if (!root)
        return;

    if (root -> c != '$') {
        o << root -> c << ">" << str << "<";
        codes << root -> c << ">" << str << "<";
    }
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

string getCode(char c, string codes) {
    for (size_t i = 0; i < codes.length(); i++) {
        // for not break line char
        if (codes[i] == c) {
            int startStr = i + 2;
            int endStr = startStr;
            // find end of code
            int j = startStr;
            while (j < startStr + 25) {
                if (codes[j] == '<') {
                    endStr = j;
                    break;
                } else {
                    j++;
                }
            }
            return codes.substr(startStr, endStr - startStr);
            // for break line char
        }
    }
    return NULL;
}

void writeCompressed(string textPath) {
    string codesStr = codes.str();

    // load text file as string
    ifstream text(textPath.c_str());
    string textStr((istreambuf_iterator<char>(text)),
                 istreambuf_iterator<char>());
    text.close();

    // write to file
    ofstream compressed("compressed.bin", ios::binary);

    for (size_t i = 0; i < textStr.length(); i++) {
        compressed << getCode(textStr[i], codesStr) << " ";
    }
    cout << '\n' << codesStr << '\n';
}
