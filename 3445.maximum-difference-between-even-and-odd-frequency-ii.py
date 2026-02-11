#
# @lc app=leetcode id=3445 lang=python3
#
# [3445] Maximum Difference Between Even and Odd Frequency II
#

# @lc code=start
class Solution:
    def maxDifference(self, s: str, k: int) -> int:
        n = len(s)
        prefix = [[0] * (n + 1) for _ in range(5)]
        for p in range(1, n + 1):
            c = ord(s[p - 1]) - ord('0')
            for j in range(5):
                prefix[j][p] = prefix[j][p - 1] + (1 if j == c else 0)
        INF = 10**18 + 7
        ans = -INF
        N = n + 10
        class SegTree:
            def __init__(self, nn: int):
                self.sz = 1
                while self.sz < nn + 1:
                    self.sz <<= 1
                self.tree = [INF] * (2 * self.sz)
            def update(self, idx: int, val: int):
                idx += self.sz
                self.tree[idx] = min(self.tree[idx], val)
                idx >>= 1
                while idx >= 1:
                    self.tree[idx] = min(self.tree[2 * idx], self.tree[2 * idx + 1])
                    idx >>= 1
            def query(self, left: int, right: int) -> int:
                res = INF
                l = left + self.sz
                r = right + self.sz
                while l <= r:
                    if l & 1:
                        res = min(res, self.tree[l])
                        l += 1
                    if not (r & 1):
                        res = min(res, self.tree[r])
                        r -= 1
                    l >>= 1
                    r >>= 1
                return res
        for a in range(5):
            for b in range(5):
                parity_a = [prefix[a][p] % 2 for p in range(n + 1)]
                parity_b = [prefix[b][p] % 2 for p in range(n + 1)]
                val = [prefix[a][p] - prefix[b][p] for p in range(n + 1)]
                preb = prefix[b]
                segs = [[SegTree(N) for _ in range(2)] for _ in range(2)]
                current_lp = 0
                for rp in range(k, n + 1):
                    maxlp = rp - k
                    while current_lp <= maxlp:
                        pa_ = parity_a[current_lp]
                        pb_ = parity_b[current_lp]
                        cb = preb[current_lp]
                        v = val[current_lp]
                        segs[pa_][pb_].update(cb, v)
                        current_lp += 1
                    M = preb[rp] - 2
                    if M >= 0:
                        t_pa = 1 - parity_a[rp]
                        t_pb = parity_b[rp]
                        minv = segs[t_pa][t_pb].query(0, M)
                        if minv < INF:
                            ans = max(ans, val[rp] - minv)
        if ans == -INF:
            return -1
        return ans

# @lc code=end