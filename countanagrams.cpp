#include <bits/stdc++.h>
using namespace std;

// Generate an unordered_map called keymap of all character occurences of the key, i.e char and its count.
// The window size becomes the length of key, and sum_keys denotes the distinct characters left in a sliding window.
// If the current character in window is present in map, decrease its value in map (when all keys have 0 value, we get anagrams)
// If its value becomes 0, decrease the sum_keys variable to denote one less distinct char left in the window.
// If the window size is lesser than K, just move the window forward till the window size == K
// When the window is hit ->
// If sum_keys is 0, it means all the characters needed for anagram are in the window, therefore increase your ans
// To remove the first char of the window (s[i] part) so that the window can be shifted ->
// If the s[i] is present in map then increase its value and if it changes from 0->1 then increase the sum_keys variable
// Note that sum_keys represents a boundary coundition ie. when sum_keys = 0 for a window, we have an anagram.
// sum_keys is reduced only when the value for a key-value pair hits 0 (not less than equal to 0, only equality)
// sum_keys is increased only when the value for a key-value pair hits 1 (only equality)
// This is because sum_keys is a boundary condition and increments only when a value goes from 0->1, decrements only for 1->0
// This sum_keys based aggregated boundary condition approach helps us to avoid using two maps, one for window and other for keymap

int countAnagram(string& s, string& key) {
	int K = key.size();
	int size = s.size();

	unordered_map<char, int> keymap;
	int sum_keys = 0;
	for (int i = 0; i < K; i++) {
		char ch = key[i];
		if (keymap.find(ch) != keymap.end()) {
			keymap[ch] += 1;
		}
		else {
			keymap.insert(pair<char, int>(ch, 1));
			sum_keys++;
		}
	}

	int i = 0, j = 0, count_anagram = 0;
	while (j < size) {
		char ch = s[j];
		if (keymap.find(ch) != keymap.end()) {
			keymap[ch]--;
			if (keymap[ch] == 0)
				sum_keys--;
		}

		if (j - i + 1 == K) {
			if (sum_keys == 0) {
				count_anagram++;
			}

			char ci = s[i];
			if (keymap.find(ci) != keymap.end()) {
				keymap[ci] += 1;
				if (keymap[ci] == 1)
					sum_keys++;
			}
			i++;
		}
		j++;
	}
	return count_anagram;
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
		string key;
		cin >> key;

		int result = countAnagram(s, key);
		cout << result << endl;
	}
	return 0;
}

// My initial, similar but semi-optimal implementation:

// int countAnagram(string& s, string& key) {
// 	int K = key.size();
// 	int size = s.size();

// 	unordered_map<char, int> keymap;
// 	for (int i = 0; i < K; i++) {
// 		char ch = key[i];
// 		if (keymap.find(ch) != keymap.end()) {
// 			keymap[ch] += 1;
// 		}
// 		else {
// 			keymap.insert(pair<char, int>(ch, 1));
// 		}
// 	}

// 	int i = 0, j = 0, count = 0;
// 	unordered_map<char, int> mp;
// 	while (j < size) {
// 		char ch = s[j];
// 		if (keymap.find(ch) != keymap.end()) {
// 			if (mp.find(ch) != mp.end()) {
// 				mp[ch] += 1;
// 			}
// 			else {
// 				mp.insert(pair<char, int>(ch, 1));
// 			}
// 		}

// 		if (j - i + 1 == K) {
// 			if (mp == keymap) {
// 				count++;
// 			}

// 			char ci = s[i];
// 			if (mp.find(ci) != mp.end()) {
// 				mp[ci] -= 1;
// 			}
// 			i++;
// 		}
// 		j++;
// 	}
// 	return count;
// }

// Test cases:-

// Inputs:

// 2
// forrxxrofxrorfxxfro
// rrof
// forxxorfxdofr
// for
