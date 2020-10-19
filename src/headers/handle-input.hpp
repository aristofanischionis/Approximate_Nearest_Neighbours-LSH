#include <stdint.h>
#include <fstream>

void handleInput(int , char**, uint32_t*, uint64_t*, int*, int*, int*, unsigned int*, std::string*, std::string*);
void handleReExecution(uint32_t*, uint64_t*, int*, int*, int*, unsigned int*, std::string*, std::string*);
void readFile(const std::string&, int, uint32_t*, uint64_t*, int, int);
void printFiles(uint32_t, uint32_t, uint64_t);
void getMeta(std::ifstream*, uint32_t &, uint32_t &, uint32_t &, uint32_t &);
void readImage(std::ifstream*, unsigned char *, uint64_t);
