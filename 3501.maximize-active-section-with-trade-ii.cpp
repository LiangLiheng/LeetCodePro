#
# @lc app=leetcode id=3501 lang=cpp
#
# [3501] Maximize Active Section with Trade II
#
# @lc code=start
class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        vector<int> result;
        
        for (const auto& query : queries) {
            int l = query[0], r = query[1];
            string sub = s.substr(l, r - l + 1);
            string aug = "1" + sub + "1";
            int n = aug.length();
            
            // Count active sections without performing any trade
            int maxCount = 0;
            for (char c : sub) {
                if (c == '1') maxCount++;
            }
            
            // Try all possible trades
            for (int i = 1; i < n - 1; i++) {
                if (aug[i] == '1') {
                    // Find the end of this block of '1's
                    int j = i;
                    while (j < n - 1 && aug[j] == '1') {
                        j++;
                    }
                    
                    // Check if this block is surrounded by '0's
                    if (aug[i - 1] == '0' && j < n && aug[j] == '0') {
                        // Perform the trade: convert this block of '1's to '0's
                        string temp = aug;
                        for (int k = i; k < j; k++) {
                            temp[k] = '0';
                        }
                        
                        // Find the maximal block of '0's containing the converted block
                        int left = i;
                        while (left > 0 && temp[left - 1] == '0') {
                            left--;
                        }
                        int right = j - 1;
                        while (right < n - 1 && temp[right + 1] == '0') {
                            right++;
                        }
                        
                        // Check if this block of '0's is surrounded by '1's
                        bool leftBounded = (left == 0 || temp[left - 1] == '1');
                        bool rightBounded = (right == n - 1 || temp[right + 1] == '1');
                        
                        if (leftBounded && rightBounded) {
                            // Convert the block of '0's to '1's
                            for (int k = left; k <= right; k++) {
                                temp[k] = '1';
                            }
                            
                            // Count active sections (excluding the augmented '1's)
                            int count = 0;
                            for (int k = 1; k < n - 1; k++) {
                                if (temp[k] == '1') {
                                    count++;
                                }
                            }
                            maxCount = max(maxCount, count);
                        }
                    }
                    
                    // Skip to the end of this block
                    i = j - 1;
                }
            }
            
            result.push_back(maxCount);
        }
        
        return result;
    }
};
# @lc code=end