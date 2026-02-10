#
# @lc app=leetcode id=3725 lang=cpp
#
# [3725] Count Ways to Choose Coprime Integers from Rows
#

# @lc code=start
class Solution {
public:
    int countCoprime(vector<vector<int>>& mat) {
        const int MOD = 1000000007;
        const int MAXV = 150;
        vector<int> Mu(MAXV + 1, 0);
        Mu[1] = 1;
        vector<char> is_composite(MAXV + 1, 0);
        vector<int> primes;
        for (int i = 2; i <= MAXV; ++i) {
            if (!is_composite[i]) {
                primes.push_back(i);
                Mu[i] = -1;
            }
            for (size_t j = 0; j < primes.size(); ++j) {
                int p = primes[j];
                if (1LL * i * p > MAXV) break;
                is_composite[i * p] = 1;
                if (i % p == 0) {
                    Mu[i * p] = 0;
                    break;
                } else {
                    Mu[i * p] = -Mu[i];
                }
            }
        }
        int m = mat.size();
        long long ans = 0;
        for (int d = 1; d <= MAXV; ++d) {
            if (Mu[d] == 0) continue;
            long long prod = 1;
            for (const auto& row : mat) {
                int cnt = 0;
                for (int x : row) {
                    if (x % d == 0) ++cnt;
                }
                prod = prod * cnt % MOD;
            }
            long long sgn = (Mu[d] == 1 ? 1LL : MOD - 1LL);
            ans = (ans + prod * sgn % MOD) % MOD;
        }
        return (int)ans;
    }
};
# @lc code=end