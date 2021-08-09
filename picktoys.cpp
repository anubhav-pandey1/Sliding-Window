#include <bits/stdc++.h>
using namespace std;

// Sliding Window useful here since toys/fruits can be picked continuously
// Toys/Fruits are also represented as a continuous ADT in the input
// Similar to "Longest Substring with K (= 2) Unique Characters"

int pickToys(vector<int>& toys, const int limit = 2) {
	unordered_map<int, int> toySet;                      // Can't use array/vector for int->int mapping, only for char->int as 128 chars only
	int i = 0, j = 0, maxSize = 0;
	while (j < toys.size()) {
		toySet[toys[j]]++;

		if (toySet.size() == limit) {
			maxSize = max(j - i + 1, maxSize);
		}

		while (toySet.size() > limit) {
			toySet[toys[i]]--;
			if (toySet[toys[i]] == 0)
				toySet.erase(toys[i]);
			i++;
		}

		j++;
	}
	return ((maxSize == 0) ? toys.size() : maxSize);     // If array is constant, we get maxSize = initialized value, but maxSize should be all toys
}

// Explanation for the concise form:-

// Suppose [i,j] is the sliding window, and it's the current longest window.
// Suppose we found current longest window [i, j], then this length will be kept because,
// If the sliding window contains more than 2, then also we will do i++ as well as j++,
// which means that the current longest length will be kept the same due to i++, j++ combo
// In other words, when [i,j] window reaches a maximum, it will not become smaller
// On the other side, if the current window contains less than two, only j++ takes place and
// then i will not increase (because the if statement takes place only when winSize > 2),
// This happens because we use if() to update i++ in tandem with main j++ loop, rather than
// using while() to update i++ many times in one iteration of the main j++ loop

int pickToysConcise(vector<int>& toys, const int limit = 2) {
	unordered_map<int, int> toySet;
	int i = 0, j = 0;
	while (j < toys.size()) {
		toySet[toys[j]]++;
		if (toySet.size() > limit) {      // if() instead of while() makes the difference and helps maintain max. winSize
			toySet[toys[i]]--;
			if (toySet[toys[i]] == 0)
				toySet.erase(toys[i]);
			i++;
		}
		j++;
	}
	return (j - i);                       // ((j - i + 1) - 1) due to extra j++ after attaining maxSize (dry run step 10)
}

// Dry run of the concise form:-

//  i
// [3, 4, 3, 1, 2, 2, 1, 2, 3, 2]         0. Initially, starting from i = 0 and j = 0
//  j                                        Only j++ executed was map size (v[0]) not greater than limit

//  i
// [3, 4, 3, 1, 2, 2, 1, 2, 3, 2]         1. Only j++ executed was map size (3, 4) not greater than limit
//     j

//  i
// [3, 4, 3, 1, 2, 2, 1, 2, 3, 2]         2. Only j++ executed was map size (3, 4) not greater than limit
//        j

//  i
// [3, 4, 3, 1, 2, 2, 1, 2, 3, 2]         3. Now map size (3, 4, 1) is greater than limit so i++ executed with j++
//           j                               With every i++, map[v[i]]-- and v[i] removed from map when it goes out of window

//     i
// [3, 4, 3, 1, 2, 2, 1, 2, 3, 2]         4. Constant window of maxSize + 1 will now be maintained as long as map.size > limit
//              j                            i++ and j++ will keep getting executed together till map.size <= limit

//        i
// [3, 4, 3, 1, 2, 2, 1, 2, 3, 2]         5. Both i++ and j++ and map size (3, 1, 2) greater than limit
//                 j                         3 will go out of window after this i++, hence will be removed from map

//           i
// [3, 4, 3, 1, 2, 2, 1, 2, 3, 2]         6. Due to prev. i++ and j++, map size (1, 2) is now under the limit of 2
//                    j                      Now only j++ executed till we find next element not in map (1, 2) so that map size > limit

//           i
// [3, 4, 3, 1, 2, 2, 1, 2, 3, 2]         7. Map size (1, 2) is under the limit, so window keeps growing as well as maxSize
//                       j                   Only j++ will be executed as map size is under the limit

//           i
// [3, 4, 3, 1, 2, 2, 1, 2, 3, 2]         8. New element 3 makes map size (3, 1, 2) > limit, so once again both i++ and j++ begin execution
//                          j                Parallel i++ and j++ will preserve this maxSize of the window attained in prev. step

//              i
// [3, 4, 3, 1, 2, 2, 1, 2, 3, 2]         9. Both i++ and j++ executed as map size (3, 1, 2) > limit (2), and max. window size preserved
//                             j             Curr. window size = maxSize (attained in step 7) + 1 (done in step 7)

//                 i
// [3, 4, 3, 1, 2, 2, 1, 2, 3, 2]         10. j goes out of bounds and becomes equal to v.size(). Main loop stops
//                                j           Curr. winSize = (j - i + 1), maxSize = winSize - 1 = (j - 1)

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
		int size;
		cin >> size;
		vector<int> v;
		for (int i = 0; i < size; i++) {
			int ele;
			cin >> ele;
			v.push_back(ele);
		}

		cout << pickToys(v) << endl;
	}
	return 0;
}

// Testcases:

// Inputs:

// 5
// 5
// 1 1 1 1 1
// 3
// 1 2 1
// 4
// 0 1 2 2
// 5
// 1 2 3 2 2
// 10
// 3 3 3 1 2 1 1 2 3 3 4

// Outputs:

// 5
// 3
// 3
// 4
// 5
