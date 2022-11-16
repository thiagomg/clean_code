// https://leetcode.com/problems/binary-tree-level-order-traversal-ii/submissions/831801274/

#include <iostream>
#include <vector>

using namespace std;

namespace bin_tree_transv_inv {
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

	int size_of(TreeNode* root, int level) {
		if (root == nullptr) {
			return level;
		}

		++level;

		int ll = size_of(root->left, level);
		int lr = size_of(root->right, level);
		return std::max(ll, lr);
	}
	
	void transverse(vector<vector<int>>& res, TreeNode* node, int level) {
		if (node == nullptr) {
			return;
		}
		res[level].push_back(node->val);

		transverse(res, node->left, level - 1);
		transverse(res, node->right, level - 1);
	}

	vector<vector<int>> levelOrderBottom(TreeNode* root) {
		if (root == nullptr) { return {}; }
				
		vector<vector<int>> result;
		int size = size_of(root, 0);
		result.resize(size);

		transverse(result, root, size - 1);

		return result;
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
		// values = { 1, 2, 3, 4, -1, -1, 5 };
		TreeNode* root = build(values);

		auto res = levelOrderBottom(root);
		print(res);
	}

}

