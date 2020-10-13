// Find sum of Manhattan 
// distances between all the pairs of 
// given points 
#include <iostream>
#include <stdexcept>
#include <algorithm>
using namespace std; 

// Return the sum of distance of one axis. 
int distanceSum(int arr[], int n) { 
    sort(arr, arr + n); 
    // For each point, finding the distance. 
    int res = 0, sum = 0; 
    for (int i = 0; i < n; i++) { 
        res += (arr[i] * i - sum); 
        sum += arr[i]; 
    }
    return res; 
} 
  
int manhattanDistance(int x[], size_t n, int y[], size_t n1) {
    // if the two arrays don't have same number of items return Error
    if(n != n1) {
        throw invalid_argument("The two arrays don't have the same number of items.");
    } else return distanceSum(x, n) + distanceSum(y, n); 
}