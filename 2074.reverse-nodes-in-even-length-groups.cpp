#
# @lc app=leetcode id=2074 lang=cpp
#
# [2074] Reverse Nodes in Even Length Groups
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
    ListNode* reverseEvenLengthGroups(ListNode* head) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* prev_tail = dummy;
        int group_size = 1;
        while (prev_tail->next != nullptr) {
            ListNode* group_start = prev_tail->next;
            ListNode* group_end = group_start;
            int actual_len = 1;
            for (int i = 1; i < group_size && group_end->next != nullptr; ++i) {
                group_end = group_end->next;
                ++actual_len;
            }
            ListNode* next_start = group_end->next;
            if (actual_len % 2 == 0) {
                ListNode* new_head = nullptr;
                ListNode* curr = group_start;
                ListNode* new_tail = group_start;
                for (int i = 0; i < actual_len; ++i) {
                    ListNode* nxt = curr->next;
                    curr->next = new_head;
                    new_head = curr;
                    curr = nxt;
                }
                new_tail->next = next_start;
                prev_tail->next = new_head;
                prev_tail = new_tail;
            } else {
                prev_tail = group_end;
            }
            ++group_size;
        }
        ListNode* ans = dummy->next;
        delete dummy;
        return ans;
    }
};
# @lc code=end