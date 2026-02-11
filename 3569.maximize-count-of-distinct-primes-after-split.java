#
# @lc app=leetcode id=3569 lang=java
#
# [3569] Maximize Count of Distinct Primes After Split
#

# @lc code=start
class Solution {
    public static class SegTree {
        private int n;
        private int[] tree;
        private int[] lazy;

        public SegTree(int _n) {
            n = _n;
            tree = new int[4 * (n + 1)];
            lazy = new int[4 * (n + 1)];
        }

        private void push(int node, int s, int e) {
            if (lazy[node] != 0) {
                tree[node] += lazy[node];
                if (s != e) {
                    lazy[2 * node] += lazy[node];
                    lazy[2 * node + 1] += lazy[node];
                }
                lazy[node] = 0;
            }
        }

        public void update(int l, int r, int val) {
            update(1, 1, n, l, r, val);
        }

        private void update(int node, int s, int e, int l, int r, int val) {
            push(node, s, e);
            if (s > e || s > r || e < l) return;
            if (l <= s && e <= r) {
                lazy[node] += val;
                push(node, s, e);
                return;
            }
            int m = (s + e) / 2;
            update(2 * node, s, m, l, r, val);
            update(2 * node + 1, m + 1, e, l, r, val);
            tree[node] = Math.max(tree[2 * node], tree[2 * node + 1]);
        }

        public int queryMax() {
            push(1, 1, n);
            return tree[1];
        }
    }

    public int[] maximumCount(int[] nums, int[][] queries) {
        int N = nums.length;
        final int MAXV = 100000;
        boolean[] isPrime = new boolean[MAXV + 10];
        java.util.Arrays.fill(isPrime, true);
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i * i <= MAXV; ++i) {
            if (isPrime[i]) {
                for (int j = i * i; j <= MAXV; j += i) {
                    isPrime[j] = false;
                }
            }
        }

        java.util.Map<Integer, java.util.TreeSet<Integer>> pos = new java.util.HashMap<>();
        for (int i = 0; i < N; ++i) {
            int v = nums[i];
            if (v <= MAXV && isPrime[v]) {
                pos.computeIfAbsent(v, k -> new java.util.TreeSet<>()).add(i);
            }
        }
        int totalDistinct = pos.size();

        SegTree st = new SegTree(N - 1);
        for (java.util.Map.Entry<Integer, java.util.TreeSet<Integer>> entry : pos.entrySet()) {
            java.util.TreeSet<Integer> positions = entry.getValue();
            if (positions.size() < 2) continue;
            int minp = positions.first();
            int maxp = positions.last();
            int L = Math.max(1, minp + 1);
            int R = Math.min(N - 1, maxp);
            if (L <= R) {
                st.update(L, R, 1);
            }
        }

        int[] ans = new int[queries.length];
        for (int qi = 0; qi < queries.length; ++qi) {
            int idx = queries[qi][0];
            int newVal = queries[qi][1];
            int oldVal = nums[idx];
            nums[idx] = newVal;

            // Remove oldVal
            if (oldVal <= MAXV && isPrime[oldVal]) {
                java.util.TreeSet<Integer> positions = pos.get(oldVal);
                int pre_size = positions.size();
                if (pre_size >= 2) {
                    int minp = positions.first();
                    int maxp = positions.last();
                    int L = Math.max(1, minp + 1);
                    int R = Math.min(N - 1, maxp);
                    if (L <= R) {
                        st.update(L, R, -1);
                    }
                }
                positions.remove(idx);
                if (positions.isEmpty()) {
                    pos.remove(oldVal);
                    totalDistinct--;
                } else {
                    if (positions.size() >= 2) {
                        int minp = positions.first();
                        int maxp = positions.last();
                        int L = Math.max(1, minp + 1);
                        int R = Math.min(N - 1, maxp);
                        if (L <= R) {
                            st.update(L, R, 1);
                        }
                    }
                }
            }

            // Add newVal
            if (newVal <= MAXV && isPrime[newVal]) {
                java.util.TreeSet<Integer> positions = pos.computeIfAbsent(newVal, k -> new java.util.TreeSet<>()));
                int pre_size = positions.size();
                if (pre_size >= 2) {
                    int minp = positions.first();
                    int maxp = positions.last();
                    int L = Math.max(1, minp + 1);
                    int R = Math.min(N - 1, maxp);
                    if (L <= R) {
                        st.update(L, R, -1);
                    }
                }
                positions.add(idx);
                if (positions.size() >= 2) {
                    int minp = positions.first();
                    int maxp = positions.last();
                    int L = Math.max(1, minp + 1);
                    int R = Math.min(N - 1, maxp);
                    if (L <= R) {
                        st.update(L, R, 1);
                    }
                }
                if (pre_size == 0) {
                    totalDistinct++;
                }
            }

            int maxCover = st.queryMax();
            ans[qi] = totalDistinct + maxCover;
        }
        return ans;
    }
}
# @lc code=end