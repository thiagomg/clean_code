// https://leetcode.com/problems/max-area-of-island/submissions/831185296/

#include <iostream>
#include <vector>

using namespace std;

namespace island {

	auto print(vector<vector<int>> &board) {
		for (auto& v : board) {
			for (auto& c : v) {
				std::cout << (c == 1 ? '#' : '_');
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	pair<size_t, size_t> size(vector<vector<int>>& grid) {
		return { grid.size(), grid[0].size() };
	}

	void count_blocks(vector<vector<int>>& grid, vector<vector<bool>>& visited, size_t r, size_t c, int &count) {
		// This is not an island or it was already counted
		if (grid[r][c] == 0 || visited[r][c]) {
			return;
		}

		// It's 1. Let's increment and add to visited
		++count;
		visited[r][c] = true;

		// Now let's check the surroundings
		
		// UP
		auto [max_r, max_c] = size(grid);
		if (r > 0) {
			count_blocks(grid, visited, r - 1, c, count);
		}
		// Down
		if ((r + 1) < max_r) {
			count_blocks(grid, visited, r + 1, c, count);
		}
		// Left
		if (c > 0) {
			count_blocks(grid, visited, r, c - 1, count);
		}
		// Down
		if ((c + 1) < max_c) {
			count_blocks(grid, visited, r, c + 1, count);
		}
	}

	int maxAreaOfIsland(vector<vector<int>>& grid) {
		auto [max_r, max_c] = size(grid);
		
		vector<vector<bool>> visited(max_r, vector<bool>(max_c, false));
		
		int total = 0;
		for (size_t r = 0; r < max_r; ++r) {
			for (size_t c = 0; c < max_c; ++c) {
				int count = 0;
				count_blocks(grid, visited, r, c, count);
				total = std::max(count, total);
			}
		}

		return total;
	}

	void run() {
		vector<vector<int>> grid {
			{0,0,1,0,0,0,0,1,0,0,0,0,0},
			{0,0,0,0,0,0,0,1,1,1,0,0,0},
			{0,1,1,0,1,0,0,0,0,0,0,0,0},
			{0,1,0,0,1,1,0,0,1,0,1,0,0},
			{0,1,0,0,1,1,0,0,1,1,1,0,0},
			{0,0,0,0,0,0,0,0,0,0,1,0,0},
			{0,0,0,0,0,0,0,1,1,1,0,0,0},
			{0,0,0,0,0,0,0,1,1,0,0,0,0}
		};
		print(grid);

		std::cout << "Max area = " << maxAreaOfIsland(grid) << std::endl;
	}

}