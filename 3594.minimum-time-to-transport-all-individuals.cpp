#
# @lc app=leetcode id=3594 lang=cpp
#
# [3594] Minimum Time to Transport All Individuals
#

# @lc code=start
class Solution {
public:
    double minTime(int n, int k, int m, vector<int>& time, vector<double>& mul) {
        const double INF = 1e20;
        const double EPS = 1e-9;
        int N = 1 << n;
        int ALL = N - 1;
        int MS = 2 * m;
        vector<double> dp(N * MS, INF);
        auto getid = [&](int mask, int boat, int st) { return mask * MS + boat * m + st; };
        using P = pair<double, int>;
        priority_queue<P, vector<P>, greater<P>> pq;
        int start = getid(0, 0, 0);
        dp[start] = 0.0;
        pq.push({0.0, start});
        while (!pq.empty()) {
            auto [cost, idx] = pq.top(); pq.pop();
            if (cost > dp[idx] + EPS) continue;
            int mask = idx / MS;
            int rem = idx % MS;
            int boat = rem / m;
            int stage = rem % m;
            if (mask == ALL) return cost;
            int right_cnt = __builtin_popcount(mask);
            int left_cnt = n - right_cnt;
            // forward
            if (boat == 0 && left_cnt > 0) {
                vector<int> lefts;
                for (int i = 0; i < n; ++i) {
                    if ((mask & (1 << i)) == 0) lefts.push_back(i);
                }
                int nl = lefts.size();
                for (int s = 1; s < (1 << nl); ++s) {
                    int pc = __builtin_popcount(s);
                    if (pc > k) continue;
                    int maxt = 0;
                    int subm = 0;
                    for (int j = 0; j < nl; ++j) {
                        if (s & (1 << j)) {
                            int p = lefts[j];
                            maxt = max(maxt, time[p]);
                            subm |= (1 << p);
                        }
                    }
                    double dtime = static_cast<double>(maxt) * mul[stage];
                    int adv = static_cast<int>(floor(dtime));
                    int nstage = (stage + (adv % m)) % m;
                    int nmask = mask | subm;
                    double ncost = cost + dtime;
                    int nidx = getid(nmask, 1, nstage);
                    if (ncost < dp[nidx] - EPS) {
                        dp[nidx] = ncost;
                        pq.push({ncost, nidx});
                    }
                }
            }
            // return
            if (boat == 1 && left_cnt > 0 && right_cnt > 0) {
                for (int i = 0; i < n; ++i) {
                    if (mask & (1 << i)) {
                        double dtime = static_cast<double>(time[i]) * mul[stage];
                        int adv = static_cast<int>(floor(dtime));
                        int nstage = (stage + (adv % m)) % m;
                        int nmask = mask ^ (1 << i);
                        double ncost = cost + dtime;
                        int nidx = getid(nmask, 0, nstage);
                        if (ncost < dp[nidx] - EPS) {
                            dp[nidx] = ncost;
                            pq.push({ncost, nidx});
                        }
                    }
                }
            }
        }
        return -1.0;
    }
};
# @lc code=end