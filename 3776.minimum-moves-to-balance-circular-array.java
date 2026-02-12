#
# @lc app=leetcode id=3776 lang=java
#
# [3776] Minimum Moves to Balance Circular Array
#

# @lc code=start
class Solution {
    public long minMoves(int[] balance) {
        int n = balance.length;
        long total = 0;
        for (int b : balance) total += b;
        if (total < 0) return -1;
        int negIdx = -1;
        for (int i = 0; i < n; ++i) {
            if (balance[i] < 0) {
                negIdx = i;
                break;
            }
        }
        if (negIdx == -1) return 0;
        if (n == 1) return balance[0] < 0 ? -1 : 0;
        long moves = 0;
        int[] arr = balance.clone();
        // Simulate step-by-step transfer
        int need = -arr[negIdx];
        int left = (negIdx - 1 + n) % n;
        int right = (negIdx + 1) % n;
        while (need > 0) {
            // Try to transfer from left neighbor
            if (arr[left] > 0) {
                arr[left]--;
                arr[negIdx]++;
                moves++;
                need--;
                continue;
            }
            // Try to transfer from right neighbor
            if (arr[right] > 0) {
                arr[right]--;
                arr[negIdx]++;
                moves++;
                need--;
                continue;
            }
            // If both neighbors cannot give, try to move balance from further away
            // Simulate moving from further left
            int dist = 2;
            boolean transferred = false;
            while (dist < n) {
                int src = (negIdx - dist + n) % n;
                if (arr[src] > 0) {
                    // Move balance stepwise toward negIdx
                    for (int d = src; d != left; d = (d + 1) % n) {
                        if (arr[d] > 0) {
                            arr[d]--;
                            arr[(d + 1) % n]++;
                            moves++;
                        }
                    }
                    break;
                }
                dist++;
            }
            // Simulate moving from further right
            dist = 2;
            while (dist < n) {
                int src = (negIdx + dist) % n;
                if (arr[src] > 0) {
                    // Move balance stepwise toward negIdx
                    for (int d = src; d != right; d = (d - 1 + n) % n) {
                        if (arr[d] > 0) {
                            arr[d]--;
                            arr[(d - 1 + n) % n]++;
                            moves++;
                        }
                    }
                    break;
                }
                dist++;
            }
            // After attempting all, check again
            if (arr[left] > 0) continue;
            if (arr[right] > 0) continue;
            // If unable to transfer any more, return -1
            return -1;
        }
        // Verify all balances are non-negative
        for (int b : arr) if (b < 0) return -1;
        return moves;
    }
}
# @lc code=end