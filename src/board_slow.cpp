// https://leetcode.com/problems/surrounded-regions/submissions/831166945/

#include <iostream>

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

namespace slow {

	// Super hack to avoid implementing a hash
	std::string _s(size_t r, size_t c) {
		return std::to_string(r) + "-" + std::to_string(c);
	}

	char check_node(vector<vector<char>>& board, size_t r, size_t c, unordered_set<std::string>& to_ignore) {
		if (board[r][c] == 'X' || (to_ignore.find(_s(r, c)) != to_ignore.end())) {
			return 'X';
		}

		// Value is O. We need to check the surrounds

		int total = 0;
		// Up
		to_ignore.insert(_s(r, c));
		if (r > 0) {
			char val = check_node(board, r - 1, c, to_ignore);
			total += (val == 'X' ? 1 : 0);
		}
		// Left
		if (c > 0) {
			char val = check_node(board, r, c - 1, to_ignore);
			total += (val == 'X' ? 1 : 0);
		}
		// Down
		if (r < (board.size() - 1)) {
			char val = check_node(board, r + 1, c, to_ignore);
			total += (val == 'X' ? 1 : 0);
		}
		// Right
		if (c < (board[r].size() - 1)) {
			char val = check_node(board, r, c + 1, to_ignore);
			total += (val == 'X' ? 1 : 0);
		}
		to_ignore.erase(_s(r, c));

		return total == 4 ? 'X' : 'O';
	}

	void capture(vector<vector<char>>& board) {
		unordered_set<std::string> to_ignore;

		// We don't need to check the borders, also, there is always index -1 and +1
		for (size_t r = 1; r < board.size() - 1; ++r) {
			for (size_t c = 1; c < board[r].size() - 1; c++) {
				char ret = check_node(board, r, c, to_ignore);
				board[r][c] = ret;
			}
		}
	}

	// Works, but slow
	void solve(vector<vector<char>>& board) {
		if (board.empty() || board.size() < 3 || board[0].size() < 3) {
			return;
		}

		// Board is at least 3x3
		capture(board);
	}

	void run() {
		std::vector<std::vector<char>> board{
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