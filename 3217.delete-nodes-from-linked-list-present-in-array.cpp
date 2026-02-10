#
# @lc app=leetcode id=3217 lang=cpp
#
# [3217] Delete Nodes From Linked List Present in Array
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
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        std::unordered_set<int> s(nums.begin(), nums.end());
        ListNode* dummy = nullptr;
        ListNode* tail = nullptr;
        ListNode* cur = head;
        while (cur != nullptr) {
            if (s.find(cur->val) == s.end()) {
                if (dummy == nullptr) {
                    dummy = cur;
                }
                if (tail != nullptr) {
                    tail->next = cur;
                }
                tail = cur;
            }
            cur = cur->next;
        }
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        return dummy;
    }
};
# @lc code=end