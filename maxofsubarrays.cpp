#include <bits/stdc++.h>
using namespace std;

// We'll store the current window highest index in maxIdx and all the window maximums in maxArray
// maxIdx = -1 if the previous max just went out of window and we don't know the current window max
// If maxIdx is not -1, and the latest encountered element (by j-pointer) is greater than v[maxIdx]..
// ..then the latest encountered element must be the max in the latest window [i -> j] since it is..
// ..greater than the prev. max, which means it must be greater than all the elements in the curr. window
// This is because we slided it by 1 unit, so only 1 element from the prev. window is not in curr. window
// That 1 excluded element from prev. window was also not its max since maxIdx != -1. This means that..
// .. the current window's j-element is greater than all the elements in the current window.
// If maxIdx == -1: This will only happen after i starts moving ie. after the window size is attained
// The element that just went out of the current window due to i-pointer++ was the max. of prev. window
// Due to this, we have no information about the max of the remaining K-1 elements in the current window
// There are two possibilities:
// If the latest encountered element v[j] is greater than max of the prev. window, then it is the maxIdx
// Because prev Max is greater than all K-1 elements in the current window except newly encountered v[j]
// If v[j] is greater than prev Max then v[j] is greater than the rest K-1 elements in the current window
// If v[j] is not greater than prev Max, then find the max for the current window using iteration in K steps
// This algorithm is O((n-K)*K) since in the worst case, we find max. in K steps for all (n-K) windows
// Worst case is descending order sorted array -> O(nk - k^2) is equal to brute force time complexity Avg. case
// But avg. case for this algorithm is better than O(nk - k^2), hence better than brute force avg. case

vector<int> maxOfSubarrays(vector<int>& v, int K) {
	int size = v.size();
	int i = 0, j = 0, maxIdx = 0;
	vector<int> maxArray;
	while (j < size) {
		if (maxIdx != -1 && v[j] > v[maxIdx]) {
			maxIdx = j;
		}

		if (j - i + 1 == K) {
			if (maxIdx == -1) {
				if (v[j] > maxArray.back()) {
					maxIdx = j;
				}
				else {
					maxIdx = max_element(v.begin() + i, v.begin() + j + 1) - v.begin();
				}
			}
			maxArray.push_back(v[maxIdx]);

			if (i == maxIdx) {
				maxIdx = -1;
			}
			i++;
		}
		j++;
	}
	return maxArray;
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

		vector<int> result = maxOfSubarrays(v, subarraySize);
		for (int x : result) {
			cout << x << " ";
		}
		cout << endl;
	}
	return 0;
}

// My previous implementation using dequeue:

// void maxOfSubarrays(vector<int>& v, int K) {
// 	int n = v.size();
// 	deque<int> dq;
// 	for (int i = 0; i < K; i++)
// 		dq.push_back(i);

// 	int max = max_element(v.begin() + (dq.front()), v.begin() + 1 + (dq.back())) - v.begin();
// 	printf("%d ", v[max]);

// 	for (int i = 0; i < (n - K); i++) {
// 		dq.pop_front();
// 		dq.push_back(K + i);

// 		if (v[K + i] >= v[max]) {
// 			max = K + i;
// 			printf("%d ", v[max]);
// 		}
// 		else {
// 			if (((K + i) - max) < K) {
// 				printf("%d ", v[max]);
// 			}
// 			else {
// 				max = max_element(v.begin() + (dq.front()), v.begin() + 1 + (dq.back())) - v.begin();
// 				printf("%d ", v[max]);
// 			}
// 		}
// 	}
// 	printf("\n");
// }

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
