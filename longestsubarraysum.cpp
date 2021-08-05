#include <bits/stdc++.h>
using namespace std;

int largestSubarraySum(vector<int> v, int sum) {
	int size = v.size();
	int i = 0, j = 0, winSize = 0, winSum = 0, maxSize = 0;
	while (j < size) {
		winSize = j - i + 1;
		cout << winSize << ": [" << i << ", " << j << "]" << endl;

		if (winSum < sum) {
			winSum += v[j];
			j++;
		}

		if (winSum >= sum) {
			if (winSum == sum && winSize > maxSize) {
				maxSize = winSize;
				cout << maxSize << endl;
			}
			winSum -= v[i];
			i++;
		}
	}
	return maxSize;
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
		int sum;
		cin >> sum;
		vector<int> v;
		for (int i = 0; i < arraySize; i++) {
			int ele;
			cin >> ele;
			v.push_back(ele);
		}

		cout << largestSubarraySum(v, sum) << endl;
	}
	return 0;
}
