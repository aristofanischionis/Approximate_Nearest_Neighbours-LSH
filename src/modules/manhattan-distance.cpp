#include <algorithm>
#include <stdint.h>
using namespace std;

unsigned int manhattanDistance(unsigned int* x, unsigned int* y, uint64_t n) {
	unsigned int sum =0;
    for (uint64_t i = 0; i < n; i++) {
        sum += abs(static_cast<int>(x[i]) - static_cast<int>(y[i])); 
    }
    return sum;
}