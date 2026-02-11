#
# @lc app=leetcode id=3534 lang=java
#
# [3534] Path Existence Queries in a Graph II
#

# @lc code=start
import java.util.*;
class Solution {
    public int[] pathExistenceQueries(int n, int[] nums, int maxDiff, int[][] queries) {
        int[] sortedIdx = new int[n];
        for (int i = 0; i < n; i++) {
            sortedIdx[i] = i;
        }
        Arrays.sort(sortedIdx, (a, b) -> Integer.compare(nums[a], nums[b]));
        
        int[] position = new int[n];
        int[] s = new int[n];
        for (int i = 0; i < n; i++) {
            int orig = sortedIdx[i];
            position[orig] = i;
            s[i] = nums[orig];
        }
        
        // Compute reach1[i]: farthest in 1 jump
        int[] reach1 = new int[n];
        int ptr = 0;
        for (int i = 0; i < n; i++) {
            while (ptr < n && s[ptr] <= s[i] + maxDiff) {
                ptr++;
            }
            reach1[i] = ptr - 1;
        }
        
        // Compute components for sorted indices
        int[] nodeComp = new int[n];
        nodeComp[0] = 0;
        int curComp = 0;
        for (int i = 1; i < n; i++) {
            if (s[i] - s[i - 1] > maxDiff) {
                curComp++;
            }
            nodeComp[i] = curComp;
        }
        
        // origComp[orig] = nodeComp[position[orig]]
        int[] origComp = new int[n];
        for (int i = 0; i < n; i++) {
            origComp[sortedIdx[i]] = nodeComp[i];
        }
        
        // Binary lifting
        final int LOG = 18;
        int[][] jump = new int[n][LOG];
        for (int i = 0; i < n; i++) {
            jump[i][0] = reach1[i];
        }
        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                int mid = jump[i][k - 1];
                jump[i][k] = jump[mid][k - 1];
            }
        }
        
        // Process queries
        int[] ans = new int[queries.length];
        for (int q = 0; q < queries.length; q++) {
            int u = queries[q][0];
            int v = queries[q][1];
            if (u == v) {
                ans[q] = 0;
                continue;
            }
            if (origComp[u] != origComp[v]) {
                ans[q] = -1;
                continue;
            }
            int p1 = position[u];
            int p2 = position[v];
            if (p1 > p2) {
                int tmp = p1;
                p1 = p2;
                p2 = tmp;
            }
            // Binary search min d >=1
            int lo = 1;
            int hi = n;
            int res = -1;
            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                int cur = p1;
                int bits = mid;
                for (int b = LOG - 1; b >= 0; b--) {
                    if ((bits & (1 << b)) != 0) {
                        cur = jump[cur][b];
                    }
                }
                if (cur >= p2) {
                    res = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            ans[q] = res;
        }
        return ans;
    }
}
# @lc code=end