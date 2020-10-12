#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include <vector>
#include <algorithm>

// 2^32 - 5
#define m 4294967291
// 2^27 
// #define m 134217728


extern int w;
extern unsigned int M;
// uniform_real_distribution components
float* calculateURDComponents(uint64_t);
int* calculateA_IComponents(unsigned char *, float *, uint64_t);
unsigned long int calculateH_XComponent(int*, uint64_t);
unsigned long long int exponentiationModulo(unsigned int , unsigned int , unsigned long);
unsigned long customModulo(unsigned long , unsigned long);