#
# @lc app=leetcode id=3762 lang=java
#
# [3762] Minimum Operations to Equalize Subarrays
#

# @lc code=start
class Solution {
    public static class MergeSortTree {
        private int n;
        private ArrayList<ArrayList<Long>> sortedTree;
        private ArrayList<ArrayList<Long>> prefixTree;

        public MergeSortTree(int nn, int[] qq) {
            n = nn;
            int tsize = 4 * n + 10;
            sortedTree = new ArrayList<>(tsize);
            prefixTree = new ArrayList<>(tsize);
            for (int i = 0; i < tsize; i++) {
                sortedTree.add(new ArrayList<Long>());
                prefixTree.add(new ArrayList<Long>());
            }
            build(1, 0, n - 1, qq);
        }

        private void build(int node, int start, int end, int[] qq) {
            if (start == end) {
                sortedTree.get(node).add((long) qq[start]);
                prefixTree.get(node).add(0L);
                prefixTree.get(node).add((long) qq[start]);
                return;
            }
            int mid = (start + end) / 2;
            build(2 * node, start, mid, qq);
            build(2 * node + 1, mid + 1, end, qq);
            ArrayList<Long> left = sortedTree.get(2 * node);
            ArrayList<Long> right = sortedTree.get(2 * node + 1);
            ArrayList<Long> merg = sortedTree.get(node);
            int i = 0, j = 0;
            int ls = left.size(), rs = right.size();
            while (i < ls && j < rs) {
                if (left.get(i) <= right.get(j)) {
                    merg.add(left.get(i++));
                } else {
                    merg.add(right.get(j++));
                }
            }
            while (i < ls) merg.add(left.get(i++));
            while (j < rs) merg.add(right.get(j++));
            ArrayList<Long> pre = prefixTree.get(node);
            pre.add(0L);
            for (int k = 1; k <= merg.size(); k++) {
                pre.add(pre.get(k - 1) + merg.get(k - 1));
            }
        }

        private int upperBound(ArrayList<Long> arr, long val) {
            int low = 0;
            int high = arr.size();
            while (low < high) {
                int m = (low + high) / 2;
                if (arr.get(m) <= val) {
                    low = m + 1;
                } else {
                    high = m;
                }
            }
            return low;
        }

        public long countLeq(int l, int r, long val) {
            return countLeqHelper(1, 0, n - 1, l, r, val);
        }

        private long countLeqHelper(int node, int start, int end, int l, int r, long val) {
            if (r < start || end < l) return 0;
            if (l <= start && end <= r) {
                return upperBound(sortedTree.get(node), val);
            }
            int mid = (start + end) / 2;
            return countLeqHelper(2 * node, start, mid, l, r, val) +
                   countLeqHelper(2 * node + 1, mid + 1, end, l, r, val);
        }

        public long sumLeq(int l, int r, long val) {
            return sumLeqHelper(1, 0, n - 1, l, r, val);
        }

        private long sumLeqHelper(int node, int start, int end, int l, int r, long val) {
            if (r < start || end < l) return 0;
            if (l <= start && end <= r) {
                int pos = upperBound(sortedTree.get(node), val);
                return prefixTree.get(node).get(pos);
            }
            int mid = (start + end) / 2;
            return sumLeqHelper(2 * node, start, mid, l, r, val) +
                   sumLeqHelper(2 * node + 1, mid + 1, end, l, r, val);
        }
    }

    private int getMinMod(int l, int r, int[][] spminm, int[] logg) {
        int j = logg[r - l + 1];
        return Math.min(spminm[j][l], spminm[j][r - (1 << j) + 1]);
    }

    private int getMaxMod(int l, int r, int[][] spmaxm, int[] logg) {
        int j = logg[r - l + 1];
        return Math.max(spmaxm[j][l], spmaxm[j][r - (1 << j) + 1]);
    }

    public long[] minOperations(int[] nums, int k, int[][] queries) {
        int n = nums.length;
        int[] mods = new int[n];
        int[] quots = new int[n];
        for (int i = 0; i < n; i++) {
            mods[i] = nums[i] % k;
            quots[i] = nums[i] / k;
        }
        long[] presum = new long[n + 1];
        for (int i = 0; i < n; i++) {
            presum[i + 1] = presum[i] + quots[i];
        }
        // log
        int[] logg = new int[n + 2];
        logg[1] = 0;
        for (int i = 2; i <= n; i++) {
            logg[i] = logg[i / 2] + 1;
        }
        int LOG = 16;
        int[][] spminm = new int[LOG][n];
        int[][] spmaxm = new int[LOG][n];
        for (int i = 0; i < n; i++) {
            spminm[0][i] = mods[i];
            spmaxm[0][i] = mods[i];
        }
        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                spminm[j][i] = Math.min(spminm[j - 1][i], spminm[j - 1][i + (1 << (j - 1))]);
                spmaxm[j][i] = Math.max(spmaxm[j - 1][i], spmaxm[j - 1][i + (1 << (j - 1))]);
            }
        }
        MergeSortTree mst = new MergeSortTree(n, quots);
        long[] ans = new long[queries.length];
        for (int qi = 0; qi < queries.length; qi++) {
            int li = queries[qi][0];
            int ri = queries[qi][1];
            int minmod = getMinMod(li, ri, spminm, logg);
            int maxmod = getMaxMod(li, ri, spmaxm, logg);
            if (minmod != maxmod) {
                ans[qi] = -1;
            } else {
                int sz = ri - li + 1;
                long target = (sz + 1L) / 2;
                long lo = 0;
                long hi = 2000000001L;
                while (lo < hi) {
                    long miv = lo + (hi - lo) / 2;
                    long cc = mst.countLeq(li, ri, miv);
                    if (cc >= target) {
                        hi = miv;
                    } else {
                        lo = miv + 1;
                    }
                }
                long med = lo;
                long cntle = mst.countLeq(li, ri, med);
                long sumle = mst.sumLeq(li, ri, med);
                long totc = sz;
                long tots = presum[ri + 1] - presum[li];
                long cntgt = totc - cntle;
                long sumgt = tots - sumle;
                ans[qi] = sumgt - med * cntgt + med * cntle - sumle;
            }
        }
        return ans;
    }
}
# @lc code=end