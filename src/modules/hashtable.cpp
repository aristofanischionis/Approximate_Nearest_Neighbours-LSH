#include <iostream>
#include "../headers/hashtable.hpp"
#include "../headers/modulo.hpp"
#include "../headers/common.hpp"
#include "../headers/handle-input.hpp"

using namespace std;

vector<vector<vector<unsigned int> > > HashTables;

void initializeHashtables(int L, uint32_t n) {
	int hashtable_size = n/HASHTABLE_NUMBER;
    HashTables.resize(L, vector<vector<unsigned int> >(hashtable_size,vector<unsigned int>(0)));
}

void insertToHashtable(int L, uint32_t image, unsigned int g_x, uint32_t n) {
	int hashtable_size = n/HASHTABLE_NUMBER;
	unsigned long pos = customModulo(g_x, hashtable_size);
	HashTables[L][pos].push_back(static_cast<unsigned int>(image));
}

void printHashtable(int L, int n) {
	int hashtable_size = n/HASHTABLE_NUMBER;
	for(int i=0; i<L; i++) {
		cout<<"Current Hashtable: "<<i<<endl;
		for(int j=0; j<hashtable_size; j++) {
			cout<<"Current Bucket: "<<j<<endl;
			for(unsigned int k=0; k<HashTables[i][j].size(); k++) {
				cout<<HashTables[i][j][k]<<'\t';
			}
			cout<<endl;
		}
	}
}

void deleteHashtable(int L, int n) {
    int hashtable_size = n/HASHTABLE_NUMBER;
    for (int i = 0; i < L;i++) {
        for (int j = 0; j < hashtable_size;j++) {
            HashTables[i][j].clear();
        }
        HashTables[i].clear();
    }
    HashTables.clear();
}