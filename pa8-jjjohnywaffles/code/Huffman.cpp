// Huffman.cpp
// This program uses huffman encoding and decoding to compress strings. This progam includes functions including both the encoding and decoding of strings
// along with the construction of the huffman tree.
//
//  Author: Jonathan Hu
//  CU ID: johu5262
//  GitHub Username: jjjohnywaffles
//  Hours to complete lab: 8 Hours
//


#include "Huffman.h"

// constructor, initialize class variables and pointers here if need.
Huffman::Huffman(){
  // your code here
}

//deconstructor,
Huffman::~Huffman(){
}

shared_ptr<freq_info> Huffman::CreateLeaf(char symbol, int count) {
    auto leaf = make_shared<freq_info>();
    leaf->symbol = symbol;
    leaf->count = count;
    leaf->left = nullptr;
    leaf->right = nullptr;
    leaf->is_leaf = true;
    return leaf;
}

shared_ptr<freq_info> Huffman::CombineNodes(shared_ptr<freq_info> left, shared_ptr<freq_info> right) {
    auto node = make_shared<freq_info>();
    node->symbol = '\0';
    node->count = left->count + right->count;
    node->left = left;
    node->right = right;
    node->is_leaf = false;
    return node;
}

void Huffman::IncrementLookup(map<char, int>& lookup, char symbol) {
    //check if symbol is already in the map
    if (lookup.count(symbol) == 0) {
        //if not, add a new entry with value 1
        lookup[symbol] = 1;
    } else {
    //otherwise, increment the count associated with the symbol
        lookup[symbol]++;
    }
}

void Huffman::LoadQueue(const map<char, int>& lookup, tree_queue& q) {
    //iterate through the lookup table
    for (auto iter = lookup.begin(); iter != lookup.end(); iter++) {
        //create a new freq_info object with the symbol and count
        shared_ptr<freq_info> node = CreateLeaf(iter->first, iter->second);
        //push the node into the priority queue
        q.push(node);
    }
}
shared_ptr<freq_info> Huffman::BuildTree(tree_queue& q) {
    //continue removing the two nodes with smallest count, merging them into a parent node until the queue only has the root node left.
    while (q.size() > 1) {
        shared_ptr<freq_info> left = q.top();
        q.pop();
        shared_ptr<freq_info> right = q.top();
        q.pop();
        shared_ptr<freq_info> parent = CombineNodes(left, right);
        q.push(parent);
    }
    return q.top();
}

map<char, string> Huffman::BuildEncodingTable(shared_ptr<freq_info> root) {
    map<char, string> encoding_table;
    string code;
    BuildEncodingTableHelper(root, encoding_table, code);
    return encoding_table;
}


void Huffman::BuildEncodingTableHelper(shared_ptr<freq_info> node, map<char, string>& encoding_table, string& code) {
    if (node->is_leaf) {
        encoding_table[node->symbol] = code;
        return;
    }
    code += LEFT_CHAR;
    BuildEncodingTableHelper(node->left, encoding_table, code);
    //remove the last character from the code string
    code.pop_back(); 
    code += RIGHT_CHAR;
    BuildEncodingTableHelper(node->right, encoding_table, code);
    //remove the last character from the code string
    code.pop_back(); 
}

string Huffman::Encode(map<char, string> enc_table, string input) {
    string encoded = "";
    for (char c : input) {
        encoded += enc_table[c];
    }
    return encoded;
}

string Huffman::Decode(shared_ptr<freq_info> root, string input) {
    string decoded = "";
    shared_ptr<freq_info> curr_node = root;
    for (char c : input) {
        if (c == LEFT_CHAR[0]) {
            curr_node = curr_node->left;
        } else if (c == RIGHT_CHAR[0]) {
            curr_node = curr_node->right;
        } else {
            throw runtime_error("Invalid character in input");
        }
        if (curr_node->is_leaf) {
            decoded += curr_node->symbol;
            curr_node = root;
        }
    }
    if (curr_node != root) {
        throw runtime_error("Invalid input last character incomplete.");
    }
    return decoded;
}