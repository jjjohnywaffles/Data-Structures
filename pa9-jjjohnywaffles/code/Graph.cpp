// Graph.cpp
// This program creates a graph and allows for depth-first search or breadth-first search.
//
//  Author: Jonathan Hu
//  CU ID: johu5262
//  GitHub Username: jjjohnywaffles
//  Hours to complete lab: 20 Hours
//

#include "Graph.h"

#include <iostream>
#include <sstream>

using namespace std;

// fwd declarations
string make_dot(Graph* g);
string what(int& v);

Graph::Graph() {
  // DONE FOR YOU
  directed = false; // graphs are undirected by default
}

Graph::~Graph() {
  // "DONE" FOR YOU
  // no implementation needed
}

vector<shared_ptr<Node>> Graph::getNodes() {
  // DONE FOR YOU
  return nodes;
}

vector<shared_ptr<Edge>> Graph::getEdges() {
  // DONE FOR YOU
  return edges;
}

int Graph::getClock() {
  // DONE FOR YOU
  return clock;
}

void Graph::addNode(shared_ptr<Node> n) {
  // DONE FOR YOU
  nodes.push_back(n);
}

void Graph::addEdge(shared_ptr<Edge> e) {
  // DONE FOR YOU
  edges.push_back(e);
}
 
void Graph::removeNode(shared_ptr<Node> n) {
  // DONE FOR YOU
  for (vector<shared_ptr<Node>>::iterator it = nodes.begin(); it != nodes.end(); it++) {
    if (n == *it) {
      nodes.erase(it);
      break;
    }
  }
}
 
void Graph::removeEdge(shared_ptr<Edge> e) {
  // DONE FOR YOU
  for (vector<shared_ptr<Edge>>::iterator it = edges.begin();
       it != edges.end(); 
       it++) {
    if (e == *it) {
      edges.erase(it);
      break;
    }
  }
}

void Graph::setDirected(bool val) {
  // DONE FOR YOU
  directed = val;
}

bool Graph::isDirected() {
  // DONE FOR YOU
  return directed;
}

set<shared_ptr<Edge>> Graph::getAdjacentEdges(shared_ptr<Node> n) {
  // DONE FOR YOU
  set<shared_ptr<Edge>> ret;
  for (vector<shared_ptr<Edge>>::iterator it = edges.begin(); it != edges.end(); it++) {
    shared_ptr<Edge> edge = *it;
    if (edge->getStart() == n) {
      ret.insert(edge);
    }
    if (!directed && (edge->getEnd() == n)) {
      ret.insert(edge);
    }
  }
  return ret;
}

void Graph::clear() {
    for (auto node : nodes) {
        node->setColor(WHITE, -1);
        node->setPredecessor(nullptr);
        node->setDiscovery(-1);
        node->setFinish(-1);
        node->setRank(-1);
  }

    // Reset all edges to type UNDISCOVERED_EDGE
    for (auto e : edges) {
        e->setType(UNDISCOVERED_EDGE);
    }

    // Reset the graph clock to 0
    clock = 0;
}

void Graph::tick(string message) {
  // DONE FOR YOU
  //
  // optional debugging function, disabled with if(false) to prevent
  // unused var warning. Change this however you want.
  //
  // recommended use: call it just after incrementing the clock.
  if (false) {
    cout << "// " << message << endl << make_dot(this) << endl;
  }
}

// Depth-first search
void Graph::dfs(shared_ptr<Node> start) {
    // Initialize all nodes to the color white and set their predecessor to null.
    for (auto node : nodes) {
        node->setColor(WHITE, -1);
        node->setPredecessor(nullptr);
    }
    // Set the clock to 0.
    clock = 0;
    // Start the depth-first search from the given node.
    dfs_visit(start);
}

// DFS Helper
void Graph::dfs_visit(shared_ptr<Node> u) {
    // Increment the clock and set the color of the current node to gray.
    clock++;
    u->setColor(GRAY, clock);

    // Get all the adjacent edges of the current node.
    set<shared_ptr<Edge>> adjEdges = getAdjacentEdges(u);

    // For each adjacent edge, visit the node at the other end of the edge.
    for (auto edge : adjEdges) {
        shared_ptr<Node> v = edge->getEnd();
        // If the other end of the edge is the same as the current node, get the start of the edge instead.
        if (v == u) {
            v = edge->getStart();
        }
        // If the node is white, set its predecessor, mark the edge as a tree edge, and visit the node.
        if (v->getColor() == WHITE) {
            v->setPredecessor(u); // set the predecessor of v to u
            edge->setType(TREE_EDGE); // mark the edge as a tree edge
            dfs_visit(v); // recursively visit node v
        }
        // If the node is gray, mark the edge as a back edge.
        else if (v->getColor() == GRAY) {
            edge->setType(BACK_EDGE); // mark the edge as a back edge
        }
        // If the node is black, mark the edge as either a forward or cross edge.
        else {
            if (u->isAncestor(v)) { // if u is an ancestor of v
                edge->setType(FORWARD_EDGE); // mark the edge as a forward edge
            } else {
                edge->setType(CROSS_EDGE); // mark the edge as a cross edge
            }
        }
    }
    // Increment the clock after visiting all adjacent nodes.
    clock++;
}
//breadth first search
void Graph::bfs(shared_ptr<Node> start) {
    queue<shared_ptr<Node>> q;

    // Reset all node ranks and colors
    for (auto &n : nodes) {
        n->setRank(-1);
        n->setColor(WHITE, -1);
    }

    // Set start node rank and color
    start->setRank(0);
    start->setColor(GRAY, 0);

    // Add start node to the queue
    q.push(start);

    while (!q.empty()) {
        // Get the next node from the queue
        auto n = q.front();
        q.pop();

        // Get all adjacent edges of the node
        auto adjEdges = getAdjacentEdges(n);

        // Loop over adjacent edges
        for (auto &e : adjEdges) {
            auto m = e->getEnd() == n ? e->getStart() : e->getEnd();
            // If the adjacent node is white, set its rank, color, predecessor, and add it to the queue
            if (m->getColor() == WHITE) {
                m->setRank(n->getRank() + 1); // set the rank of the adjacent node as the rank of the current node + 1
                m->setColor(GRAY, getClock()); // set the color of the adjacent node as gray and the clock as the current time
                m->setPredecessor(n); // set the predecessor of the adjacent node as the current node
                q.push(m); // add the adjacent node to the queue
            }
        }

        // Set the color of the current node to black
        n->setColor(BLACK, getClock());
    }
}
// bfs that takes start node and the target node.
void Graph::bfs(shared_ptr<Node> start, shared_ptr<Node> target) {
    // Create a queue to store the nodes to visit.
    queue<shared_ptr<Node>> q;

    // Reset all node ranks and colors.
    // Set all nodes' rank to -1 and color to WHITE.
    for (auto &n : nodes) {
        n->setRank(-1);
        n->setColor(WHITE, -1);
    }

    // Set start node rank to 0 and color to GRAY.
    start->setRank(0);
    start->setColor(GRAY, 0);

    // Add start node to the queue.
    q.push(start);

    // Loop through the queue until it is empty.
    while (!q.empty()) {
        // Get the next node from the queue.
        auto n = q.front();
        q.pop();

        // If target node is reached, set its color to black and return.
        if (n == target) {
            target->setColor(BLACK, target->getRank());
            return;
        }
        // Get all adjacent edges of the node.
        auto adjEdges = getAdjacentEdges(n);

        // Loop over adjacent edges.
        for (auto &e : adjEdges) {
            auto m = e->getEnd() == n ? e->getStart() : e->getEnd();
            // If the adjacent node is white, set its rank, color, and add it to the queue.
            if (m->getColor() == WHITE) {
                m->setRank(n->getRank() + 1);
                m->setColor(GRAY, m->getRank());
                q.push(m);
            }
        }
        // Set the color of the current node to black.
        n->setColor(BLACK, n->getRank());
    }
    // If target node was not reached, set its color and rank to white and -1, respectively.
    target->setColor(WHITE, -1);
    target->setRank(-1);
}

// overloading operator << lets you put a Graph object into an output
// stream.
ostream &operator << (ostream& out, Graph graph) {
  // DONE FOR YOU
  out << graph.nodes.size() << " Nodes:" << endl;
  out << "[";
  for (vector<shared_ptr<Node>>::iterator it = graph.nodes.begin(); it != graph.nodes.end(); it++) {
    shared_ptr<Node> n = *it;
    out << *n << ", ";
  }
  out << "]" << endl;
  out << graph.edges.size() << " Edges:" << endl;
  out << "[";
  for (vector<shared_ptr<Edge>>::iterator it = graph.edges.begin(); it != graph.edges.end(); it++) {
    shared_ptr<Edge> e = *it;
    out << *e << ", ";
  }
  out << "]";
  return out;
}

// what is a helper function that turns a constant (e.g. WHITE or
// FORWARD_EDGE) into a string for debugging goodness. 
string what(int& v) {
  // DONE FOR YOU
  string ret = "Unknown";
  if (v == WHITE) {
    ret = "white";
  } else if (v == GRAY) {
    ret = "gray";
  } else if (v == BLACK) {
    ret = "black";
  } else if (v == UNDISCOVERED_EDGE) {
    ret = "undiscovered";
  } else if (v == TREE_EDGE) {
    ret = "tree";
  } else if (v == BACK_EDGE) {
    ret = "back";
  } else if (v == FORWARD_EDGE) {
    ret = "forward";
  } else if (v == CROSS_EDGE) {
    ret = "cross";
  }
  return ret;
}

// make_dot generates a dotfile string for viewing your graph. Have
// tick() print out the results of this function, and then use
// http://www.webgraphviz.com/ (or get a copy of GraphViz) to view the
// result. If you're stuck, this can help you get un-stuck.
string make_dot(Graph* g) {
  // DONE FOR YOU
  stringstream ss;
  vector<shared_ptr<Node>> nodes = g->getNodes();
  vector<shared_ptr<Edge>> edges = g->getEdges();
  string gt = "graph";
  string con = "--";
  if (g->isDirected()) {
    con = "->";
    gt = "digraph";
  }
  ss << gt << " homework {" << endl;
  int c, dt, ft, r;
  string textColor = "black";
  for (auto it=nodes.begin(); it != nodes.end(); ++it) {
    shared_ptr<Node> n = *it;
    n->getDiscoveryInformation(c, dt, ft, r);
    if (c == BLACK) {
      textColor = "white";
    } else {
      textColor = "black";
    }
    ss << "  " << n->getData() << " [ style=\"filled\" fontcolor=\"" << textColor << "\" fillcolor=\"" << what(c) << "\"" << " ]" << endl;
  }
  
  string edgeColor = "black";
  for (auto it=edges.begin(); it != edges.end(); ++it) {
    shared_ptr<Edge> e = *it;
    if (e->getType() == TREE_EDGE) {
      edgeColor = "black";
    } else if (e->getType() == FORWARD_EDGE) {
      edgeColor = "purple";
    } else if (e->getType() == BACK_EDGE) {
      edgeColor = "blue";
    } else if (e->getType() == CROSS_EDGE) {
      edgeColor = "green";
    } else {
      edgeColor = "gray";
    }
    ss << "  " << e->getStart()->getData() << con << e->getEnd()->getData() << " [color=\"" << edgeColor << "\"]" << endl;
  }
  ss << "}" << endl;
  return ss.str();
}