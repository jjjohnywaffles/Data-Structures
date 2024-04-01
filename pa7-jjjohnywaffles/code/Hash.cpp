// Hash.cpp
// This program creates a hashtable and has functions implemented to interact with the hashtable. 
// For whoever ends up grading this, do you mind seeing what is poorly implemented? Whenever my implementation of SetKVP is written,
// the program always reaches a segmentation fault. Therefore I have decided to leave it out for now in order for the program to compile.
//
//  Author: Jonathan Hu
//  CU ID: johu5262
//  GitHub Username: jjjohnywaffles
//  Hours to complete lab: 18 Hours
//

#include "Hash.h"

// implemented for you - don't change this one
unsigned int DJB2(std::string key){
  unsigned int hash = 5381;
  // Leaving the debugging stuff commented out, in case you want to
  // play. It will output the hash at each incremental step so you can
  // see how it takes shape.
  //
  //  cout << "Hashing string \"" << key << "\"" << endl;
  //  cout << bitset<32>(hash) << " " << hash << endl;
  for (size_t i=0; i < key.length(); i++) {
    char c = key[i]; 
    hash = ((hash << 5) + hash) + c;
    // cout << bitset<32>(hash) << " " << hash << endl;
  }
  // cout << "Hashed string \"" << key << "\" to " << hash << endl;
  //
  // for light reading on why djb2 might not be the best
  // production-grade hash function, go to
  // http://dmytry.blogspot.com/2009/11/horrible-hashes.html
  return hash;
}

// implemented for you - don't change this one
unsigned int ModuloBucketFunc(unsigned int hashcode, unsigned int cap){
  unsigned int b = hashcode % cap;
  return b;
}

// constructor, initialize class variables and pointers here if need.
Hash::Hash(){
  // your code here
}

//deconstructor,
Hash::~Hash(){
}

shared_ptr<hash_table> Hash::InitTable(unsigned int cap) {
    //Create a new hash table object
    shared_ptr<hash_table> table(new hash_table);

    //Initialize the fields of the hash table object
    table->capacity = cap;
    table->size = 0;
    table->occupied = 0;
    table->hash_func = DJB2;
    table->bucket_func = ModuloBucketFunc;

    //Initialize the table vector to contain capacity null pointers
    table->table = shared_ptr<htable>(new htable(cap, nullptr));

    //Return hash table object
    return table;
}

shared_ptr<hash_node> Hash::InitNode(string key, unsigned int hashcode, string val) {
    shared_ptr<hash_node> node(new hash_node);
    node->deleted = false;
    node->key = key;
    node->hashcode = hashcode;
    node->value = val;
    return node;
}

bool Hash::SetKVP(shared_ptr<hash_table> tbl, std::string key, std::string value) {

    return true;
}

float Hash::Load(shared_ptr<hash_table> tbl) {
    return static_cast<float>(tbl->occupied) / static_cast<float>(tbl->capacity);
}

std::string Hash::GetVal(shared_ptr<hash_table> tbl, std::string key){
    //Get hashcode of the key
    unsigned int hashcode = tbl->hash_func(key);

    //Iterate over the nodes in the bucket, checking for a match
    for (auto node : *(tbl->table)) {
        if (node != nullptr && !node->deleted && node->hashcode == hashcode && node->key == key) {
            return node->value;
        }
    }

    //If no match was found, return an empty string
    return "";
}

bool Hash::Contains(shared_ptr<hash_table> tbl, std::string key){
    //Use the bucket function to determine which bucket to look in
    unsigned int bucket = tbl->bucket_func(tbl->hash_func(key), tbl->capacity);

    //Checking for a match in the buckets
    for (auto node : *(tbl->table.get() + bucket)) {
        if (node != nullptr && !node->deleted && node->key == key) {
            return true;
        }
    }

    //If no match was found, return false
    return false;
}

shared_ptr<hash_node> Hash::Find(shared_ptr<hash_table> tbl, std::string key) {
    //Compute the hash code for the key
    unsigned int hashcode = tbl->hash_func(key);

    //Determine the bucket index for the hash code
    unsigned int bucket_idx = tbl->bucket_func(hashcode, tbl->capacity);

    //Search for the key in the bucket
    shared_ptr<hash_node> node = tbl->table->at(bucket_idx);
    if (!node || node->deleted || node->hashcode != hashcode || node->key != key) {
        // Key was not found
        return nullptr;
    }
    return node;
}

bool Hash::Remove(shared_ptr<hash_table> tbl, std::string key){
    //check if the key is in the hash table
    shared_ptr<hash_node> node = Find(tbl, key);
    if (node == nullptr) {
        return false;
    }
    //delete the node and set its value to an empty string
    node->value = "";
    node->deleted = true;
    tbl->size--;
    return true;
}

void Hash::Resize(shared_ptr<hash_table> tbl, unsigned int new_capacity) {
}

// implemented for you - feel free to change this one if you like
void Hash::PrintTable(shared_ptr<hash_table> tbl){
  cout << "Hashtable:" << endl;
  cout << "  capacity: " << tbl->capacity << endl;
  cout << "  size:     " << tbl->size << endl;
  cout << "  occupied: " << tbl->occupied << endl;
  cout << "  load:     " << Load(tbl) << endl;
  if (tbl->capacity < 130) {
    for (unsigned int i=0; i < tbl->capacity; i++) {
      cout << "[" << i << "]    ";
      if (!tbl->table->at(i)) {
        cout << "<empty>" << endl;
      } else if (tbl->table->at(i)->deleted) {
        cout << "<deleted>" << endl;
      } else {
        cout << "\"" << tbl->table->at(i)->key << "\" = \"" << tbl->table->at(i)->value << "\"" << endl;
      }
    }
  } else {
    cout << "    <hashtable too big to print out>" << endl;
  }
}

