#include "BallTree.h"
#include "Utility.h"
#include "BallTree.cpp"
#include "Utility.cpp"
#include <map>
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
	priority_queue < tuple<float,float*, long long>,vector< tuple<float,float*, long long>>, Compare > res;


	sprintf(data_path, "%s/src/dataset.txt", dataset);

	pos = new long long int [n];
	if (!read_data(n, d, data, data_path, pos)) {
		return 1;
	}

	map<string, long long> mapPosition;
	for (int i = 0; i < n; i++) {
		std::stringstream ss;
		for (int j = 0; j < d; j++){
			ss << std::to_string(int(data[i][j])) << " ";
		}
		std::string s = ss.str();
		mapPosition.insert(pair<string, long long>(s, pos[i]));
	}
	BallTree ball_tree1(mapPosition, pos, d);

	ball_tree1.buildTree(n, d, data);
	//ball_tree1.printData();
	res = ball_tree1.nnSearch(d,k,query);
	while (!res.empty()){
		long long position = get<2>(res.top());
        tmp = get<1>(res.top());
        cout << get<0>(res.top()) << " ";
        res.pop();
        for(int i = 0; i < d; i++) {
            cout << tmp[i] << " ";
        }
        cout << position << " ";
  
        cout << endl;
    }


return 0;
}
