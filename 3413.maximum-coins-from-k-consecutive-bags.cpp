#
# @lc app=leetcode id=3413 lang=cpp
#
# [3413] Maximum Coins From K Consecutive Bags
#

# @lc code=start
class Solution {
public:
    long long maximumCoins(vector<vector<int>>& coins, int k) {
        int m = coins.size();
        if (m == 0) return 0;
        std::sort(coins.begin(), coins.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            return a[0] < b[0];
        });
        std::vector<long long> prefix(m + 1, 0LL);
        for (int i = 1; i <= m; ++i) {
            int idx = i - 1;
            long long l = coins[idx][0];
            long long r = coins[idx][1];
            long long c = coins[idx][2];
            prefix[i] = prefix[i - 1] + c * (r - l + 1LL);
        }
        std::vector<long long> segment_r(m);
        for (int i = 0; i < m; ++i) {
            segment_r[i] = coins[i][1];
        }
        auto computeP = [&](long long pos) -> long long {
            if (pos < 0) return 0LL;
            auto it = std::upper_bound(segment_r.begin(), segment_r.end(), pos);
            int j = (it - segment_r.begin()) - 1;
            long long full_sum = (j >= 0 ? prefix[j + 1] : 0LL);
            int jj = j + 1;
            if (jj < m) {
                long long li_val = coins[jj][0];
                if (li_val <= pos) {
                    long long c_val = coins[jj][2];
                    long long partial = c_val * (pos - li_val + 1LL);
                    full_sum += partial;
                }
            }
            return full_sum;
        };
        std::vector<long long> B;
        for (const auto& seg : coins) {
            B.push_back(seg[0]);
            B.push_back((long long)seg[1] + 1LL);
        }
        std::vector<long long> cand;
        long long K = k;
        for (auto b : B) {
            cand.push_back(b);
            cand.push_back(b - K);
        }
        long long ans = 0LL;
        for (auto s : cand) {
            long long end_pos = s + K - 1LL;
            long long p_right = computeP(end_pos);
            long long p_left_pos = s - 1LL;
            long long p_left = (p_left_pos < 0 ? 0LL : computeP(p_left_pos));
            long long curr = p_right - p_left;
            if (curr > ans) ans = curr;
        }
        return ans;
    }
};
# @lc code=end