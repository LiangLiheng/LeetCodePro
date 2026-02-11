#
# @lc app=leetcode id=3562 lang=java
#
# [3562] Maximum Profit from Trading Stocks with Discounts
#

# @lc code=start
import java.util.*;

class Solution {
    private static final int MAXN = 165;
    private static final int MAXB = 165;
    private static final int NEG_INF = -1000000000;

    int[][][][] dp;
    List<Integer>[] ch;
    int[] pre, fut;
    int B;

    public int maxProfit(int n, int[] present, int[] future, int[][] hierarchy, int budget) {
        ch = new ArrayList[n + 1];
        for (int i = 0; i <= n; i++) {
            ch[i] = new ArrayList<Integer>();
        }
        for (int[] h : hierarchy) {
            ch[h[0]].add(h[1]);
        }
        pre = present;
        fut = future;
        B = budget;
        dp = new int[MAXN][2][2][MAXB];
        // Initialize dp to NEG_INF up to B
        for (int u = 1; u <= n; u++) {
            for (int boss = 0; boss < 2; boss++) {
                for (int buy = 0; buy < 2; buy++) {
                    for (int s = 0; s <= B; s++) {
                        dp[u][boss][buy][s] = NEG_INF;
                    }
                }
            }
        }
        dfs(1);
        int ans = 0;
        for (int buy = 0; buy < 2; buy++) {
            for (int s = 0; s <= B; s++) {
                ans = Math.max(ans, dp[1][0][buy][s]);
            }
        }
        return ans;
    }

    private void dfs(int u) {
        // Recurse on children first
        for (int v : ch[u]) {
            dfs(v);
        }
        // Compute dp[u]
        for (int boss = 0; boss < 2; boss++) {
            for (int buy = 0; buy < 2; buy++) {
                int u_cost = 0;
                int u_prof = 0;
                if (buy == 1) {
                    int full = pre[u - 1];
                    u_cost = (boss == 1) ? full / 2 : full;
                    u_prof = fut[u - 1] - u_cost;
                }
                int[] temp = new int[B + 1];
                Arrays.fill(temp, NEG_INF);
                if (u_cost <= B) {
                    temp[u_cost] = u_prof;
                }
                // Merge children
                for (int v : ch[u]) {
                    // Precompute best for this child v (boss_for_v = buy)
                    int[] bestv = new int[B + 1];
                    Arrays.fill(bestv, NEG_INF);
                    for (int sub = 0; sub <= B; sub++) {
                        for (int bv = 0; bv < 2; bv++) {
                            bestv[sub] = Math.max(bestv[sub], dp[v][buy][bv][sub]);
                        }
                    }
                    int[] ntemp = new int[B + 1];
                    Arrays.fill(ntemp, NEG_INF);
                    for (int curr = 0; curr <= B; curr++) {
                        if (temp[curr] == NEG_INF) continue;
                        for (int sub = 0; sub <= B - curr; sub++) {
                            if (bestv[sub] == NEG_INF) continue;
                            int nc = curr + sub;
                            int np = temp[curr] + bestv[sub];
                            ntemp[nc] = Math.max(ntemp[nc], np);
                        }
                    }
                    temp = ntemp;
                }
                // Set dp
                for (int s = 0; s <= B; s++) {
                    dp[u][boss][buy][s] = temp[s];
                }
            }
        }
    }
}
# @lc code=end