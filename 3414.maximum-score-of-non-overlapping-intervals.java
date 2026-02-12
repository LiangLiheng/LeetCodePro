//
// @lc app=leetcode id=3414 lang=java
//
// [3414] Maximum Score of Non-overlapping Intervals
//
// @lc code=start
class Solution {
    public int[] maximumWeight(List<List<Integer>> intervals) {
        int n = intervals.size();
        int[][] arr = new int[n][4]; // [l, r, weight, original_index]
        for (int i = 0; i < n; ++i) {
            List<Integer> iv = intervals.get(i);
            arr[i][0] = iv.get(0);
            arr[i][1] = iv.get(1);
            arr[i][2] = iv.get(2);
            arr[i][3] = i;
        }
        java.util.Arrays.sort(arr, java.util.Comparator.comparingInt(a -> a[1]));
        int[] ends = new int[n];
        for (int i = 0; i < n; ++i) ends[i] = arr[i][1];
        int[] prev = new int[n];
        for (int i = 0; i < n; ++i) {
            int l = arr[i][0];
            int lo = 0, hi = i - 1, res = -1;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (ends[mid] < l) {
                    res = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            prev[i] = res;
        }
        int K = 4;
        long[][] dp = new long[n + 1][K + 1];
        int[][][] idx = new int[n + 1][K + 1][K];
        for (int i = 0; i <= n; ++i)
            for (int k = 0; k <= K; ++k)
                for (int j = 0; j < K; ++j)
                    idx[i][k][j] = -1;
        for (int i = 1; i <= n; ++i) {
            for (int k = 1; k <= K; ++k) {
                // Option 1: not take current
                dp[i][k] = dp[i - 1][k];
                System.arraycopy(idx[i - 1][k], 0, idx[i][k], 0, K);
                // Option 2: take current
                int j = prev[i - 1] + 1;
                long candidate = dp[j][k - 1] + arr[i - 1][2];
                if (candidate > dp[i][k] || (candidate == dp[i][k] && lexSmaller(idx[j][k - 1], k - 1, idx[i][k], k, arr[i - 1][3]))) {
                    dp[i][k] = candidate;
                    for (int m = 0; m < k - 1; ++m) idx[i][k][m] = idx[j][k - 1][m];
                    idx[i][k][k - 1] = arr[i - 1][3];
                    for (int m = k; m < K; ++m) idx[i][k][m] = -1;
                }
            }
            // k=0
            dp[i][0] = dp[i - 1][0];
            System.arraycopy(idx[i - 1][0], 0, idx[i][0], 0, K);
        }
        long best = -1;
        int[] ans = new int[0];
        for (int k = 1; k <= K; ++k) {
            if (dp[n][k] > best) {
                best = dp[n][k];
                ans = extract(idx[n][k], k);
            } else if (dp[n][k] == best && lexSmaller(idx[n][k], k, ans, ans.length, -1)) {
                ans = extract(idx[n][k], k);
            }
        }
        return ans;
    }
    private boolean lexSmaller(int[] a, int lenA, int[] b, int lenB, int extra) {
        int[] A = new int[lenA + (extra >= 0 ? 1 : 0)];
        for (int i = 0; i < lenA; ++i) A[i] = a[i];
        if (extra >= 0) A[lenA] = extra;
        java.util.Arrays.sort(A);
        int[] B = new int[lenB];
        for (int i = 0; i < lenB; ++i) B[i] = b[i];
        java.util.Arrays.sort(B);
        int n = Math.min(A.length, B.length);
        for (int i = 0; i < n; ++i) {
            if (A[i] < B[i]) return true;
            if (A[i] > B[i]) return false;
        }
        return A.length < B.length;
    }
    private int[] extract(int[] arr, int k) {
        int[] res = new int[k];
        for (int i = 0; i < k; ++i) res[i] = arr[i];
        java.util.Arrays.sort(res);
        return res;
    }
}
// @lc code=end