// https://leetcode.com/problems/surrounded-regions/submissions/831166945/

#include <iostream>
#include <vector>

using namespace std;

namespace board {

	std::pair<size_t, size_t> size(const vector<vector<char>>&board) {
		return { board.size(), board[0].size() };
	}

	void check_visited(const vector<vector<char>>&board, vector<vector<bool>> &visited, size_t r, size_t c) {
		auto [max_r, max_c] = size(board);

		if (board[r][c] == 'X' || visited[r][c]) {
			return;
		}

		// Value is O. Let's mark this visited and check connected nodes
		visited[r][c] = true;

		// UP
		if (r > 0) {
			check_visited(board, visited, r - 1, c);
		}
		// Down
		if ((r + 1) < max_r) {
			check_visited(board, visited, r + 1, c);
		}
		// Left
		if (c > 0) {
			check_visited(board, visited, r, c - 1);
		}
		// Down
		if ((c + 1) < max_c) {
			check_visited(board, visited, r, c + 1);
		}
	}

	// Everything that is not connected with the borders is going to be changed
	void solve(vector<vector<char>> &board) {
		if (board.empty() || board.size() < 3 || board[0].size() < 3) {
			return;
		}

		auto [max_r, max_c] = size(board);

		vector<vector<bool>> visited(max_r, vector<bool>(max_c));

		size_t r, c;
		r = 0; // First line
		for (c = 0; c < max_c; ++c) {
			check_visited(board, visited, r, c);
		}
		r = max_r - 1; // Last line
		for (c = 0; c < max_c; ++c) {
			check_visited(board, visited, r, c);
		}
		c = 0; // First column
		for (r = 0; r < max_r; ++r) {
			check_visited(board, visited, r, c);
		}
		c = max_c - 1; // Last column
		for (r = 0; r < max_r; ++r) {
			check_visited(board, visited, r, c);
		}

		for (size_t r = 1; r < (max_r - 1); ++r) {
			for (size_t c = 1; c < (max_c - 1); ++c) {
				if (!visited[r][c]) {
					board[r][c] = 'X';
				}
			}
		}
	}

	void run() {
		std::vector<std::vector<char>> board {
			{'X','X','X','X'},
			{'X','O','O','X'},
			{'X','X','O','X'},
			{'X','O','X','X'}
		};

		auto print = [](const std::vector<std::vector<char>>& board) {
			std::cout << "+---------------+" << std::endl;
			for (auto& v : board) {
				for (auto& c : v) {
					std::cout << "| " << c << " ";
				}
				std::cout << "|" << std::endl;
				std::cout << "+---+---+---+---+" << std::endl;
			}
		};

		print(board);
		solve(board);
		print(board);
	}

}