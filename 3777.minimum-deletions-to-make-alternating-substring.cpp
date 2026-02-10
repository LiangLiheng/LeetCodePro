#
# @lc app=leetcode id=3777 lang=cpp
#
# [3777] Minimum Deletions to Make Alternating Substring
#
# @lc code=start
class Solution {
public:
    vector<int> minDeletions(string s, vector<vector<int>>& queries) {
        vector<int> result;
        
        for (auto& query : queries) {
            if (query[0] == 1) {
                // Type 1: Flip operation
                int j = query[1];
                s[j] = (s[j] == 'A') ? 'B' : 'A';
            } else {
                // Type 2: Compute minimum deletions
                int l = query[1];
                int r = query[2];
                
                // Try pattern starting with 'A'
                int countA = 0;
                char expected = 'A';
                for (int i = l; i <= r; i++) {
                    if (s[i] == expected) {
                        countA++;
                        expected = (expected == 'A') ? 'B' : 'A';
                    }
                }
                
                // Try pattern starting with 'B'
                int countB = 0;
                expected = 'B';
                for (int i = l; i <= r; i++) {
                    if (s[i] == expected) {
                        countB++;
                        expected = (expected == 'A') ? 'B' : 'A';
                    }
                }
                
                // Choose the pattern with maximum matches
                int maxKeep = max(countA, countB);
                int deletions = (r - l + 1) - maxKeep;
                result.push_back(deletions);
            }
        }
        
        return result;
    }
};
# @lc code=end