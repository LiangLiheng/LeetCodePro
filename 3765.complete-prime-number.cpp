#
# @lc app=leetcode id=3765 lang=cpp
#
# [3765] Complete Prime Number
#

# @lc code=start
class Solution {
public:
    bool completePrime(int num) {
        auto is_prime = [&](long long x) -> bool {
            if (x <= 1) return false;
            if (x == 2 || x == 3) return true;
            if (x % 2 == 0 || x % 3 == 0) return false;
            for (long long i = 5; i * i <= x; i += 6) {
                if (x % i == 0 || x % (i + 2) == 0) return false;
            }
            return true;
        };
        std::string s = std::to_string(num);
        int n = s.size();
        for (int len = 1; len <= n; ++len) {
            // prefix
            long long pre = std::stoll(s.substr(0, len));
            if (!is_prime(pre)) return false;
            // suffix
            long long suf = std::stoll(s.substr(n - len, len));
            if (!is_prime(suf)) return false;
        }
        return true;
    }
};
# @lc code=end