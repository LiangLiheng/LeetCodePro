#
# @lc app=leetcode id=3640 lang=cpp
#
# [3640] Trionic Array II
#

# @lc code=start
class Solution {
public:
    long long maxSumTrionic(vector<int>& nums) {
        int n = nums.size();
        const long long NINF = -(1LL << 60);
        vector<long long> pref(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            pref[i] = pref[i - 1] + (long long)nums[i - 1];
        }
        vector<long long> dpl(n);
        dpl[0] = (long long)nums[0];
        for (int i = 1; i < n; ++i) {
            dpl[i] = (long long)nums[i];
            if (nums[i - 1] < nums[i]) {
                dpl[i] = max(dpl[i], dpl[i - 1] + (long long)nums[i]);
            }
        }
        vector<long long> lmax(n, NINF);
        for (int i = 1; i < n; ++i) {
            if (nums[i - 1] < nums[i]) {
                lmax[i] = dpl[i - 1] + (long long)nums[i];
            }
        }
        vector<long long> dpr(n);
        dpr[n - 1] = (long long)nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            dpr[i] = (long long)nums[i];
            if (nums[i] < nums[i + 1]) {
                dpr[i] = max(dpr[i], (long long)nums[i] + dpr[i + 1]);
            }
        }
        vector<long long> rmax(n, NINF);
        for (int i = 0; i < n - 1; ++i) {
            if (nums[i] < nums[i + 1]) {
                rmax[i] = (long long)nums[i] + dpr[i + 1];
            }
        }
        vector<int> ds(n);
        ds[0] = 0;
        for (int i = 1; i < n; ++i) {
            ds[i] = (nums[i - 1] > nums[i] ? ds[i - 1] : i);
        }
        vector<long long> vals(n, NINF);
        for (int p = 0; p < n; ++p) {
            if (lmax[p] != NINF) {
                vals[p] = lmax[p] - pref[p + 1];
            }
        }
        const int LOGN = 18;
        vector<vector<long long>> st(LOGN, vector<long long>(n, NINF));
        for (int i = 0; i < n; ++i) {
            st[0][i] = vals[i];
        }
        for (int j = 1; j < LOGN; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
        vector<int> logn(n + 1, 0);
        for (int i = 2; i <= n; ++i) {
            logn[i] = logn[i / 2] + 1;
        }
        auto get_max = [&](int L, int R) -> long long {
            if (L > R) return NINF;
            int k = logn[R - L + 1];
            return max(st[k][L], st[k][R - (1 << k) + 1]);
        };
        long long ans = NINF;
        for (int q = 0; q < n - 1; ++q) {
            if (rmax[q] == NINF) continue;
            int L = ds[q];
            int RR = q - 1;
            long long bl = get_max(L, RR);
            if (bl == NINF) continue;
            long long cur = bl + pref[q + 1] - (long long)nums[q] + rmax[q];
            ans = max(ans, cur);
        }
        return ans;
    }
};
# @lc code=end