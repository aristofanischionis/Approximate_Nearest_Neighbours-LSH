#define INPUT_FILE 0
#define QUERY_FILE 1
#define SUCCESS 0
#define ERROR 1

// define default values
#define SMALL_K 4
#define SMALL_L 5
#define	SMALL_N	1
#define	SMALL_R	1.0

using namespace std;
// giving universal access to the all_images array
extern unsigned char **all_images;

void handleInput(int , char**, uint32_t*, uint64_t*, int*, int*, int*, double*, string*, string*);
void handleReExecution(uint32_t*, uint64_t*, int*, int*, int*, double*, string*, string*);
void readFile(const std::string&, int, uint32_t*, uint64_t*);
