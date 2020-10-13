#include <vector>
// uint32_t undefined reference.
#include <stdint.h>
extern std::vector<unsigned int>** HashTables;
void initializeHashtables(unsigned int, uint32_t);
void insertToHashtable(unsigned int, uint32_t, unsigned int);