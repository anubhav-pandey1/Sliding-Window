#include <bits/stdc++.h>
using namespace std;

int maxSumSubarray(vector<int>& v, int K) {
	int size = v.size();
	int sum = 0;                             // = 0, not INT_MIN
	for (int i = 0; i < K; i++) {            // Find sum for first window from 0 -> (K-1)
		sum += v[i];                         // Sum gets updated to sum of first window
	}
	int maxSum = sum;                        // Current maxSum is equal to sum of first window
	for (int i = K; i < size; i++) {         // Iterate from K to end, ie. just next to the first window
		sum += (v[i] - v[i - K]);            // Add the new element, and subtract the first element of prev. window
		maxSum = max(maxSum, sum);           // Update maxSum is sum > maxSum
	}
	return maxSum;                           // maxSum is our target variable, we can also save and return indices
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

		int result = maxSumSubarray(v, subarraySize);
		cout << result << endl;
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

// 9
// 11
// 19
// 20
// 25
// 27
// 28
