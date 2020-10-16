// 2^32 - 5
#define m 4294967291

extern unsigned int w;
extern unsigned int M;
// uniform_real_distribution components
// float* calculateURDComponents(uint64_t);
// int* calculateA_IComponents(unsigned char *, float *, uint64_t);
// unsigned long int calculateH_XComponent(int*, uint64_t);
unsigned int calculateG_X(int, int, uint32_t, int);
void calculateW_Component(uint64_t, uint32_t, uint32_t);