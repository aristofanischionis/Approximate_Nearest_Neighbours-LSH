#include "../headers/hashtable.hpp"
#include "../headers/modulo.hpp"
#include <iostream>

using namespace std;

vector<vector<vector<unsigned int>>> HashTables;

void initializeHashtables(unsigned int L, uint32_t n) {
	int hashtable_size = n/HASHTABLE_NUMBER;
    HashTables.resize(L, vector<vector<unsigned int>>(hashtable_size, vector<unsigned int> (HASHTABLE_NUMBER)));

    // for (unsigned int i=0; i<L; i++) {
    // 	HashTables[i].push_back(vector<vector<unsigned int>>());
    // 	for (int j=0; j<hashtable_size; j++) {
    // 		HashTables[i][j].push_back(j);
    // 	}
    // }
}

void insertToHashtable(unsigned int L, uint32_t image, unsigned int g_x, uint32_t n) {
	int hashtable_size = n/HASHTABLE_NUMBER;
	unsigned long pos = customModulo(g_x, hashtable_size);
	cout<<HashTables[0][0][0]<<endl;
	HashTables[L][pos].insert(HashTables[L][pos].begin(), static_cast<unsigned int>(image));
}

void printHashtable(int L, int n) {
	int hashtable_size = n/HASHTABLE_NUMBER;
	for(int i=0; i<L; i++) {
		cout<<"Current Hashtable: "<<i<<endl;
		for(int j=0; j<hashtable_size; j++) {
			cout<<"Current Bucket: "<<j<<endl;
			for(int k=0; k<HASHTABLE_NUMBER; k++) {
				cout<<HashTables[i][j][k]<<'\t';
			}
			cout<<endl;
		}
	}
}

void deleteHashtable() {

}