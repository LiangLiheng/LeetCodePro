#
# @lc app=leetcode id=3569 lang=python3
#
# [3569] Maximize Count of Distinct Primes After Split
#

# @lc code=start
class Solution:
    def maximumCount(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        MAXN = 10**5 + 1
        is_prime = [False, False] + [True] * (MAXN - 2)
        for i in range(2, int(MAXN ** 0.5) + 1):
            if is_prime[i]:
                for j in range(i * i, MAXN, i):
                    is_prime[j] = False
        def isPrime(x):
            return is_prime[x]
        n = len(nums)
        res = []
        for idx, val in queries:
            nums[idx] = val
            prefix_sets = [set() for _ in range(n + 1)]
            for i in range(1, n + 1):
                prefix_sets[i] = prefix_sets[i - 1].copy()
                if isPrime(nums[i - 1]):
                    prefix_sets[i].add(nums[i - 1])
            suffix_sets = [set() for _ in range(n + 1)]
            for i in range(n - 1, -1, -1):
                suffix_sets[i] = suffix_sets[i + 1].copy()
                if isPrime(nums[i]):
                    suffix_sets[i].add(nums[i])
            max_count = 0
            for k in range(1, n):
                count = len(prefix_sets[k]) + len(suffix_sets[k])
                max_count = max(max_count, count)
            res.append(max_count)
        return res
# @lc code=end