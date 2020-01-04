#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cstring>
#include <stdio.h>

#include "Utility.h"

using namespace std;

void writeInt(ofstream &out, int num);
void writeFloatArr(ofstream &out, float * arr, int len);
void writeFloat(ofstream &out, float data);

ballTreeNode::ballTreeNode() {
	index = indexRight = indexData = -1;
	radius = 0;
	tableSize = 0;
	mean = NULL;
	data = NULL;
	left = right = NULL;
	dimension = 0;
}

ballTreeNode::ballTreeNode(float r, float *m, int d) {
	index = indexRight = indexData = -1;
	radius = r;
	tableSize = 0;
	mean = new float[d];
	memcpy(mean, m, (d) * sizeof(float));
	dimension = d;
	data = NULL;
	left = right = NULL;
}

ballTreeNode::~ballTreeNode() {
	if (mean != NULL) {
		delete[] mean;
	}
	if (data != NULL) {
		for (int i = 0; i < tableSize; i++) {
			delete[] data[i];
		}
		delete[] data;
	}
}

bool read_data(
	int n,
	int d,
	float** &data,
	const char* file_name, 
	long long int* pos)
{
	FILE* fin = fopen(file_name, "r");
	if (!fin) {
		printf("%s doesn't exist!\n", file_name);
		return false;
	}

	data = new float*[n];
	for (int i = 0; i < n; i++) {
		data[i] = new float[d];
		for (int j = 0; j < d; j++) {
			fscanf(fin, "%f", &data[i][j]);
			//cout  << data[i][j] << endl;
		}
		fscanf(fin, "%lld", &pos[i]);
		//cout  << pos[i] << endl;
	}

	printf("Finish reading %s\n", file_name);
	fclose(fin);

	return true;
}
