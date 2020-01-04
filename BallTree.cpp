#include "Utility.h"
#include "BallTree.h"

bool BallTree::makeBallTreeSplit(int numberOfData, float **dataSet, float* &A, float* &B) {
	srand((unsigned)time(NULL));
	int randomNum = rand() % numberOfData;
	float *x = dataSet[randomNum];
	A = getFarthestPoint(x, dataSet, numberOfData);
	B = getFarthestPoint(A, dataSet, numberOfData);
	return true;
}

float* BallTree::getFarthestPoint(float *x, float **dataSet, int n) {
	float *farthestPoint = NULL;
	float farthest = 0;
	float distance = 0;
	for (int i = 0; i < n; i++) {
		distance = getDistance(x, dataSet[i]);
		if (farthest < distance) {
			farthest = distance;
			farthestPoint = dataSet[i];
		}
	}
	return farthestPoint;
}

void BallTree::getCenter(float *&center, float **dataSet, int numberOfData) {
	for (int i = 0; i < dimension; i++) {
		float mean = 0;
		for (int j = 0; j < numberOfData; j++) {
			mean += dataSet[j][i];
		}
		mean = mean / numberOfData;
		center[i] = mean;
	}
}

void BallTree::getRadius(float &radius, float **dataSet, int numberOfData, float *center) {
	float max = 0;
	for (int i = 0; i < numberOfData; i++) {
		float distance = getDistance(center, dataSet[i]);
		if (distance > max) {
			max = distance;
		}
	}
	radius = max;
}

float BallTree::getDistance(float *x, float *y) {
	float sum = 0;
	for (int i = 0; i < dimension; i++) {
		sum += (x[i] - y[i]) * (x[i] - y[i]);
	}
	return sqrt(sum);
}

bool BallTree::makeBallTree(ballTreeNode *&node, int numberOfData, float **dataSet) {
	index++;
	float *center = new float[dimension];
	float radius;
	getCenter(center, dataSet, numberOfData);
	getRadius(radius, dataSet, numberOfData, center);
	node = new ballTreeNode(radius, center, dimension);
	delete[]center;
	node->index = index;
	//叶子节点
	if (numberOfData <= N0) {
		node->indexData = indexData;
		node->data = new float*[numberOfData];
		for (int i = 0; i < numberOfData; i++) {
			node->data[i] = new float[dimension];
			for (int j = 0; j < dimension; j++) {
				node->data[i][j] = dataSet[i][j];
			}
		}
		node->tableSize = numberOfData;
		indexData = indexData + numberOfData + 1;
		for (int i = 0; i < numberOfData; i++) {
			if (dataSet[i] != NULL) {
				delete[] dataSet[i];
			}
		}
		if (dataSet != NULL) {
			delete[] dataSet;
		}
		return false;
	}
	//得到A、B节点
	float *A;
	float *B;
	makeBallTreeSplit(numberOfData, dataSet, A, B);
	//得到分开的数据集
	float **leftDataSet = new float*[numberOfData];
	float **rightDataSet = new float*[numberOfData];
	int leftDataSize = 0;
	int rightDataSize = 0;
	for (int i = 0; i < numberOfData; i++) {
		float ADistance = getDistance(dataSet[i], A);
		float BDistance = getDistance(dataSet[i], B);
		if (ADistance <= BDistance) {
			leftDataSet[leftDataSize] = dataSet[i];
			leftDataSize++;
		}
		else {
			rightDataSet[rightDataSize] = dataSet[i];
			rightDataSize++;
		}
	}
	//cout << "leftDataSize " << leftDataSize  << endl;
	//cout << "rightDataSize " << rightDataSize  << endl;
	//重新分配数据集
	float **leftData = new float*[leftDataSize];
	float **rightData = new float*[rightDataSize];
	for (int i = 0; i < leftDataSize; i++) {
		leftData[i] = new float[dimension];
		for (int j = 0; j < dimension; j++) {
			leftData[i][j] = leftDataSet[i][j];
		}
	}
	for (int i = 0; i < rightDataSize; i++) {
		rightData[i] = new float[dimension];
		for (int j = 0; j < dimension; j++) {
			rightData[i][j] = rightDataSet[i][j];
		}
	}
	for (int i = 0; i < numberOfData; i++) {
		if (dataSet[i] != NULL) {
			delete[] dataSet[i];
		}
	}
	if (dataSet != NULL) {
		delete[] dataSet;
	}
	delete[] leftDataSet;
	delete[] rightDataSet;
	//为左右节点赋值
	makeBallTree(node->left, leftDataSize, leftData);
	makeBallTree(node->right, rightDataSize, rightData);
	node->indexRight = node->right->index;
	return true;
}

BallTree::BallTree() {
	dimension = 0;
	root = NULL;
	index = -1;
	indexData = 0;
}

BallTree::BallTree(std::map<string, long long> &mapPosition, long long int* pos, int d) {
	dimension = 0;
	root = NULL;
	index = -1;
	indexData = 0;
	//this->pos = new long long int[n];
	this->pos = pos;
	this->mapPosition = mapPosition;
	this->d = d;
}
BallTree::~BallTree() {

	clear();

}

//读进去之后删除整棵树
void BallTree::clear() {
	if (root == NULL) {
		return;
	}
	recursive_clear(root);
}

//递归删除节点
void BallTree::recursive_clear(ballTreeNode *&node) {
	if (node == NULL) {
		return;
	}
	if (node->left != NULL) {
		recursive_clear(node->left);
	}
	if (node->right != NULL) {
		recursive_clear(node->right);
	}
	delete node;
	node = NULL;
}
//建树
bool BallTree::buildTree(int numberOfData, int dimension, float** data) {
	this->dimension = dimension;
	makeBallTree(root, numberOfData, data);
	return true;
}

bool BallTree::printData() {
	list<ballTreeNode*> leave;
	getLeaveNodePreOrder(leave, root);

/*	for (ballTreeNode* curNode : leave) {
		for (int i = 0; i < curNode->tableSize; i++) {
            cout << curNode->index<< " "<< curNode->indexData<< " ";
            for (int j = 0; j < curNode->dimension; j++) {
                cout << curNode->data[i][j]<< " ";
            }
            cout << endl;
		}
	}
*/	leave.clear();
	cout << "Finish print data." << endl;
	return true;
}

void BallTree::getLeaveNodePreOrder(list<ballTreeNode*> &leave, ballTreeNode* curNode) {
    cout << curNode->index<< " ";
    for(int i = 0; i < this->dimension; i++) {
        cout << curNode->mean[i] << " ";
	}
    if (curNode->left != NULL)
		cout << "left:" << curNode->left->index << " ";
	if (curNode->right != NULL)
		cout << "right:" << curNode->right->index << " ";
	cout << endl;
	if (curNode->indexData != -1) {
		leave.push_back(curNode);
		return;
	}
	if (curNode->left != NULL)
		getLeaveNodePreOrder(leave, curNode->left);
	if (curNode->right != NULL)
		getLeaveNodePreOrder(leave, curNode->right);
	return;
}


void BallTree::linearSearch(float* query, ballTreeNode*& T, priority_queue < tuple<float,float*, long long>, vector< tuple<float,float*, long long>>, Compare > &nnQuery) {
	float** data = T->data;
	for (int i = 0; i < T->tableSize; i++) {
		float* p = data[i];
		float IP = getDistance(query, p);
        tuple<float,float*, long long> top = nnQuery.top();
		if (IP <= get<0>(top)) {
			nnQuery.pop();

			std::stringstream ss;
			for (int j = 0; j < this->d; j++){
				ss << std::to_string(int(data[i][j])) << " ";
			}
			std::string s = ss.str();

			map<string, long long>::iterator iter;
			iter = this->mapPosition.find(s);
			nnQuery.push(make_tuple(IP,p, iter->second));
			//cout << "tableSize" << T->tableSize << endl;
			//cout << "linear " << i << " " << p[2] << pos[i] << endl;
		}
	}
	for (int i = 0; i < T->tableSize; i++) {
		//cout << data[i] << endl;
		//delete[] data[i];
	}
	//delete[] data;
}

void BallTree::treeSearch(float* query, ballTreeNode* T,  priority_queue < tuple<float,float*, long long>, vector< tuple<float,float*, long long>>, Compare > &nnQuery) {
	tuple<float,float*, long long> top = nnQuery.top();
	if (T->indexData != -1) {   // if T is a leaf
	    float disToVector = getDistance(query, T->mean);
		if (get<0>(top) >= disToVector) {
			linearSearch(query, T, nnQuery);
		}

	}
    else {
        ballTreeNode* leftChild = T->left;
        ballTreeNode* rightChild = T->right;
        float iL = getDistance(query, leftChild->mean) - leftChild->radius;
        float iR = getDistance(query, rightChild->mean) - rightChild->radius;
        if (get<0>(top) < iL && get<0>(top) < iR) {
        }else{
            if(iL < iR){
                treeSearch(query, leftChild, nnQuery);
                ////delete leftChild;
                treeSearch(query, rightChild, nnQuery);
                ////delete rightChild;
            }else {
                treeSearch(query, rightChild, nnQuery);
                ////delete rightChild;
                treeSearch(query, leftChild, nnQuery);
                ////delete leftChild;
                }
        }
    }
}

priority_queue < tuple<float,float*, long long>, vector< tuple<float,float*, long long>>, Compare > BallTree::nnSearch(int d, int k,float* query) {
    priority_queue < tuple<float,float*, long long>, vector< tuple<float,float*, long long>>, Compare > nnQuery;
	//cout << 'here' << endl;
    for (int i=0; i < k; i++){
        nnQuery.push(make_tuple (3.40E+38, nullptr, 0));
    }
	//cout << 'here2' << endl;
	ballTreeNode* root = this->root;
	treeSearch(query, root, nnQuery);
	//cout << 'here3' << endl;
	//delete root;
	root = NULL;
	return nnQuery;
}
