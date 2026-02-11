#
# @lc app=leetcode id=3515 lang=java
#
# [3515] Shortest Path in a Weighted Tree
#

# @lc code=start
class Solution {
    static class FenwickTree {
        int[] tree;
        FenwickTree(int n) {
            tree = new int[n + 2];
        }
        void update(int idx, int val) {
            while (idx < tree.length) {
                tree[idx] += val;
                idx += idx & -idx;
            }
        }
        int query(int idx) {
            int sum = 0;
            while (idx > 0) {
                sum += tree[idx];
                idx -= idx & -idx;
            }
            return sum;
        }
    }

    private void dfs(int root, java.util.List<Integer>[] children, int[] tin, int[] tout, int[] timer) {
        java.util.Stack<int[]> stack = new java.util.Stack<>();
        stack.push(new int[]{root, 0});
        while (!stack.isEmpty()) {
            int[] curr = stack.peek();
            int u = curr[0];
            int ci = curr[1];
            if (ci == 0) {
                tin[u] = ++timer[0];
            }
            if (ci < children[u].size()) {
                int v = children[u].get(ci);
                curr[1]++;
                stack.push(new int[]{v, 0});
            } else {
                tout[u] = timer[0];
                stack.pop();
            }
        }
    }

    public int[] treeQueries(int n, int[][] edges, int[][] queries) {
        @SuppressWarnings("unchecked")
        java.util.List<int[]>[] adj = new java.util.List[n + 1];
        for (int i = 0; i <= n; ++i) {
            adj[i] = new java.util.ArrayList<>();
        }
        for (int[] e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].add(new int[]{v, w});
            adj[v].add(new int[]{u, w});
        }

        int[] parent = new int[n + 1];
        int[] weight = new int[n + 1];
        boolean[] visited = new boolean[n + 1];
        @SuppressWarnings("unchecked")
        java.util.List<Integer>[] children = new java.util.List[n + 1];
        for (int i = 0; i <= n; ++i) {
            children[i] = new java.util.ArrayList<>();
        }
        java.util.Queue<Integer> queue = new java.util.LinkedList<>();
        queue.offer(1);
        visited[1] = true;
        parent[1] = -1;
        while (!queue.isEmpty()) {
            int u = queue.poll();
            for (int[] ne : adj[u]) {
                int v = ne[0];
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    weight[v] = ne[1];
                    children[u].add(v);
                    queue.offer(v);
                }
            }
        }

        int[] tin = new int[n + 1];
        int[] tout = new int[n + 1];
        int[] timerr = {0};
        dfs(1, children, tin, tout, timerr);

        FenwickTree ft = new FenwickTree(n + 1);
        for (int v = 2; v <= n; ++v) {
            int w = weight[v];
            ft.update(tin[v], w);
            ft.update(tout[v] + 1, -w);
        }

        java.util.List<Integer> ans = new java.util.ArrayList<>();
        for (int[] q : queries) {
            if (q[0] == 1) {
                int u = q[1], v = q[2], nw = q[3];
                int child = (parent[v] == u ? v : u);
                int oldw = weight[child];
                int delta = nw - oldw;
                weight[child] = nw;
                ft.update(tin[child], delta);
                ft.update(tout[child] + 1, -delta);
            } else {
                int x = q[1];
                ans.add(ft.query(tin[x]));
            }
        }

        int[] result = new int[ans.size()];
        for (int i = 0; i < ans.size(); ++i) {
            result[i] = ans.get(i);
        }
        return result;
    }
}
# @lc code=end