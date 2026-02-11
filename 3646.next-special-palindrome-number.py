#
# @lc app=leetcode id=3646 lang=python3
#
# [3646] Next Special Palindrome Number
#

# @lc code=start
class Solution:
    def specialPalindrome(self, n: int) -> int:
        s_n = str(n)
        len_n = len(s_n)
        candidates = []
        even_ds = [2, 4, 6, 8]
        odds = [1, 3, 5, 7, 9]

        def get_smallest_pal(pair_counts, is_odd, o, L):
            m = L // 2
            remaining = dict(pair_counts)
            paired_left = []
            for _ in range(m):
                for d in range(1, 10):
                    if d in remaining and remaining[d] > 0:
                        paired_left.append(str(d))
                        remaining[d] -= 1
                        break
            paired_left_str = ''.join(paired_left)
            rev_paired = paired_left_str[::-1]
            if is_odd:
                left_str = paired_left_str + str(o)
            else:
                left_str = paired_left_str
            return left_str + rev_paired

        def get_next_pal(pair_counts, is_odd, o, L, target):
            m = L // 2
            all_paired = []
            def backtrack(curr, rem):
                if len(curr) == m:
                    all_paired.append(''.join(curr))
                    return
                for d in range(1, 10):
                    if d in rem and rem[d] > 0:
                        rem[d] -= 1
                        curr.append(str(d))
                        backtrack(curr, rem)
                        curr.pop()
                        rem[d] += 1
            backtrack([], dict(pair_counts))
            all_paired.sort()
            for p_left in all_paired:
                rev_paired = p_left[::-1]
                if is_odd:
                    left_str = p_left + str(o)
                else:
                    left_str = p_left
                full_str = left_str + rev_paired
                if full_str > target:
                    return full_str
            return None

        # Even length palindromes
        for mask in range(1, 16):
            S = [even_ds[j] for j in range(4) if (mask & (1 << j))]
            L = sum(S)
            if L < len_n:
                continue
            pair_counts = {d: d // 2 for d in S}
            if L == len_n:
                nextf = get_next_pal(pair_counts, False, 0, L, s_n)
                if nextf:
                    candidates.append(nextf)
            else:
                sm = get_smallest_pal(pair_counts, False, 0, L)
                candidates.append(sm)

        # Odd length palindromes
        for o in odds:
            for mask in range(16):
                S_e = [even_ds[j] for j in range(4) if (mask & (1 << j))]
                L = o + sum(S_e)
                if L < len_n:
                    continue
                pair_counts = {d: d // 2 for d in S_e}
                pair_counts[o] = (o - 1) // 2
                if L == len_n:
                    nextf = get_next_pal(pair_counts, True, o, L, s_n)
                    if nextf:
                        candidates.append(nextf)
                else:
                    sm = get_smallest_pal(pair_counts, True, o, L)
                    candidates.append(sm)

        return min(int(c) for c in candidates)
# @lc code=end