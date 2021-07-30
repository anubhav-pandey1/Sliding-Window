#include <bits/stdc++.h>
using namespace std;

vector<int> firstNegativeNumber(vector<int>& v, int K) {
	int i = 0, j = 0, idx = 0;                          // i is for first elem, j for last elem in the window, idx is for the latest -ve in negatives array
	vector<int> result, negatives;                      // A list of results, and ordered list of all the -ve ints encountered in the input array (negatives)
	while (j < v.size()) {                              // j iterates over all the elements in v, whereas i iterates over the first size - K elements
		if (v[j] < 0)                                   // Keep storing all the -ve ints for processing later, as not all windows will be straightforward
			negatives.push_back(v[j]);                  // If the first int in window isn't negative, then the latest int in negatives is the first -ve

		if ((j - i + 1) == K) {                         // Once the correct window size is attained due to j++ in line 24, enter scope for i++ (line 22)
			if (v[i] < 0) {                             // i is the first elem, if first elem in curr. window is -ve, directly push it to results
				result.push_back(v[i]);                 // Once we add this int to results, the idx in negatives is not the latest -ve int, the next one is
				idx++;                                  // Also, when the first element of curr. window gets into results, its removed from next window
			}                                           // So it can not be the first -ve in any other window, so increase idx to check for next -ve (dry run)
			else {                                      // If the first elem. of window isn't -ve, then some other previously encountered int is the first -ve
				if (idx < negatives.size())             // If idx is inside the bounds of negatives, ie. the window hasn't run out ahead of -ve ints
					result.push_back(negatives[idx]);   // -ve pointed by idx is the answer since we raise idx to remove ints which were first -ve in a window
				else                                    // If idx > negatives.size(), we have run out of -ve ints for now so the next window must be all +ve
					result.push_back(0);                // This happens because j-pointer keeps ahead of i-pointer and always encounters -ve ints to be stored
			}                                           // Either the first int in window is -ve, or the latest int in negatives is -ve, else window is all +ive
			i++;                                        // i++ takes place once and only when the window size has been attained, unlike j++ in line 24
		}                                               // Marks the end of scope highlighting the window size being attained
		j++;                                            // j++ occures even before window size is attained and also while maintaining the window size
	}                                                   // Marks the end of the j-pointers journey, concluding our O(N) traversal of the array
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

// 1
// 8
// 3
// 12 -1 7 -8 -15 30 16 28

// Outputs:

// -1 -1 -8 -8 -15 0
