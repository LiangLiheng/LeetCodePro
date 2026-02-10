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
        auto check = [&](auto&& self, TreeNode* node, ListNode* list) -> bool {
            if (!list) return true;
            if (!node || node->val != list->val) return false;
            return self(self, node->left, list->next) || self(self, node->right, list->next);
        };
        auto dfs = [&](auto&& self, TreeNode* node) -> bool {
            if (!node) return false;
            if (node->val == head->val && check(check, node, head)) return true;
            return self(self, node->left) || self(self, node->right);
        };
        return dfs(dfs, root);
    }
};
# @lc code=end