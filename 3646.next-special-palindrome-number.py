#
# @lc app=leetcode id=3646 lang=python3
#
# [3646] Next Special Palindrome Number
#

# @lc code=start
class Solution:
    def specialPalindrome(self, n: int) -> int:
        from itertools import combinations, permutations
        from collections import Counter
        
        # Step 1: Precompute all valid digit multisets (each digit k appears k times, digits 1-9)
        digit_sets = []
        for r in range(1, 10):
            for subset in combinations(range(1, 10), r):
                freq = []
                for d in subset:
                    freq.extend([str(d)] * d)
                digit_sets.append(freq)
        
        # Step 2: For each multiset, construct all valid palindromic numbers
        # Only construct one representative per unique half (to avoid full permutation explosion)
        candidates = set()
        for freq in digit_sets:
            total = len(freq)
            counter = Counter(freq)
            odd_digits = [d for d in counter if counter[d] % 2 == 1]
            if len(odd_digits) > 1:
                continue
            # Build half and center
            half = []
            center = ''
            for d in sorted(counter):
                if counter[d] % 2 == 1:
                    center = d
                half += [d] * (counter[d] // 2)
            # Generate unique half-permutations, enforce no leading zero
            seen = set()
            for perm in set(permutations(half)):
                if perm and perm[0] == '0':
                    continue
                left = ''.join(perm)
                pal_candidate = left + center + left[::-1]
                if pal_candidate and pal_candidate[0] != '0':
                    candidates.add(int(pal_candidate))
        # Step 3: Find the minimal candidate greater than n
        min_cand = None
        for x in candidates:
            if x > n:
                if min_cand is None or x < min_cand:
                    min_cand = x
        if min_cand is not None:
            return min_cand
        # Step 4: (Fallback, extremely rare) If no candidate found, incrementally search upwards
        curr = n + 1
        while True:
            s = str(curr)
            if s == s[::-1]:
                freq = Counter(s)
                if all(int(d) == freq[d] for d in freq):
                    return curr
            curr += 1
# @lc code=end