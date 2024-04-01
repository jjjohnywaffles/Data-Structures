//  LinkedList.cpp
//      This program implements a linked list data structure. This program utilizes functions that allow the creation, deletion, insertion and       
//      traversal of nodes within a linked list. 
//
//  Author: Jonathan Hu
//  CU ID: johu5262
//  GitHub Username: jjjohnywaffles
//  Hours to complete lab: 9 Hours
//

#include "LinkedList.h"

// constructor, initialize class variables and pointers here if need.
// Initially set top pointer to a null shared_ptr of node
LinkedList::LinkedList(){
    //setting top pointer to null
    top_ptr_ = nullptr;
}

//deconstructor, if you are using shared_pointers you don't need to keep track of
// freeing memory and you can leave this blank
LinkedList::~LinkedList(){
}

// init_node creates a new node structure from heap memory. It points
// to NULL and holds the provided integer. The function returns a
// pointer to that new node.
shared_ptr<node> LinkedList::InitNode(int data){
    //creating new node
    shared_ptr<node> init(new node);
    //node holding provided integer
    init->data = data;
    //points to null
    init->next = nullptr;
    return init;
}

// report creates a space-separated string representing the contents
// of the list, in the same order they are found beginning from the
// top of the list. return that string object.  For example, this
// might return "" (the empty string) if the list is empty, or it
// might return "1 7 3 " (note the space at the end).
string LinkedList::Report(){
    //initialize empty string
    string str;
    //setting current node to head
    shared_ptr<node> curr = top_ptr_;
    //while current node is not null, adds the value to the string
    while (curr != nullptr) {
        //adds data to string with space at the end
        str += to_string(curr->data) + " ";
        //goes to next node
        curr = curr->next;
      }
      return str;
}

// append_data adds a node onto the end of the list pointed to by
// top. the resulting list is one element longer, and the newly
// appended node has the given data value. consider using the 'append'
// function to help.
void LinkedList::AppendData(int data){
    Append(InitNode(data));
}

// append is the same as append_data, except we're adding a node, rather
// than a value.
void LinkedList::Append(shared_ptr<node> new_node){
    //adding new node if pointer is null
    if (top_ptr_ == nullptr) {
        top_ptr_ = new_node;
        return;
    }

    shared_ptr<node> curr = top_ptr_;
    //while the next node is not null, traverse to next node
    while (curr->next != nullptr) {
        //traverse to next node
        curr = curr->next;
    }
    //if next node is null, create new node
    curr->next = new_node;
}

// insert_data inserts a new node that contains the given data value,
// such that the new node occupies the offset indicated. Any nodes
// that were already in the list at that offset and beyond are shifted
// down by one. For example if the list contains 23, 74, 93, and we
// insert 42 at index 1, the resulting list should be 23, 42, 74, 93.
//
// If an offset is beyond the end of the list, this function should
// have no effect.
//
// Inserting at the end of the list should have the same effect as
// appending.
void LinkedList::InsertData(int offset, int data){
    //call insert function, the difference being we are inserting the data inside the node
    //rather than the node itself. This is why InitNode(data)is called rather than just the node
    Insert(offset, InitNode(data));
}

// insert is the same as insert_data, except we're inserting a node,
// rather than a value.
void LinkedList::Insert(int offset, shared_ptr<node> new_node){
    //in the case offset is 0 thus being the head of the linked list
    if (offset == 0) {
        //setting top_ptr as the newnodes next pointer
        new_node->next = top_ptr_;
        top_ptr_ = new_node;
        return;
    }
    shared_ptr<node> curr = top_ptr_;
        //go to node to insert after
        for (int i = 0; i < offset - 1 && curr->next != nullptr; i++) {
        curr = curr->next;
    }
    //if current node is null create new node
    if (curr->next == nullptr) {
        curr->next = new_node;
        return;
    }
//The new_node pointer is assigned the value of the next pointer of the curr node. This means that the next pointer of the new node now points to the same node that the next pointer of curr was previously pointing to.

//The next pointer of curr is then updated to point to the new_node. This means that the curr node now points to the new node, and the new node   points to the node that the curr node used to point to.
    new_node->next = curr->next;
    curr->next = new_node;
}


// remove removes the node indicated by the given offset and frees its
// memory. For example if our list contains 23, 74, 93, and we remove
// offset 1, the resulting list should then contain 23, 93.
//
// If an invalid offset is given (e.g. negative or beyond the end of
// the list), this function has no effect.
void LinkedList::Remove(int offset){
    //checks if offset = 0 and sets top_ptr to next node
    if (offset == 0) {
        top_ptr_ = top_ptr_->next;
        return;
    }
    
    shared_ptr<node> curr = top_ptr_;
    //for loops iterate through linked list
    for (int i = 0; i < offset - 1 && curr->next != nullptr; i++) {
        curr = curr->next;
    }
    //checks if beyond the list
    if (curr->next == nullptr) {
        return;
    }
    //sets next node to the one after next removing the node
    curr->next = curr->next->next;
}

// size returns the number of nodes in the linked list reachable by
// head before (but not including) the terminating NULL link. E.g., an
// empty list has size 0, a list with one item has size 1, etc.
int LinkedList::Size(){
    //counter
    int i = 0;
    //setting current node to head
    shared_ptr<node> curr = top_ptr_;
    //while node is not null
    while (curr != nullptr) {
        i++;
        //go to next node
        curr = curr->next;
    }
    //returns list size
    return i;
}

// contains returns true if the linked list pointed to by head
// contains a node with the specified value, false otherwise.
bool LinkedList::Contains(int data){
    shared_ptr<node> curr = top_ptr_;
    //iterate until node is null
    while (curr != nullptr) {
        //if node value is = to specified data
        if (curr->data == data){
            return true;
        }
        //go to next node if value is not found
        curr = curr->next;
    }
    //return false if value is not found in the linked list
    return false;
}

// This function is implemented for you
// It returns the top pointer
shared_ptr<node> LinkedList::GetTop(){
    return top_ptr_;
}

// This function is implemented for you
// It sets a given pointer as the top pointer
void LinkedList::SetTop(shared_ptr<node> top_ptr){
    top_ptr_ = top_ptr;
}
