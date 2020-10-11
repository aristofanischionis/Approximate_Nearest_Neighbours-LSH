#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include <vector>
#include <algorithm>

#define m 4294967291


extern int w;
extern unsigned long M;
// uniform_real_distribution components
float* calculateURDComponents(uint64_t);
int* calculateA_IComponents(unsigned char *, float *, uint64_t);
int calculateH_XComponents(int*, uint64_t);
unsigned int exponentiationModulo(unsigned int , unsigned int , unsigned long);
unsigned long customModulo(unsigned long , unsigned long);