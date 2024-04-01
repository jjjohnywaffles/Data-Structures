//BTree.cpp
//This program interacts with a BTree data structure by utilizing functions including insert, remove and find. This program also runs into a segmentation fault
//that I cannot figure out why or where. Hopefully the code makes sense with the comments which explain what the program is trying to do. 
//
// Author: Jonathan Hu
//  CU ID: johu5262
//  GitHub Username: jjjohnywaffles
//  Hours to complete lab: 20~ Hours
//


#include "BTree.h"

// constructor, initialize class variables and pointers here if need.
BTree::BTree(){
  // initialize variables as needed
}

// deconstructor, if you are using shared_pointers you don't need to keep track of
// freeing memory and you can leave this blank
BTree::~BTree(){
}

void BTree::insert(shared_ptr<btree>& root, int key) {

    if (root == nullptr) {
        root = make_shared<btree>();
        root->num_keys = 1;
        root->keys[0] = key;
        root->is_leaf = true;
        return;
    }
    //checks if full
    if (root->num_keys == 2*BTREE_ORDER - 1) {
        //split the root node
        shared_ptr<btree> new_root = make_shared<btree>();
        new_root->is_leaf = false;
        new_root->num_keys = 0;
        new_root->children[0] = root;

        split_child(new_root, 0, root);

        //insert the key into child
        int i = 0;
        if (new_root->keys[0] < key) i++;
        insert_nonfull(new_root->children[i], key);

        root = new_root;
    } else {
        insert_nonfull(root, key);
    }
}
//insert into nonfull tree
void BTree::insert_nonfull(shared_ptr<btree>& node, int key) {
    int i = node->num_keys - 1;
    if (node->is_leaf) {
    // Shift keys greater than key to the right
    while (i >= 0 && node->keys[i] > key) {
        node->keys[i+1] = node->keys[i];
        i--;
    }

    //insert the key to correct position
    node->keys[i+1] = key;
    node->num_keys++;
    } else {
        //find child that contains the key
        while (i >= 0 && node->keys[i] > key) {
            i--;
        }

        i++;

    //if the child is full, split before inserting the key
    if (node->children[i]->num_keys == 2*BTREE_ORDER - 1) {
        split_child(node, i, node->children[i]);
        if (node->keys[i] < key) i++;
        }
    insert_nonfull(node->children[i], key);
    } 
}

void BTree::split_child(shared_ptr<btree>& parent, int index, shared_ptr<btree>& child) {
    //create a new node to store the right half of the keys
    shared_ptr<btree> new_node = make_shared<btree>();
    new_node->is_leaf = child->is_leaf;
    new_node->num_keys = BTREE_ORDER - 1;

    //copy the right half of the keys and children from the child node to the new node
    for (int i = 0; i < BTREE_ORDER - 1; i++) {
        new_node->keys[i] = child->keys[i+BTREE_ORDER];
    }

    if (!child->is_leaf) {
        for (int i = 0; i < BTREE_ORDER; i++) {
            new_node->children[i] = child->children[i+BTREE_ORDER];
        }
    }

    child->num_keys = BTREE_ORDER - 1;

    //shift the children of the parent node to the right
    for (int i = parent->num_keys; i > index; i--) {
        parent->children[i] = parent->children[i-1];
    }

    //insert the new node as a child of the parent
    parent->children[index+1] = new_node;

    //shift the keys of the parent node to the right and insert median key
    for (int i = parent->num_keys - 1; i >= index; i--) {
        parent->keys[i+1] = parent->keys[i];
    }
    parent->keys[index] = child->keys[BTREE_ORDER-1];
    parent->num_keys++;
}
                
void BTree::remove(shared_ptr<btree> root, int key) {
    //if the tree is empty
    if (!root) {
        return;
    }
    //find the index of the key to remove
    int key_idx = -1;
    for (int i = 0; i < root->num_keys; i++) {
        if (root->keys[i] == key) {
            key_idx = i;
            break;
        }
    }
    if (key_idx != -1) {
        //key is in leaf node
        if (root->is_leaf) {
            for (int i = key_idx; i < root->num_keys - 1; i++) {
                root->keys[i] = root->keys[i+1];
            }
        root->num_keys--;
        return;
        }
        // find smallest key in right subtree
        shared_ptr<btree> successor = root->children[key_idx+1];
        while (!successor->is_leaf) {
            successor = successor->children[0];
        }
        int successor_key = successor->keys[0];
    
        //delete the successor from leaf node
        remove(successor, successor_key);
    
        //replace the key with the successor
        root->keys[key_idx] = successor_key;
        return;
    }
    //find the child that should contain the key
    int child_idx = 0;
    while (child_idx < root->num_keys && key > root->keys[child_idx]) {
        child_idx++;
    }
    shared_ptr<btree> child = root->children[child_idx];


    //if the child has too few keys, rebalance the tree
    if (child->num_keys == BTREE_ORDER/2 - 1) {
        shared_ptr<btree> left_sibling, right_sibling;
        if (child_idx > 0) {
            left_sibling = root->children[child_idx - 1];
        }
        if (child_idx < root->num_keys) {
            right_sibling = root->children[child_idx + 1];
        }
        if (left_sibling && left_sibling->num_keys > BTREE_ORDER/2 - 1) {
            //borrow from left sibling
            for (int i = child->num_keys; i > 0; i--) {
                child->keys[i] = child->keys[i-1];
            }
            if (!child->is_leaf) {
                for (int i = child->num_keys + 1; i > 0; i--) {
                    child->children[i] = child->children[i-1];
                }
                child->children[0] = left_sibling->children[left_sibling->num_keys];
            }
            child->keys[0] = root->keys[child_idx - 1];
            root->keys[child_idx - 1] = left_sibling->keys[left_sibling->num_keys - 1];
            child->num_keys++;
            left_sibling->num_keys--;
        } else if (right_sibling && right_sibling->num_keys > BTREE_ORDER/2 - 1) {
            
            //borrow from right sibling
            child->keys[child->num_keys] = root->keys[child_idx];
            if (!child->is_leaf) {
                child->children[child->num_keys + 1] = right_sibling->children[0];
            }
            root->keys[child_idx] = right_sibling->keys[0];
            for (int i = 0; i < right_sibling->num_keys - 1; i++) {
                right_sibling->keys[i] = right_sibling->keys[i+1];
            }
            if (!right_sibling->is_leaf) {
                for (int i = 0; i < right_sibling->num_keys; i++) {
                    right_sibling->children[i] = right_sibling->children[i+1];
                }
                child->children[child->num_keys + 1] = right_sibling->children[0];
            }
            child->num_keys++;
            right_sibling->num_keys--;
        } else {
            
            //merge with a sibling
            if (left_sibling) {
                //merge with left sibling
                left_sibling->keys[left_sibling->num_keys] = root->keys[child_idx - 1];
                for (int i = 0; i < child->num_keys; i++) {
                    left_sibling->keys[left_sibling->num_keys + 1 + i] = child->keys[i];
                }
                if (!child->is_leaf) {
                    for (int i = 0; i <= child->num_keys; i++) {
                        left_sibling->children[left_sibling->num_keys + 1 + i] = child->children[i];
                    }
                }
                left_sibling->num_keys += 1 + child->num_keys;
                //remove child node from root
                for (int i = child_idx - 1; i < root->num_keys - 1; i++) {
                    root->keys[i] = root->keys[i+1];
                    root->children[i+1] = root->children[i+2];
                }
                root->num_keys--;
            } else {
                //merge with right sibling
                child->keys[child->num_keys] = root->keys[child_idx];
                for (int i = 0; i < right_sibling->num_keys; i++) {
                    child->keys[child->num_keys + 1 + i] = right_sibling->keys[i];
                }
                if (!child->is_leaf) {
                    for (int i = 0; i <= right_sibling->num_keys; i++) {
                        child->children[child->num_keys + 1 + i] = right_sibling->children[i];
                    }
                }
                child->num_keys += 1 + right_sibling->num_keys;

                //remove right sibling node from root
                for (int i = child_idx; i < root->num_keys - 1; i++) {
                    root->keys[i] = root->keys[i+1];
                    root->children[i+1] = root->children[i+2];
                }
                root->num_keys--;
            }
        }
    }
    //recursively remove key from child node
    remove(child, key);
}

shared_ptr<btree> BTree::find(shared_ptr<btree> root, int key) {
    //if the root is null, return null
    if (!root) {
        return nullptr;
    }

    int i = 0;
    //searches for the first key greater than or equal to the search key
    while (i < root->num_keys && key > root->keys[i]) {
        i++;
    }

    //if the key is found at this node, return the node
    if (i < root->num_keys && key == root->keys[i]) {
        return root;
    }

    //if this is a leaf node, the key is not in the tree
    if (root->is_leaf) {
        return nullptr;
    }

    //recurse down to the child node
    return find(root->children[i], key);
}
int BTree::count_nodes(shared_ptr<btree> root){
  if (root == nullptr) {
    return 0;
  }
  int count = 1;
  if (!root->is_leaf) {
    for (int i = 0; i <= root->num_keys; i++) {
      count += count_nodes(root->children[i]);
    }
  }
  return count;
}

int BTree::count_keys(shared_ptr<btree> root){
  if (root == nullptr) {
    return 0;
  }
  int count = root->num_keys;
  if (!root->is_leaf) {
    for (int i = 0; i <= root->num_keys; i++) {
      count += count_keys(root->children[i]);
    }
  }
  return count;
}