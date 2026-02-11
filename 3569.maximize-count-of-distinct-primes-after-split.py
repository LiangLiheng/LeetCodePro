#
# @lc app=leetcode id=3569 lang=python3
#
# [3569] Maximize Count of Distinct Primes After Split
#

# @lc code=start
from typing import List
from collections import defaultdict
import heapq

class Solution:
    def maximumCount(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        def get_min_pos(prime_pos, min_heaps, p):
            minh = min_heaps[p]
            while minh and minh[0] not in prime_pos[p]:
                heapq.heappop(minh)
            return minh[0] if minh else -1

        def get_max_pos(prime_pos, max_heaps, p):
            maxh = max_heaps[p]
            while maxh and -maxh[0] not in prime_pos[p]:
                heapq.heappop(maxh)
            return -maxh[0] if maxh else -1

        class SegTree:
            def __init__(self, n: int):
                self.n = n
                self.tree = [0] * (4 * (n + 1))
                self.lazy = [0] * (4 * (n + 1))

            def push(self, v: int, tl: int, tr: int):
                if self.lazy[v] != 0:
                    self.tree[v] += self.lazy[v]
                    if tl != tr:
                        self.lazy[2 * v] += self.lazy[v]
                        self.lazy[2 * v + 1] += self.lazy[v]
                    self.lazy[v] = 0

            def update_range(self, v: int, tl: int, tr: int, l: int, r: int, add: int):
                self.push(v, tl, tr)
                if l > r:
                    return
                if tl == l and tr == r:
                    self.lazy[v] += add
                    self.push(v, tl, tr)
                    return
                tm = (tl + tr) // 2
                self.update_range(2 * v, tl, tm, l, min(r, tm), add)
                self.update_range(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, add)
                self.tree[v] = max(self.tree[2 * v], self.tree[2 * v + 1])

            def query_max(self, v: int, tl: int, tr: int, l: int, r: int) -> int:
                self.push(v, tl, tr)
                if l > r:
                    return float('-inf')
                if tl == l and tr == r:
                    return self.tree[v]
                tm = (tl + tr) // 2
                return max(
                    self.query_max(2 * v, tl, tm, l, min(r, tm)),
                    self.query_max(2 * v + 1, tm + 1, tr, max(l, tm + 1), r)
                )

        n = len(nums)
        if n == 0:
            return []
        MAXV = 100010
        is_prime = [True] * MAXV
        is_prime[0] = is_prime[1] = False
        for i in range(2, int(MAXV ** 0.5) + 1):
            if is_prime[i]:
                for j in range(i * i, MAXV, i):
                    is_prime[j] = False

        prime_pos = defaultdict(set)
        min_heaps = defaultdict(list)
        max_heaps = defaultdict(list)
        total_distinct = 0

        for i in range(n):
            v = nums[i]
            if v < MAXV and is_prime[v]:
                p = v
                old_len = len(prime_pos[p])
                prime_pos[p].add(i)
                heapq.heappush(min_heaps[p], i)
                heapq.heappush(max_heaps[p], -i)
                if old_len == 0:
                    total_distinct += 1

        seg = SegTree(n - 1)
        for p in list(prime_pos.keys()):
            if len(prime_pos[p]) >= 2:
                mn = get_min_pos(prime_pos, min_heaps, p)
                mx = get_max_pos(prime_pos, max_heaps, p)
                l = mn + 1
                r = mx
                if l <= r:
                    seg.update_range(1, 1, n - 1, l, r, 1)

        ans = []
        for idx, val in queries:
            oldv = nums[idx]
            nums[idx] = val

            # Handle removal of oldv
            if oldv < MAXV and is_prime[oldv]:
                p = oldv
                old_len = len(prime_pos[p])
                if old_len >= 2:
                    mn = get_min_pos(prime_pos, min_heaps, p)
                    mx = get_max_pos(prime_pos, max_heaps, p)
                    l = mn + 1
                    r = mx
                    if l <= r:
                        seg.update_range(1, 1, n - 1, l, r, -1)
                prime_pos[p].remove(idx)
                new_len = old_len - 1
                if new_len == 0:
                    total_distinct -= 1
                if new_len >= 2:
                    mn = get_min_pos(prime_pos, min_heaps, p)
                    mx = get_max_pos(prime_pos, max_heaps, p)
                    l = mn + 1
                    r = mx
                    if l <= r:
                        seg.update_range(1, 1, n - 1, l, r, 1)

            # Handle addition of val
            if val < MAXV and is_prime[val]:
                p = val
                old_len = len(prime_pos[p])
                if old_len >= 2:
                    mn = get_min_pos(prime_pos, min_heaps, p)
                    mx = get_max_pos(prime_pos, max_heaps, p)
                    l = mn + 1
                    r = mx
                    if l <= r:
                        seg.update_range(1, 1, n - 1, l, r, -1)
                prime_pos[p].add(idx)
                heapq.heappush(min_heaps[p], idx)
                heapq.heappush(max_heaps[p], -idx)
                new_len = old_len + 1
                if old_len == 0:
                    total_distinct += 1
                if new_len >= 2:
                    mn = get_min_pos(prime_pos, min_heaps, p)
                    mx = get_max_pos(prime_pos, max_heaps, p)
                    l = mn + 1
                    r = mx
                    if l <= r:
                        seg.update_range(1, 1, n - 1, l, r, 1)

            max_inter = seg.query_max(1, 1, n - 1, 1, n - 1)
            ans.append(total_distinct + max_inter)

        return ans

# @lc code=end