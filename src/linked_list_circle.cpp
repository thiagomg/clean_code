// https://leetcode.com/problems/linked-list-cycle/
// https://leetcode.com/problems/remove-nth-node-from-end-of-list/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

namespace linked_list_circle {

    struct ListNode {
        int val;
        ListNode* next;
        ListNode(int x) : val(x), next(nullptr) {}
    };

    void print(ListNode* head, const std::string &prefix = "") {
        if (!prefix.empty()) {
            std::cout << prefix << ": ";
        }

        while (head != nullptr) {
            std::cout << head->val << " ";
            head = head->next;
        }
        std::cout << std::endl;
    }

    ListNode *build(const std::vector<int> values) {
        ListNode* head = nullptr;
        ListNode* prev = nullptr;
        for (int v : values) {
            ListNode* node = new ListNode(v);
            if (head == nullptr) {
                head = node;
                prev = node;
                continue;
            }
            prev->next = node;
            prev = node;
        }
        return head;
    }

    bool hasCycle(ListNode* head) {
        std::unordered_set<ListNode*> visited;

        while (head != nullptr) {
            if (visited.find(head) != visited.end()) {
                return true;
            }
            visited.insert(head);
            head = head->next;
        }

        return false;
    }

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int64_t pos_before_n = -n;
        ListNode* left, * right;
        left = nullptr;
        right = head;

        if (head == nullptr) {
            return nullptr;
        }

        while (right != nullptr) {
            if (pos_before_n == 0) {
                left = head;
            }

            if (right->next == nullptr) break;

            ++pos_before_n;
            right = right->next;
            if (left != nullptr) { left = left->next; }
        }

        ListNode* to_remove;

        // Special case - We are removing the first element.
        if (pos_before_n == -1) {
            to_remove = head;
            head = head->next;
            to_remove->next = nullptr;
        }
        else {
            to_remove = left->next;
            left->next = to_remove->next;
            to_remove->next = nullptr;
        }

        return head;
    }

    void run() {
        ListNode* head = build({ 3, 2, 1, 0, 4, 5 });
        print(head, "BF");
        ListNode* removed = removeNthFromEnd(head, 2);
        print(removed, "AF");

        head = build({ 1, 2, 3, 4, 5 });
        print(head, "BF");
        removed = removeNthFromEnd(head, 4);
        print(removed, "AF");

        head = build({ 1 });
        print(head, "BF");
        removed = removeNthFromEnd(head, 1);
        print(removed, "AF");

        // ListNode* head = build({ 1 });

        // head->next->next->next->next->next = head->next;
        // std::cout << hasCycle(nullptr) << std::endl;
    }
}