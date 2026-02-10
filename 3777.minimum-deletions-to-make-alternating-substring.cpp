#
# @lc app=leetcode id=3777 lang=cpp
#
# [3777] Minimum Deletions to Make Alternating Substring
#
# @lc code=start
class Solution {
public:
    vector<int> minDeletions(string s, vector<vector<int>>& queries) {
        vector<int> answer;
        
        for (auto& query : queries) {
            if (query[0] == 1) {
                // Type 1: Flip character at index j
                int j = query[1];
                s[j] = (s[j] == 'A') ? 'B' : 'A';
            } else {
                // Type 2: Compute minimum deletions for substring s[l..r]
                int l = query[1];
                int r = query[2];
                
                // Dynamic programming to find longest alternating subsequence
                // dpA: max length of alternating subsequence ending with 'A'
                // dpB: max length of alternating subsequence ending with 'B'
                int dpA = 0, dpB = 0;
                
                for (int i = l; i <= r; i++) {
                    if (s[i] == 'A') {
                        // Can extend sequence ending with 'B', or keep current 'A' sequence
                        dpA = max(dpA, dpB + 1);
                    } else { // s[i] == 'B'
                        // Can extend sequence ending with 'A', or keep current 'B' sequence
                        dpB = max(dpB, dpA + 1);
                    }
                }
                
                // Maximum length of alternating subsequence
                int maxLength = max(dpA, dpB);
                // Minimum deletions = total length - max alternating length
                int deletions = (r - l + 1) - maxLength;
                answer.push_back(deletions);
            }
        }
        
        return answer;
    }
};
# @lc code=end