#
# @lc app=leetcode id=3327 lang=python3
#
# [3327] Check if DFS Strings Are Palindromes
#

# @lc code=start
from typing import List
class Solution:
    def findAnswer(self, parent: List[int], s: str) -> List[bool]:
        n = len(parent)
        # Build adjacency list
        tree = [[] for _ in range(n)]
        for i in range(1, n):
            tree[parent[i]].append(i)
        for node in range(n):
            tree[node].sort()  # Ensure increasing order traversal

        # Hash parameters
        MOD1, MOD2 = 10**9 + 7, 10**9 + 9
        BASE1, BASE2 = 911, 3571

        # Precompute powers for both hashes
        pow1 = [1] * (n + 2)
        pow2 = [1] * (n + 2)
        for i in range(1, n + 2):
            pow1[i] = (pow1[i-1] * BASE1) % MOD1
            pow2[i] = (pow2[i-1] * BASE2) % MOD2

        # Store hashes and lengths for each node
        fw_hash1 = [0] * n
        fw_hash2 = [0] * n
        rv_hash1 = [0] * n
        rv_hash2 = [0] * n
        length = [0] * n

        def dfs(x):
            h1, h2 = 0, 0
            rh1, rh2 = 0, 0
            l = 0
            for y in tree[x]:
                dfs(y)
                # Append child's hashes/lengths to current
                h1 = (h1 * pow1[length[y]] + fw_hash1[y]) % MOD1
                h2 = (h2 * pow2[length[y]] + fw_hash2[y]) % MOD2
                rh1 = (rv_hash1[y] * pow1[l] + rh1) % MOD1
                rh2 = (rv_hash2[y] * pow2[l] + rh2) % MOD2
                l += length[y]
            # Add current node's character
            code = ord(s[x]) - ord('a') + 1
            h1 = (h1 * BASE1 + code) % MOD1
            h2 = (h2 * BASE2 + code) % MOD2
            rh1 = (rh1 + code * pow1[l]) % MOD1
            rh2 = (rh2 + code * pow2[l]) % MOD2
            l += 1
            fw_hash1[x], fw_hash2[x] = h1, h2
            rv_hash1[x], rv_hash2[x] = rh1, rh2
            length[x] = l

        for i in range(n):
            length[i] = 0
        dfs(0)

        answer = [False] * n
        def dfs_check(x):
            # For the subtree rooted at x, check palindrome
            answer[x] = (fw_hash1[x] == rv_hash1[x]) and (fw_hash2[x] == rv_hash2[x])
            for y in tree[x]:
                dfs_check(y)
        dfs_check(0)
        return answer
# @lc code=end