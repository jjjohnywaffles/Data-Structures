// Node.cpp
// This program creates nodes for the graph.
//
//  Author: Jonathan Hu
//  CU ID: johu5262
//  GitHub Username: jjjohnywaffles
//  Hours to complete lab: 20 Hours
//

#include "Node.h"

Node::Node(string s) {
  // DONE FOR YOU
  data = s;
}

Node::~Node() {
  // "DONE" FOR YOU
  //
  // This is equivalent to the default destructor the compiler will
  // generate for you. As a rule of thumb, you only need to `delete`
  // member variables that were created with `new` inside this
  // class. So, you don't need to do anything here. It could have been
  // left out of the header/impl file entirely.
}

string Node::getData() {
  // DONE FOR YOU
  return data;
}

void Node::setRank(int r) {
  // DONE FOR YOU
  rank = r;
}

int Node::getRank() {
    return rank;
}

int Node::getColor() {
    return color;
}

void Node::setDiscovery(int time) {
    discovery_time = time;
}

void Node::setFinish(int time) {
    completion_time = time;
}
void Node::clear() {
    color = WHITE;
    discovery_time = -1;
    completion_time = -1;
    rank = -1;
    predecessor = NULL;
}

void Node::setColor(int search_color, int time) {
    if (search_color == WHITE) {
        clear();
    } else if (search_color == GRAY) {
        color = GRAY;
        discovery_time = time;
    } else { // BLACK
        color = BLACK;
        completion_time = time;
    }
}

void Node::getDiscoveryInformation(int& thecolor, int& disco_time,
    int& finish_time, int& bfs_rank) {
    thecolor = color;
    disco_time = discovery_time;
    finish_time = completion_time;
    bfs_rank = rank;
}

bool Node::isAncestor(shared_ptr<Node> other) {
    shared_ptr<Node> cur = predecessor;
    while (cur != nullptr) {
        if (cur == other) {
            return true;
        }
        cur = cur->predecessor;
    }
    return false;
}

void Node::setPredecessor(shared_ptr<Node> other) {
    predecessor = other;
}
// overloading operator << lets you put a Node object into an output
// stream.
ostream &operator << (std::ostream& out, Node node) {
  // DONE FOR YOU
  out << node.data;
  return out;
}
