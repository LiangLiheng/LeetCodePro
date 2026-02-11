#
# @lc app=leetcode id=3413 lang=python3
#
# [3413] Maximum Coins From K Consecutive Bags
#
# @lc code=start
from typing import List
from bisect import bisect_left, bisect_right
class Solution:
    def maximumCoins(self, coins: List[List[int]], k: int) -> int:
        # Collect all unique segment endpoints
        events = []
        for l, r, c in coins:
            events.append((l, c))
            events.append((r + 1, -c))
        events.sort()
        # Build position and prefix sum arrays
        pos = []
        coin_at = []
        cur = 0
        prev = None
        for p, delta in events:
            if prev is not None and p != prev:
                pos.append(prev)
                coin_at.append(cur)
            cur += delta
            prev = p
        # Add last position if needed
        if prev is not None:
            pos.append(prev)
            coin_at.append(cur)
        n = len(pos)
        # Build prefix sum of coins over positions
        prefix = [0]
        for i in range(n - 1):
            segment_len = pos[i+1] - pos[i]
            prefix.append(prefix[-1] + coin_at[i] * segment_len)
        max_coins = 0
        # Slide window of size k
        for i in range(n - 1):
            window_start = pos[i]
            window_end = window_start + k
            # Find the rightmost index where pos[j] < window_end
            j = bisect_left(pos, window_end, i, n) - 1
            total = prefix[j+1] - prefix[i]
            # Add partial segment if needed
            overlap = max(0, window_end - pos[j])
            if j < n - 1 and overlap > 0:
                total += coin_at[j] * overlap
            max_coins = max(max_coins, total)
        return max_coins
# @lc code=end