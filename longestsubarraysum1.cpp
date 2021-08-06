#include <bits/stdc++.h>
using namespace std;

// Case: Positive Integers only:-

// For each window marked by [i, j], calculate winSum and winSize to be compared with maxSize
// Loop over array till either i or j goes out of bounds of the input array
// Calculate winSize and winSum right at the start of each iteration so we can perform checks
// Firstly, check if winSum = target sum and then if current window size is greater than maxSize
// If true, update maxSize to reflect the size for the longest subarray with sum = target sum
// If winSum exceeds target sum or equals target sum, we must reduce the window elems from front
// Because increasing window elems from right will cause winSum to exceed even more (positive ints)
// Hence, there are no more acceptable subarrays possible starting at i if curr. subarray sum = target sum
// Before increasing i-pointer, we must reduce winSum by v[i] to reflect v[i] going out of the subarray
// We can now increase j-pointer to increase winSum, since currently winSum is definitely < target sum..
// ..because either it got reduced by i-pointer movement, or it was never >= sum to begin with

int longestSubarraySum(vector<int> v, int sum) {
	int size = v.size();
	int i = 0, j = 0, winSize = 0, winSum = 0, maxSize = 0;

	while (j < size && i < size) {             // In this type of problem, i might go beyond j and exceed size
		winSize = j - i + 1;                   // Calculations at the beginning of the loop only
		winSum += v[j];

		if (winSum == sum) {                   // Checking if problem constraint is met before moving window
			maxSize = max(winSize, maxSize);   // Update maxSize if winSize is greater than maxSize
		}                                      // ^This function helps avoid adding another condition to the if (winSize > maxSize)

		if (winSum >= sum) {                   // Equality because we want to move i++ directly after changing maxSize if winSize = sum
			winSum -= v[i];                    // Reducing winSum by v[i] since i++
			i++;                               // i might move ahead of j if a single cell at v[i] == sum
		}

		j++;                                   // j++ in all cases to keep checking the next window -> [i,j+1] or [i+1,j+1]
	}                                          // Even when i++ happens above^, we move j since [i+1,j] != sum if [i,j] was equal to sum
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

		cout << longestSubarraySum(v, sum) << endl;
	}
	return 0;
}

// Incorrect implementation as it does j++ too early and doesn't calculate winSum in same iteration
// Fails for v = {3 1 1 2 2 4 1} and sum = 5 as it does i++ and winSum -= v[i] to get winSum = 5,..
// but new winSize gets calculated in next iteration to be 4, hence incorrectly gives maxSize = 4

// Lesson: calculate winSize and winSum for new [i, j] at start of curr. iteration and not in next iteration

// int longestSubarraySum(vector<int> v, int sum) {
// 	int size = v.size();
// 	int i = 0, j = 0, winSize = 0, winSum = 0, maxSize = 0;
// 	while (j < size && i < size) {
// 		winSize = j - i + 1;
// 		// cout << winSize << ": [" << i << ", " << j << "]" << endl;

// 		if (winSum < sum) {
// 			winSum += v[j];
// 			j++;
// 		}

// 		if (winSum >= sum) {
// 			if (winSum == sum && winSize > maxSize) {
// 				maxSize = winSize;
// 				// cout << maxSize << endl;
// 			}
// 			winSum -= v[i];
// 			i++;
// 		}
// 	}
// 	return maxSize;
// }

// Test cases (positive integers):

// 5
// 7
// 5
// 3 1 1 2 2 4 1
// 7
// 5
// 4 1 1 1 2 3 5
// 10
// 5
// 1 1 1 1 1 2 3 2 3 5
// 6
// 15
// 10 5 2 7 1 9
// 6
// 55
// 5 5 5 5 5 5

// Outputs:

// 3
// 4
// 5
// 4
// 0
