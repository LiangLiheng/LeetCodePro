#
# @lc app=leetcode id=3721 lang=python3
#
# [3721] Longest Balanced Subarray II
#

# @lc code=start
from typing import List

class Solution:
    def longestBalanced(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 0:
            return 0
        
        class SegTree:
            def __init__(self, size: int):
                self.n = size
                N = 4 * (size + 2)
                self.minv = [0] * N
                self.maxv = [0] * N
                self.lazy = [0] * N
            
            def _push(self, node: int, start: int, end: int) -> None:
                if self.lazy[node] != 0:
                    self.minv[node] += self.lazy[node]
                    self.maxv[node] += self.lazy[node]
                    if start != end:
                        self.lazy[2 * node] += self.lazy[node]
                        self.lazy[2 * node + 1] += self.lazy[node]
                    self.lazy[node] = 0
            
            def _update_range(self, node: int, start: int, end: int, l: int, r: int, val: int) -> None:
                self._push(node, start, end)
                if start > r or end < l:
                    return
                if l <= start and end <= r:
                    self.lazy[node] += val
                    self._push(node, start, end)
                    return
                mid = (start + end) // 2
                self._update_range(2 * node, start, mid, l, r, val)
                self._update_range(2 * node + 1, mid + 1, end, l, r, val)
                self.minv[node] = min(self.minv[2 * node], self.minv[2 * node + 1])
                self.maxv[node] = max(self.maxv[2 * node], self.maxv[2 * node + 1])
            
            def update_range(self, l: int, r: int, val: int) -> None:
                if l > r:
                    return
                self._update_range(1, 0, self.n, l, r, val)
            
            def _get_value(self, node: int, start: int, end: int, idx: int) -> int:
                self._push(node, start, end)
                if start == end:
                    return self.minv[node]
                mid = (start + end) // 2
                if idx <= mid:
                    return self._get_value(2 * node, start, mid, idx)
                else:
                    return self._get_value(2 * node + 1, mid + 1, end, idx)
            
            def get_value(self, idx: int) -> int:
                return self._get_value(1, 0, self.n, idx)
            
            def _find_leftmost(self, node: int, start: int, end: int, target: int) -> int:
                self._push(node, start, end)
                if self.minv[node] > target or self.maxv[node] < target:
                    return -1
                if start == end:
                    return start
                mid = (start + end) // 2
                left_res = self._find_leftmost(2 * node, start, mid, target)
                if left_res != -1:
                    return left_res
                return self._find_leftmost(2 * node + 1, mid + 1, end, target)
            
            def find_leftmost(self, target: int) -> int:
                return self._find_leftmost(1, 0, self.n, target)
        
        tree = SegTree(n)
        last_pos: dict[int, int] = {}
        ans = 0
        for r in range(n):
            num = nums[r]
            is_even_num = (num % 2 == 0)
            contrib = -1 if is_even_num else 1
            old_pos = last_pos.get(num, -1)
            if old_pos != -1:
                remove_val = -contrib
                tree.update_range(old_pos + 1, n, remove_val)
            last_pos[num] = r
            tree.update_range(r + 1, n, contrib)
            target = tree.get_value(r + 1)
            i_min = tree.find_leftmost(target)
            j = i_min - 1
            length = r - j
            ans = max(ans, length)
        return ans

# @lc code=end