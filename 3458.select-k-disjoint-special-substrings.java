#
# @lc app=leetcode id=3458 lang=java
#
# [3458] Select K Disjoint Special Substrings
#

# @lc code=start
class Solution {
    public boolean maxSubstringLength(String s, int k) {
        int n = s.length();
        int[] first = new int[26];
        int[] last = new int[26];
        java.util.Arrays.fill(first, -1);
        java.util.Arrays.fill(last, -1);
        for (int i = 0; i < n; i++) {
            int idx = s.charAt(i) - 'a';
            if (first[idx] == -1) first[idx] = i;
            last[idx] = i;
        }
        java.util.List<int[]> intervals = new java.util.ArrayList<>();
        for (int i = 0; i < n; i++) {
            int start = i;
            int end = i;
            // Expand the interval to include all last occurrences of characters in [start, end]
            for (int j = i; j <= end; j++) {
                end = Math.max(end, last[s.charAt(j) - 'a']);
            }
            // Only consider substrings not covering the entire string
            if (start != 0 || end != n - 1) {
                // Validate: for all characters in s[start:end], their first/last occurrence is within [start, end]
                boolean valid = true;
                for (int j = start; j <= end && valid; j++) {
                    int idx = s.charAt(j) - 'a';
                    if (first[idx] < start || last[idx] > end) {
                        valid = false;
                    }
                }
                if (valid) {
                    intervals.add(new int[]{start, end});
                }
            }
            i = end;
        }
        // Greedily select maximal set of disjoint intervals
        java.util.Collections.sort(intervals, (a, b) -> a[1] - b[1]);
        int count = 0, prevEnd = -1;
        for (int[] iv : intervals) {
            if (iv[0] > prevEnd) {
                count++;
                prevEnd = iv[1];
                if (count >= k) break;
            }
        }
        return count >= k;
    }
}
# @lc code=end