#
# @lc app=leetcode id=2058 lang=cpp
#
# [2058] Find the Minimum and Maximum Number of Nodes Between Critical Points
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
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> crit;
        if (!head || !head->next) return {-1, -1};
        ListNode* p = head;
        ListNode* c = head->next;
        int pos = 2;
        while (c->next) {
            ListNode* n = c->next;
            if ((c->val > p->val && c->val > n->val) || 
                (c->val < p->val && c->val < n->val)) {
                crit.push_back(pos);
            }
            p = c;
            c = n;
            ++pos;
        }
        if (crit.size() < 2) {
            return {-1, -1};
        }
        int min_dist = crit[1] - crit[0];
        int max_dist = crit.back() - crit[0];
        for (size_t i = 2; i < crit.size(); ++i) {
            min_dist = min(min_dist, crit[i] - crit[i - 1]);
        }
        return {min_dist, max_dist};
    }
};
# @lc code=end