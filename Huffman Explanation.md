***\*\*Huffman Coding File Compression Project\*\**** **-**



**Explanation:**

This project implements a File Compression and Decompression tool using Huffman Coding in C++. It demonstrates the use of Data Structures such as Min Heap, Binary Tree, Hash Map, and the Greedy Algorithm strategy. 



**Algorithm Overview**:

1\. Count frequency of each character in the input file

2\. Insert characters with their frequencies into a Min Heap

3\. Extract the two smallest nodes and create a new parent node

4\. Repeat until a single node remains – this becomes the Huffman Tree root

5. Traverse the tree to generate binary codes for each character

6. Encode the text using generated binary codes

7. Store encoded data and frequency table to reconstruct during decompression



**Data Structures Used:**

1. Priority Queue (Min Heap) – to efficiently extract minimum frequency elements

2. Binary Tree – to build Huffman Tree nodes

3. Hash Map – to store character to binary code mapping

4. Bit Manipulation – to convert binary string to byte format



**Complexity:**

>Time Complexity: O(n log n)

>Space Complexity: O(n)



**How to Run:**

Compile using: g++ huffman.cpp -o huffman 

Run using: ./huffman 

Choose option 1 to compress and option 2 to decompress.



**Project Highlights:**

1. Real-world application project

2. Demonstrates strong knowledge of DSA

3. Shows understanding of compression algorithms



