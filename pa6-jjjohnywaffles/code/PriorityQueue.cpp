// PriorityQueue.cpp
// This program interacts with a Priority Queue by utilizing functions including insert, remove and peek. 
//
//  Author: Jonathan Hu
//  CU ID: johu5262
//  GitHub Username: jjjohnywaffles
//  Hours to complete lab: 5 Hours
//


#include "PriorityQueue.h"
#include <algorithm>

PriorityQueue::PriorityQueue(){
    // YOUR CODE HERE
}

PriorityQueue::~PriorityQueue(){
    // You don't need to add anything here
}

shared_ptr<pq> PriorityQueue::InitPriorityQueue(){
    return shared_ptr<pq>(new pq);
}
void PriorityQueue::Insert(shared_ptr<pq> queue, string text, float priority){
    if (!queue) {
        //if queue is null or uninitialized.
        return;
    }
    //insert based on priority
    queue->q.emplace_back(text, priority);
    sort(queue->q.begin(), queue->q.end(), [](pair<string, float> a, pair<string, float> b) -> bool {
        return a.second > b.second;
    });
}
string PriorityQueue::Remove(shared_ptr<pq> queue){
    if (queue->q.empty()) {
        //if empty
        return "";
    }
    //remove at position
    string result = queue->q.front().first;
    queue->q.erase(queue->q.begin());
    return result;
}

string PriorityQueue::Peek(shared_ptr<pq> queue){
    if (queue->q.empty()) {
        //if empty, return empty string
        return "";
    }
    //returns the first element in queue
    return queue->q.front().first;
}