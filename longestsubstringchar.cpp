#include <bits/stdc++.h>
using namespace std;

int longestSubstringUniqueChars(string& s, int uniqueLen) {
	int strSize = s.size();
	int i = 0, j = 0, maxSize = 0;
	unordered_map<char, int> uniqueChars;
	while (j < strSize) {
		// uniqueChars.insert(pair<char, int>(s[j], 0));              // Doesn't add new element if key already present but this is not needed as map['a']++ handles this too
		uniqueChars[s[j]]++;                                          // Increasing by 1 is default for new s[j], but works even for new element (s[j], 0) --> (s[j], 1)
		int setSize = uniqueChars.size();                             // Line 9 is not needed, line 10 alone does the insertion and updates as and when required

		if (setSize == uniqueLen) {
			// while (uniqueChars.find(s[j+1]) != uniqueChars.end()){ // Removing this forwardScan block doesn't matter (Dry run)
			// 	j++;                                                  // The free j++ in line 28 covers this forwardScan in the next steps of the main iteration
			// 	uniqueChars[s[j]] += 1;
			// }
			int winSize = j - i + 1;
			maxSize = max(winSize, maxSize);
		}

		if (setSize > uniqueLen) {                                    // >= cant be used if we remove the forwardScan while() block..
			uniqueChars[s[i]]--;                                      // ..as setSize remains equal to uniqueLen => i++ happens consecutively many times
			if (uniqueChars[s[i]] == 0)                               // If the value for any char becomes 0, remove it from the uniqueChars map
				uniqueChars.erase(s[i]);
			i++;
		}
		j++;                                                          // j++ hit in all cases, still code works because even if i++ hits, winSize becomes maxSize - 1
	}                                                                 // ..so an extra j++ only makes it equal to maxSize which does no harm and we can find next maxSize
	return maxSize;
}

int longestSubstringUniqueCharsClean(string& s, int uniqueLen) {
	int strSize = s.size();
	int i = 0, j = 0, maxSize = 0;
	unordered_map<char, int> uniqueChars;
	while (j < strSize) {
		uniqueChars[s[j]]++;
		int setSize = uniqueChars.size();

		if (setSize == uniqueLen) {
			int winSize = j - i + 1;
			maxSize = max(winSize, maxSize);
		}

		if (setSize > uniqueLen) {
			uniqueChars[s[i]]--;
			if (uniqueChars[s[i]] == 0) {
				uniqueChars.erase(s[i]);
			}
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

		cout << longestSubstringUniqueCharsClean(s, K) << endl;
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

// Testcases:-

// Inputs:

// 3
// 3
// aabacbeb
// 3
// aabacb
// 3
// aabacbebebe

// Outputs:

// 6
// 6
// 7
