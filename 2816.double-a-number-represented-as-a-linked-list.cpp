#
# @lc app=leetcode id=2816 lang=cpp
#
# [2816] Double a Number Represented as a Linked List
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
    ListNode* doubleIt(ListNode* head) {
        auto reverse = [&](ListNode* h) -> ListNode* {
            ListNode* prev = nullptr;
            ListNode* curr = h;
            while (curr) {
                ListNode* next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }
            return prev;
        };
        ListNode* rev = reverse(head);
        ListNode* curr = rev;
        int carry = 0;
        ListNode* tail = nullptr;
        while (curr) {
            int sum = curr->val * 2 + carry;
            curr->val = sum % 10;
            carry = sum / 10;
            tail = curr;
            curr = curr->next;
        }
        if (carry) {
            tail->next = new ListNode(carry);
        }
        return reverse(rev);
    }
};
# @lc code=end