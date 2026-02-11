#
# @lc app=leetcode id=3625 lang=java
#
# [3625] Count Number of Trapezoids II
#
# @lc code=start
class Solution {
    public int countTrapezoids(int[][] points) {
        int n = points.length;
        Map<Long, Integer> pointToIndex = new HashMap<>();
        final int OFFSET = 1000;
        final int MODD = 2001;
        for (int i = 0; i < n; i++) {
            long x = (long)points[i][0] + OFFSET;
            long y = (long)points[i][1] + OFFSET;
            long key = x * MODD + y;
            pointToIndex.put(key, i);
        }

        // Compute number of unique parallelograms P using set for dedup
        Set<String> paraSet = new HashSet<>();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    // Try origin = i
                    {
                        long lx = (long)points[j][0] + points[k][0] - points[i][0];
                        long ly = (long)points[j][1] + points[k][1] - points[i][1];
                        long px = lx + OFFSET;
                        long py = ly + OFFSET;
                        if (px >= 0 && px < MODD && py >= 0 && py < MODD) {
                            long key = px * MODD + py;
                            if (pointToIndex.containsKey(key)) {
                                int l = pointToIndex.get(key);
                                if (l != i && l != j && l != k) {
                                    long dx1 = (long)points[j][0] - points[i][0];
                                    long dy1 = (long)points[j][1] - points[i][1];
                                    long dx2 = (long)points[k][0] - points[i][0];
                                    long dy2 = (long)points[k][1] - points[i][1];
                                    long cross = dx1 * dy2 - dy1 * dx2;
                                    if (cross != 0) {
                                        int[] idxs = {i, j, k, l};
                                        // manual sort for 4 ints
                                        int a = idxs[0], b = idxs[1], c = idxs[2], d = idxs[3];
                                        if (a > b) { int t = a; a = b; b = t; }
                                        if (a > c) { int t = a; a = c; c = t; }
                                        if (a > d) { int t = a; a = d; d = t; }
                                        if (b > c) { int t = b; b = c; c = t; }
                                        if (b > d) { int t = b; b = d; d = t; }
                                        if (c > d) { int t = c; c = d; d = t; }
                                        String skey = a + "_" + b + "_" + c + "_" + d;
                                        paraSet.add(skey);
                                    }
                                }
                            }
                        }
                    }
                    // Try origin = j
                    {
                        long lx = (long)points[i][0] + points[k][0] - points[j][0];
                        long ly = (long)points[i][1] + points[k][1] - points[j][1];
                        long px = lx + OFFSET;
                        long py = ly + OFFSET;
                        if (px >= 0 && px < MODD && py >= 0 && py < MODD) {
                            long key = px * MODD + py;
                            if (pointToIndex.containsKey(key)) {
                                int l = pointToIndex.get(key);
                                if (l != i && l != j && l != k) {
                                    long dx1 = (long)points[i][0] - points[j][0];
                                    long dy1 = (long)points[i][1] - points[j][1];
                                    long dx2 = (long)points[k][0] - points[j][0];
                                    long dy2 = (long)points[k][1] - points[j][1];
                                    long cross = dx1 * dy2 - dy1 * dx2;
                                    if (cross != 0) {
                                        int[] idxs = {i, j, k, l};
                                        int a = idxs[0], b = idxs[1], c = idxs[2], d = idxs[3];
                                        if (a > b) { int t = a; a = b; b = t; }
                                        if (a > c) { int t = a; a = c; c = t; }
                                        if (a > d) { int t = a; a = d; d = t; }
                                        if (b > c) { int t = b; b = c; c = t; }
                                        if (b > d) { int t = b; b = d; d = t; }
                                        if (c > d) { int t = c; c = d; d = t; }
                                        String skey = a + "_" + b + "_" + c + "_" + d;
                                        paraSet.add(skey);
                                    }
                                }
                            }
                        }
                    }
                    // Try origin = k
                    {
                        long lx = (long)points[i][0] + points[j][0] - points[k][0];
                        long ly = (long)points[i][1] + points[j][1] - points[k][1];
                        long px = lx + OFFSET;
                        long py = ly + OFFSET;
                        if (px >= 0 && px < MODD && py >= 0 && py < MODD) {
                            long key = px * MODD + py;
                            if (pointToIndex.containsKey(key)) {
                                int l = pointToIndex.get(key);
                                if (l != i && l != j && l != k) {
                                    long dx1 = (long)points[i][0] - points[k][0];
                                    long dy1 = (long)points[i][1] - points[k][1];
                                    long dx2 = (long)points[j][0] - points[k][0];
                                    long dy2 = (long)points[j][1] - points[k][1];
                                    long cross = dx1 * dy2 - dy1 * dx2;
                                    if (cross != 0) {
                                        int[] idxs = {i, j, k, l};
                                        int a = idxs[0], b = idxs[1], c = idxs[2], d = idxs[3];
                                        if (a > b) { int t = a; a = b; b = t; }
                                        if (a > c) { int t = a; a = c; c = t; }
                                        if (a > d) { int t = a; a = d; d = t; }
                                        if (b > c) { int t = b; b = c; c = t; }
                                        if (b > d) { int t = b; b = d; d = t; }
                                        if (c > d) { int t = c; c = d; d = t; }
                                        String skey = a + "_" + b + "_" + c + "_" + d;
                                        paraSet.add(skey);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        long para = paraSet.size();

        // Compute S: trapezoid edge pairs
        Map<String, Map<Long, Set<Integer>>> collinearGroups = new HashMap<>();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                long x1 = points[i][0];
                long y1 = points[i][1];
                long x2 = points[j][0];
                long y2 = points[j][1];
                long dx = x2 - x1;
                long dy = y2 - y1;
                if (dx == 0 && dy == 0) continue;
                boolean flip = (dx < 0 || (dx == 0 && dy < 0));
                if (flip) {
                    dx = -dx;
                    dy = -dy;
                }
                long g = gcd(dx, dy);
                if (g != 0) {
                    dx /= g;
                    dy /= g;
                }
                String slopeKey = dx + "," + dy;
                long b = dy * x1 - dx * y1;
                Map<Long, Set<Integer>> lineMap = collinearGroups.computeIfAbsent(slopeKey, k -> new HashMap<>());
                Set<Integer> pts = lineMap.computeIfAbsent(b, k -> new HashSet<>());
                pts.add(i);
                pts.add(j);
            }
        }

        long S = 0;
        for (String slope : collinearGroups.keySet()) {
            Map<Long, Set<Integer>> lineMap = collinearGroups.get(slope);
            List<Integer> sizes = new ArrayList<>();
            for (Set<Integer> pts : lineMap.values()) {
                int sz = pts.size();
                if (sz >= 2) {
                    sizes.add(sz);
                }
            }
            int m = sizes.size();
            for (int a = 0; a < m; a++) {
                for (int b = a + 1; b < m; b++) {
                    long c1 = (long) sizes.get(a) * (sizes.get(a) - 1) / 2;
                    long c2 = (long) sizes.get(b) * (sizes.get(b) - 1) / 2;
                    S += c1 * c2;
                }
            }
        }

        return (int) (S - para);
    }

    private long gcd(long a, long b) {
        a = Math.abs(a);
        b = Math.abs(b);
        while (b != 0) {
            long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
}
# @lc code=end