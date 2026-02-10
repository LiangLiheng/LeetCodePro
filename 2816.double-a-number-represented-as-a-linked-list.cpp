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
        // Reverse the list to make LSD first
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr != nullptr) {
            ListNode* nextTemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        }
        ListNode* newHead = prev;

        // Process doubling with carry, track tail
        ListNode* iter = newHead;
        int carry = 0;
        ListNode* listTail = nullptr;
        while (iter != nullptr) {
            int temp = iter->val * 2 + carry;
            iter->val = temp % 10;
            carry = temp / 10;
            listTail = iter;
            iter = iter->next;
        }

        // Append new node(s) if carry remains
        while (carry != 0) {
            ListNode* newNode = new ListNode(carry % 10);
            listTail->next = newNode;
            listTail = newNode;
            carry /= 10;
        }

        // Reverse back to MSD first
        prev = nullptr;
        curr = newHead;
        while (curr != nullptr) {
            ListNode* nextTemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        }

        return prev;
    }
};
# @lc code=end