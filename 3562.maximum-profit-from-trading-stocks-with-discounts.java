class Solution {
    public int maxProfit(int n, int[] present, int[] future, int[][] hierarchy, int budget) {
        List<Integer>[] tree = new List[n];
        for (int i = 0; i < n; i++) tree[i] = new ArrayList<>();
        for (int[] edge : hierarchy) tree[edge[0] - 1].add(edge[1] - 1);
        int[][][] dp = new int[n][2][budget + 1];
        dfs(0, tree, present, future, dp, budget);
        int ans = 0;
        for (int b = 0; b <= budget; b++) {
            ans = Math.max(ans, Math.max(dp[0][0][b], dp[0][1][b]));
        }
        return ans;
    }
    private void dfs(int u, List<Integer>[] tree, int[] present, int[] future, int[][][] dp, int budget) {
        // dp[u][0][b]: max profit at u with budget b, boss did NOT buy
        // dp[u][1][b]: max profit at u with budget b, boss DID buy
        // Initialize for leaf: both states as 0 (skip action)
        for (int state = 0; state < 2; ++state) {
            for (int b = 0; b <= budget; ++b) dp[u][state][b] = 0;
        }
        // State 0: boss did NOT buy, can buy at present[u]
        for (int b = present[u]; b <= budget; ++b) {
            dp[u][0][b] = Math.max(dp[u][0][b], future[u] - present[u]);
        }
        // State 1: boss DID buy, can buy at floor(present[u]/2)
        int disc = present[u] / 2;
        for (int b = disc; b <= budget; ++b) {
            dp[u][1][b] = Math.max(dp[u][1][b], future[u] - disc);
        }
        // Always consider skip action: dp[u][state][b] = 0 is already set
        for (int v : tree[u]) {
            dfs(v, tree, present, future, dp, budget);
            int[][] ndp = new int[2][budget + 1];
            for (int state = 0; state < 2; ++state) {
                for (int b = 0; b <= budget; ++b) {
                    // For each way to split b budget between u and v
                    for (int x = 0; x <= b; ++x) {
                        // For skip or buy at u, combine with skip or buy at child
                        ndp[state][b] = Math.max(ndp[state][b], dp[u][state][b - x] + dp[v][state][x]);
                    }
                }
            }
            for (int state = 0; state < 2; ++state) {
                System.arraycopy(ndp[state], 0, dp[u][state], 0, budget + 1);
            }
        }
    }
}