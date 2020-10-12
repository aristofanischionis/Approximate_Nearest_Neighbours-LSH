#include "../headers/modulo.hpp"

// Calculate the m^x%M for x = [0,d-1]
unsigned long long int exponentiationModulo(unsigned int x, unsigned int y, unsigned long p) {
	// Initialize result
    unsigned long long int res = 1;
    // Update x if it is more than or  
    // equal to p 
    x = x % p;
    if (x == 0) return 0; // In case x is divisible by p; 

    while (y > 0) {  
        // If y is odd, multiply x with result  
        if (y & 1) res = (res*x) % p;  
  
        // y must be even now  
        y = y>>1; // y = y/2  
        x = (x*x) % p;  
    }  
    return res;
}

unsigned long customModulo(unsigned long x, unsigned long y){
	// Modulo between x and y, supports negative numers
	return (x % y + y) %y;
}
