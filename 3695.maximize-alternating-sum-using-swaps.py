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
        rank = [0] * n
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        def union(x, y):
            px = find(x)
            py = find(y)
            if px == py:
                return
            if rank[px] < rank[py]:
                parent[px] = py
            elif rank[px] > rank[py]:
                parent[py] = px
            else:
                parent[py] = px
                rank[px] += 1
        for a, b in swaps:
            union(a, b)
        groups = {}
        for i in range(n):
            root = find(i)
            groups.setdefault(root, []).append(i)
        ans = 0
        for group in groups.values():
            vals = sorted(nums[i] for i in group)
            num_minus = sum(i % 2 == 1 for i in group)
            ans += sum(vals[num_minus:]) - sum(vals[:num_minus])
        return ans
# @lc code=end