// https://leetcode.com/problems/reorganize-string/

#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

namespace reorganize_string {

	string reorganizeString(string s) {
		// A single char string is already organized
		if (s.size() <= 1) {
			return s;
		}

		// Creating a frequency map or the string
		std::unordered_map<char, size_t> freq;
		for (char c : s) {
			freq[c] += 1;
		}

		// If we have a single char and we reached this point, it means that it repeats
		// Hence we cannot reorganize
		if (freq.size() == 1) {
			return "";
		}

		// Variable to receive the result
		std::string result;
		result.reserve(s.size());

		using s_c = std::pair<size_t, char>;
		std::priority_queue<s_c> pq;
		for (auto& [c, s] : freq) {
			pq.push({ s, c });
		}
		
		// This is the current. This is the one that cannot be retrieved again
		// Even if in more frequency
		s_c cur = pq.top();
		result += cur.second;
		--cur.first;
		pq.pop();

		while (true) {
			if (pq.empty()) { break; }

			// Let's get the most frequent one that is not the current
			s_c most = pq.top();
			// If we used all chars of the most frequent one, let's stop
			if (most.first == 0) { break; }
			
			result += most.second;
			pq.pop();
			--most.first;

			// The second most was added to the string, so it cannot be added again if the most frequent. 
			// Let's set as current
			pq.push(cur);
			cur = most;
		}

		// If the size is different, we didn't have a different char than current to retrieve
		if (result.size() != s.size()) { return ""; }
		return result;
	}

	void run() {
		std::string what = "aaaabcdddee";
		std::cout << "Final result: " << reorganizeString(what) << std::endl;
		what = "abbabbaaab";
		std::cout << "Final result: " << reorganizeString(what) << std::endl;
		
	}

}