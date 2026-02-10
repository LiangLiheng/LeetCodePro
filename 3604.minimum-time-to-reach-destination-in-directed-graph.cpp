#
# @lc app=leetcode id=3604 lang=cpp
#
# [3604] Minimum Time to Reach Destination in Directed Graph
#

# @lc code=start
class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges) {
        struct Edge {
            int to, start, end;
        };
        vector<vector<Edge>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2], e[3]});
        }
        using ll = long long;
        vector<ll> dist(n, LLONG_MAX / 2);
        dist[0] = 0;
        using pli = pair<ll, int>;
        priority_queue<pli, vector<pli>, greater<pli>> pq;
        pq.push({0, 0});
        while (!pq.empty()) {
            ll t = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            if (t > dist[u]) continue;
            for (const auto& ed : adj[u]) {
                ll dep = max(t, (ll)ed.start);
                if (dep <= ed.end) {
                    ll arr = dep + 1;
                    if (arr < dist[ed.to]) {
                        dist[ed.to] = arr;
                        pq.push({arr, ed.to});
                    }
                }
            }
        }
        ll res = dist[n - 1];
        return res == LLONG_MAX / 2 ? -1 : (int)res;
    }
};
# @lc code=end