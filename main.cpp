#include "BallTree.h"
#include "Utility.h"
#include "BallTree.cpp"
#include "Utility.cpp"
#define test
#define L 256

#ifdef test
char dataset[L] = "test";
int n = 10, d= 5, k=3;
#endif

int main() {
	char data_path[L];
	float** data = nullptr;
	long long int* pos = nullptr;
	float query[] = {1,2,3,4,10};
	float* tmp = nullptr;
	priority_queue < pair<float,float*>,vector< pair<float,float*>>, Compare > res;


	sprintf(data_path, "%s/src/dataset.txt", dataset);

	pos = new long long int [n];
	if (!read_data(n, d, data, data_path, pos)) {
		return 1;
	}
	BallTree ball_tree1(pos);

	ball_tree1.buildTree(n, d, data);
	//ball_tree1.printData();
	res = ball_tree1.nnSearch(d,k,query);
	while (!res.empty()){
        tmp = res.top().second;
        cout << res.top().first << " ";
        res.pop();
        for(int i = 0; i < d; i++) {
            cout << tmp[i] << " ";
        }
        cout << endl;
    }

	res = ball_tree1.nnSearch(d,k,query);
	while (!res.empty()){
        tmp = res.top().second;
        cout << res.top().first << " ";
        res.pop();
        for(int i = 0; i < d; i++) {
            cout << tmp[i] << " ";
        }
        cout << endl;
    }

return 0;
}
