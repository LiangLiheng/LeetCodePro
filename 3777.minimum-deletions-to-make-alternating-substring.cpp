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
                
                // Find longest alternating subsequence in s[l..r]
                int lastA = 0, lastB = 0;
                
                for (int i = l; i <= r; i++) {
                    if (s[i] == 'A') {
                        int newLastA = max(lastA, lastB + 1);
                        lastA = newLastA;
                    } else {
                        int newLastB = max(lastB, lastA + 1);
                        lastB = newLastB;
                    }
                }
                
                int maxLength = max(lastA, lastB);
                int minDeletions = (r - l + 1) - maxLength;
                result.push_back(minDeletions);
            }
        }
        
        return result;
    }
};
# @lc code=end