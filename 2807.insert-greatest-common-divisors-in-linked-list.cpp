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
        
        auto gcd_func = [](int a, int b) -> int {
            while (b != 0) {
                int temp = b;
                b = a % b;
                a = temp;
            }
            return a;
        };
        
        ListNode* cur = head;
        while (cur && cur->next) {
            int g = gcd_func(cur->val, cur->next->val);
            ListNode* newNode = new ListNode(g, cur->next);
            cur->next = newNode;
            cur = newNode->next;
        }
        return head;
    }
};
# @lc code=end