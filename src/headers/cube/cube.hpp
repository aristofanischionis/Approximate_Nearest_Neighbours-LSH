#include <vector>
#include <unordered_map>

// define default values
#define INPUT_FILE 0
#define QUERY_FILE 1
#define SUCCESS 0
#define ERROR 1
#define SMALL_K 14
#define	SMALL_N	1
#define POINTS_M 10
#define	PROBES	2
#define	SMALL_R	10000

extern int d_space;
extern unsigned int w;
extern unsigned int M;
extern unsigned int m;

using namespace std;

extern vector<std::unordered_map<int, string> > projections;
extern unsigned char **all_images;
extern unsigned char **query_images;
