#
# @lc app=leetcode id=3519 lang=cpp
#
# [3519] Count Numbers with Non-Decreasing Digits
#
# @lc code=start
class Solution {
public:
    const int MOD = 1e9 + 7;
    map<tuple<int, int, bool, bool>, long long> memo;
    vector<int> digits;
    int base;
    
    vector<int> toBase(string num, int b) {
        if (num == "0") return {0};
        vector<int> result;
        while (num != "0") {
            int remainder = 0;
            string newNum = "";
            for (char c : num) {
                int current = remainder * 10 + (c - '0');
                if (!newNum.empty() || current / b > 0) {
                    newNum += to_string(current / b);
                }
                remainder = current % b;
            }
            result.push_back(remainder);
            num = newNum.empty() ? "0" : newNum;
        }
        reverse(result.begin(), result.end());
        return result;
    }
    
    long long solve(int pos, int prevDigit, bool tight, bool started) {
        if (pos == digits.size()) {
            return started ? 1 : 0;
        }
        
        auto key = make_tuple(pos, prevDigit, tight, started);
        if (memo.count(key)) {
            return memo[key];
        }
        
        int limit = tight ? digits[pos] : base - 1;
        long long result = 0;
        
        for (int digit = 0; digit <= limit; digit++) {
            if (started && digit < prevDigit) {
                continue;
            }
            
            bool newStarted = started || (digit > 0);
            int newPrevDigit = newStarted ? digit : 0;
            bool newTight = tight && (digit == limit);
            
            result = (result + solve(pos + 1, newPrevDigit, newTight, newStarted)) % MOD;
        }
        
        return memo[key] = result;
    }
    
    long long countUpTo(string num, int b) {
        base = b;
        digits = toBase(num, b);
        memo.clear();
        return solve(0, 0, true, false);
    }
    
    string subtract1(string num) {
        int n = num.size();
        for (int i = n - 1; i >= 0; i--) {
            if (num[i] > '0') {
                num[i]--;
                break;
            }
            num[i] = '9';
        }
        size_t i = 0;
        while (i < num.size() && num[i] == '0') i++;
        return i == num.size() ? "0" : num.substr(i);
    }
    
    int countNumbers(string l, string r, int b) {
        long long countR = countUpTo(r, b);
        string lMinus1 = subtract1(l);
        long long countL = countUpTo(lMinus1, b);
        
        return (countR - countL + MOD) % MOD;
    }
};
# @lc code=end