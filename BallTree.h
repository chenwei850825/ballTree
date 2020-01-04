#ifndef __BALL_TREE_H
#define __BALL_TREE_H

#include "Utility.h"

#include <ctime>
#include <math.h>
#include <stack>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <tuple>
#include <map>
using namespace std;

#define N0 2
struct Compare {
    bool operator()(const tuple<float,float*, long long> & a, const tuple<float,float*, long long> & b)
    { return get<0>(a) < get<0>(b); }
};
class BallTree {
private:
	int dimension; // dimension作为一个私有数据，即全局变量
	int index;
	int indexData;
	const char* PATH;

	void getCenter(float *&center, float **dataSet, int numberOfData);

	void getRadius(float &radius, float **dataSet, int numberOfData, float *center);

	float getDistance(float *x, float *y);

	bool makeBallTreeSplit(int numberOfData, float **dataSet, float *&A, float *&B);

	bool makeBallTree(ballTreeNode*& node, int numberOfData, float **dataSet);

	float* getFarthestPoint(float *x, float **dataSet, int n);


	void getLeaveNodePreOrder(list<ballTreeNode*> &leave, ballTreeNode* root);

	void treeSearch(float* query, ballTreeNode* T,  priority_queue < tuple<float,float*, long long>, vector< tuple<float,float*, long long>>, Compare > &nnQuery);

	void linearSearch(float* query, ballTreeNode*& T, priority_queue < tuple<float,float*, long long>, vector< tuple<float,float*, long long>>, Compare > &nnQuery) ;

public:
	BallTree();
	BallTree(map<string, long long> &, long long int*, int);
	~BallTree();
    ballTreeNode *root;

	void clear();
	void recursive_clear(ballTreeNode *&node);

	bool buildTree(
		int n,
		int d,
		float** data);
    bool printData();
    priority_queue < tuple<float,float*, long long>, vector< tuple<float,float*, long long>>, Compare > nnSearch(
		int d,
		int k,
		float* query);
	
	long long int* pos;
	map<string, long long> mapPosition;
	int d;
};

#endif
