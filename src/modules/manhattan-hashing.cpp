#include <math.h>
#include <valarray>
#include "../headers/manhattan-hashing.hpp"
using namespace std;

float* calculateURDComponents(uint64_t d){
	float* s = new float[d];
	float random;
	random_device generator;
	uniform_real_distribution<float> distribution (0.0, (float) w);

	for(uint64_t i=0; i<d; i++){ 	/* Each hash function has its own s */
		random = distribution(generator); /* Generate a new double number */
		s[i] = random;
	}
	return s;
}

int* calculateA_IComponents(unsigned char* x_i_array, float* s_i, uint64_t d) {
	// with this function we will calcuate the a_i components
	// for an image
	float sub, div;
	int *a_i = new int[d];
	float* x_i = new float[d];

	for (uint64_t i=0; i<d; i++) {
		// transform the unsigned char* to float
		x_i[i] = static_cast<float>(x_i_array[i]);
		// do the subtraction of x_i and s_i
		sub = x_i[i] - s_i[i];
		// divide the subtraction with the w, which is globally accessible
		div = sub / w;
		// find the floor of the division
		a_i[i] = static_cast<int>(floor(static_cast<double>(div)));
	}
	return a_i;
}

// Calculate the m^x%M for x = [0,d-1]
unsigned long long int exponentiationModulo(unsigned int x, unsigned int y, unsigned long p){
	unsigned long long int res = 1;     // Initialize result  
  
    x = x % p; // Update x if it is more than or  
                // equal to p 
   
    if (x == 0) return 0; // In case x is divisible by p; 
  
    while (y > 0) {  
        // If y is odd, multiply x with result  
        if (y & 1)  
            res = (res*x) % p;  
  
        // y must be even now  
        y = y>>1; // y = y/2  
        x = (x*x) % p;  
    }  
    return res;
}

unsigned long customModulo(unsigned long x, unsigned long y){
	/* Modulo between x and y, supports negative numers */
	return (x % y + y) %y;
}

unsigned long int calculateH_XComponents(int* a_i, uint64_t d) {
	unsigned long int hx = 0;
	unsigned long long int ma = 0;

	for (uint64_t i=0; i<d; i++){
		// m^x%M
		ma = exponentiationModulo(m, d-(i+1), M);
		hx += ma*abs(a_i[i]);
	}
	//need to check if hx is correct!
	hx = customModulo(hx, M);
	return hx;
}