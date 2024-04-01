// Edge.cpp
// This program creates edges for the graph.
//
//  Author: Jonathan Hu
//  CU ID: johu5262
//  GitHub Username: jjjohnywaffles
//  Hours to complete lab: 20 Hours
//

#include "Edge.h"

Edge::Edge(shared_ptr<Node> n1, shared_ptr<Node> n2) {
  a = n1;
  b = n2;
  type = UNDISCOVERED_EDGE; // default edge type
}

Edge::~Edge() {
  // Destructor is empty since we are using smart pointers
}

shared_ptr<Node> Edge::getStart() {
  return a;
}

shared_ptr<Node> Edge::getEnd() {
  return b;
}

int Edge::getType() {
  return type;
}

void Edge::setType(int edge_type) {
  type = edge_type;
}

ostream &operator << (std::ostream& out, Edge edge) {
  out << *edge.a << " -- " << *edge.b;
  return out;
}