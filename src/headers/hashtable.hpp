#include <vector>
// uint32_t undefined reference.
#include <stdint.h>
#define HASHTABLE_NUMBER 16
extern std::vector<std::vector<std::vector<unsigned int> > > HashTables;
void initializeHashtables(unsigned int, uint32_t);
void insertToHashtable(unsigned int, uint32_t, unsigned int, uint32_t);
void printHashtable(int, int);
void deleteHashtable(int, int);