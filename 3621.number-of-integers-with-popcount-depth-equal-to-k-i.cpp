#
# @lc app=leetcode id=3621 lang=cpp
#
# [3621] Number of Integers With Popcount-Depth Equal to K I
#

# @lc code=start
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>
using namespace std;

class Solution {
public:
    long long popcountDepth(long long n, int k) {
        // Precompute binomial coefficients C[i][j]
        long long C[65][65];
        memset(C, 0, sizeof(C));
        for (int i = 0; i < 65; ++i) {
            C[i][0] = 1;
            for (int j = 1; j <= i; ++j) {
                C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
            }
        }

        auto get_depth = [](long long m) -> int {
            int dep = 0;
            while (m > 1) {
                m = __builtin_popcountll(m);
                ++dep;
            }
            return dep;
        };

        if (k == 0) {
            return 1LL;
        }

        // Collect target popcounts s with depth(s) == k-1
        vector<int> S;
        for (int m = 1; m <= 64; ++m) {
            if (get_depth(m) == k - 1) {
                S.push_back(m);
            }
        }

        auto get_bits = [](long long num) -> vector<int> {
            vector<int> bits;
            while (num > 0) {
                bits.push_back(num & 1);
                num >>= 1;
            }
            reverse(bits.begin(), bits.end());
            return bits;
        };

        auto count_pop = [&](long long nn, int target_s, const long long (&comb)[65][65]) -> long long {
            if (nn < 1) return 0LL;
            vector<int> bits = get_bits(nn);
            int L = bits.size();
            if (L == 0) return 0LL;
            function<long long(int, int, int)> dfs = [&](int pos, int cnt, int tight) -> long long {
                if (cnt > target_s) return 0LL;
                if (pos == L) {
                    return (cnt == target_s) ? 1LL : 0LL;
                }
                if (!tight) {
                    int rem = L - pos;
                    int need = target_s - cnt;
                    if (need < 0 || need > rem) return 0LL;
                    return comb[rem][need];
                }
                int up = bits[pos];
                long long res = 0;
                for (int d = 0; d <= up; ++d) {
                    res += dfs(pos + 1, cnt + d, tight && (d == up));
                }
                return res;
            };
            return dfs(0, 0, 1);
        };

        long long ans = 0;
        for (int s : S) {
            ans += count_pop(n, s, C);
        }
        if (k == 1) {
            ans -= 1LL;
        }
        return ans;
    }
};
# @lc code=end