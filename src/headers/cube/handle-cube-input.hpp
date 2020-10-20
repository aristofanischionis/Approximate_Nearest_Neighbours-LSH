#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <map>
#include <bitset>

// define default values
#define SMALL_CUBE_K 14
#define POINTS_M 10
#define	PROBES	2

void handleCubeInput(int , char**, uint32_t*, uint64_t*, int*, int*, int*, int*, unsigned int*, std::string*, std::string*);
void handleCubeReExecution(uint32_t*, uint64_t*, int*, int*, int*, int*, unsigned int*, std::string*, std::string*);
void readCubeFile(const std::string&, int, uint32_t*, uint64_t*, int, int);

extern int d_space;
extern std::vector<std::unordered_map<int, int> > projections;
extern std::multimap <std::string, int> Hypercube;
extern unsigned char **all_cube_images;
extern unsigned char **query_cube_images;
