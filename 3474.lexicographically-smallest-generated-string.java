#
# @lc app=leetcode id=3474 lang=java
#
# [3474] Lexicographically Smallest Generated String
#

# @lc code=start
class Solution {
    public String generateString(String str1, String str2) {
        int n = str1.length(), m = str2.length();
        int len = n + m - 1;
        char[] res = new char[len];
        Arrays.fill(res, '?');
        // Step 1: place all required str2s
        for (int i = 0; i < n; ++i) {
            if (str1.charAt(i) == 'T') {
                for (int j = 0; j < m; ++j) {
                    int pos = i + j;
                    if (res[pos] == '?') {
                        res[pos] = str2.charAt(j);
                    } else if (res[pos] != str2.charAt(j)) {
                        return ""; // Conflict
                    }
                }
            }
        }
        // Step 2: mark forbidden positions for F
        for (int i = 0; i < len; ++i) {
            if (res[i] == '?') {
                res[i] = 'a';
            }
        }
        // Step 3: check F constraints and try to fix if needed
        for (int i = 0; i < n; ++i) {
            if (str1.charAt(i) == 'F') {
                boolean match = true;
                for (int j = 0; j < m; ++j) {
                    if (res[i + j] != str2.charAt(j)) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    // Try to break lex smallest
                    boolean changed = false;
                    for (int j = m - 1; j >= 0 && !changed; --j) {
                        int pos = i + j;
                        for (char c = (char) (str2.charAt(j) + 1); c <= 'z'; ++c) {
                            if (res[pos] == str2.charAt(j)) {
                                // Check if changing to c is valid (doesn't break T's)
                                boolean ok = true;
                                for (int k = 0; k < n; ++k) {
                                    if (str1.charAt(k) == 'T') {
                                        int start = k, end = k + m - 1;
                                        if (pos >= start && pos <= end) {
                                            if (str2.charAt(pos - start) != c) {
                                                ok = false;
                                                break;
                                            }
                                        }
                                    }
                                }
                                if (ok) {
                                    res[pos] = c;
                                    changed = true;
                                    break;
                                }
                            }
                        }
                    }
                    if (!changed) return "";
                }
            }
        }
        // Step 4: Final verification of all constraints
        for (int i = 0; i < n; ++i) {
            boolean match = true;
            for (int j = 0; j < m; ++j) {
                if (res[i + j] != str2.charAt(j)) {
                    match = false;
                    break;
                }
            }
            if ((str1.charAt(i) == 'T' && !match) || (str1.charAt(i) == 'F' && match)) {
                return "";
            }
        }
        return new String(res);
    }
}
# @lc code=end