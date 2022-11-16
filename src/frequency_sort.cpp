// https://leetcode.com/problems/sort-characters-by-frequency/

#include <iostream>
#include <string>
#include <unordered_map>
#include <map>

using namespace std;

namespace frequency_sort {

	string frequencySort(string s) {
		std::unordered_map<char, size_t> freq;
		
		for (char c : s) {
			freq[c] += 1;
		}

		std::map<size_t, std::string, std::greater<size_t>> freq_inv;
		for (auto [k, v] : freq) {
			freq_inv[v] += k;
		}

		std::string res;
		res.reserve(s.size());
		for (auto [k, v] : freq_inv) {
			for(char c : v) {
				res.append(k, c);
			}
		}
		return res;
	}

	void run() {
		std::cout << frequencySort("abaco") << std::endl;
		std::cout << frequencySort("tree") << std::endl;
	}

}