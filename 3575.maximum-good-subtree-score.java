#
# @lc app=leetcode id=3575 lang=java
#
# [3575] Maximum Good Subtree Score
#

# @lc code=start
class Solution {
    public int goodSubtreeSum(int[] vals, int[] par) {
        int n = vals.length;
        final long MOD = 1000000007L;
        final int SZ = 1 << 10;
        List<Integer>[] children = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            children[i] = new ArrayList<>();
        }
        for (int i = 1; i < n; i++) {
            children[par[i]].add(i);
        }
        int[] masks = new int[n];
        boolean[] valid = new boolean[n];
        for (int i = 0; i < n; i++) {
            String s = String.valueOf(vals[i]);
            boolean[] used = new boolean[10];
            boolean ok = true;
            int mask = 0;
            for (char c : s.toCharArray()) {
                int d = c - '0';
                if (used[d]) {
                    ok = false;
                    break;
                }
                used[d] = true;
                mask |= (1 << d);
            }
            if (ok) {
                valid[i] = true;
                masks[i] = mask;
            }
        }
        long[] maxScore = new long[n];
        java.util.function.Function<Integer, long[]> dfs = new java.util.function.Function<Integer, long[]>() {
            @Override
            public long[] apply(Integer uu) {
                int u = uu;
                long[] curr = new long[SZ];
                java.util.Arrays.fill(curr, -1L);
                curr[0] = 0L;
                for (int v : children[u]) {
                    long[] ch = apply(v);
                    long[] nxt = new long[SZ];
                    java.util.Arrays.fill(nxt, -1L);
                    nxt[0] = 0L;
                    for (int m1 = 0; m1 < SZ; m1++) {
                        if (curr[m1] == -1L) continue;
                        for (int m2 = 0; m2 < SZ; m2++) {
                            if (ch[m2] == -1L) continue;
                            if ((m1 & m2) == 0) {
                                int nm = m1 | m2;
                                long nsum = curr[m1] + ch[m2];
                                nxt[nm] = Math.max(nxt[nm], nsum);
                            }
                        }
                    }
                    curr = nxt;
                }
                long[] sub = new long[SZ];
                System.arraycopy(curr, 0, sub, 0, SZ);
                if (valid[u]) {
                    int mu = masks[u];
                    long val = vals[u];
                    for (int m = 0; m < SZ; m++) {
                        if (sub[m] == -1L) continue;
                        if ((m & mu) == 0) {
                            int nm = m | mu;
                            long nsum = sub[m] + val;
                            sub[nm] = Math.max(sub[nm], nsum);
                        }
                    }
                }
                long mx = 0L;
                for (int i = 0; i < SZ; i++) {
                    if (sub[i] > mx) mx = sub[i];
                }
                maxScore[u] = mx;
                return sub;
            }
        };
        dfs.apply(0);
        long ans = 0L;
        for (long s : maxScore) {
            ans = (ans + s) % MOD;
        }
        return (int) ans;
    }
}
# @lc code=end