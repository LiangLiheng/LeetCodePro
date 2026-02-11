#
# @lc app=leetcode id=3504 lang=java
#
# [3504] Longest Palindrome After Substring Concatenation II
#

# @lc code=start
class Solution {
    static class RollingHash {
        long[] prefix, pow;
        long mod, base;
        public RollingHash(String str, long b, long m) {
            int n = str.length();
            mod = m;
            base = b;
            prefix = new long[n + 1];
            pow = new long[n + 1];
            pow[0] = 1;
            for (int i = 1; i <= n; i++) {
                pow[i] = pow[i - 1] * b % m;
            }
            for (int i = 1; i <= n; i++) {
                prefix[i] = (prefix[i - 1] * b + (str.charAt(i - 1) - 'a' + 1)) % m;
            }
        }
        public long get(int l, int r) {
            long h = (prefix[r + 1] + mod - prefix[l] * pow[r - l + 1] % mod) % mod;
            return h;
        }
    }

    static class HashPair {
        long h1, h2;
        public HashPair(long a, long b) {
            h1 = a;
            h2 = b;
        }
        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            HashPair p = (HashPair) o;
            return h1 == p.h1 && h2 == p.h2;
        }
        @Override
        public int hashCode() {
            return (int) (h1 ^ h2);
        }
    }

    private static int[] computeLongestPalPrefix(RollingHash hf1, RollingHash hr1, RollingHash hf2, RollingHash hr2, int n) {
        int[] lps = new int[n + 1];
        lps[n] = 0;
        for (int q = 0; q < n; q++) {
            int maxLen = 0;
            for (int len = 1; len <= n - q; len++) {
                int rr = q + len - 1;
                long f1 = hf1.get(q, rr);
                long r1 = hr1.get(n - 1 - rr, n - 1 - q);
                long f2 = hf2.get(q, rr);
                long r2 = hr2.get(n - 1 - rr, n - 1 - q);
                if (f1 == r1 && f2 == r2) {
                    maxLen = len;
                }
            }
            lps[q] = maxLen;
        }
        return lps;
    }

    private static int[] computeLongestPalSuffix(RollingHash hf1, RollingHash hr1, RollingHash hf2, RollingHash hr2, int n) {
        int[] slps = new int[n];
        for (int p = 0; p < n; p++) {
            int maxLen = 0;
            for (int len = 1; len <= p + 1; len++) {
                int l = p - len + 1;
                long f1 = hf1.get(l, p);
                long r1 = hr1.get(n - 1 - p, n - 1 - l);
                long f2 = hf2.get(l, p);
                long r2 = hr2.get(n - 1 - p, n - 1 - l);
                if (f1 == r1 && f2 == r2) {
                    maxLen = len;
                }
            }
            slps[p] = maxLen;
        }
        return slps;
    }

    public int longestPalindrome(String s, String t) {
        final long MOD1 = 1000000007L;
        final long BASE1 = 131L;
        final long MOD2 = 1000000009L;
        final long BASE2 = 137L;

        String rs = new StringBuilder(s).reverse().toString();
        String rt = new StringBuilder(t).reverse().toString();
        int ns = s.length();
        int mt = t.length();

        RollingHash sh1 = new RollingHash(s, BASE1, MOD1);
        RollingHash shr1 = new RollingHash(rs, BASE1, MOD1);
        RollingHash sh2 = new RollingHash(s, BASE2, MOD2);
        RollingHash shr2 = new RollingHash(rs, BASE2, MOD2);

        RollingHash th1 = new RollingHash(t, BASE1, MOD1);
        RollingHash thr1 = new RollingHash(rt, BASE1, MOD1);
        RollingHash th2 = new RollingHash(t, BASE2, MOD2);
        RollingHash thr2 = new RollingHash(rt, BASE2, MOD2);

        int[] lps_s = computeLongestPalPrefix(sh1, shr1, sh2, shr2, ns);
        int[] lps_t = computeLongestPalPrefix(th1, thr1, th2, thr2, mt);
        int[] suffix_lps_t = computeLongestPalSuffix(th1, thr1, th2, thr2, mt);

        int max_pal_s = 0;
        for (int i = 0; i <= ns; i++) {
            max_pal_s = Math.max(max_pal_s, lps_s[i]);
        }
        int max_pal_t = 0;
        for (int i = 0; i <= mt; i++) {
            max_pal_t = Math.max(max_pal_t, lps_t[i]);
        }
        int ans = Math.max(max_pal_s, max_pal_t);

        // Build substring hash sets for s and t
        java.util.List<java.util.Set<HashPair>> s_subs = new java.util.ArrayList<>(ns + 1);
        for (int i = 0; i <= ns; i++) {
            s_subs.add(new java.util.HashSet<>()));
        }
        for (int lb = 1; lb <= ns; lb++) {
            for (int st = 0; st + lb <= ns; st++) {
                long h1 = sh1.get(st, st + lb - 1);
                long h2 = sh2.get(st, st + lb - 1);
                s_subs.get(lb).add(new HashPair(h1, h2));
            }
        }

        java.util.List<java.util.Set<HashPair>> t_subs = new java.util.ArrayList<>(mt + 1);
        for (int i = 0; i <= mt; i++) {
            t_subs.add(new java.util.HashSet<>()));
        }
        for (int lb = 1; lb <= mt; lb++) {
            for (int st = 0; st + lb <= mt; st++) {
                long h1 = th1.get(st, st + lb - 1);
                long h2 = th2.get(st, st + lb - 1);
                t_subs.get(lb).add(new HashPair(h1, h2));
            }
        }

        // s-center spanning (longer or equal)
        for (int endC = 0; endC < ns; endC++) {
            int q = endC + 1;
            int maxd = lps_s[q];
            for (int lb = 1; lb <= endC + 1; lb++) {
                int startC = endC - lb + 1;
                if (startC < 0) continue;
                int lrev = ns - 1 - endC;
                int rrev = ns - 1 - startC;
                long rh1 = shr1.get(lrev, rrev);
                long rh2 = shr2.get(lrev, rrev);
                if (t_subs.get(lb).contains(new HashPair(rh1, rh2))) {
                    ans = Math.max(ans, 2 * lb + maxd);
                }
            }
        }

        // t-center spanning (longer or equal)
        for (int endC = 0; endC < mt; endC++) {
            for (int lb = 1; lb <= endC + 1; lb++) {
                int startC = endC - lb + 1;
                if (startC < 0) continue;
                int endD = startC - 1;
                int maxd = 0;
                if (endD >= 0) {
                    maxd = suffix_lps_t[endD];
                }
                int lrev = mt - 1 - endC;
                int rrev = mt - 1 - startC;
                long rh1 = thr1.get(lrev, rrev);
                long rh2 = thr2.get(lrev, rrev);
                if (s_subs.get(lb).contains(new HashPair(rh1, rh2))) {
                    ans = Math.max(ans, 2 * lb + maxd);
                }
            }
        }

        return ans;
    }
}
# @lc code=end