//  BST.cpp
//      This datastructure is a Binary Search Tree which holds keys in order where nodes on the left side of a node are always less than the root and the nodes 
//      on the right being larger than the root.This program implements a BST and has functions that are able to edit and read the BST datastructure.
//
//  Author: Jonathan Hu
//  CU ID: johu5262
//  GitHub Username: jjjohnywaffles
//  Hours to complete lab: 18 Hours ~
//

#include "BST.h"

// constructor, initialize class variables and pointers here if need.
BST::BST(){
    root_ptr_ = nullptr;
}

//destructor,
BST::~BST(){
  // As we are using shared_ptr, we don't need to manually free the memory
}

shared_ptr<bst_node> BST::InitNode(int data){
    shared_ptr<bst_node> ret = make_shared<bst_node>();
    ret->data = data;
    ret->left = nullptr;
    ret->right = nullptr;
    return ret;
}

void BST::Insert(shared_ptr<bst_node> new_node){
    if (root_ptr_ == nullptr) {
    root_ptr_ = new_node;
    } else {
    shared_ptr<bst_node> current = root_ptr_;
    while (true) {
        if (new_node->data < current->data) {
            if (current->left == nullptr) {
                current->left = new_node;
                break;
            } else {
                  current = current->left;
                }
            } else {
                if (current->right == nullptr) {
                    current->right = new_node;
                    break;
            } else {
                current = current->right;
                }
            }
        }
    }
}

void BST::InsertData(int data){
    shared_ptr<bst_node> new_node = InitNode(data);
    Insert(new_node);
}

void BST::Remove(int data) {
    shared_ptr<bst_node> parent_node = nullptr;
    shared_ptr<bst_node> curr_node = root_ptr_;
  
    // Search for the node to remove
    while (curr_node != nullptr && curr_node->data != data) {
        parent_node = curr_node;
        if (data < curr_node->data) {
            curr_node = curr_node->left;
        } else {
        curr_node = curr_node->right;
        }
      }
  
    // If node to remove is not found, return
    if (curr_node == nullptr) {
        return;
        }

    // If node has two children
    if (curr_node->left != nullptr && curr_node->right != nullptr) {
    // Find the minimum value in the right subtree
        shared_ptr<bst_node> min_node = curr_node->right;
        parent_node = curr_node;
        while (min_node->left != nullptr) {
            parent_node = min_node;
            min_node = min_node->left;
        }

    // Replace node to remove with the minimum node in the right subtree
    curr_node->data = min_node->data;
    curr_node = min_node;
    }

// If node to remove has no left child
    if (curr_node->left == nullptr) {
        if (parent_node == nullptr) {
            root_ptr_ = curr_node->right;
        } else if (parent_node->left == curr_node) {
            parent_node->left = curr_node->right;
        } else {
            parent_node->right = curr_node->right;
        }
    }

// If node to remove has no right child
    else if (curr_node->right == nullptr) {
        if (parent_node == nullptr) {
            root_ptr_ = curr_node->left;
        } else if (parent_node->left == curr_node) {
            parent_node->left = curr_node->left;
        } else {
            parent_node->right = curr_node->left;
        }
    }
}

bool BST::Contains(shared_ptr<bst_node> subt, int data) {
    if (subt == nullptr) {
        return false;
        }
    if (subt->data == data) {
        return true;
        }
    if (data < subt->data) {
        return Contains(subt->left, data);
    } else {
        return Contains(subt->right, data);
    }
}

shared_ptr<bst_node> BST::GetNode(shared_ptr<bst_node> subt, int data) {
    if (subt == nullptr) {
        return nullptr;
        }
    if (subt->data == data) {
        return subt;
        }
    if (data < subt->data) {
        return GetNode(subt->left, data);
    } else {
        return GetNode(subt->right, data);
    }
    return shared_ptr<bst_node>(NULL);
}

int BST::Size(shared_ptr<bst_node> subt) {
    if (subt == nullptr) {
        return 0;
        }
    return 1 + Size(subt->left) + Size(subt->right);
}

void BST::ToVector(shared_ptr<bst_node> subt, vector<int>& vec){
    if (subt != nullptr) {
        ToVector(subt->left, vec);
        vec.push_back(subt->data);
        ToVector(subt->right, vec);
    }
}

// This function is implemented for you
// Returns the root pointer
shared_ptr<bst_node> BST::GetRoot(){
  return root_ptr_;
}

// This function is implemented for you
// sets a given pointer as the top pointer
void BST::SetRoot(shared_ptr<bst_node> root_ptr){
  root_ptr_ = root_ptr;
}
