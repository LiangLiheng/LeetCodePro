#
# @lc app=leetcode id=3786 lang=java
#
# [3786] Total Sum of Interaction Cost in Tree Groups
#

# @lc code=start
class Solution {
    public long interactionCosts(int n, int[][] edges, int[] group) {
        java.util.List<java.util.List<java.util.Integer>> adj = new java.util.ArrayList<>();
        for (int i = 0; i < n; i++) {
            adj.add(new java.util.ArrayList<>());
        }
        for (int[] e : edges) {
            int u = e[0], v = e[1];
            adj.get(u).add(v);
            adj.get(v).add(u);
        }
        int[] totals = new int[21];
        for (int i = 0; i < n; i++) {
            totals[group[i]]++;
        }
        java.util.List<java.util.List<java.util.Integer>> children = new java.util.ArrayList<>();
        for (int i = 0; i < n; i++) {
            children.add(new java.util.ArrayList<>());
        }
        int[] par = new int[n];
        java.util.Arrays.fill(par, -1);
        java.util.Queue<java.util.Integer> q = new java.util.LinkedList<>();
        q.offer(0);
        while (!q.isEmpty()) {
            int u = q.poll();
            for (int v : adj.get(u)) {
                if (v != par[u]) {
                    par[v] = u;
                    children.get(u).add(v);
                    q.offer(v);
                }
            }
        }
        int[][] sub = new int[n][21];
        int[] pending = new int[n];
        java.util.Queue<java.util.Integer> qq = new java.util.LinkedList<>();
        for (int i = 0; i < n; i++) {
            pending[i] = children.get(i).size();
            if (pending[i] == 0) {
                qq.offer(i);
            }
        }
        long ans = 0;
        while (!qq.isEmpty()) {
            int u = qq.poll();
            sub[u][group[u]] = 1;
            for (int v : children.get(u)) {
                for (int g = 1; g <= 20; g++) {
                    sub[u][g] += sub[v][g];
                }
            }
            if (par[u] != -1) {
                for (int g = 1; g <= 20; g++) {
                    long sa = sub[u][g];
                    long sb = totals[g] - sa;
                    ans += sa * sb;
                }
            }
            if (par[u] != -1) {
                pending[par[u]]--;
                if (pending[par[u]] == 0) {
                    qq.offer(par[u]);
                }
            }
        }
        return ans;
    }
}
# @lc code=end