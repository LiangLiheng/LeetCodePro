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
        ListNode* pre = dummy;
        ListNode* curr = head;
        int groupSize = 1;
        while (curr != nullptr) {
            ListNode* nextGroupStart = curr;
            int actualLength = 0;
            while (actualLength < groupSize && nextGroupStart != nullptr) {
                nextGroupStart = nextGroupStart->next;
                ++actualLength;
            }
            if (actualLength % 2 == 0) {
                // Reverse the group
                ListNode* prevNode = nullptr;
                ListNode* currentNode = curr;
                for (int i = 0; i < actualLength; ++i) {
                    ListNode* nextNode = currentNode->next;
                    currentNode->next = prevNode;
                    prevNode = currentNode;
                    currentNode = nextNode;
                }
                curr->next = nextGroupStart;
                pre->next = prevNode;
                pre = curr;
                curr = nextGroupStart;
            } else {
                // Skip: move pre to group tail
                ListNode* groupTail = curr;
                for (int i = 1; i < actualLength; ++i) {
                    groupTail = groupTail->next;
                }
                pre = groupTail;
                curr = nextGroupStart;
            }
            ++groupSize;
        }
        return dummy->next;
    }
};
# @lc code=end