#
# @lc app=leetcode id=3771 lang=python3
#
# [3771] Total Score of Dungeon Runs
#

# @lc code=start
from typing import List

class Solution:
    def totalScore(self, hp: int, damage: List[int], requirement: List[int]) -> int:
        n = len(damage)
        # Suffix sum of damages to allow O(1) computation of cumulative damage from room j to i
        suffix_damage = [0] * (n + 1)
        for i in range(n - 1, -1, -1):
            suffix_damage[i] = suffix_damage[i + 1] + damage[i]

        total = 0
        # For each room, determine all possible starting points where you will have enough hp after damage
        # Instead, we reverse the approach: For each start position, simulate in one pass
        # But to achieve O(n) total, we process each run once
        cur_hp = [0] * n
        for start in range(n):
            cur_hp[start] = hp - suffix_damage[start] + damage[start]

        for start in range(n):
            h = hp
            for i in range(start, n):
                h -= damage[i]
                if h >= requirement[i]:
                    total += 1
        # Above is still O(n^2). Need O(n):
        # Instead, we process from the back: For each i, for all runs that include i, count the number of starts where hp - (prefix_damage[i+1] - prefix_damage[start]) >= requirement[i]
        # But that's still O(n^2). Optimize:
        # Reverse: For each room i, the health before entering is hp - (prefix_damage[i] - prefix_damage[start])
        # The score is number of starts s.t. hp - (prefix_damage[i] - prefix_damage[start]) >= requirement[i] ==> prefix_damage[start] <= hp - requirement[i] + prefix_damage[i]
        # So for each i, the number of start in [0, i] with prefix_damage[start] <= hp - requirement[i] + prefix_damage[i]
        # Build prefix_damage array:
        prefix_damage = [0] * (n + 1)
        for i in range(n):
            prefix_damage[i + 1] = prefix_damage[i] + damage[i]

        # For all i, process prefix_damage[0]...prefix_damage[i] and count number <= bound
        # This is equivalent to, for each i, count number of prefix_damage[s] for s in [0, i] <= hp - requirement[i] + prefix_damage[i]
        # Since prefix_damage is non-decreasing, we can use binary search
        import bisect
        res = 0
        for i in range(n):
            bound = hp - requirement[i] + prefix_damage[i+1]
            # bisect_right returns index of first prefix_damage > bound, so number <= bound is that index
            cnt = bisect.bisect_right(prefix_damage, bound, 0, i+1)
            res += cnt
        return res
# @lc code=end