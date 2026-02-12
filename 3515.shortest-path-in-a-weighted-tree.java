import java.util.*;

class Solution {
    public int[] treeQueries(int n, int[][] edges, int[][] queries) {
        Map<Integer, List<int[]>> tree = new HashMap<>();
        Map<Long, Integer> edgeIdx = new HashMap<>();
        for (int i = 1; i <= n; ++i) tree.put(i, new ArrayList<>());
        for (int i = 0; i < edges.length; ++i) {
            int u = edges[i][0], v = edges[i][1], w = edges[i][2];
            tree.get(u).add(new int[]{v, w, i});
            tree.get(v).add(new int[]{u, w, i});
            edgeIdx.put(hash(u, v), i);
            edgeIdx.put(hash(v, u), i);
        }
        int[] parent = new int[n + 1];
        int[] in = new int[n + 1];
        int[] out = new int[n + 1];
        int[] time = new int[1];
        dfs(1, 0, tree, parent, in, out, time);
        BIT bit = new BIT(n + 2);
        for (int i = 2; i <= n; ++i) {
            int eidx = edgeIdx.get(hash(parent[i], i));
            int w = 0;
            for (int[] nei : tree.get(parent[i])) {
                if (nei[0] == i) { w = nei[1]; break; }
            }
            bit.add(in[i], w);
            bit.add(out[i], -w);
        }
        List<Integer> ans = new ArrayList<>();
        for (int[] q : queries) {
            if (q[0] == 1) {
                int u = q[1], v = q[2], nw = q[3];
                int node = parent[u] == v ? u : v;
                int oldw = bit.query(in[node]) - bit.query(in[node] - 1);
                bit.add(in[node], nw - oldw);
                bit.add(out[node], oldw - nw);
            } else {
                int x = q[1];
                int d = bit.query(in[x]);
                ans.add(d);
            }
        }
        int[] res = new int[ans.size()];
        for (int i = 0; i < ans.size(); ++i) res[i] = ans.get(i);
        return res;
    }
    private static long hash(int u, int v) {
        return ((long)u << 32) | v;
    }
    private static void dfs(int u, int p, Map<Integer, List<int[]>> tree, int[] parent, int[] in, int[] out, int[] time) {
        parent[u] = p;
        in[u] = ++time[0];
        for (int[] nei : tree.get(u)) {
            int v = nei[0];
            if (v != p) {
                dfs(v, u, tree, parent, in, out, time);
            }
        }
        out[u] = ++time[0];
    }
    static class BIT {
        int[] tree;
        public BIT(int n) {
            tree = new int[n + 2];
        }
        public void add(int i, int v) {
            while (i < tree.length) { tree[i] += v; i += i & -i; }
        }
        public int query(int i) {
            int res = 0;
            while (i > 0) { res += tree[i]; i -= i & -i; }
            return res;
        }
    }
}