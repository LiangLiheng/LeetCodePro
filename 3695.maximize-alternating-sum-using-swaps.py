#
# @lc app=leetcode id=3695 lang=python3
#
# [3695] Maximize Alternating Sum Using Swaps
#

# @lc code=start
class Solution:
    def maxAlternatingSum(self, nums: List[int], swaps: List[List[int]]) -> int:
        n = len(nums)
        parent = list(range(n))
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        def union(x, y):
            px, py = find(x), find(y)
            if px != py:
                parent[px] = py
        for a, b in swaps:
            union(a, b)
        from collections import defaultdict
        groups = defaultdict(list)
        for i in range(n):
            groups[find(i)].append(i)
        res = [0]*n
        for indices in groups.values():
            vals = [nums[i] for i in indices]
            indices.sort()
            vals.sort(reverse=True)
            for idx, val in zip(indices, vals):
                res[idx] = val
        ans = 0
        for i,v in enumerate(res):
            if i%2==0:
                ans += v
            else:
                ans -= v
        return ans
# @lc code=end