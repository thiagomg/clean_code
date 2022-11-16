// https://leetcode.com/problems/binary-tree-level-order-traversal/

#include <iostream>
#include <vector>

using namespace std;

namespace bin_tree_transv {
	// AUX START --------------------
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
	};

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
	// AUX END ----------------------
	
	void ensure_capacity(vector<vector<int>>& res, int size) {
		if (res.size() < size) {
			res.resize(size);
		}
	}

	void transverse(vector<vector<int>>& res, TreeNode* node, int root_level) {
		if (node == nullptr) {
			return;
		}

		if (node->left == nullptr && node->right == nullptr) {
			return;
		}

		int node_level = root_level + 1;
		ensure_capacity(res, node_level + 1);

		std::vector<int> &vals = res[node_level];
		if (node->left != nullptr) { vals.push_back(node->left->val); }
		if (node->right != nullptr) { vals.push_back(node->right->val); }
		
		transverse(res, node->left, node_level);
		transverse(res, node->right, node_level);
	}

	vector<vector<int>> levelOrder(TreeNode* root) {
		if (root == nullptr) { return {}; }

		vector<vector<int>> result;
		result.push_back({ root->val });

		transverse(result, root, 0);

		return result;
	}

	auto print = [](const std::vector<std::vector<int>>& board) {
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

	void run() {
		/*
		[1, 2, 3, 4, null, null, 5]
		Output
			[[1], [2, 3], [4], [5]]
		Expected
			[[1], [2, 3], [4, 5]]
		*/

		std::vector<int> values {3, 9, 20, -1, -1, 15, 7};
		values = { 1, 2, 3, 4, -1, -1, 5 };
		TreeNode* root = build(values);
		
		auto res = levelOrder(root);
		std::cout << root->val << std::endl;
		print(res);
	}

}

