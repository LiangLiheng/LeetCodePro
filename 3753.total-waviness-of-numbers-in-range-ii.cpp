#
# @lc app=leetcode id=3753 lang=cpp
#
# [3753] Total Waviness of Numbers in Range II
#
# @lc code=start
class Solution {
public:
    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }
    
private:
    map<tuple<int, bool, int, int, bool>, pair<long long, long long>> memo;
    string numStr;
    
    long long solve(long long num) {
        if (num < 0) return 0;
        numStr = to_string(num);
        memo.clear();
        auto [count, sum] = dp(0, true, -1, -1, false);
        return sum;
    }
    
    pair<long long, long long> dp(int pos, bool tight, int prev1, int prev2, bool started) {
        if (pos == numStr.size()) {
            if (!started) return {0, 0};  // FIX: No actual number was formed
            return {1, 0};
        }
        
        auto key = make_tuple(pos, tight, prev1, prev2, started);
        if (memo.count(key)) {
            return memo[key];
        }
        
        int limit = tight ? (numStr[pos] - '0') : 9;
        long long totalCount = 0, totalSum = 0;
        
        for (int digit = 0; digit <= limit; digit++) {
            if (!started && digit == 0 && numStr.size() > 1) {
                // Leading zero for multi-digit number, continue with started=false
                auto [count, sum] = dp(pos + 1, tight && (digit == limit), -1, -1, false);
                totalCount += count;
                totalSum += sum;
            } else {
                bool newStarted = started || (digit > 0);
                bool newTight = tight && (digit == limit);
                auto [count, sum] = dp(pos + 1, newTight, digit, prev1, newStarted);
                
                long long contribution = 0;
                if (pos >= 2 && prev2 >= 0 && prev1 >= 0) {
                    bool isPeak = (prev1 > prev2 && prev1 > digit);
                    bool isValley = (prev1 < prev2 && prev1 < digit);
                    if (isPeak || isValley) {
                        contribution = count;
                    }
                }
                
                totalCount += count;
                totalSum += sum + contribution;
            }
        }
        
        memo[key] = {totalCount, totalSum};
        return {totalCount, totalSum};
    }
};
# @lc code=end