#
# @lc app=leetcode id=3525 lang=python3
#
# [3525] Find X Value of Array II
#

# @lc code=start
from typing import List


class SegTree:
    def __init__(self, a: List[int], k: int):
        self.n = len(a)
        self.k = k
        self.a = a[:]
        self.tree_total = [0] * (4 * self.n + 4)
        self.tree_count = [[0] * k for _ in range(4 * self.n + 4)]
        if self.n > 0:
            self._build(1, 0, self.n - 1)

    def _build(self, node: int, start: int, end: int) -> None:
        if start == end:
            val = self.a[start]
            self.tree_total[node] = val
            self.tree_count[node][val] = 1
            return
        mid = (start + end) // 2
        self._build(2 * node, start, mid)
        self._build(2 * node + 1, mid + 1, end)
        self._merge(node, 2 * node, 2 * node + 1)

    def _merge(self, node: int, left: int, right: int) -> None:
        l_total = self.tree_total[left]
        r_total = self.tree_total[right]
        self.tree_total[node] = (l_total * r_total) % self.k
        temp = [0] * self.k
        for z in range(self.k):
            mapped = (l_total * z) % self.k
            temp[mapped] += self.tree_count[right][z]
        for x in range(self.k):
            self.tree_count[node][x] = self.tree_count[left][x] + temp[x]

    def update(self, pos: int, new_val: int) -> None:
        self._update(1, 0, self.n - 1, pos, new_val)

    def _update(self, node: int, start: int, end: int, pos: int, new_val: int) -> None:
        if start == end:
            self.a[start] = new_val
            self.tree_total[node] = new_val
            for i in range(self.k):
                self.tree_count[node][i] = 0
            self.tree_count[node][new_val] = 1
            return
        mid = (start + end) // 2
        if pos <= mid:
            self._update(2 * node, start, mid, pos, new_val)
        else:
            self._update(2 * node + 1, mid + 1, end, pos, new_val)
        self._merge(node, 2 * node, 2 * node + 1)

    def query(self, left: int, right: int) -> tuple:
        return self._query(1, 0, self.n - 1, left, right)

    def _query(self, node: int, nstart: int, nend: int, l: int, r: int) -> tuple:
        if r < nstart or nend < l:
            return None
        if l <= nstart and nend <= r:
            return (self.tree_total[node], self.tree_count[node][:])
        mid = (nstart + nend) // 2
        lres = self._query(2 * node, nstart, mid, l, r)
        rres = self._query(2 * node + 1, mid + 1, nend, l, r)
        if lres is None:
            return rres
        if rres is None:
            return lres
        l_total, l_count = lres
        r_total, r_count = rres
        tot = (l_total * r_total) % self.k
        temp = [0] * self.k
        for z in range(self.k):
            mapped = (l_total * z) % self.k
            temp[mapped] += r_count[z]
        new_count = [l_count[x] + temp[x] for x in range(self.k)]
        return (tot, new_count)

class Solution:
    def resultArray(self, nums: List[int], k: int, queries: List[List[int]]) -> List[int]:
        n = len(nums)
        a = [num % k for num in nums]
        st = SegTree(a, k)
        result = []
        for query in queries:
            indexi, valuei, starti, xi = query
            new_val = valuei % k
            st.update(indexi, new_val)
            _, counts = st.query(starti, n - 1)
            result.append(counts[xi])
        return result

# @lc code=end