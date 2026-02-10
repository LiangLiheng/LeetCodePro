#
# @lc app=leetcode id=3470 lang=cpp
#
# [3470] Permutations IV
#

# @lc code=start
class Solution {
public:
    vector<int> permute(int n, long long k) {
        int no = (n + 1) / 2;
        int ne = n / 2;
        const long long INF = 9223372036854775807LL;
        vector<vector<vector<long long>>> dp(no + 1, vector<vector<long long>>(ne + 1, vector<long long>(2, 0LL)));
        for (int ro = 0; ro <= no; ++ro) {
            for (int re = 0; re <= ne; ++re) {
                if (ro == 0 && re == 0) {
                    dp[0][0][0] = 1;
                    dp[0][0][1] = 1;
                    continue;
                }
                // dp[ro][re][0]: next odd
                if (ro > 0) {
                    long long sub = dp[ro - 1][re][1];
                    if (sub > INF / ro) {
                        dp[ro][re][0] = INF;
                    } else {
                        dp[ro][re][0] = (long long)ro * sub;
                    }
                }
                // dp[ro][re][1]: next even
                if (re > 0) {
                    long long sub = dp[ro][re - 1][0];
                    if (sub > INF / re) {
                        dp[ro][re][1] = INF;
                    } else {
                        dp[ro][re][1] = (long long)re * sub;
                    }
                }
            }
        }
        long long cnt_start_odd = dp[no][ne][0];
        long long cnt_start_even = dp[no][ne][1];
        bool enough = cnt_start_odd >= k || cnt_start_even >= k;
        if (!enough) {
            if (cnt_start_odd == INF || cnt_start_even == INF) {
                enough = true;
            } else {
                long long max_ll = 9223372036854775807LL;
                if (cnt_start_odd > max_ll - cnt_start_even) {
                    enough = true;
                } else {
                    long long total = cnt_start_odd + cnt_start_even;
                    if (total >= k) enough = true;
                }
            }
        }
        if (!enough) {
            return {};
        }
        set<int> avail_o, avail_e;
        for (int i = 1; i <= n; ++i) {
            if (i % 2 == 1) avail_o.insert(i);
            else avail_e.insert(i);
        }
        vector<int> result;
        int rem_o = no;
        int rem_e = ne;
        int prev_p = -1;
        long long rem_k = k;
        for (int pos = 0; pos < n; ++pos) {
            vector<int> cands;
            auto add_cands = [&](const set<int>& s) {
                for (int x : s) cands.push_back(x);
            };
            if (prev_p == -1) {
                add_cands(avail_o);
                add_cands(avail_e);
            } else {
                int req_p = 1 - prev_p;
                if (req_p == 0) {
                    add_cands(avail_o);
                } else {
                    add_cands(avail_e);
                }
            }
            sort(cands.begin(), cands.end());
            bool found = false;
            for (int cand : cands) {
                int this_p = (cand % 2 == 0 ? 1 : 0);
                int new_ro = rem_o - (this_p == 0 ? 1 : 0);
                int new_re = rem_e - (this_p == 1 ? 1 : 0);
                int next_p = 1 - this_p;
                long long branch = dp[new_ro][new_re][next_p];
                if (branch >= rem_k) {
                    result.push_back(cand);
                    if (this_p == 0) {
                        avail_o.erase(cand);
                    } else {
                        avail_e.erase(cand);
                    }
                    rem_o = new_ro;
                    rem_e = new_re;
                    prev_p = this_p;
                    found = true;
                    break;
                } else {
                    rem_k -= branch;
                }
            }
            if (!found) {
                return {};
            }
        }
        return result;
    }
};
# @lc code=end