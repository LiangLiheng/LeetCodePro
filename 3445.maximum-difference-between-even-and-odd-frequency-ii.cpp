#
# @lc app=leetcode id=3445 lang=cpp
#
# [3445] Maximum Difference Between Even and Odd Frequency II
#

# @lc code=start
class Solution {
public:
    struct SegTree {
        int n;
        vector<int> tree;
        SegTree(int _n) : n(_n), tree(4*(_n + 1), 2000000007) {}
        void update(int idx, int val) { update_util(1, 0, n, idx, val); }
        int query(int left, int right) {
            if (left > right) return 2000000007;
            return query_util(1, 0, n, left, right);
        }
    private:
        void update_util(int node, int start, int end, int idx, int val) {
            if (start == end) {
                tree[node] = val;
                return;
            }
            int mid = (start + end) / 2;
            if (idx <= mid)
                update_util(2 * node, start, mid, idx, val);
            else
                update_util(2 * node + 1, mid + 1, end, idx, val);
            tree[node] = min(tree[2 * node], tree[2 * node + 1]);
        }
        int query_util(int node, int start, int end, int left, int right) {
            if (right < start || end < left) return 2000000007;
            if (left <= start && end <= right) return tree[node];
            int mid = (start + end) / 2;
            int p1 = query_util(2 * node, start, mid, left, right);
            int p2 = query_util(2 * node + 1, mid + 1, end, left, right);
            return min(p1, p2);
        }
    };
    int maxDifference(string s, int k) {
        int n = s.length();
        vector<vector<int>> prefix(5, vector<int>(n + 1, 0));
        vector<vector<int>> positions(5);
        for (int i = 0; i < n; ++i) {
            int c = s[i] - '0';
            positions[c].push_back(i);
            for (int ch = 0; ch < 5; ++ch) {
                prefix[ch][i + 1] = prefix[ch][i] + (ch == c);
            }
        }
        int ans = INT_MIN / 2;
        for (int a = 0; a < 5; ++a) {
            for (int b = 0; b < 5; ++b) {
                if (a == b) continue;
                vector<int> val(n + 1), pa(n + 1), pb(n + 1);
                for (int i = 0; i <= n; ++i) {
                    val[i] = prefix[a][i] - prefix[b][i];
                    pa[i] = prefix[a][i] & 1;
                    pb[i] = prefix[b][i] & 1;
                }
                vector<SegTree> sts(4, SegTree(n));
                for (int i = 0; i <= n; ++i) {
                    if (i >= k) {
                        int cnt = prefix[b][i];
                        if (cnt >= 2) {
                            size_t idx = static_cast<size_t>(cnt - 2);
                            if (idx < positions[b].size()) {
                                int max_lb = positions[b][idx];
                                int u1 = i - k;
                                int u = min(u1, max_lb);
                                if (u >= 0) {
                                    int tpa = pa[i] ^ 1;
                                    int tpb = pb[i];
                                    int st_idx = tpa * 2 + tpb;
                                    int minv = sts[st_idx].query(0, u);
                                    if (minv < 1000000000) {
                                        ans = max(ans, val[i] - minv);
                                    }
                                }
                            }
                        }
                    }
                    int st_idx = pa[i] * 2 + pb[i];
                    sts[st_idx].update(i, val[i]);
                }
            }
        }
        return (ans == INT_MIN / 2) ? -1 : ans;
    }
};
# @lc code=end