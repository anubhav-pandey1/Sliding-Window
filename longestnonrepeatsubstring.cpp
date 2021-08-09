#include <bits/stdc++.h>
using namespace std;

int longestNonRepeatSubstring(string& s) {      // Similar to "Longest Substring with K Unique Characters"
	unordered_map<char, int> charSet;           // Map to maintain key-value pairs of chars and their occurences in substrings
	int i = 0, j = 0, maxSize = 0;
	while (j < s.size()) {
		charSet[s[j]]++;                        // Insert pair(s[j], 1) or increase value for char s[j] by 1
		// int sumChars = j - i + 1;            // Sum of occurrences of all chars in a substring = length of substring
		// int numChars = charSet.size();       // Num. of unique chars in a substring = Size of the map charSet

		if (j - i + 1 == charSet.size()) {      // if (sumChars == numChars), substring has only unique characters
			maxSize = max(j - i + 1, maxSize);  // Update maxSize if size of substring (i - j + 1) > prev. maxSize
		}

		while (j - i + 1 > charSet.size()) {    // While (sumChars > numChars), ie. there is repetition of a char in substring
			charSet[s[i]]--;                    // Keep reducing the mapped value of first char (i-pointer) in the subtring
			if (charSet[s[i]] == 0) {           // If mapped value falls to 0, remove the first char of substring from the map
				charSet.erase(s[i]);            // This reduces numChars (= mp.size()) by 1 implicitly, so it can converge
			}                                   // numChars and sumChars get implicitly updated automatically in each iteration
			i++;                                // Since first char gets value reduced/removed, move i and implicitly reduce sumChars
		}                                       // We can maintain explicit variables for numChars and sumChars and keep updating them

		j++;                                    // Increase substr. size in each iteration so that new chars can be checked
	}                                           // j++ happens in all cases, even when we update i++ (as it pushes winSize below maxSize)
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
		string s;
		cin >> s;

		cout << longestNonRepeatSubstring(s) << endl;
	}
	return 0;
}

// Testcases:

// Inputs:

// 5
// pwwkew
// pwwkewxt
// aabacbeb
// aabacb
// aabacbebebe

// Outputs:

// 3
// 5
// 4
// 3
// 4
