#include <bits/stdc++.h>
using namespace std;

int longestSubstringUniqueChars(string& s, int uniqueLen) {
	int strSize = s.size();
	int i = 0, j = 0, maxSize = 0;
	unordered_map<char, int> uniqueChars;
	while (j < strSize) {
		uniqueChars.insert(pair<char, int>(s[j], 0));  // Doesn't add new element if key already present (Dry Run compared to prev. alternative)
		uniqueChars[s[j]] += 1;                        // Increasing by 1 is default for new s[j], but works even for new element (s[j], 0) --> (s[j], 1)
		int setSize = uniqueChars.size();

		if (setSize == uniqueLen) {
			while (uniqueChars.find(s[j + 1]) != uniqueChars.end()) {  // Removing this block doesn't matter (why? dry run)
				j++;
				uniqueChars[s[j]] += 1;
			}
			int winSize = j - i + 1;
			maxSize = max(winSize, maxSize);
		}

		if (setSize > uniqueLen) {     // >= or >, doesn't matter.(Why? Dry run)
			uniqueChars[s[i]] -= 1;
			if (uniqueChars[s[i]] == 0)
				uniqueChars.erase(s[i]);
			i++;
		}
		j++;
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
		int K;
		cin >> K;
		string s;
		cin >> s;

		cout << longestSubstringUniqueChars(s, K) << endl;
	}
	return 0;
}

// Incorrect implementation using unordered_set
// A set won't work as during i++, we must remove v[i] only if char v[i] is not in the substring
// Set doesn't help maintain counts of occurences of chars, so we must use maps

// int longestSubstringUniqueChars(string& s, int uniqueLen) {
// 	int strSize = s.size();
// 	int i = 0, j = 0, maxSize = 0;
// 	unordered_set<char> uniqueChars;
// 	while (j < strSize) {
// 		uniqueChars.insert(s[j]);
// 		int setSize = uniqueChars.size();

// 		if (setSize == uniqueLen) {
// 			while (uniqueChars.find(s[j + 1]) != uniqueChars.end()) {
// 				j++;
// 			}
// 			winSize = j - i + 1;
// 			maxSize = max(winSize, maxSize);
// 		}

// 		if (setSize < uniqueLen) {
// 			j++;
// 		}

// 		if (setSize > uniqueLen) {
// 			uniqueChars.erase(v[i]);
// 			i++;
// 		}
// 	}
// 	return maxSize;
// }
