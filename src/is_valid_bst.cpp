// https://leetcode.com/problems/validate-binary-search-tree/

#include "tree_util.h"

using namespace std;

namespace is_valid_bst {

	bool validate_node(TreeNode* node, int64_t min, int64_t max) {
		if (node == nullptr) {
			return true;
		}

		if (node->val < max && node->val > min) {
			bool valid_l = validate_node(node->left, min, node->val);
			if (!valid_l) return false;
			bool valid_r = validate_node(node->right, node->val, max);
			if (!valid_r) return false;
			return true;
		}
		return false;
	}

    bool isValidBST(TreeNode* root) {
		return validate_node(root, std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max());
    }

	void run() {
		BinTree bt;
		// bt.insert(5, 1, 8, 6, 10, 7);
		bt.insert(5, 1, 8, 6, 10, 7);
		bt.root->right->left->val = 4;
		bt.Dump();

		std::cout << isValidBST(bt.root) << std::endl;
	}

}

