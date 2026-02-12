#
# @lc app=leetcode id=3625 lang=java
#
# [3625] Count Number of Trapezoids II
#

# @lc code=start
import java.util.*;

class Solution {
    public int countTrapezoids(int[][] points) {
        int n = points.length;
        Map<String, List<int[]>> slopeToPairs = new HashMap<>();
        // Step 1: For each pair, compute slope as reduced fraction
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];
                int g = gcd(dx, dy);
                dx /= g; dy /= g;
                // Normalize direction
                if (dx < 0) { dx = -dx; dy = -dy; }
                else if (dx == 0 && dy < 0) { dy = -dy; }
                String key = dx + "," + dy;
                slopeToPairs.computeIfAbsent(key, k -> new ArrayList<>()).add(new int[]{i, j});
            }
        }
        Set<String> unique = new HashSet<>();
        int res = 0;
        // Step 2: For each group of pairs with same slope, process all disjoint pairs
        for (List<int[]> group : slopeToPairs.values()) {
            int m = group.size();
            for (int a = 0; a < m; ++a) {
                for (int b = a + 1; b < m; ++b) {
                    int[] p1 = group.get(a), p2 = group.get(b);
                    Set<Integer> quad = new HashSet<>(Arrays.asList(p1[0], p1[1], p2[0], p2[1]));
                    if (quad.size() < 4) continue; // not 4 distinct points
                    int[] idxs = quad.stream().mapToInt(x -> x).toArray();
                    // Step 3: Verify convexity
                    if (!isConvex(points, idxs)) continue;
                    int[] sorted = idxs.clone();
                    Arrays.sort(sorted);
                    String sig = sorted[0] + "," + sorted[1] + "," + sorted[2] + "," + sorted[3];
                    if (unique.add(sig)) res++;
                }
            }
        }
        return res;
    }
    // Helper for GCD
    private int gcd(int a, int b) {
        if (b == 0) return Math.abs(a);
        return gcd(b, a % b);
    }
    // Check convexity via cross product
    private boolean isConvex(int[][] pts, int[] idxs) {
        List<int[]> list = new ArrayList<>();
        for (int i : idxs) list.add(pts[i]);
        // Try all circular orderings, find one that is convex
        int perm[] = new int[4];
        for (int i = 0; i < 4; ++i) perm[i] = i;
        do {
            boolean ok = true;
            int prev = 0;
            for (int j = 0; j < 4; ++j) {
                int[] a = list.get(perm[j]);
                int[] b = list.get(perm[(j + 1) % 4]);
                int[] c = list.get(perm[(j + 2) % 4]);
                int cp = cross(a, b, c);
                if (j == 0) prev = cp;
                else if ((long)cp * prev < 0) { ok = false; break; }
            }
            if (ok) return true;
        } while (nextPerm(perm));
        return false;
    }
    private int cross(int[] a, int[] b, int[] c) {
        int x1 = b[0] - a[0], y1 = b[1] - a[1];
        int x2 = c[0] - b[0], y2 = c[1] - b[1];
        return x1 * y2 - y1 * x2;
    }
    // Lexical permutation
    private boolean nextPerm(int[] arr) {
        int i = arr.length - 2;
        while (i >= 0 && arr[i] >= arr[i+1]) i--;
        if (i < 0) return false;
        int j = arr.length - 1;
        while (arr[j] <= arr[i]) j--;
        int t = arr[i]; arr[i] = arr[j]; arr[j] = t;
        Arrays.sort(arr, i+1, arr.length);
        return true;
    }
}
# @lc code=end