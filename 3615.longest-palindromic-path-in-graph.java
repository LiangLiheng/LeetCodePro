#
# @lc app=leetcode id=3615 lang=java
#
# [3615] Longest Palindromic Path in Graph
#
# @lc code=start
class Solution {
    public int maxLen(int n, int[][] edges, String label) {
        List<Integer>[] graph = new ArrayList[n];
        for (int i = 0; i < n; ++i) graph[i] = new ArrayList<>();
        for (int[] e : edges) {
            graph[e[0]].add(e[1]);
            graph[e[1]].add(e[0]);
        }
        int[] max = new int[1];
        Set<String> visitedPaths = new HashSet<>();
        for (int start = 0; start < n; ++start) {
            boolean[] visited = new boolean[n];
            dfs(graph, label, start, new ArrayList<>(), visited, max, visitedPaths);
        }
        return max[0];
    }
    private void dfs(List<Integer>[] graph, String label, int u, List<Integer> path, boolean[] visited, int[] max, Set<String> visitedPaths) {
        visited[u] = true;
        path.add(u);
        // Use canonical path representation to avoid reverse duplicates
        String canonical = canonicalPath(path);
        if (!visitedPaths.add(canonical)) {
            path.remove(path.size() - 1);
            visited[u] = false;
            return;
        }
        if (isPalindrome(label, path)) {
            max[0] = Math.max(max[0], path.size());
        }
        for (int v : graph[u]) {
            if (!visited[v]) {
                dfs(graph, label, v, path, visited, max, visitedPaths);
            }
        }
        path.remove(path.size() - 1);
        visited[u] = false;
    }
    private boolean isPalindrome(String label, List<Integer> path) {
        int l = 0, r = path.size() - 1;
        while (l < r) {
            if (label.charAt(path.get(l)) != label.charAt(path.get(r))) return false;
            ++l; --r;
        }
        return true;
    }
    // Generate a canonical string for the path or its reverse
    private String canonicalPath(List<Integer> path) {
        StringBuilder a = new StringBuilder();
        StringBuilder b = new StringBuilder();
        for (int idx : path) a.append(idx).append(",");
        for (int i = path.size() - 1; i >= 0; --i) b.append(path.get(i)).append(",");
        return a.toString().compareTo(b.toString()) < 0 ? a.toString() : b.toString();
    }
}
# @lc code=end