// 2^32 - 5
#define m 4294967291

extern int w;
extern unsigned int M;
// uniform_real_distribution components
float* calculateURDComponents(uint64_t);
int* calculateA_IComponents(unsigned char *, float *, uint64_t);
unsigned long int calculateH_XComponent(int*, uint64_t);
