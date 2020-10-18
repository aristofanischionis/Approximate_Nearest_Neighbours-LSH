#include <stdint.h>
#include <string>
using namespace std;
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

void handleInput(int , char**, uint32_t*, uint64_t*, int*, int*, int*, int*, unsigned int*, string*, string*);
void handleReExecution(uint32_t*, uint64_t*, int*, int*, int*, int*, unsigned int*, string*, string*);
void readFile(const string&, int, uint32_t*, uint64_t*, int, int);