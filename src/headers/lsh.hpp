#define inf 4294967295
#define HASHTABLE_NUMBER 16
#include <vector>

extern unsigned int w;
extern unsigned int M;
extern unsigned int m;
extern std::vector<std::vector<std::vector<unsigned int> > > HashTables;

#define INPUT_FILE 0
#define QUERY_FILE 1
#define SUCCESS 0
#define ERROR 1

// define default values
#define SMALL_K 4
#define SMALL_L 5
#define	SMALL_N	1
#define	SMALL_R	10000

using namespace std;
// giving universal access to the all_images array
extern unsigned char **all_images;
extern unsigned char **query_images;
