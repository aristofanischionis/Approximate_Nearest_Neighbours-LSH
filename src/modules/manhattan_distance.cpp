// Find sum of Manhattan 
// distances between all the pairs of 
// given points 
#include <iostream>
#include <stdexcept>
using namespace std; 

// Return the sum of distance of one axis. 
int distancesum(int arr[], int n) { 
    sort(arr, arr + n); 
    // For each point, finding the distance. 
    int res = 0, sum = 0; 
    for (int i = 0; i < n; i++) { 
        res += (arr[i] * i - sum); 
        sum += arr[i]; 
    }
    return res; 
} 
  
int manhattan_distance(int x[], size_t n, int y[], size_t n1) {
    // Calculate the number of items in the array
    
    // if the two arrays don't have same number of items return Error
    if(n != n1) {
        throw invalid_argument("The two arrays don't have the same number of items.");
    } else return distancesum(x, n) + distancesum(y, n); 
}