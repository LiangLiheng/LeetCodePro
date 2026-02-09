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
        vector<int> criticalPoints;
        
        // Need at least 3 nodes to have a critical point
        if (!head || !head->next || !head->next->next) {
            return {-1, -1};
        }
        
        ListNode* prev = head;
        ListNode* curr = head->next;
        int position = 1; // Position of curr (1-indexed)
        
        while (curr->next) {
            ListNode* next = curr->next;
            
            // Check if curr is a critical point (local maxima or minima)
            if ((curr->val > prev->val && curr->val > next->val) ||
                (curr->val < prev->val && curr->val < next->val)) {
                criticalPoints.push_back(position);
            }
            
            prev = curr;
            curr = next;
            position++;
        }
        
        // Need at least 2 critical points
        if (criticalPoints.size() < 2) {
            return {-1, -1};
        }
        
        // Calculate minimum distance between consecutive critical points
        int minDistance = INT_MAX;
        for (int i = 1; i < criticalPoints.size(); i++) {
            minDistance = min(minDistance, criticalPoints[i] - criticalPoints[i-1]);
        }
        
        // Maximum distance is between first and last critical point
        int maxDistance = criticalPoints.back() - criticalPoints.front();
        
        return {minDistance, maxDistance};
    }
};
# @lc code=end