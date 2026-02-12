#
# @lc app=leetcode id=3786 lang=java
#
# [3786] Total Sum of Interaction Cost in Tree Groups
#
# @lc code=start
class Solution {
    public long interactionCosts(int n, int[][] edges, int[] group) {
        // Build the tree
        List<Integer>[] tree = new List[n];
        for (int i = 0; i < n; ++i) tree[i] = new ArrayList<>();
        for (int[] e : edges) {
            tree[e[0]].add(e[1]);
            tree[e[1]].add(e[0]);
        }
        long total = 0;
        for (int g = 1; g <= 20; ++g) {
            boolean[] inGroup = new boolean[n];
            int groupCount = 0;
            for (int i = 0; i < n; ++i) {
                if (group[i] == g) {
                    inGroup[i] = true;
                    groupCount++;
                }
            }
            if (groupCount < 2) continue;
            long[] res = new long[1];
            dfs(0, -1, tree, inGroup, groupCount, res);
            // Each pair is counted twice (once from each direction), so divide by 2
            total += res[0] / 2;
        }
        return total;
    }
    private int dfs(int node, int parent, List<Integer>[] tree, boolean[] inGroup, int groupCount, long[] res) {
        int cnt = inGroup[node] ? 1 : 0;
        for (int nei : tree[node]) {
            if (nei == parent) continue;
            int sub = dfs(nei, node, tree, inGroup, groupCount, res);
            res[0] += (long) sub * (groupCount - sub);
            cnt += sub;
        }
        return cnt;
    }
}
# @lc code=end