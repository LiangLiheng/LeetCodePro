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
        if (!head || !head->next) return head;
        
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* prev = dummy;
        
        int groupLength = 1;
        
        while (prev->next) {
            // Count actual nodes in this group
            int count = 0;
            ListNode* curr = prev->next;
            while (curr && count < groupLength) {
                count++;
                curr = curr->next;
            }
            
            // If count is even, reverse this group
            if (count % 2 == 0) {
                ListNode* groupStart = prev->next;
                ListNode* groupEnd = groupStart;
                
                // Find the end of the group
                for (int i = 1; i < count; i++) {
                    groupEnd = groupEnd->next;
                }
                
                ListNode* nextGroupStart = groupEnd->next;
                
                // Reverse the group
                ListNode* newHead = reverseList(groupStart, count);
                
                // Reconnect
                prev->next = newHead;
                groupStart->next = nextGroupStart;
                prev = groupStart; // groupStart is now the tail
            } else {
                // Move prev to the end of current group
                for (int i = 0; i < count; i++) {
                    prev = prev->next;
                }
            }
            
            groupLength++;
        }
        
        return dummy->next;
    }
    
private:
    ListNode* reverseList(ListNode* head, int count) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        
        for (int i = 0; i < count; i++) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        
        return prev; // New head
    }
};
# @lc code=end