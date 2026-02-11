#
# @lc app=leetcode id=3768 lang=python3
#
# [3768] Minimum Inversion Count in Subarrays of Fixed Length
#

# @lc code=start
class Solution:
    def minInversionCount(self, nums: List[int], k: int) -> int:
        class FenwickTree:
            def __init__(self, size: int):
                self.size = size
                self.tree = [0] * (size + 2)
            def update(self, index: int, delta: int) -> None:
                while index <= self.size:
                    self.tree[index] += delta
                    index += index & -index
            def query(self, index: int) -> int:
                res = 0
                while index > 0:
                    res += self.tree[index]
                    index -= index & -index
                return res
        n = len(nums)
        vals = sorted(set(nums))
        rank = {v: i + 1 for i, v in enumerate(vals)}
        m = len(vals)
        ft = FenwickTree(m)
        inv = 0
        for i in range(k):
            rnk = rank[nums[i]]
            inv += ft.query(m) - ft.query(rnk)
            ft.update(rnk, 1)
        ans = inv
        for i in range(1, n - k + 1):
            rnk_out = rank[nums[i - 1]]
            delta_out = ft.query(rnk_out - 1)
            inv -= delta_out
            ft.update(rnk_out, -1)
            idx_in = i + k - 1
            rnk_in = rank[nums[idx_in]]
            cnt_leq = ft.query(rnk_in)
            delta_in = (k - 1) - cnt_leq
            inv += delta_in
            ft.update(rnk_in, 1)
            ans = min(ans, inv)
        return ans

# @lc code=end