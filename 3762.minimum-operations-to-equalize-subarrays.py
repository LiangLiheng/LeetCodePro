#
# @lc app=leetcode id=3762 lang=python3
#
# [3762] Minimum Operations to Equalize Subarrays
#

# @lc code=start
from typing import List
import bisect

class Solution:
    def minOperations(self, nums: List[int], k: int, queries: List[List[int]]) -> List[int]:
        n = len(nums)
        mods = [x % k for x in nums]
        qs = [x // k for x in nums]
        max_q = max(qs)
        prefix_qs = [0] * (n + 1)
        for i in range(n):
            prefix_qs[i + 1] = prefix_qs[i] + qs[i]
        # logg for sparse table
        logg = [0] * (n + 2)
        for i in range(2, n + 1):
            logg[i] = logg[i // 2] + 1
        LOG = logg[n] + 1
        # Sparse table for range min/max mods
        st_min = [[0] * n for _ in range(LOG)]
        st_max = [[0] * n for _ in range(LOG)]
        for i in range(n):
            st_min[0][i] = st_max[0][i] = mods[i]
        for j in range(1, LOG):
            for i in range(n - (1 << j) + 1):
                st_min[j][i] = min(st_min[j - 1][i], st_min[j - 1][i + (1 << (j - 1))])
                st_max[j][i] = max(st_max[j - 1][i], st_max[j - 1][i + (1 << (j - 1))])
        def range_min(l: int, r: int) -> int:
            leng = r - l + 1
            j = logg[leng]
            return min(st_min[j][l], st_min[j][r - (1 << j) + 1])
        def range_max(l: int, r: int) -> int:
            leng = r - l + 1
            j = logg[leng]
            return max(st_max[j][l], st_max[j][r - (1 << j) + 1])
        # Merge Sort Tree
        class MST:
            def __init__(self, n, qs):
                self.n = n
                self.tree = [[] for _ in range(4 * n)]
                self.pref = [[] for _ in range(4 * n)]
                self._build(1, 0, n - 1, qs)
            def _build(self, node, start, end, qs):
                if start == end:
                    self.tree[node] = [qs[start]]
                    self.pref[node] = [0, qs[start]]
                    return
                mid = (start + end) // 2
                self._build(2 * node, start, mid, qs)
                self._build(2 * node + 1, mid + 1, end, qs)
                left_list = self.tree[2 * node]
                right_list = self.tree[2 * node + 1]
                i = j = 0
                merged = []
                while i < len(left_list) and j < len(right_list):
                    if left_list[i] <= right_list[j]:
                        merged.append(left_list[i])
                        i += 1
                    else:
                        merged.append(right_list[j])
                        j += 1
                merged += left_list[i:]
                merged += right_list[j:]
                self.tree[node] = merged
                p = [0]
                for v in merged:
                    p.append(p[-1] + v)
                self.pref[node] = p
            def get_cover_nodes(self, node, start, end, l, r, nodes):
                if l > end or r < start:
                    return
                if l <= start and end <= r:
                    nodes.append(node)
                    return
                mid = (start + end) // 2
                self.get_cover_nodes(2 * node, start, mid, l, r, nodes)
                self.get_cover_nodes(2 * node + 1, mid + 1, end, l, r, nodes)
            def count_le(self, nodes, val):
                tot = 0
                for nd in nodes:
                    tot += bisect.bisect_right(self.tree[nd], val)
                return tot
            def sum_le(self, nodes, val):
                tot = 0
                for nd in nodes:
                    idx = bisect.bisect_right(self.tree[nd], val)
                    tot += self.pref[nd][idx]
                return tot
        mst = MST(n, qs)
        ans = []
        for l, r in queries:
            if range_min(l, r) != range_max(l, r):
                ans.append(-1)
                continue
            mlen = r - l + 1
            nodes = []
            mst.get_cover_nodes(1, 0, n - 1, l, r, nodes)
            low = 0
            high = max_q + 1
            need = mlen // 2 + 1
            while low < high:
                mid_val = low + (high - low) // 2
                if mst.count_le(nodes, mid_val) >= need:
                    high = mid_val
                else:
                    low = mid_val + 1
            med_val = low
            cnt_le = mst.count_le(nodes, med_val)
            sum_le = mst.sum_le(nodes, med_val)
            total_sum = prefix_qs[r + 1] - prefix_qs[l]
            ops = cnt_le * med_val - sum_le + total_sum - sum_le - (mlen - cnt_le) * med_val
            ans.append(ops)
        return ans
# @lc code=end