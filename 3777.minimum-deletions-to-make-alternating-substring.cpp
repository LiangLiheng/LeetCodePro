#
# @lc app=leetcode id=3777 lang=cpp
#
# [3777] Minimum Deletions to Make Alternating Substring
#

# @lc code=start
class Solution {
public:
    vector<int> minDeletions(string s, vector<vector<int>>& queries) {
        struct Node {
            int aa = 0, ab = 0, ba = 0, bb = 0;
            int get_max() const {
                int mx = std::max(aa, ab);
                mx = std::max(mx, ba);
                mx = std::max(mx, bb);
                return mx;
            }
        };
        auto merge = [&](const Node& l, const Node& r) -> Node {
            Node res;
            // aa: start A end A
            res.aa = std::max(l.aa, r.aa);
            if (l.aa > 0 && r.ba > 0) res.aa = std::max(res.aa, l.aa + r.ba);
            if (l.ab > 0 && r.aa > 0) res.aa = std::max(res.aa, l.ab + r.aa);
            // ab: start A end B
            res.ab = std::max(l.ab, r.ab);
            if (l.aa > 0 && r.bb > 0) res.ab = std::max(res.ab, l.aa + r.bb);
            if (l.ab > 0 && r.ab > 0) res.ab = std::max(res.ab, l.ab + r.ab);
            // ba: start B end A
            res.ba = std::max(l.ba, r.ba);
            if (l.ba > 0 && r.ba > 0) res.ba = std::max(res.ba, l.ba + r.ba);
            if (l.bb > 0 && r.aa > 0) res.ba = std::max(res.ba, l.bb + r.aa);
            // bb: start B end B
            res.bb = std::max(l.bb, r.bb);
            if (l.ba > 0 && r.bb > 0) res.bb = std::max(res.bb, l.ba + r.bb);
            if (l.bb > 0 && r.ab > 0) res.bb = std::max(res.bb, l.bb + r.ab);
            return res;
        };
        int n = s.length();
        if (n == 0) return {};
        vector<Node> tree(4 * (n + 1));
        auto build = [&](auto&& self, int v, int tl, int tr) -> void {
            if (tl == tr) {
                char c = s[tl];
                if (c == 'A') tree[v].aa = 1;
                else tree[v].bb = 1;
                return;
            }
            int tm = (tl + tr) / 2;
            self(self, 2 * v, tl, tm);
            self(self, 2 * v + 1, tm + 1, tr);
            tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
        };
        build(build, 1, 0, n - 1);
        auto upd = [&](auto&& self, int v, int tl, int tr, int pos, char c) -> void {
            if (tl == tr) {
                tree[v].aa = tree[v].ab = tree[v].ba = tree[v].bb = 0;
                if (c == 'A') tree[v].aa = 1;
                else tree[v].bb = 1;
                return;
            }
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                self(self, 2 * v, tl, tm, pos, c);
            else
                self(self, 2 * v + 1, tm + 1, tr, pos, c);
            tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
        };
        auto qry = [&](auto&& self, int v, int tl, int tr, int l, int r) -> Node {
            if (l > r) return Node{0, 0, 0, 0};
            if (tl == l && tr == r) return tree[v];
            int tm = (tl + tr) / 2;
            Node p1{0, 0, 0, 0};
            Node p2{0, 0, 0, 0};
            if (l <= tm) p1 = self(self, 2 * v, tl, tm, l, std::min(r, tm));
            if (r >= tm + 1) p2 = self(self, 2 * v + 1, tm + 1, tr, std::max(l, tm + 1), r);
            if (l > tm) return p2;
            if (r < tm + 1) return p1;
            return merge(p1, p2);
        };
        vector<int> answer;
        for (const auto& q : queries) {
            if (q[0] == 1) {
                int j = q[1];
                s[j] = (s[j] == 'A' ? 'B' : 'A');
                upd(upd, 1, 0, n - 1, j, s[j]);
            } else {
                int l = q[1], r = q[2];
                Node resn = qry(qry, 1, 0, n - 1, l, r);
                int keep = resn.get_max();
                answer.push_back((r - l + 1) - keep);
            }
        }
        return answer;
    }
};
# @lc code=end