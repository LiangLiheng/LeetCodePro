#
# @lc app=leetcode id=3519 lang=cpp
#
# [3519] Count Numbers with Non-Decreasing Digits
#
# @lc code=start
class Solution {
public:
    int countNumbers(string l, string r, int b) {
        const int MOD = 1e9 + 7;
        
        // Convert decimal string to base b digits
        auto toBase = [&](string num) {
            vector<int> result;
            while (!num.empty() && num != "0") {
                int remainder = 0;
                string next = "";
                for (char c : num) {
                    int digit = remainder * 10 + (c - '0');
                    if (!next.empty() || digit / b > 0) {
                        next += char('0' + digit / b);
                    }
                    remainder = digit % b;
                }
                result.push_back(remainder);
                num = next;
            }
            if (result.empty()) result.push_back(0);
            reverse(result.begin(), result.end());
            return result;
        };
        
        // Digit DP to count numbers with non-decreasing digits
        auto countUpTo = [&](vector<int>& digits) -> long long {
            int n = digits.size();
            map<tuple<int, int, bool, bool>, long long> memo;
            
            function<long long(int, int, bool, bool)> dp = [&](int pos, int prev, bool tight, bool started) -> long long {
                if (pos == n) {
                    return started ? 1 : 0;
                }
                
                auto key = make_tuple(pos, prev, tight, started);
                if (memo.count(key)) return memo[key];
                
                int limit = tight ? digits[pos] : (b - 1);
                long long res = 0;
                
                for (int d = 0; d <= limit; d++) {
                    if (started && d < prev) continue;
                    
                    bool newStarted = started || (d > 0);
                    bool newTight = tight && (d == limit);
                    int newPrev = newStarted ? d : 0;
                    
                    res = (res + dp(pos + 1, newPrev, newTight, newStarted)) % MOD;
                }
                
                return memo[key] = res;
            };
            
            return dp(0, 0, true, false);
        };
        
        // Subtract 1 from string
        auto subtract1 = [](string num) -> string {
            int i = num.size() - 1;
            while (i >= 0 && num[i] == '0') {
                num[i] = '9';
                i--;
            }
            if (i >= 0) {
                num[i]--;
            }
            size_t start = num.find_first_not_of('0');
            if (start == string::npos) return "0";
            return num.substr(start);
        };
        
        // Count for r
        vector<int> rDigits = toBase(r);
        long long countR = countUpTo(rDigits);
        
        // Count for l-1
        string lMinus1 = subtract1(l);
        long long countL = 0;
        if (lMinus1 != "0") {
            vector<int> lDigits = toBase(lMinus1);
            countL = countUpTo(lDigits);
        }
        
        return (countR - countL + MOD) % MOD;
    }
};
# @lc code=end