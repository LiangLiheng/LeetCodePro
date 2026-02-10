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
        auto matches = [&](auto&& self, ListNode* node, TreeNode* tree) -> bool {
            if (!node) return true;
            if (!tree || tree->val != node->val) return false;
            return self(self, node->next, tree->left) || self(self, node->next, tree->right);
        };
        auto dfs = [&](auto&& self, TreeNode* node) -> bool {
            if (!node) return false;
            return matches(matches, head, node) || self(self, node->left) || self(self, node->right);
        };
        return dfs(dfs, root);
    }
};
# @lc code=end