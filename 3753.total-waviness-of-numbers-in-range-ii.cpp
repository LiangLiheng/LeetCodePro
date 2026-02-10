#
# @lc app=leetcode id=3753 lang=cpp
#
# [3753] Total Waviness of Numbers in Range II
#
# @lc code=start
class Solution {
public:
    long long totalWaviness(long long num1, long long num2) {
        int len1 = to_string(num1).length();
        int len2 = to_string(num2).length();
        
        long long result = 0;
        
        for (int length = len1; length <= len2; length++) {
            if (length < 3) continue;
            
            long long lower, upper;
            if (length == len1 && length == len2) {
                lower = num1;
                upper = num2;
            } else if (length == len1) {
                lower = num1;
                upper = getPower10(length) - 1;
            } else if (length == len2) {
                lower = getPower10(length - 1);
                upper = num2;
            } else {
                lower = getPower10(length - 1);
                upper = getPower10(length) - 1;
            }
            
            result += sumWavinessWithLength(lower, upper, length);
        }
        
        return result;
    }
    
private:
    map<tuple<int, int, int, bool, bool>, pair<long long, long long>> memo;
    string lower_str, upper_str;
    int curr_length;
    
    long long getPower10(int exp) {
        long long result = 1;
        for (int i = 0; i < exp; i++) {
            result *= 10;
        }
        return result;
    }
    
    pair<long long, long long> dp(int pos, int prev, int prevprev, bool tight_lower, bool tight_upper) {
        if (pos == curr_length) {
            return {1LL, 0LL};
        }
        
        auto key = make_tuple(pos, prev, prevprev, tight_lower, tight_upper);
        if (memo.count(key)) return memo[key];
        
        int lower_limit = tight_lower ? (lower_str[pos] - '0') : 0;
        int upper_limit = tight_upper ? (upper_str[pos] - '0') : 9;
        
        long long count = 0, waviness = 0;
        
        for (int digit = lower_limit; digit <= upper_limit; digit++) {
            bool new_tight_lower = tight_lower && (digit == lower_limit);
            bool new_tight_upper = tight_upper && (digit == upper_limit);
            
            long long wav_contrib = 0;
            if (pos >= 2 && prevprev >= 0) {
                if (prev > prevprev && prev > digit) {
                    wav_contrib = 1;
                } else if (prev < prevprev && prev < digit) {
                    wav_contrib = 1;
                }
            }
            
            auto [sub_count, sub_wav] = dp(pos + 1, digit, prev, new_tight_lower, new_tight_upper);
            count += sub_count;
            waviness += sub_wav + sub_count * wav_contrib;
        }
        
        return memo[key] = {count, waviness};
    }
    
    long long sumWavinessWithLength(long long lower, long long upper, int length) {
        lower_str = to_string(lower);
        upper_str = to_string(upper);
        curr_length = length;
        memo.clear();
        
        auto [cnt, wav] = dp(0, -1, -1, true, true);
        return wav;
    }
};
# @lc code=end