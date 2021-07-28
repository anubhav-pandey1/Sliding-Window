#include <bits/stdc++.h>
using namespace std;

vector<int> firstNegativeNumber(vector<int>& v, int K) {
	int i = 0, j = 0, idx = 0;
	vector<int> result, negatives;
	while (j < v.size()) {
		if ((j - i + 1) < K) {                 // Just create the initial window of reqd size
			if (v[j] < 0) {
				negatives.push_back(v[j]);     // Keep storing all the negatives
				// if (result.empty()) {       // Not needed as handled in else below
				// 	result.push_back(v[j]);
				// }
			}
		}
		else {
			if (v[j] < 0)
				negatives.push_back(v[j]);

			if (v[i] < 0) {
				result.push_back(v[i]);
				idx++;                         // When the first element of curr window gets into results, it gets out of next window
			}                                  // So it can not be the first neg in any other window, so increase idx to check for next neg
			else {
				if (idx < negatives.size())
					result.push_back(negatives[idx]);
				else
					result.push_back(0);
			}
			i++;
		}
		j++;
	}
	return result;
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

		vector<int> result = firstNegativeNumber(v, subarraySize);
		for (auto x : result) {
			cout << x << " ";
		}
		cout << endl;
	}
	return 0;
}

// Test cases:-

// Inputs:

