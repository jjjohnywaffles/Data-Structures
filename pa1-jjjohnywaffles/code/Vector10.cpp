//  Vector10.cpp
//      <TODO: Describe the data structure here >
//
//  Author: Jonathan Hu
//  CU ID: johu5262
//  GitHub Username: jjjohnywaffles
//  Hours to complete lab: <TODO: place the number of hours needed to complete lab, do not count time reading or watching videos>
//

#include "Vector10.h"

Vector10::Vector10(){
    size = 0;
    for (int i = 0; i < 10; i++) {
        arr[i] = 0;
        }
    }
Vector10::~Vector10(){
    // You don't need to add anything here
}

// Implement this function first, since all tests use it.
// get an index return the value of array at that index
int Vector10::ValueAt(int index){
    if (index >= 0 && index < 10) {
        return arr[index];
        } else {
            return 0;
        }
    }
// Implement this function second, since most tests use it.
// puts value in the last empty spot of array (back), function returns false if
// array is already full and true if push was successful
// data in array is always left alligned. check class video for details
bool Vector10::PushBack(int value){
    if(size == 10){
        return false;
        }
    arr[size] = value;
    size++;
    return true;
}

// this member function returns number of empty spaces left in the array
int Vector10::CountEmpty(){
    int count = 0;
    for (int i = 0; i < 10; i++) {
        if (arr[i] == 0) {
            count++;
            }
        }
        return count;
    }
// this function searches the value in the array and returns if value exists
// and returns false otherwise
bool Vector10::Search(int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}
// this function removes a value from array. (removal process includes 
// if requested index is not in the range of valid data locations then function returns a false otherwise 
// it removes the value and returns true.
// check class video for details.
bool Vector10::Remove(int index) {
    if (index < 0 || index >= size){
        return false;
    }
    for (int i = index; i < 10; i++){
        arr[i] = arr[i + 1];
    }
    size--;
    return true;
}