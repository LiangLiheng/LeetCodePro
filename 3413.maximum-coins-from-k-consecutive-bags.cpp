#
# @lc app=leetcode id=3413 lang=cpp
#
# [3413] Maximum Coins From K Consecutive Bags
#
# @lc code=start
class Solution {
public:
    long long maximumCoins(vector<vector<int>>& coins, int k) {
        sort(coins.begin(), coins.end());
        
        set<long long> startPositions;
        
        // Consider windows starting at segment starts
        // and windows ending at segment ends
        for (const auto& seg : coins) {
            long long l = seg[0], r = seg[1];
            startPositions.insert(l);
            if (r - k + 1 >= 1) {
                startPositions.insert(r - k + 1);
            }
        }
        
        long long maxCoins = 0;
        
        // Evaluate each candidate window
        for (long long start : startPositions) {
            long long end = start + k - 1;
            long long currentCoins = 0;
            
            // Calculate coins in window [start, end]
            for (const auto& seg : coins) {
                long long l = seg[0], r = seg[1], c = seg[2];
                
                // Calculate overlap between [start, end] and [l, r]
                long long overlapLeft = max(start, l);
                long long overlapRight = min(end, r);
                
                if (overlapLeft <= overlapRight) {
                    currentCoins += (overlapRight - overlapLeft + 1) * c;
                }
            }
            
            maxCoins = max(maxCoins, currentCoins);
        }
        
        return maxCoins;
    }
};
# @lc code=end