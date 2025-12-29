#include <bits/stdc++.h>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = NULL;
    }
};

// Compare function for min heap
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

unordered_map<char, string> huffmanCode;
unordered_map<string, char> reverseCode;

void buildCodes(Node* root, string code) {
    if (!root)
        return;

    if (!root->left && !root->right)
        huffmanCode[root->ch] = code;

    buildCodes(root->left, code + "0");
    buildCodes(root->right, code + "1");
}

// Build Huffman Tree
Node* buildHuffmanTree(unordered_map<char, int>& freq) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (auto it : freq)
        minHeap.push(new Node(it.first, it.second));

    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();

        Node* newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        minHeap.push(newNode);
    }

    return minHeap.top();
}

// Convert binary string to bytes for file storing
string binaryToBytes(string bin) {
    string res = "";
    for (int i = 0; i < bin.length(); i += 8) {
        string byte = bin.substr(i, 8);
        bitset<8> bits(byte);
        res += char(bits.to_ulong());
    }
    return res;
}

// Convert bytes back to binary
string bytesToBinary(string data) {
    string res = "";
    for (unsigned char c : data) {
        bitset<8> bits(c);
        res += bits.to_string();
    }
    return res;
}

// Compress Function
void compress(string inputFile, string outputFile) {
    ifstream in(inputFile, ios::binary);
    if (!in.is_open()) {
        cout << "File not found!";
        return;
    }

    string text((istreambuf_iterator<char>(in)), (istreambuf_iterator<char>()));
    in.close();

    unordered_map<char, int> freq;
    for (char c : text)
        freq[c]++;

    Node* root = buildHuffmanTree(freq);
    buildCodes(root, "");

    string encoded = "";
    for (char c : text)
        encoded += huffmanCode[c];

    ofstream out(outputFile, ios::binary);

    // Write Table Size
    out << freq.size() << "\n";

    // Write Table (char frequency)
    for (auto p : freq)
        out << p.first << " " << p.second << "\n";

    // Write Encoded Binary as Bytes
    // Padding to make 8-bit chunks
    int padding = 8 - (encoded.size() % 8);
    for(int i=0;i<padding;i++) encoded += "0";

    out << padding << "\n";
    out << binaryToBytes(encoded);

    out.close();

    cout << "Compression Successful! ✔\n";
}

// Decompress Function
void decompress(string inputFile, string outputFile) {
    ifstream in(inputFile, ios::binary);
    if (!in.is_open()) {
        cout << "Compressed file not found!";
        return;
    }

    int tableSize;
    in >> tableSize;

    unordered_map<char, int> freq;
    for (int i = 0; i < tableSize; i++) {
        char c;
        int f;
        in >> noskipws >> c;
        in >> skipws >> f;
        freq[c] = f;
    }

    int padding;
    in >> padding;

    string data((istreambuf_iterator<char>(in)), (istreambuf_iterator<char>()));
    in.close();

    Node* root = buildHuffmanTree(freq);
    buildCodes(root, "");

    for (auto it : huffmanCode)
        reverseCode[it.second] = it.first;

    string binary = bytesToBinary(data);

    binary = binary.substr(0, binary.size() - padding);

    string decoded = "", temp = "";
    for (char bit : binary) {
        temp += bit;
        if (reverseCode.find(temp) != reverseCode.end()) {
            decoded += reverseCode[temp];
            temp = "";
        }
    }

    ofstream out(outputFile);
    out << decoded;
    out.close();

    cout << "Decompression Successful! ✔\n";
}

int main() {
    int choice;
    cout << "1. Compress File\n2. Decompress File\nChoose: ";
    cin >> choice;

    string inFile, outFile;
    if (choice == 1) {
        cout << "Enter input file name: ";
        cin >> inFile;
        cout << "Enter output compressed file name: ";
        cin >> outFile;
        compress(inFile, outFile);
    } else {
        cout << "Enter compressed file name: ";
        cin >> inFile;
        cout << "Enter output file name: ";
        cin >> outFile;
        decompress(inFile, outFile);
    }
}
