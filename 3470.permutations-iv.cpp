#
# @lc app=leetcode id=3470 lang=cpp
#
# [3470] Permutations IV
#
# @lc code=start
class Solution {
public:
    long long dp[51][51][3];
    bool computed[51][51][3];
    
    long long countWays(int oddsLeft, int evensLeft, int lastParity) {
        // lastParity: 0 = last was even, 1 = last was odd, 2 = first position
        if (oddsLeft == 0 && evensLeft == 0) return 1;
        
        if (computed[oddsLeft][evensLeft][lastParity]) {
            return dp[oddsLeft][evensLeft][lastParity];
        }
        
        long long count = 0;
        const long long MAX = 1e15 + 1;
        
        // Can place odd if last was even or this is first
        if ((lastParity == 0 || lastParity == 2) && oddsLeft > 0) {
            long long ways = countWays(oddsLeft - 1, evensLeft, 1);
            if (ways >= MAX / oddsLeft) count = MAX;
            else count = min(MAX, count + oddsLeft * ways);
        }
        
        // Can place even if last was odd or this is first
        if ((lastParity == 1 || lastParity == 2) && evensLeft > 0) {
            long long ways = countWays(oddsLeft, evensLeft - 1, 0);
            if (ways >= MAX / evensLeft) count = MAX;
            else count = min(MAX, count + evensLeft * ways);
        }
        
        computed[oddsLeft][evensLeft][lastParity] = true;
        return dp[oddsLeft][evensLeft][lastParity] = count;
    }
    
    vector<int> permute(int n, long long k) {
        memset(computed, false, sizeof(computed));
        
        vector<int> odds, evens;
        for (int i = 1; i <= n; i++) {
            if (i % 2 == 1) odds.push_back(i);
            else evens.push_back(i);
        }
        
        int numOdds = odds.size();
        int numEvens = evens.size();
        
        // Check if k is valid
        long long total = countWays(numOdds, numEvens, 2);
        if (k > total) return {};
        
        vector<int> result;
        vector<bool> usedOdd(numOdds, false);
        vector<bool> usedEven(numEvens, false);
        int lastParity = 2; // Start with "no last element"
        
        for (int pos = 0; pos < n; pos++) {
            bool placed = false;
            
            // Try odds first (for lexicographical order)
            if ((lastParity == 0 || lastParity == 2) && !placed) {
                for (int i = 0; i < numOdds; i++) {
                    if (usedOdd[i]) continue;
                    
                    usedOdd[i] = true;
                    int oddsLeft = 0, evensLeft = 0;
                    for (int j = 0; j < numOdds; j++) if (!usedOdd[j]) oddsLeft++;
                    for (int j = 0; j < numEvens; j++) if (!usedEven[j]) evensLeft++;
                    
                    long long count = countWays(oddsLeft, evensLeft, 1);
                    
                    if (k <= count) {
                        result.push_back(odds[i]);
                        lastParity = 1;
                        placed = true;
                        break;
                    } else {
                        k -= count;
                        usedOdd[i] = false;
                    }
                }
            }
            
            // Try evens
            if ((lastParity == 1 || lastParity == 2) && !placed) {
                for (int i = 0; i < numEvens; i++) {
                    if (usedEven[i]) continue;
                    
                    usedEven[i] = true;
                    int oddsLeft = 0, evensLeft = 0;
                    for (int j = 0; j < numOdds; j++) if (!usedOdd[j]) oddsLeft++;
                    for (int j = 0; j < numEvens; j++) if (!usedEven[j]) evensLeft++;
                    
                    long long count = countWays(oddsLeft, evensLeft, 0);
                    
                    if (k <= count) {
                        result.push_back(evens[i]);
                        lastParity = 0;
                        placed = true;
                        break;
                    } else {
                        k -= count;
                        usedEven[i] = false;
                    }
                }
            }
        }
        
        return result;
    }
};
# @lc code=end