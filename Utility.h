#ifndef __UTILITY_H
#define __UTILITY_H

#include <math.h>
#include <stack>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#define PAGE_SIZE 65536

using namespace std;

struct ballTreeNode {
	int index;//球的序号
	int indexRight;//球的右节点序号
	int indexData;//数据的序号
	float radius;  //球的半径
	float *mean;   //球的圆心
	int dimension;

	ballTreeNode *left;
	ballTreeNode *right;

	float **data;   // dataSet in leave node
	long long *pos;
	int tableSize;

	ballTreeNode();
	ballTreeNode(float radius, float *mean, int dimension);
	~ballTreeNode();

};


bool read_data(int n, int d, float** &data, const char* file_name, long long int* pos);


#endif
