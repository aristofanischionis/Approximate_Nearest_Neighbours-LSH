// Find sum of Manhattan 
// distances between all the pairs of 
// given points 
#include <algorithm>
using namespace std;
// Return the sum of distance of one axis.
unsigned int distanceSum(unsigned int* arr, uint64_t n) { 
    sort(arr, arr + n); 
    // For each point, finding the distance. 
    int res = 0, sum = 0; 
    for (int i = 0; i < n; i++) { 
        res += (arr[i] * i - sum); 
        sum += arr[i]; 
    }
    return res; 
} 
  
unsigned int manhattanDistance(unsigned int* x, unsigned int* y, uint64_t n) {
    return distanceSum(x, n) + distanceSum(y, n);
}