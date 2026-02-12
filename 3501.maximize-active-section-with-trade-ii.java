import java.util.*;
class Solution {
    public List<Integer> maxActiveSectionsAfterTrade(String s, int[][] queries) {
        List<Integer> res = new ArrayList<>();
        for (int[] q : queries) {
            int l = q[0], r = q[1];
            String sub = s.substring(l, r+1);
            String t = "1" + sub + "1";
            int n = t.length();
            int orig = countBlocks(t);
            int maxBlocks = orig;
            List<int[]> oneBlocks = findBlocks(t, '1');
            for (int[] block : oneBlocks) {
                if (block[0] == 0 || block[1] == n-1) continue;
                if (t.charAt(block[0]-1) == '0' && t.charAt(block[1]+1) == '0') {
                    char[] arr = t.toCharArray();
                    for (int i = block[0]; i <= block[1]; ++i) arr[i] = '0';
                    List<int[]> zeroBlocks = findBlocks(new String(arr), '0');
                    for (int[] zblock : zeroBlocks) {
                        if (zblock[0] == 0 || zblock[1] == n-1) continue;
                        if (arr[zblock[0]-1] == '1' && arr[zblock[1]+1] == '1') {
                            char[] arr2 = arr.clone();
                            for (int i = zblock[0]; i <= zblock[1]; ++i) arr2[i] = '1';
                            int count = countBlocks(new String(arr2));
                            maxBlocks = Math.max(maxBlocks, count);
                        }
                    }
                }
            }
            res.add(maxBlocks);
        }
        return res;
    }
    private int countBlocks(String t) {
        int n = t.length();
        int left = 1, right = n - 2;
        int cnt = 0, i = left;
        while (i <= right) {
            while (i <= right && t.charAt(i) != '1') ++i;
            if (i > right) break;
            cnt++;
            while (i <= right && t.charAt(i) == '1') ++i;
        }
        return cnt;
    }
    private List<int[]> findBlocks(String s, char c) {
        List<int[]> res = new ArrayList<>();
        int n = s.length(), i = 0;
        while (i < n) {
            while (i < n && s.charAt(i) != c) ++i;
            if (i == n) break;
            int start = i;
            while (i < n && s.charAt(i) == c) ++i;
            int end = i-1;
            res.add(new int[]{start, end});
        }
        return res;
    }
}