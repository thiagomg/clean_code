// https://leetcode.com/problems/kth-largest-element-in-an-array/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


namespace find_kth_largest {
	
	int findKthLargest(vector<int>& nums, int k) {
		// Option 1
		sort(std::begin(nums), std::end(nums));
		int pos = nums.size() - k;
		return nums[pos];
		
		// Option 2
		std::partial_sort(std::begin(nums), std::begin(nums) + k, std::end(nums), std::greater<int>());
		return nums[k - 1];

		// Option 3
		std::nth_element(std::begin(nums), std::begin(nums) + (k-1), std::end(nums), std::greater<int>());
		return nums[k - 1];
	}
	
	
	void run() {

		auto pr = [](const vector<int> &enums, int k) {
			for (int i = 1; i <= enums.size(); ++i) {
				vector<int> nums = enums;
				k = i;
				int x = findKthLargest(nums, k);
				std::cout << k << "th = " << x << " for [ ";
				for (auto n : nums) {
					std::cout << n << " ";
				}
				std::cout << "]";
				std::cout << std::endl;
			}
		};

		pr({ 5, 4, 1, 2, 3, 6 }, 2);

	}

}