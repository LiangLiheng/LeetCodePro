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
        // Try to match from current node, or from left/right subtree
        return dfs(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right);
    }
    
private:
    bool dfs(ListNode* head, TreeNode* root) {
        // If we've matched all of the linked list, success
        if (!head) return true;
        // If tree node is null but list isn't finished, no match
        if (!root) return false;
        // Values must match, and rest of list must match in left or right subtree
        if (head->val != root->val) return false;
        return dfs(head->next, root->left) || dfs(head->next, root->right);
    }
};
# @lc code=end