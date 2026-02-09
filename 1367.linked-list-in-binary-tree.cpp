#
# @lc app=leetcode id=1367 lang=cpp
#
# [1367] Linked List in Binary Tree
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
/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode() : val(0), left(nullptr), right(nullptr) {}
*     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
*     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
* };
*/
class Solution {
public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        if (!root) return false;
        // Check if path starts at current node, or recurse to children
        return dfs(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right);
    }
    
private:
    bool dfs(ListNode* head, TreeNode* root) {
        // If we've matched all list nodes, success
        if (!head) return true;
        // If tree ended but list didn't, failure
        if (!root) return false;
        // If values don't match, failure
        if (head->val != root->val) return false;
        // Continue matching in left or right subtree
        return dfs(head->next, root->left) || dfs(head->next, root->right);
    }
};
# @lc code=end