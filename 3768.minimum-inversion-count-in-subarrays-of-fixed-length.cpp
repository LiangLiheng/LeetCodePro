#
# @lc app=leetcode id=3768 lang=cpp
#
# [3768] Minimum Inversion Count in Subarrays of Fixed Length
#
# @lc code=start
class Solution {
public:
    long long minInversionCount(vector<int>& nums, int k) {
        struct FenwickTree {
            vector<long long> tree;
            int sz;
            FenwickTree(int n) : sz(n), tree(n + 2, 0LL) {}
            void update(int idx, long long val) {
                while (idx <= sz) {
                    tree[idx] += val;
                    idx += idx & -idx;
                }
            }
            long long query(int idx) {
                long long sum = 0;
                idx = min(idx, sz);
                while (idx > 0) {
                    sum += tree[idx];
                    idx -= idx & -idx;
                }
                return sum;
            }
            long long query(int l, int r) {
                return query(r) - query(l - 1);
            }
        };
        int n = nums.size();
        vector<int> vals = nums;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        int max_rank = vals.size();
        FenwickTree ft(max_rank);
        auto get_rank = [&](int x) -> int {
            return lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
        };
        long long ans = LLONG_MAX;
        long long cur_inv = 0;
        for (int i = 0; i < k; ++i) {
            int r = get_rank(nums[i]);
            cur_inv += ft.query(r + 1, max_rank);
            ft.update(r, 1LL);
        }
        ans = cur_inv;
        for (int i = k; i < n; ++i) {
            int r = get_rank(nums[i]);
            cur_inv += ft.query(r + 1, max_rank);
            ft.update(r, 1LL);
            int l = get_rank(nums[i - k]);
            cur_inv -= ft.query(1, l - 1);
            ft.update(l, -1LL);
            ans = min(ans, cur_inv);
        }
        return ans;
    }
};
# @lc code=end