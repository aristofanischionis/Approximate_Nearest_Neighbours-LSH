#include <stdint.h>
#include <fstream>
#include <vector>

std::vector<pair<unsigned int, unsigned int> > approximateN_NNs(ofstream*, uint64_t, int, int, int, uint32_t, int, int);
std::vector<pair<unsigned int, unsigned int> > approximateN_NNs_Full_Search(uint64_t, int, uint32_t, int);
std::vector<pair<unsigned int, unsigned int> > rangeSearch(ofstream*, uint64_t, int, int, uint32_t, unsigned int, int, int);
int* convertArray(unsigned char* , int);
