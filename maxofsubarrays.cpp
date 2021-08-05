#include <bits/stdc++.h>
using namespace std;

// Approach 1:-

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
// Avg. case is closer to amortized O(n) since almost all elements will be polled and put only once except for..
// ..K elements in a few windows where maxIdx was -1

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

// Approach 2:- Optimal Approach - Monotonic Queue Approach

// We scan the array from 0 to size, keep "promising" elements in a deque.
// At each j, we keep "promising" elements, which are potentially max. number for window [i,j] or any subsequent window.
// If an element in the deque and it goes out of [i,j] as i++, we discard them.
// We just need to poll the max from the front, as we are using a deque and elements are ordered as the sequence in the array
// Now only "promising" elements within [i,j] are in the deque, in a reverse sorted manner.
// We then discard elements smaller than v[j] from the back till we find an element >= v[j] or maxElems goes empty
// Because if v[j] > v[x] and j > x, then v[x] has no chance to be the "max" in [i,j], or any other subsequent window.
// As a result elements in the deque are ordered in both sequence in array and their value.
// At each step, the front of the deque is the max element in [i, j]
// The algorithm is amortized O(n) as each element is removed from maxElems only once and put only once in maxElems.
// A dry run will show that even for reverse sorted arrays, each element is added and removed from maxElems once -> O(2n)

vector<int> maxInSubarrays(vector<int>& v, int K) {
	int size = v.size();
	int i = 0, j = 0;
	deque<int> maxElems;
	vector<int> results;
	while (j < size) {
		while (!maxElems.empty() && v[j] > maxElems.back()) {    // Purging all elems smaller than v[j] whose indices in v[] are less than j
			maxElems.pop_back();                                 // These elements cannot be the max of curr. window or any subsequent window
		}                                                        // After removing, push v[j] to maxElems since it is "promising" atleast fow now
		maxElems.push_back(v[j]);                                // When j->j+1, we might once again remove v[j] from maxElems if v[j+1] > v[j]

		if (j - i + 1 == K) {                                    // The following steps run only when correct window size is attained
			int currentWindowMax = maxElems.front();             // First element of maxElems after purging smaller ones from left of j is the max
			results.push_back(currentWindowMax);                 // Because we ensure a monotonic decreasing deque in the purging steps

			if (v[i] == currentWindowMax) {                      // If the curr. window max is at the front of the current window [i,j] at pos. i
				maxElems.pop_front();                            // then we must remove it from maxElems before we slide the window forward
			}                                                    // As v[i] cannot be the max for any upcoming window, hence it is not "promising"
			i++;                                                 // Slide the window forward, front index
		}
		j++;                                                     // Slide the window forward, back index
	}
	return results;
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

		vector<int> result = maxInSubarrays(v, subarraySize);
		for (int x : result) {
			cout << x << " ";
		}
		cout << endl;
	}
	return 0;
}

// My previous sub-optimal implementation using dequeue:

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

// 9
// 5
// 2
// 3 4 6 3 4
// 10
// 4
// 2 3 3 1 5 5 2 2 4 9
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

// 4 6 6 4
// 3 5 5 5 5 5 9
// 2 5 1 8 2 9 1
// 5 5 8 8 9 9
// 5 8 8 9 9
// 8 8 9 9
// 8 9 9
// 9 9
// 9
