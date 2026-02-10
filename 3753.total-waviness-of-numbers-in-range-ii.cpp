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
    map<tuple<int, int, int, int, int>, pair<long long, long long>> memo;
    string num_str;
    
    pair<long long, long long> dp(int pos, int tight, int prev, int prevPrev, int started) {
        if (pos == num_str.size()) {
            return {started ? 1LL : 0LL, 0LL};
        }
        
        auto key = make_tuple(pos, tight, prev, prevPrev, started);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        int limit = tight ? (num_str[pos] - '0') : 9;
        long long total_count = 0;
        long long total_waviness = 0;
        
        for (int digit = 0; digit <= limit; digit++) {
            if (!started && digit == 0) {
                auto [cnt, wav] = dp(pos + 1, tight && (digit == limit), -1, -1, 0);
                total_count += cnt;
                total_waviness += wav;
            } else {
                long long extra_waviness = 0;
                if (prevPrev != -1 && prev != -1) {
                    if ((prev > prevPrev && prev > digit) || (prev < prevPrev && prev < digit)) {
                        extra_waviness = 1;
                    }
                }
                
                auto [cnt, wav] = dp(pos + 1, tight && (digit == limit), digit, prev, 1);
                total_count += cnt;
                total_waviness += wav + extra_waviness * cnt;
            }
        }
        
        memo[key] = {total_count, total_waviness};
        return {total_count, total_waviness};
    }
    
    long long solve(long long num) {
        if (num < 0) return 0;
        num_str = to_string(num);
        memo.clear();
        auto [cnt, wav] = dp(0, 1, -1, -1, 0);
        return wav;
    }
};
# @lc code=end