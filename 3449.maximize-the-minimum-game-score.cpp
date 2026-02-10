#
# @lc app=leetcode id=3449 lang=cpp
#
# [3449] Maximize the Minimum Game Score
#

# @lc code=start
class Solution {
public:
    long long maxScore(vector<int>& points, int m) {
        int n = points.size();
        auto can_achieve = [&](long long x) -> bool {
            vector<long long> need(n);
            for (int i = 0; i < n; i++) {
                need[i] = (x + (long long)points[i] - 1LL) / (long long)points[i];
                if (need[i] > m) return false;
            }
            vector<long long> t(n - 1, 0LL);
            // backward pass
            for (int k = n - 2; k >= 0; --k) {
                long long right = (k + 1 < n - 1 ? t[k + 1] : 0LL);
                t[k] = max(t[k], need[k + 1] - right);
            }
            // forward pass
            t[0] = max(t[0], need[0] - 1LL);
            for (int k = 1; k < n - 1; ++k) {
                t[k] = max(t[k], need[k] - t[k - 1]);
            }
            long long sum_t = 0LL;
            for (auto tt : t) sum_t += tt;
            long long total = 1LL + 2LL * sum_t;
            long long v0 = 1LL + t[0];
            if (v0 > need[0]) --total;
            return total <= (long long)m;
        };
        long long lo = 0LL;
        long long hi = 1LL * m * 1000000LL + 1;
        while (lo < hi) {
            long long mid = lo + (hi - lo + 1LL) / 2;
            if (can_achieve(mid)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return lo;
    }
};
# @lc code=end