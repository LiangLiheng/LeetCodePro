#
# @lc app=leetcode id=3739 lang=cpp
#
# [3739] Count Subarrays With Majority Element II
#

# @lc code=start
class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> a(n);
        for(int i = 0; i < n; ++i) {
            a[i] = (nums[i] == target ? 1 : -1);
        }
        vector<long long> prefix(n + 1, 0LL);
        for(int i = 1; i <= n; ++i) {
            prefix[i] = prefix[i - 1] + a[i - 1];
        }
        auto vals = prefix;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        int m = vals.size();
        vector<int> rank(n + 1);
        for(int i = 0; i <= n; ++i) {
            rank[i] = lower_bound(vals.begin(), vals.end(), prefix[i]) - vals.begin() + 1;
        }
        struct Fenwick {
            int n;
            vector<long long> t;
            Fenwick(int _n) : n(_n), t(_n + 1, 0LL) {};
            void update(int i, long long v) {
                for (; i <= n; i += i & -i) t[i] += v;
            }
            long long query(int i) {
                long long s = 0;
                for (; i > 0; i -= i & -i) s += t[i];
                return s;
            }
        };
        Fenwick ft(m);
        long long ans = 0;
        ft.update(rank[0], 1LL);
        for(int r = 1; r <= n; ++r) {
            ans += ft.query(rank[r] - 1);
            ft.update(rank[r], 1LL);
        }
        return ans;
    }
};
# @lc code=end