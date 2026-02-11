#
# @lc app=leetcode id=3525 lang=python3
#
# [3525] Find X Value of Array II
#

# @lc code=start
class Solution:
    def resultArray(self, nums: List[int], k: int, queries: List[List[int]]) -> List[int]:
        res = []
        nums = nums[:]
        for idx, val, start, xi in queries:
            nums[idx] = val  # Step 1: Update nums persistently
            arr = nums[start:]  # Step 2: Remove prefix
            m = len(arr)
            prefix_prod = [1]
            # Step 4: Precompute prefix products modulo k
            for num in arr:
                prefix_prod.append((prefix_prod[-1] * num) % k)
            cnt = 0
            # Step 5: Consider all non-empty prefixes after possible suffix removals
            for t in range(1, m + 1):
                if prefix_prod[t] == xi:
                    cnt += 1
            res.append(cnt)
        return res
# @lc code=end