#
# @lc app=leetcode id=3470 lang=python3
#
# [3470] Permutations IV
#

# @lc code=start
from typing import List
from functools import lru_cache

class Solution:
    def permute(self, n: int, k: int) -> List[int]:
        odds = [i for i in range(1, n+1) if i % 2 == 1]
        evens = [i for i in range(1, n+1) if i % 2 == 0]
        total_odds, total_evens = len(odds), len(evens)
        
        @lru_cache(maxsize=None)
        def count(o, e, p):
            if o + e == 0:
                return 1
            res = 0
            if p == 0:
                if o > 0:
                    res += o * count(o-1, e, 1)
                if e > 0:
                    res += e * count(o, e-1, 2)
            elif p == 1:
                if e > 0:
                    res += e * count(o, e-1, 2)
            else:
                if o > 0:
                    res += o * count(o-1, e, 1)
            return res

        total_valid = count(total_odds, total_evens, 0)
        if k > total_valid:
            return []

        res = []
        o, e = total_odds, total_evens
        p = 0
        avail = set(range(1, n+1))
        for pos in range(n):
            for v in sorted(avail):
                v_parity = 1 if v % 2 == 1 else 2
                if p == 0 or p != v_parity:
                    no = o - (1 if v_parity == 1 else 0)
                    ne = e - (1 if v_parity == 2 else 0)
                    cnt = count(no, ne, v_parity)
                    if k > cnt:
                        k -= cnt
                    else:
                        res.append(v)
                        avail.remove(v)
                        if v_parity == 1:
                            o -= 1
                        else:
                            e -= 1
                        p = v_parity
                        break
        # Verification step for general correctness
        if len(res) != n:
            return []
        for i in range(1, n):
            if (res[i] % 2) == (res[i-1] % 2):
                return []
        return res
# @lc code=end