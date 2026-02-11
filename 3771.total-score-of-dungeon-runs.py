#
# @lc app=leetcode id=3771 lang=python3
#
# [3771] Total Score of Dungeon Runs
#

# @lc code=start
import bisect
from typing import List

class Solution:
    def totalScore(self, hp: int, damage: List[int], requirement: List[int]) -> int:
        n = len(damage)
        prefix = [0] * (n + 1)
        for i in range(1, n + 1):
            prefix[i] = prefix[i - 1] + damage[i - 1]
        ans = 0
        for i in range(n):
            thresh = prefix[i + 1] + requirement[i] - hp
            left = bisect.bisect_left(prefix, thresh, 0, i + 1)
            ans += i + 1 - left
        return ans
# @lc code=end