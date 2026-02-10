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
        if (!head || !head->next) {
            return {-1, -1};
        }
        ListNode* prev_node = head;
        ListNode* curr_node = head->next;
        int index = 2;
        int first = -1;
        int last_crit = -1;
        int prev_crit = -1;
        int min_distance = 100000001;
        while (curr_node->next != nullptr) {
            ListNode* next_node = curr_node->next;
            bool is_critical = (curr_node->val > prev_node->val && curr_node->val > next_node->val) ||
                               (curr_node->val < prev_node->val && curr_node->val < next_node->val);
            if (is_critical) {
                if (first == -1) {
                    first = index;
                }
                if (prev_crit != -1) {
                    int dist = index - prev_crit;
                    if (dist < min_distance) {
                        min_distance = dist;
                    }
                }
                prev_crit = index;
                last_crit = index;
            }
            prev_node = curr_node;
            curr_node = next_node;
            ++index;
        }
        if (first == -1 || min_distance == 100000001) {
            return {-1, -1};
        }
        return {min_distance, last_crit - first};
    }
};
# @lc code=end