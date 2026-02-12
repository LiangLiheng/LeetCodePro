#
# @lc app=leetcode id=3493 lang=java
#
# [3493] Properties Graph
#
# @lc code=start
class Solution {
    public int numberOfComponents(int[][] properties, int k) {
        int n = properties.length;
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < n; i++) adj.add(new ArrayList<>());
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                Set<Integer> setA = new HashSet<>();
                for (int x : properties[i]) setA.add(x);
                Set<Integer> setB = new HashSet<>();
                for (int x : properties[j]) setB.add(x);
                setA.retainAll(setB);
                if (setA.size() >= k) {
                    adj.get(i).add(j);
                    adj.get(j).add(i);
                }
            }
        }
        boolean[] visited = new boolean[n];
        int components = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, adj, visited);
                components++;
            }
        }
        return components;
    }
    private void dfs(int node, List<List<Integer>> adj, boolean[] visited) {
        visited[node] = true;
        for (int nei : adj.get(node)) {
            if (!visited[nei]) dfs(nei, adj, visited);
        }
    }
}
# @lc code=end