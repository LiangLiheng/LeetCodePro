#
# @lc app=leetcode id=3734 lang=java
#
# [3734] Lexicographically Smallest Palindromic Permutation Greater Than Target
#

# @lc code=start
class Solution {
    public String lexPalindromicPermutation(String s, String target) {
        int n = s.length();
        int[] freq = new int[26];
        for (char ch : s.toCharArray()) {
            freq[ch - 'a']++;
        }
        for (int k = n - 1; k >= 0; k--) {
            boolean consistent = true;
            for (int j = 0; j < k; j++) {
                int mir = n - 1 - j;
                if (mir < k && target.charAt(j) != target.charAt(mir)) {
                    consistent = false;
                    break;
                }
            }
            if (!consistent) continue;
            char[] cand = new char[n];
            for (int j = 0; j < k; j++) {
                cand[j] = target.charAt(j);
            }
            for (int j = 0; j < k; j++) {
                cand[n - 1 - j] = cand[j];
            }
            int[] remain = new int[26];
            System.arraycopy(freq, 0, remain, 0, 26);
            boolean over = false;
            for (int j = 0; j < n; j++) {
                if (cand[j] != '\u0000') {
                    int idx = cand[j] - 'a';
                    if (--remain[idx] < 0) {
                        over = true;
                        break;
                    }
                }
            }
            if (over) continue;
            char tgtk = target.charAt(k);
            int mirk = n - 1 - k;
            boolean ismidk = (k == mirk);
            boolean diverged = false;
            if (cand[k] != '\u0000') {
                if (cand[k] > tgtk) {
                    diverged = true;
                }
            } else {
                char best = '\u0000';
                for (char ch = (char)(tgtk + 1); ch <= 'z'; ch++) {
                    int idx = ch - 'a';
                    int need = ismidk ? 1 : 2;
                    if (remain[idx] >= need) {
                        if (cand[mirk] != '\u0000' && cand[mirk] != ch) continue;
                        best = ch;
                        break;
                    }
                }
                if (best != '\u0000') {
                    cand[k] = best;
                    cand[mirk] = best;
                    int idx = best - 'a';
                    remain[idx] -= 1;
                    if (!ismidk) remain[idx] -= 1;
                    diverged = true;
                }
            }
            if (!diverged) continue;
            int rr = 0;
            for (int i = 0; i < n / 2; i++) {
                if (cand[i] == '\u0000') rr++;
            }
            boolean needm = (n % 2 == 1) && (cand[n / 2] == '\u0000');
            int od = 0;
            int mp = 0;
            for (int i = 0; i < 26; i++) {
                mp += remain[i] / 2;
                if (remain[i] % 2 == 1) od++;
            }
            if (mp != rr || od != (needm ? 1 : 0)) continue;
            // fill pairs
            for (int pos = 0; pos < n / 2; pos++) {
                if (cand[pos] != '\u0000') continue;
                for (int cc = 0; cc < 26; cc++) {
                    if (remain[cc] >= 2) {
                        char ch = (char) ('a' + cc);
                        cand[pos] = ch;
                        cand[n - 1 - pos] = ch;
                        remain[cc] -= 2;
                        break;
                    }
                }
            }
            // fill mid
            if (needm) {
                int midp = n / 2;
                for (int cc = 0; cc < 26; cc++) {
                    if (remain[cc] >= 1) {
                        cand[midp] = (char) ('a' + cc);
                        remain[cc]--;
                        break;
                    }
                }
            }
            return new String(cand);
        }
        return "";
    }
}
# @lc code=end