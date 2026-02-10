#
# @lc app=leetcode id=3525 lang=cpp
#
# [3525] Find X Value of Array II
#

# @lc code=start
class Solution {
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        int n = nums.size();
        struct Node {
            int total;
            int cnt[6];
            Node() : total(1) {
                memset(cnt, 0, sizeof(cnt));
            }
        };
        vector<Node> tree(4 * n + 10);
        auto merg = [&](const Node& a, const Node& b, int kk) -> Node {
            Node res;
            res.total = (1LL * a.total * b.total % kk + kk) % kk;
            for (int i = 0; i < kk; ++i) {
                res.cnt[i] = a.cnt[i];
            }
            for (int rp = 0; rp < kk; ++rp) {
                int comb = (1LL * a.total * rp % kk + kk) % kk;
                res.cnt[comb] += b.cnt[rp];
            }
            return res;
        };
        std::function<void(int, int, int)> buildf = [&](int node, int start, int end) {
            if (start == end) {
                int m = nums[start] % k;
                tree[node].total = m;
                memset(tree[node].cnt, 0, sizeof(tree[node].cnt));
                tree[node].cnt[m] = 1;
                return;
            }
            int mid = (start + end) / 2;
            buildf(2 * node, start, mid);
            buildf(2 * node + 1, mid + 1, end);
            tree[node] = merg(tree[2 * node], tree[2 * node + 1], k);
        };
        std::function<void(int, int, int, int, int)> updatef = [&](int node, int start, int end, int idx, int nval) {
            if (start == end) {
                int m = nval % k;
                tree[node].total = m;
                memset(tree[node].cnt, 0, sizeof(tree[node].cnt));
                tree[node].cnt[m] = 1;
                return;
            }
            int mid = (start + end) / 2;
            if (idx <= mid) {
                updatef(2 * node, start, mid, idx, nval);
            } else {
                updatef(2 * node + 1, mid + 1, end, idx, nval);
            }
            tree[node] = merg(tree[2 * node], tree[2 * node + 1], k);
        };
        std::function<Node(int, int, int, int, int, int)> queryf = [&](int node, int start, int end, int l, int r, int kk) -> Node {
            if (r < start || end < l) {
                return Node();
            }
            if (l <= start && end <= r) {
                return tree[node];
            }
            int mid = (start + end) / 2;
            Node p1 = queryf(2 * node, start, mid, l, r, kk);
            Node p2 = queryf(2 * node + 1, mid + 1, end, l, r, kk);
            return merg(p1, p2, kk);
        };
        buildf(1, 0, n - 1);
        vector<int> result;
        for (const auto& q : queries) {
            int indexi = q[0];
            int valuei = q[1];
            int starti = q[2];
            int xi = q[3];
            nums[indexi] = valuei;
            updatef(1, 0, n - 1, indexi, valuei);
            Node qres = queryf(1, 0, n - 1, starti, n - 1, k);
            result.push_back(qres.cnt[xi]);
        }
        return result;
    }
};
# @lc code=end