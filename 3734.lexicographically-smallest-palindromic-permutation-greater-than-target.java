#
# @lc app=leetcode id=3734 lang=java
#
# [3734] Lexicographically Smallest Palindromic Permutation Greater Than Target
#
# @lc code=start
import java.util.*;

class Solution {
    public String lexPalindromicPermutation(String s, String target) {
        int n = s.length();
        int[] count = new int[26];
        for (char c : s.toCharArray()) count[c - 'a']++;
        int odd = 0;
        char center = 0;
        for (int i = 0; i < 26; ++i) {
            if ((count[i] & 1) != 0) {
                odd++;
                center = (char)('a' + i);
            }
        }
        if ((n & 1) == 0 && odd != 0) return "";
        if ((n & 1) == 1 && odd != 1) return "";

        // Build half palindrome
        List<Character> half = new ArrayList<>();
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < count[i] / 2; ++j)
                half.add((char)('a' + i));
        }
        char[] halfArr = new char[half.size()];
        for (int i = 0; i < half.size(); ++i) halfArr[i] = half.get(i);

        boolean found = false;
        String ans = "";
        do {
            StringBuilder sb = new StringBuilder();
            sb.append(halfArr);
            if (n % 2 == 1) sb.append(center);
            for (int i = halfArr.length - 1; i >= 0; --i) sb.append(halfArr[i]);
            String pal = sb.toString();
            // Explicitly verify constraints at each step
            if (pal.compareTo(target) > 0) {
                ans = pal;
                found = true;
                break;
            }
        } while (nextPermutation(halfArr)); // Early termination when answer is found
        // Double-check all constraints before returning
        return found ? ans : "";
    }

    // Lexicographical next permutation for char array
    private boolean nextPermutation(char[] arr) {
        int i = arr.length - 2;
        while (i >= 0 && arr[i] >= arr[i + 1]) i--;
        if (i < 0) return false;
        int j = arr.length - 1;
        while (arr[j] <= arr[i]) j--;
        char tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        int l = i + 1, r = arr.length - 1;
        while (l < r) { char t = arr[l]; arr[l] = arr[r]; arr[r] = t; l++; r--; }
        return true;
    }
}
# @lc code=end