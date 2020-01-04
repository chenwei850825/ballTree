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
using namespace std;

#define N0 2
struct Compare {
    bool operator()(const pair<float,float*> & a, const pair<float,float*> & b)
    { return a.first< b.first; }
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

	void treeSearch(float* query, ballTreeNode* T,  priority_queue < pair<float,float*>, vector< pair<float,float*>>, Compare > &nnQuery);

	void linearSearch(float* query, ballTreeNode*& T, priority_queue < pair<float,float*>, vector< pair<float,float*>>, Compare > &nnQuery) ;

public:
	BallTree();
	BallTree(long long int*);
	~BallTree();
    ballTreeNode *root;

	void clear();
	void recursive_clear(ballTreeNode *&node);

	bool buildTree(
		int n,
		int d,
		float** data);
    bool printData();
    priority_queue < pair<float,float*>, vector< pair<float,float*>>, Compare > nnSearch(
		int d,
		int k,
		float* query);
	
	long long int* pos;

};

#endif
