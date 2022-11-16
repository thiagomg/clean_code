// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/submissions/843696131/

#include <vector>

using namespace std;

namespace bin_search_range {

    int bin_search(const vector<int>& nums, size_t low, size_t high, int target) {
        // If they have crossed, exit
        while (low <= high) {
            // offset + distance/2
            size_t mid = low + ((high - low) / 2);
            int n = nums[mid];
            if (n == target) {
                return mid;
            }

            // if the current number n is greater than target
            // we need to search to the left
            if (n > target) {
                if (mid == 0) { return -1; }
                high = mid - 1;
            }
            else {
                // n < target
                if (mid == std::numeric_limits<size_t>::max()) { return -1; }
                low = mid + 1;
            }

        }

        // Nothing was found.
        return -1;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.empty()) {
            return { -1, -1 };
        }

        const size_t low = 0;
        const size_t high = nums.size() - 1;
        int pos = bin_search(nums, 0, nums.size() - 1, target);
        if (pos == -1) {
            return { -1, -1 };
        }

        // The value was found. We need to find the left-most and right-most value

        // Left-most value
        size_t left_most = pos;
        while (left_most > low) {
            if (nums[left_most - 1] != target) {
                break;
            }
            // There is at least one equal.
            int cur_pos = bin_search(nums, 0, left_most - 1, target);
            if (cur_pos == -1) {
                break;
            }
            left_most = cur_pos;
        }

        size_t right_most = pos;
        while (right_most < high) {
            if (nums[right_most + 1] != target) {
                break;
            }

            // Ther is at least one equal
            int cur_pos = bin_search(nums, right_most + 1, high, target);
            if (cur_pos == -1) {
                break;
            }
            right_most = cur_pos;
        }

        return { (int)left_most, (int)right_most };
    }

	void run() {

	}
}