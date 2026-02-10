#
# @lc app=leetcode id=3538 lang=cpp
#
# [3538] Merge Operations for Minimum Travel Time
#
# @lc code=start
class Solution {
public:
    int minTravelTime(int l, int n, int k, vector<int>& position, vector<int>& time) {
        const long long INF = 4e18;
        vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(k + 1, vector<long long>(101, INF)));
        vector<long long> pref(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + time[i];
        }
        if (time[0] <= 100) dp[0][0][time[0]] = 0;
        for (int i = 1; i < n; ++i) {
            for (int p = 0; p < i; ++p) {
                int delta = i - p - 1;
                if (delta > k) continue;
                long long gsum = pref[i + 1] - pref[p + 1];
                int ns = (int)gsum;
                if (ns > 100) continue;
                for (int j = 0; j <= k - delta; ++j) {
                    for (int s = 0; s <= 100; ++s) {
                        long long val = dp[p][j][s];
                        if (val == INF) continue;
                        long long addc = (long long)(position[i] - position[p]) * s;
                        long long nc = val + addc;
                        int nj = j + delta;
                        if (nc < dp[i][nj][ns]) {
                            dp[i][nj][ns] = nc;
                        }
                    }
                }
            }
        }
        long long ans = INF;
        for (int s = 0; s <= 100; ++s) {
            ans = min(ans, dp[n - 1][k][s]);
        }
        return (int)ans;
    }
};
# @lc code=end