/*
 * @lc app=leetcode id=3373 lang=java
 *
 * [3373] Maximize the Number of Target Nodes After Connecting Trees II
 */

// @lc code=start
class Solution {
    public int[] maxTargetNodes(int[][] edges1, int[][] edges2) {
        int n = edges1.length + 1;
        int m = edges2.length + 1;
        List<Integer>[] g1 = new ArrayList[n];
        List<Integer>[] g2 = new ArrayList[m];
        for (int i = 0; i < n; ++i) g1[i] = new ArrayList<>();
        for (int i = 0; i < m; ++i) g2[i] = new ArrayList<>();
        for (int[] e : edges1) {
            g1[e[0]].add(e[1]);
            g1[e[1]].add(e[0]);
        }
        for (int[] e : edges2) {
            g2[e[0]].add(e[1]);
            g2[e[1]].add(e[0]);
        }
        int[] parity1 = new int[n];
        int[] parity2 = new int[m];
        Arrays.fill(parity1, -1);
        Arrays.fill(parity2, -1);
        bfsParity(g1, parity1, 0);
        bfsParity(g2, parity2, 0);
        int[] cnt1 = new int[2];
        int[] cnt2 = new int[2];
        for (int i = 0; i < n; ++i) cnt1[parity1[i]]++;
        for (int i = 0; i < m; ++i) cnt2[parity2[i]]++;
        int[] ans = new int[n];
        for (int i = 0; i < n; ++i) {
            int myParity = parity1[i];
            ans[i] = Math.max(
                cnt1[myParity] + cnt2[0],
                cnt1[1 - myParity] + cnt2[1]
            );
        }
        return ans;
    }
    private void bfsParity(List<Integer>[] g, int[] parity, int root) {
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(root);
        parity[root] = 0;
        while (!queue.isEmpty()) {
            int u = queue.poll();
            for (int v : g[u]) {
                if (parity[v] == -1) {
                    parity[v] = parity[u] ^ 1;
                    queue.offer(v);
                }
            }
        }
    }
}
// @lc code=end