#
# @lc app=leetcode id=3762 lang=cpp
#
# [3762] Minimum Operations to Equalize Subarrays
#
# @lc code=start
class Solution {
public:
    vector<long long> minOperations(vector<int>& nums, int k, vector<vector<int>>& queries) {
        using ll = long long;
        int n = nums.size();
        ll K = k;
        vector<ll> R(n), Q(n);
        for(int i = 0; i < n; i++) {
            R[i] = (ll)nums[i] % K;
            Q[i] = (ll)nums[i] / K;
        }
        // Sparse table for RMQ on R
        const int LOGN = 17;
        vector<vector<ll>> stmin(LOGN, vector<ll>(n));
        vector<vector<ll>> stmax(LOGN, vector<ll>(n));
        for(int i = 0; i < n; i++) {
            stmin[0][i] = stmax[0][i] = R[i];
        }
        for(int j = 1; j < LOGN; j++) {
            for(int i = 0; i + (1 << j) <= n; i++) {
                stmin[j][i] = min(stmin[j-1][i], stmin[j-1][i + (1 << (j-1))]);
                stmax[j][i] = max(stmax[j-1][i], stmax[j-1][i + (1 << (j-1))]);
            }
        }
        auto get_rmin = [&](int L, int RR) -> ll {
            int leng = RR - L + 1;
            int j = 31 - __builtin_clz(leng);
            return min(stmin[j][L], stmin[j][RR - (1 << j) + 1]);
        };
        auto get_rmax = [&](int L, int RR) -> ll {
            int leng = RR - L + 1;
            int j = 31 - __builtin_clz(leng);
            return max(stmax[j][L], stmax[j][RR - (1 << j) + 1]);
        };
        // Prefix sum for Q
        vector<ll> prefq(n + 1, 0);
        for(int i = 1; i <= n; i++) {
            prefq[i] = prefq[i - 1] + Q[i - 1];
        }
        // Merge sort tree
        int tsz = 4 * (n + 1);
        vector<vector<ll>> treesort(tsz);
        vector<vector<ll>> treepref(tsz);
        // Recursive build
        auto build = [&](auto&& self, int node, int start, int end) -> void {
            if(start == end) {
                treesort[node] = {Q[start]};
                treepref[node] = {0LL, Q[start]};
                return;
            }
            int mid = (start + end) / 2;
            self(self, 2 * node, start, mid);
            self(self, 2 * node + 1, mid + 1, end);
            const vector<ll>& left = treesort[2 * node];
            const vector<ll>& right = treesort[2 * node + 1];
            treesort[node].resize(left.size() + right.size());
            merge(left.cbegin(), left.cend(), right.cbegin(), right.cend(), treesort[node].begin());
            treepref[node].resize(treesort[node].size() + 1);
            treepref[node][0] = 0;
            for(size_t jj = 1; jj <= treesort[node].size(); ++jj) {
                treepref[node][jj] = treepref[node][jj - 1] + treesort[node][jj - 1];
            }
        };
        build(build, 1, 0, n - 1);
        // Recursive query for {count_leq, sum_leq}
        using pll = pair<ll, ll>;
        auto qry = [&](auto&& self, int node, int start, int end, int l, int r, ll val) -> pll {
            if(r < start || end < l) return {0, 0};
            if(l <= start && end <= r) {
                const auto& sv = treesort[node];
                auto it = upper_bound(sv.cbegin(), sv.cend(), val);
                size_t pos = it - sv.cbegin();
                return {(ll)pos, treepref[node][pos]};
            }
            int mid = (start + end) / 2;
            pll p1 = self(self, 2 * node, start, mid, l, r, val);
            pll p2 = self(self, 2 * node + 1, mid + 1, end, l, r, val);
            return {p1.first + p2.first, p1.second + p2.second};
        };
        auto qcount_leq = [&](int L, int R, ll v) -> ll {
            if(v < 0) return 0;
            return qry(qry, 1, 0, n - 1, L, R, v).first;
        };
        auto qsum_leq = [&](int L, int R, ll v) -> ll {
            if(v < 0) return 0;
            return qry(qry, 1, 0, n - 1, L, R, v).second;
        };
        // Get median: smallest v s.t. count_leq(v) >= target_k
        auto get_med = [&](int L, int R) -> ll {
            int len_ = R - L + 1;
            int tk = len_ / 2 + 1;
            ll lo = 0, hi = 2000000000LL;
            while(lo < hi) {
                ll mval = lo + (hi - lo) / 2;
                if(qcount_leq(L, R, mval) >= (ll)tk) {
                    hi = mval;
                } else {
                    lo = mval + 1;
                }
            }
            return lo;
        };
        // Process queries
        int qs = queries.size();
        vector<ll> res(qs);
        for(int i = 0; i < qs; i++) {
            int li = queries[i][0];
            int ri = queries[i][1];
            ll rminv = get_rmin(li, ri);
            ll rmaxv = get_rmax(li, ri);
            if(rminv != rmaxv) {
                res[i] = -1;
                continue;
            }
            ll tots = prefq[ri + 1] - prefq[li];
            int len_ = ri - li + 1;
            ll medv = get_med(li, ri);
            ll cless = qcount_leq(li, ri, medv - 1);
            ll sless = qsum_leq(li, ri, medv - 1);
            ll cleq = qcount_leq(li, ri, medv);
            ll sleq = qsum_leq(li, ri, medv);
            ll cgreat = (ll)len_ - cleq;
            ll sgreat = tots - sleq;
            ll ops = sgreat - medv * cgreat + medv * cless - sless;
            res[i] = ops;
        }
        return res;
    }
};
# @lc code=end