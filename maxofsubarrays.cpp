#include <bits/stdc++.h>
using namespace std;

void maxOfSubarrays(vector<int>& v, int K) {
	int n = v.size();
	deque<int> dq;
	for (int i = 0; i < K; i++)
		dq.push_back(i);

	int max = max_element(v.begin() + (dq.front()), v.begin() + 1 + (dq.back())) - v.begin();
	printf("%d ", v[max]);

	for (int i = 0; i < (n - K); i++) {
		dq.pop_front();
		dq.push_back(K + i);

		if (v[K + i] >= v[max]) {
			max = K + i;
			printf("%d ", v[max]);
		}
		else {
			if (((K + i) - max) < K) {
				printf("%d ", v[max]);
			}
			else {
				max = max_element(v.begin() + (dq.front()), v.begin() + 1 + (dq.back())) - v.begin();
				printf("%d ", v[max]);
			}
		}
	}
	printf("\n");
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int testNum;
	cin >> testNum;
	while (testNum--) {
		int arraySize;
		cin >> arraySize;
		int subarraySize;
		cin >> subarraySize;
		vector<int> v;
		for (int i = 0; i < arraySize; i++) {
			int ele;
			cin >> ele;
			v.push_back(ele);
		}

		maxOfSubarrays(v, subarraySize);
		// for (int x : result) {
		// 	cout << x << endl;
		// }
	}
	return 0;
}

// Test cases:-

// Inputs:

// 7
// 7
// 1
// 2 5 1 8 2 9 1
// 7
// 2
// 2 5 1 8 2 9 1
// 7
// 3
// 2 5 1 8 2 9 1
// 7
// 4
// 2 5 1 8 2 9 1
// 7
// 5
// 2 5 1 8 2 9 1
// 7
// 6
// 2 5 1 8 2 9 1
// 7
// 7
// 2 5 1 8 2 9 1

// Outputs:

// 2 5 1 8 2 9 1
// 5 5 8 8 9 9
// 5 8 8 9 9
// 8 8 9 9
// 8 9 9
// 9 9
// 9
