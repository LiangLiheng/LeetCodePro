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
        
        // We need at least 3 nodes to have a critical point
        if (!head || !head->next || !head->next->next) {
            return {-1, -1};
        }
        
        ListNode* prev = head;
        ListNode* curr = head->next;
        int position = 1; // Position starts from 1 (second node)
        
        while (curr->next) {
            // Check if current node is a critical point
            bool isMaxima = curr->val > prev->val && curr->val > curr->next->val;
            bool isMinima = curr->val < prev->val && curr->val < curr->next->val;
            
            if (isMaxima || isMinima) {
                criticalPoints.push_back(position);
            }
            
            prev = curr;
            curr = curr->next;
            position++;
        }
        
        // If less than 2 critical points, return [-1, -1]
        if (criticalPoints.size() < 2) {
            return {-1, -1};
        }
        
        // Calculate min and max distances
        int minDistance = INT_MAX;
        int maxDistance = criticalPoints.back() - criticalPoints[0];
        
        for (int i = 1; i < criticalPoints.size(); i++) {
            minDistance = min(minDistance, criticalPoints[i] - criticalPoints[i-1]);
        }
        
        return {minDistance, maxDistance};
    }
};
# @lc code=end