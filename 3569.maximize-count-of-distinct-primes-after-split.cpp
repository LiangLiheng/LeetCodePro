#
# @lc app=leetcode id=3569 lang=cpp
#
# [3569] Maximize Count of Distinct Primes After Split
#

# @lc code=start
class Solution {
public:
    vector<int> maximumCount(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        const int MAXV = 100010;
        vector<bool> is_prime(MAXV, true);
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i * i < MAXV; ++i) {
            if (is_prime[i]) {
                for (int j = i * i; j < MAXV; j += i) {
                    is_prime[j] = false;
                }
            }
        }
        vector<set<int>> pos(MAXV);
        int D = 0;
        for (int i = 0; i < n; ++i) {
            int v = nums[i];
            if (v < MAXV && is_prime[v]) {
                auto& s = pos[v];
                size_t sz = s.size();
                s.insert(i);
                if (sz == 0) ++D;
            }
        }
        struct SegTree {
            int nn;
            vector<long long> tree, lazy;
            SegTree(int _n) : nn(_n), tree(4 * _n + 10, 0LL), lazy(4 * _n + 10, 0LL) {}
            void push(int node, int l, int r) {
                if (lazy[node] != 0) {
                    tree[node] += lazy[node];
                    if (l != r) {
                        lazy[2 * node] += lazy[node];
                        lazy[2 * node + 1] += lazy[node];
                    }
                    lazy[node] = 0;
                }
            }
            void range_add(int ql, int qr, long long val, int node, int l, int r) {
                push(node, l, r);
                if (ql > r || qr < l) return;
                if (ql <= l && r <= qr) {
                    lazy[node] += val;
                    push(node, l, r);
                    return;
                }
                int m = (l + r) / 2;
                range_add(ql, qr, val, 2 * node, l, m);
                range_add(ql, qr, val, 2 * node + 1, m + 1, r);
                tree[node] = max(tree[2 * node], tree[2 * node + 1]);
            }
            void range_add(int ql, int qr, long long val) {
                if (ql > qr) return;
                range_add(ql, qr, val, 1, 1, nn);
            }
            long long query_max() {
                push(1, 1, nn);
                return tree[1];
            }
        };
        SegTree st(n - 1);
        for (int p = 2; p < MAXV; ++p) {
            auto& s = pos[p];
            if (s.size() >= 2) {
                int mn = *s.begin();
                int mx = *s.rbegin();
                st.range_add(mn + 1, mx, 1LL);
            }
        }
        vector<int> ans;
        for (auto& q : queries) {
            int idx = q[0], nval = q[1];
            int oval = nums[idx];
            nums[idx] = nval;
            // handle old
            if (oval < MAXV && is_prime[oval]) {
                int p = oval;
                auto& s = pos[p];
                size_t osz = s.size();
                int omn = osz ? *s.begin() : -1;
                int omx = osz ? *s.rbegin() : -1;
                bool wcontrib = (osz >= 2);
                s.erase(idx);
                size_t nsz = s.size();
                int nmn = (nsz >= 2 ? *s.begin() : -1);
                int nmx = (nsz >= 2 ? *s.rbegin() : -1);
                bool ncontrib = (nsz >= 2);
                if (wcontrib) {
                    st.range_add(omn + 1, omx, -1LL);
                }
                if (ncontrib) {
                    st.range_add(nmn + 1, nmx, 1LL);
                }
                if (osz >= 1 && nsz == 0) --D;
            }
            // handle new
            if (nval < MAXV && is_prime[nval]) {
                int p = nval;
                auto& s = pos[p];
                size_t osz = s.size();
                int omn = osz ? *s.begin() : -1;
                int omx = osz ? *s.rbegin() : -1;
                bool wcontrib = (osz >= 2);
                s.insert(idx);
                size_t nsz = s.size();
                int nmn = *s.begin();
                int nmx = *s.rbegin();
                bool ncontrib = (nsz >= 2);
                if (wcontrib) {
                    st.range_add(omn + 1, omx, -1LL);
                }
                if (ncontrib) {
                    st.range_add(nmn + 1, nmx, 1LL);
                }
                if (osz == 0) ++D;
            }
            long long mstrad = st.query_max();
            ans.push_back(D + (int)mstrad);
        }
        return ans;
    }
};
# @lc code=end