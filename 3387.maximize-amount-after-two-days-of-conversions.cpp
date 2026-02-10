#
# @lc app=leetcode id=3387 lang=cpp
#
# [3387] Maximize Amount After Two Days of Conversions
#

# @lc code=start
class Solution {
public:
double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2) {
    set<string> curr_set;
    curr_set.insert(initialCurrency);
    for(const auto& p : pairs1) {
        curr_set.insert(p[0]);
        curr_set.insert(p[1]);
    }
    for(const auto& p : pairs2) {
        curr_set.insert(p[0]);
        curr_set.insert(p[1]);
    }
    vector<string> currencies(curr_set.begin(), curr_set.end());
    int N = currencies.size();
    unordered_map<string, int> cid;
    for(int i = 0; i < N; ++i) {
        cid[currencies[i]] = i;
    }
    int s = cid[initialCurrency];
    vector<vector<double>> dist1(N, vector<double>(N, 0.0));
    for(int i = 0; i < N; ++i) dist1[i][i] = 1.0;
    for(size_t j = 0; j < pairs1.size(); ++j) {
        int u = cid[pairs1[j][0]];
        int v = cid[pairs1[j][1]];
        double r = rates1[j];
        dist1[u][v] = max(dist1[u][v], r);
        dist1[v][u] = max(dist1[v][u], 1.0 / r);
    }
    // Floyd-Warshall for day1
    for(int k = 0; k < N; ++k)
        for(int i = 0; i < N; ++i)
            for(int jj = 0; jj < N; ++jj) {
                if (dist1[i][k] > 0.0 && dist1[k][jj] > 0.0) {
                    dist1[i][jj] = max(dist1[i][jj], dist1[i][k] * dist1[k][jj]);
                }
            }
    vector<vector<double>> dist2(N, vector<double>(N, 0.0));
    for(int i = 0; i < N; ++i) dist2[i][i] = 1.0;
    for(size_t j = 0; j < pairs2.size(); ++j) {
        int u = cid[pairs2[j][0]];
        int v = cid[pairs2[j][1]];
        double r = rates2[j];
        dist2[u][v] = max(dist2[u][v], r);
        dist2[v][u] = max(dist2[v][u], 1.0 / r);
    }
    // Floyd-Warshall for day2
    for(int k = 0; k < N; ++k)
        for(int i = 0; i < N; ++i)
            for(int jj = 0; jj < N; ++jj) {
                if (dist2[i][k] > 0.0 && dist2[k][jj] > 0.0) {
                    dist2[i][jj] = max(dist2[i][jj], dist2[i][k] * dist2[k][jj]);
                }
            }
    double ans = 1.0;
    for(int c = 0; c < N; ++c) {
        double to_c = dist1[s][c];
        if (to_c > 0.0) {
            double back = dist2[c][s];
            if (back > 0.0) {
                ans = max(ans, to_c * back);
            }
        }
    }
    return ans;
}
};
# @lc code=end