// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/

#include <iostream>
#include <vector>

#include "tree_util.h"

using namespace std;

namespace tree_zigzag {
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
	
	enum Dir { lr, rl };
	Dir invert(Dir dir) {
		if (dir == lr) return rl;
		return lr;
	}

	int size_of(TreeNode* node, int level) {
		if (node == nullptr) {
			return level;
		}

		int ll = size_of(node->left, level + 1);
		int lr = size_of(node->right, level + 1);
		return std::max(ll, lr);
	}

	void zigzag_transverse(vector<vector<int>>& res, TreeNode* node, int level) {
		if (node == nullptr) {
			return;
		}

		res[level].push_back(node->val);

		zigzag_transverse(res, node->left, level + 1);
		zigzag_transverse(res, node->right, level + 1);
	}

	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		if (root == nullptr) { return { }; }
		
		vector<vector<int>> res;
		int size = size_of(root, 0);
		res.resize(size);

		zigzag_transverse(res, root, 0);

		Dir dir = lr;
		for (auto& v : res) {
			if (dir == rl) {
				std::reverse(begin(v), end(v));
			}
			dir = invert(dir);
		}


		return res;
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
		TreeNode* root = build(values);

		auto res = zigzagLevelOrder(root);
		print(res);

		BinTree bt(root);

		// Build OP's tree
		bt.Dump();
	}

}
