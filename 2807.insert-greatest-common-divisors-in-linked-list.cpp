#
# @lc app=leetcode id=2807 lang=cpp
#
# [2807] Insert Greatest Common Divisors in Linked List
#

# @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        if (!head || !head->next) return head;
        auto gcd = [](int a, int b) -> int {
            while (b != 0) {
                int temp = b;
                b = a % b;
                a = temp;
            }
            return a;
        };
        ListNode* curr = head;
        while (curr && curr->next) {
            int g = gcd(curr->val, curr->next->val);
            ListNode* new_node = new ListNode(g, curr->next);
            curr->next = new_node;
            curr = new_node->next;
        }
        return head;
    }
};
# @lc code=end