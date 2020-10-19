#include <stdint.h>
#include <vector>
#include <unordered_map>

// define default values
#define SMALL_CUBE_K 14
#define POINTS_M 10
#define	PROBES	2

void handleCubeInput(int , char**, uint32_t*, uint64_t*, int*, int*, int*, int*, unsigned int*, std::string*, std::string*);
void handleCubeReExecution(uint32_t*, uint64_t*, int*, int*, int*, int*, unsigned int*, std::string*, std::string*);
void readCubeFile(const std::string&, int, uint32_t*, uint64_t*, int, int);

extern int d_space;
extern std::vector<std::unordered_map<int, std::string> > projections;
extern unsigned char **all_cube_images;
extern unsigned char **query_cube_images;
