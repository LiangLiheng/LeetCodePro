#
# @lc app=leetcode id=3777 lang=python3
#
# [3777] Minimum Deletions to Make Alternating Substring
#

# @lc code=start
from typing import List

class Solution:
    def minDeletions(self, s: str, queries: List[List[int]]) -> List[int]:
        class FenwickTree:
            def __init__(self, size: int):
                self.size = size
                self.tree = [0] * (size + 2)

            def update(self, index: int, delta: int):
                index += 1
                while index <= self.size:
                    self.tree[index] += delta
                    index += index & -index

            def query(self, index: int) -> int:
                index += 1
                res = 0
                while index > 0:
                    res += self.tree[index]
                    index -= index & -index
                return res

            def range_query(self, left: int, right: int) -> int:
                return self.query(right) - (self.query(left - 1) if left > 0 else 0)

        n = len(s)
        s_list = list(s)
        ans = []
        ft = FenwickTree(n - 1) if n > 1 else None
        if n > 1:
            for i in range(n - 1):
                val = 1 if s_list[i] != s_list[i + 1] else 0
                ft.update(i, val)
        for qry in queries:
            if len(qry) == 2:
                # flip
                j = qry[1]
                old_left = 1 if j > 0 and s_list[j - 1] != s_list[j] else 0
                old_right = 1 if j < n - 1 and s_list[j] != s_list[j + 1] else 0
                s_list[j] = 'A' if s_list[j] == 'B' else 'B'
                new_left = 1 if j > 0 and s_list[j - 1] != s_list[j] else 0
                new_right = 1 if j < n - 1 and s_list[j] != s_list[j + 1] else 0
                if ft is not None:
                    if j > 0:
                        ft.update(j - 1, new_left - old_left)
                    if j < n - 1:
                        ft.update(j, new_right - old_right)
            else:
                # query
                l, r = qry[1], qry[2]
                sublen = r - l + 1
                if sublen == 1:
                    ans.append(0)
                else:
                    changes = ft.range_query(l, r - 1)
                    dels = sublen - 1 - changes
                    ans.append(dels)
        return ans

# @lc code=end