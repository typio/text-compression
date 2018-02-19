#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

char getChar(string code, string codes) {
    int pos = codes.find(code);
    int findStart = 0;
    bool found = false;
    while (!found) {
        pos = codes.find(code, findStart);
        char c = codes[pos - 2];
        if (c == '>' || c == '<' || c == '1' || c == '0') {
            findStart++;
        } else {
            found = true;
        }
    }
    // this cout is just for fun
    cout << codes[pos - 2];
    return codes[pos - 2];
}

void writeDecompressed(string compressedPath, string freqsPath) {

    // load text file as string
    ifstream compressed(compressedPath.c_str());
    string compressedStr((istreambuf_iterator<char>(compressed)),
                 istreambuf_iterator<char>());
    compressed.close();

    // load freq file as string
    ifstream freqs(freqsPath.c_str());
    string freqsStr((istreambuf_iterator<char>(freqs)),
                 istreambuf_iterator<char>());
    freqs.close();

    // write to file
    ofstream decompressed("decompressed.txt");

    string s = compressedStr;
    stringstream ss(s);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> codes(begin, end);
    copy(codes.begin(), codes.end(), ostream_iterator<string>(cout, " "));

    for (size_t i = 0; i < codes.size(); i++) {
        decompressed << getChar(codes.at(i), freqsStr);
    }
}
