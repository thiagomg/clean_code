// https://leetcode.com/problems/search-a-2d-matrix/

#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

namespace search_matrix {

	struct flat_matrix {
		using value_type = int;
		const vector<vector<int>>& _matrix;
		size_t _size;

		flat_matrix(const vector<vector<int>>& matrix) : _matrix(matrix) {
			if (matrix.size() > 0) {
				_size = matrix.size() * matrix[0].size();
			}
			else {
				_size = 0;
			}
		}

		size_t size() const {
			return _size;
		}

		int operator[] (size_t pos) const {
			size_t cols = _matrix[0].size();
			size_t r = pos / cols;
			// size_t c = pos % cols;
			size_t c = pos - (r * cols);
			return _matrix[r][c];
		}
	};

	template<typename Vector>
	size_t bin_search(const Vector& nums, size_t low, size_t high, typename Vector::value_type target) {
		while (low <= high) {
			size_t middle = low + ((high - low) / 2);
			int current_val = nums[middle];
			if (current_val == target) {
				return middle;
			}

			if (target < current_val) {
				if (middle == std::numeric_limits<size_t>::min()) { // avoid overflow rotation
					return -1;
				}

				high = middle - 1;
			}
			else {
				// n > found
				if (middle == std::numeric_limits<size_t>::max()) { // avoid overflow rotation
					return -1;
				}
				low = middle + 1;
			}
		}
		return -1;
	}

	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		flat_matrix virt_vector(matrix);

		return bin_search(virt_vector, 0, virt_vector.size() - 1, target) != -1;
	}

	void run() {
		vector<vector<int>> matrix {
			{ 1, 3, 5, 7},
			{10,11,16,20},
			{23,30,34,60}
		};

		std::unordered_set<int> nums = {
			1, 3, 5, 7,
			10,11,16,20,
			23,30,34,60
		};

		for (int i = 0; i <= 60; ++i) {
			bool ret = searchMatrix(matrix, i);
			if (ret != (nums.find(i) != nums.end())) {
				std::cout << "Error: " << i << std::endl;
			}
		}
		std::cout << "Done" << std::endl;
	}

}