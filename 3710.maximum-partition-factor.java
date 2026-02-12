#
# @lc app=leetcode id=3710 lang=java
#
# [3710] Maximum Partition Factor
#

# @lc code=start
import java.util.*;
class Solution {
    public int maxPartitionFactor(int[][] points) {
        int n = points.length;
        if (n == 2) return 0;
        List<Integer> dists = new ArrayList<>();
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                dists.add(Math.abs(points[i][0] - points[j][0]) + Math.abs(points[i][1] - points[j][1]));
        Set<Integer> unique = new HashSet<>(dists);
        List<Integer> sorted = new ArrayList<>(unique);
        Collections.sort(sorted);

        int left = 0, right = sorted.size() - 1, ans = 0;
        while (left <= right) {
            int mid = (left + right) / 2;
            int threshold = sorted.get(mid);
            // Build the conflict graph: edge if distance < threshold
            List<List<Integer>> graph = new ArrayList<>();
            for (int i = 0; i < n; ++i) graph.add(new ArrayList<>());
            for (int i = 0; i < n; ++i)
                for (int j = i + 1; j < n; ++j) {
                    int dist = Math.abs(points[i][0] - points[j][0]) + Math.abs(points[i][1] - points[j][1]);
                    if (dist < threshold) {
                        graph.get(i).add(j);
                        graph.get(j).add(i);
                    }
                }
            // Check if the conflict graph is bipartite
            int[] color = new int[n];
            Arrays.fill(color, -1);
            boolean isBipartite = true;
            for (int i = 0; i < n && isBipartite; ++i) {
                if (color[i] == -1) {
                    Queue<Integer> queue = new LinkedList<>();
                    queue.add(i);
                    color[i] = 0;
                    while (!queue.isEmpty() && isBipartite) {
                        int cur = queue.poll();
                        for (int nei : graph.get(cur)) {
                            if (color[nei] == -1) {
                                color[nei] = 1 - color[cur];
                                queue.add(nei);
                            } else if (color[nei] == color[cur]) {
                                isBipartite = false;
                                break;
                            }
                        }
                    }
                }
            }
            if (isBipartite) {
                ans = threshold;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return ans;
    }
}
# @lc code=end