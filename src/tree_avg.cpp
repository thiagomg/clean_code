// https://leetcode.com/problems/average-of-levels-in-binary-tree/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#include "tree_util.h"

using namespace std;

namespace tree_avg {
	// AUX START --------------------
	void build_node(const std::vector<int>& values, TreeNode* parent_node, int pos, char dir) {
		if (pos >= values.size() || values[pos] == -1) {
			return;
		}

		TreeNode* node = new TreeNode();
		node->val = values[pos];

		if (dir == 'l') { parent_node->left = node; }
		else /* == r */ { parent_node->right = node; }

		pos *= 2;
		build_node(values, node, pos + 1, 'l');
		build_node(values, node, pos + 2, 'r');
	}

	TreeNode* build(const std::vector<int>& values) {
		TreeNode* node = new TreeNode();
		node->val = values[0];

		build_node(values, node, 1, 'l');
		build_node(values, node, 2, 'r');

		return node;
	}

	void print(const std::vector<std::vector<int>>& board) {
		std::cout << "{ ";
		for (auto& v : board) {
			std::cout << "{ ";
			for (auto& c : v) {
				std::cout << c << " ";
			}
			std::cout << "} ";
		}
		std::cout << "} " << std::endl;
	};
	// AUX END ----------------------

	int size_of(TreeNode* node, int level) {
		if (node == nullptr) {
			return level;
		}

		int ll = size_of(node->left, level + 1);
		int lr = size_of(node->right, level + 1);
		return std::max(ll, lr);
	}

	void transverse(vector<vector<int64_t>>& res, TreeNode* node, int level) {
		if (node == nullptr) {
			return;
		}

		res[level].push_back(node->val);

		transverse(res, node->left, level + 1);
		transverse(res, node->right, level + 1);
	}

	vector<double> averageOfLevels(TreeNode* root) {
		if (root == nullptr) { return { }; }

		vector<vector<int64_t>> res;
		int size = size_of(root, 0);
		res.resize(size);

		transverse(res, root, 0);

		vector<double> avgs;
		avgs.reserve(res.size());
		for(auto &v : res) {
			int64_t total = std::accumulate(begin(v), end(v), (int64_t)0);
			double res = (double)total / (double)v.size();
			avgs.push_back(res);
		}
		
		double n = 2147483647;
		double d = n + n;

		return avgs;
	}

	void run() {
		/*
		[1, 2, 3, 4, null, null, 5]
		Output
			[[1], [2, 3], [4], [5]]
		Expected
			[[1], [2, 3], [4, 5]]
		*/

		std::vector<int> values{ 3, 9, 20, -1, -1, 15, 7 };
		values = { 1, 2, 3, 4, -1, -1, 5, 6, 7, -1, -1, 8, 9, 10, 11 };
		values = { 2147483647,2147483647,2147483647 };
		TreeNode* root = build(values);

		auto res = averageOfLevels(root);

		BinTree bt(root);

		// Build OP's tree
		bt.Dump();
	}

}
