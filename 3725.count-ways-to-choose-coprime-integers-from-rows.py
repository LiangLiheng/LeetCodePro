#
# @lc app=leetcode id=3725 lang=python3
#
# [3725] Count Ways to Choose Coprime Integers from Rows
#

# @lc code=start
class Solution:
    def countCoprime(self, mat: List[List[int]]) -> int:
        MOD = 10**9 + 7
        MAXN = 150
        # Compute Mobius function
        mu = [0] * (MAXN + 1)
        is_composite = [False] * (MAXN + 1)
        primes = []
        mu[1] = 1
        for i in range(2, MAXN + 1):
            if not is_composite[i]:
                primes.append(i)
                mu[i] = -1
            for p in primes:
                if i * p > MAXN:
                    break
                is_composite[i * p] = True
                if i % p == 0:
                    mu[i * p] = 0
                    break
                else:
                    mu[i * p] = -mu[i]
        # Frequency per row
        m = len(mat)
        freq = [[0] * (MAXN + 1) for _ in range(m)]
        for i in range(m):
            for x in mat[i]:
                if 1 <= x <= MAXN:
                    freq[i][x] += 1
        # Compute answer
        ans = 0
        for d in range(1, MAXN + 1):
            if mu[d] == 0:
                continue
            ways = 1
            zero_count = False
            for i in range(m):
                cnt = sum(freq[i][j] for j in range(d, MAXN + 1, d))
                if cnt == 0:
                    zero_count = True
                    break
                ways = (ways * cnt) % MOD
            if zero_count:
                continue
            contrib = (mu[d] * ways) % MOD
            ans = (ans + contrib) % MOD
        return ans

# @lc code=end