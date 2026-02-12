#
# @lc app=leetcode id=3534 lang=java
#
# [3534] Path Existence Queries in a Graph II
#
# @lc code=start
import java.util.*;
class Solution {
    public int[] pathExistenceQueries(int n, int[] nums, int maxDiff, int[][] queries) {
        int[] parent = new int[n];
        for (int i = 0; i < n; i++) parent[i] = i;
        int[][] indexedNums = new int[n][2];
        for (int i = 0; i < n; i++) {
            indexedNums[i][0] = nums[i];
            indexedNums[i][1] = i;
        }
        Arrays.sort(indexedNums, Comparator.comparingInt(a -> a[0]));
        // Union pairs within maxDiff
        for (int i = 0; i < n; i++) {
            int j = i + 1;
            while (j < n && indexedNums[j][0] - indexedNums[i][0] <= maxDiff) {
                union(parent, indexedNums[i][1], indexedNums[j][1]);
                j++;
            }
        }
        // Build adjacency list
        List<Integer>[] adj = new ArrayList[n];
        for (int i = 0; i < n; i++) adj[i] = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            int idx = indexedNums[i][1];
            int j = i - 1;
            while (j >= 0 && indexedNums[i][0] - indexedNums[j][0] <= maxDiff) {
                adj[idx].add(indexedNums[j][1]);
                adj[indexedNums[j][1]].add(idx);
                j--;
            }
            j = i + 1;
            while (j < n && indexedNums[j][0] - indexedNums[i][0] <= maxDiff) {
                adj[idx].add(indexedNums[j][1]);
                adj[indexedNums[j][1]].add(idx);
                j++;
            }
        }
        // Optional: Verification step to ensure adjacency lists are correct
        // for (int i = 0; i < n; i++) {
        //     for (int neighbor : adj[i]) {
        //         assert Math.abs(nums[i] - nums[neighbor]) <= maxDiff;
        //     }
        // }
        int q = queries.length;
        int[] answer = new int[q];
        Map<Long, Integer> cache = new HashMap<>(); // For caching repeated queries
        for (int qi = 0; qi < q; qi++) {
            int u = queries[qi][0], v = queries[qi][1];
            if (u == v) {
                answer[qi] = 0;
                continue;
            }
            if (find(parent, u) != find(parent, v)) {
                answer[qi] = -1;
                continue;
            }
            long key = ((long)u << 32) | v;
            if (cache.containsKey(key)) {
                answer[qi] = cache.get(key);
                continue;
            }
            // BFS
            Queue<Integer> queue = new ArrayDeque<>();
            boolean[] visited = new boolean[n];
            queue.offer(u);
            visited[u] = true;
            int dist = 0;
            boolean found = false;
            while (!queue.isEmpty() && !found) {
                int size = queue.size();
                dist++;
                for (int i = 0; i < size; i++) {
                    int curr = queue.poll();
                    for (int nei : adj[curr]) {
                        if (!visited[nei]) {
                            if (nei == v) { found = true; break; }
                            visited[nei] = true;
                            queue.offer(nei);
                        }
                    }
                    if (found) break;
                }
            }
            answer[qi] = found ? dist : -1;
            cache.put(key, answer[qi]);
        }
        return answer;
    }
    private int find(int[] parent, int x) {
        if (parent[x] != x) parent[x] = find(parent, parent[x]);
        return parent[x];
    }
    private void union(int[] parent, int x, int y) {
        int fx = find(parent, x), fy = find(parent, y);
        if (fx != fy) parent[fx] = fy;
    }
}
# @lc code=end