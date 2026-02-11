#
# @lc app=leetcode id=3777 lang=python3
#
# [3777] Minimum Deletions to Make Alternating Substring
#

# @lc code=start
class Solution:
    def minDeletions(self, s: str, queries: List[List[int]]) -> List[int]:
        n = len(s)
        s = list(s)
        class SegmentTree:
            def __init__(self, n):
                self.N = n - 1
                self.size = 1
                while self.size < self.N:
                    self.size <<= 1
                self.tree = [0] * (self.size * 2)
            def build(self, data):
                for i in range(self.N):
                    self.tree[self.size + i] = data[i]
                for i in range(self.size - 1, 0, -1):
                    self.tree[i] = self.tree[i << 1] + self.tree[i << 1 | 1]
            def update(self, idx, val):
                idx += self.size
                self.tree[idx] = val
                while idx > 1:
                    idx >>= 1
                    self.tree[idx] = self.tree[idx << 1] + self.tree[idx << 1 | 1]
            def query(self, l, r):
                res = 0
                l += self.size
                r += self.size + 1
                while l < r:
                    if l & 1:
                        res += self.tree[l]
                        l += 1
                    if r & 1:
                        r -= 1
                        res += self.tree[r]
                    l >>= 1
                    r >>= 1
                return res
        # Build initial data: 1 if s[i] == s[i+1], else 0
        data = [1 if s[i] == s[i+1] else 0 for i in range(n-1)]
        seg = SegmentTree(n)
        seg.build(data)
        ans = []
        for q in queries:
            if q[0] == 1:
                j = q[1]
                # flip s[j]
                s[j] = 'A' if s[j] == 'B' else 'B'
                if j > 0:
                    seg.update(j-1, 1 if s[j-1] == s[j] else 0)
                if j < n-1:
                    seg.update(j, 1 if s[j] == s[j+1] else 0)
            else:
                l, r = q[1], q[2]
                if l == r:
                    ans.append(0)
                else:
                    ans.append(seg.query(l, r-1))
        return ans
# @lc code=end