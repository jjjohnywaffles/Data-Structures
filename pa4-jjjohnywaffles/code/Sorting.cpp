//  Sorting.cpp
//      This program utilizes different sorting algorithms on a vector data structure. The functions implemented include quicksort, bubble sort and merge sort.
//      An additional mystery sort function has been implemented which is selection sort. The details of how selection sort is implemented is commented above the //function itself
//
//  Author: Jonathan Hu
//  CU ID: johu5262
//  GitHub Username: jjjohnywaffles
//  Hours to complete lab: 19~ Hours
//

#include "Sorting.h"

// constructor, initialize class variables and pointers here if you need.
Sorting::Sorting() {
    // constructor code here
}

Sorting::~Sorting() {
    // destructor code here
}

//Quicksort function
void Sorting::quicksort(vector<int>& data, int low_idx, int high_idx) {
    if (low_idx < high_idx) {
        //Finds the pivot index
        int pivot = quicksort_partition(data, low_idx, high_idx);
        //Recursively call the function on both right and left subarrays
        //left subarray
        quicksort(data, low_idx, pivot - 1);
        //right subarray
        quicksort(data, pivot + 1, high_idx);
    }
}

//Quicksort Partition
int Sorting::quicksort_partition(vector<int>& data, int low_idx, int high_idx) {
    //Setting highest index as the pivot
    int pivot = data[high_idx];
    //set i to the index before the lowest index
    int i = low_idx - 1;
    for (int j = low_idx; j < high_idx; j++) {
        //Checks if current element is smaller than or equal to pivot
        if (data[j] <= pivot) {
            //Increment index of smaller element
            i++;
            //Swap current element with element at index i
            swap(data[i], data[j]);
        }
    }
    //Swap the pivot element with the element at index i+1
    swap(data[i + 1], data[high_idx]);
    //Return index of pivot element
    return i + 1;
}

//Bubble Sort
void Sorting::bubblesort(vector<int>& data) {
    int n = data.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            //Swap adjacent elements if they are in wrong order
            if (data[j] > data[j + 1]) {
                swap(data[j], data[j + 1]);
            }
        }
    }
}

//Merge sort
void Sorting::mergesort(vector<int>& data) {
    if (data.size() <= 1) {
        return;
    }
    //Split vector into 2 arrays
    int middle = data.size() / 2;
    //left array
    vector<int> left(data.begin(), data.begin() + middle);
    //Right array
    vector<int> right(data.begin() + middle, data.end());
    //Call function recursively on left and right arrays until sorted
    mergesort(left);
    mergesort(right);
    //Merge the left and right arrays
    merge(left, right, data);
}

//Merge function to merge 2 arrays
// merge is the helper function for mergesort. It returns a vector
// containing the merged contents of the two input vectors.
// you must first define an empty vector and pass to result, once this
// function returns, merged content will be in that vector (hence pass by reference).
void Sorting::merge(vector<int>& left, vector<int>& right, vector<int>& result) {
    //left vector
    int i = 0; 
    //right vector
    int j = 0;
    //result vector
    int k = 0;
    //Loop through left and right vector 
    //compares the current elements at the i-th index of the left vector and j-th index of the right vector. 
    //If the element at the i-th index of the left vector is less than or equal to the element at the j-th index of the right vector, it is added to the result vector at the k-th index
    //and i is incremented. Otherwise, the element at the j-th index of the right vector is added to the result vector at the k-th index and j is incremented. 
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            result[k] = left[i];
            i++;
        }
        else {
            result[k] = right[j];
            j++;
        }
        k++;
    }
    //Adds any remaining elements in the left vector to result vector
    while (i < left.size()) {
        result[k] = left[i];
        i++;
        k++;
    }
    //Adds any remaining elements in the right vector to result vector
    while (j < right.size()) {
        result[k] = right[j];
        j++;
        k++;
    }
}

//This mystery sort implements a selection sort
//This function implements this by iterating over the vector, finding the smallest element in the unsorted elements of the vector, and swaps the element with the first unsorted element. This will repeat until the entire vector is sorted.
void Sorting::mystery_sort(vector<int>& data) {
    //Retrieve number of elements within vector
    int n = data.size(); 
    for (int i = 0; i < n - 1; i++) {
        //iterate through vector until the element before the last
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            //iterate through vector to find minimum
            if (data[j] < data[min_idx]) {
                //Update the index of the minimum element
                min_idx = j;
            }
        }
        //Swap minimum element with the first element in the unsorted list
        //Only swap if the minimum element is not already in its correct position
        if (min_idx != i) { 
            swap(data[i], data[min_idx]);
        }
    }
}