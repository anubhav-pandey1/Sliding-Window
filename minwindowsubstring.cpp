#include <bits/stdc++.h>
using namespace std;

//

string minWindowSubstring(string& s, string& text) {
	unordered_map<char, int> t;                          // Hashmap to create frequency-value map for text
	for (char ch : text) {
		t[ch]++;
	}

	int count = t.size();                                // count = 0 if all chars in text have atleast the min. desired frequency
	string sub = "";                                     // To store the smallest substring satisfying count == 0
	int i = 0, j = 0;
	while (j < s.size()) {
		if (t.find(s[j]) != t.end()) {                   // If we find the j-char in the map..
			t[s[j]]--;                                   // Reduce the value in freq-map (-ve freq. represents exta chars in substring)
			if (t[s[j]] == 0)                            // If frequency of j goes to 0 after reducing, then requirement for j fulfilled
				count--;                                 // Reduce count by 1 to represent requirement for 1 char (j) has been fulfilled
		}                                                // If freq. stays +ve, or goes -ve then we don't change count as no effect on requirement count

		while (count == 0) {                             // While() instead of if() to keep reducing size (i++) while requirements fulfilled
			if (sub.empty() || sub.size() > j - i + 1)   // Initially pass as sub empty, later winSize has to be smaller than sub.size
				sub = s.substr(i, j - i + 1);            // substr(initial position, length)

			if (t.find(s[i]) != t.end()) {               // If we find the i-char in the map (preprocessing before i++)..
				t[s[i]]++;                               // Increase requirement value for i-char as we are discarding it from substring
				if (t[s[i]] == 1)                        // If req. value goes from 0 -> 1 ie. from not required to required, we must update..
					count++;                             // .. count++ as now we have requirement for 1 more char in positive
			}                                            // If freq. stays -ve, or was already >= 1, then t[s[i]]++ has no effect on requirement count

			i++;                                         // Discard first char and if count remains 0, we have a new smaller substring, else we go to j++
		}

		j++;                                             // If count != 0, we will keep doing j++ till we find a substring with count = 0
	}

	return sub;
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
		string t;
		cin >> t;

		cout << minWindowSubstring(s, t) << endl;
	}
	return 0;
}

// My inconcise, space-inefficient solution:-

// (1) We don't need a deque to store positions where key elements were found
// sumt tells us the sum of the map t, used for checking if substring matches requirements
// sumt itself can be used to navigate to next key element using while (sumt == 0) instead of if()
// (2) It is better to use count (of elements in map) instead of sumt since we can use more insights
// count we only need to change if t[s[i]] goes from 0 -> 1 on t[s[i]]++ and t[s[j]] goes from 1 -> 0 on t[s[j]]--
// When all values of all keys are <= 0, count = 0 and we have a valid answer substring.
// While (count == 0), we can keep increasing i++ and checking if the new substring is valid (ie. has count = 0)
// Hence, we can avoid using deque to store key locations in string to reduce substring to optimal size
// (3) We can use a 128-len array with INT_MINs instead of a hashmap since only 128 chars are present

// string minWindowSubstring(string& s, string& text) {
// unordered_map<char, int> t;
// for (char ch : text) {
// 	t[ch]++;
// }

// 	int i = 0, j = 0, sumt = text.size();
// 	string subs = "";
// 	deque<int> keys;
// 	while (j < s.size()) {
// 		if (t.find(s[j]) != t.end()) {
// 			if (keys.empty() || j > keys.back()) {
// 				t[s[j]]--;
// 				keys.push_back(j);
// 				if (t[s[j]] >= 0)
// 					sumt--;
// 			}
// 		}

// 		if (sumt == 0) {
// 			if (subs.empty() || subs.size() > (j - i + 1))
// 				subs = s.substr(i, j - i + 1);

// 			if (t.find(s[i]) != t.end()) {
// 				if (t[s[i]] >= 0)
// 					sumt++;
// 				t[s[i]]++;

// 				keys.pop_front();
// 			}
// 			i = keys.front();
// 		}

// 		if (sumt > 0)
// 			j++;
// 	}
// 	return subs;
// }

// Testcases:

// Inputs:

// 7
// TOTMTAPTAT
// TTA
// ADOBECODEBANC
// ABC
// ADOBEBODEBANB
// ABB
// a
// a
// a
// aa
// ab
// b
// abc
// bc

// Outputs:

// TAT
// BANC
// BANB
// a
//
// b
// bc
