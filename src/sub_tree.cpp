// https://leetcode.com/problems/subtree-of-another-tree/

#include "tree_util.h"

using namespace std;

namespace sub_tree {

	bool compare_nodes(TreeNode* root, TreeNode* sub_root) {
		if (root == nullptr || sub_root == nullptr) {
			return (root == nullptr && sub_root == nullptr);
		}

		bool res;
		if (root->val == sub_root->val) {
			res = compare_nodes(root->left, sub_root->left);
			if (res == false) { return false; }
			res = compare_nodes(root->right, sub_root->right);
			if (res == false) { return false; }
			return true;
		}
		return false;
	}

	bool isSubtree(TreeNode* root, TreeNode* subRoot) {
		if( root == nullptr || subRoot == nullptr) {
			return false;
		}

		if (compare_nodes(root, subRoot)) {
			return true;
		}

		bool res;
		res = isSubtree(root->left, subRoot);
		if (res) { return true; }
		res = isSubtree(root->right, subRoot);
		if (res) { return true; }

		return false;
	}

	void run() {
		BinTree bt;
		bt.insert(5, 1, 8, 6, 10, 7);
		bt.Dump();

		BinTree bt2;
		bt2.insert(8, 6, 10, 7);
		bt2.Dump();

		std::cout << (isSubtree(bt.root, bt2.root) ? "T" : "F");
	}

}

