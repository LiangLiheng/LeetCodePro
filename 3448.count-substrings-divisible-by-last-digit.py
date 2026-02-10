#
# @lc app=leetcode id=3448 lang=python3
#
# [3448] Count Substrings Divisible By Last Digit
#
# @lc code=start
class Solution:
    def countSubstrings(self, s: str) -> int:
        n = len(s)
        ans = 0
        M_dict = {1:1, 2:1, 4:2, 5:1, 8:3}
        for d in range(1, 10):
            if d in M_dict:
                M = M_dict[d]
                for i in range(n):
                    if int(s[i]) != d:
                        continue
                    cnt = 0
                    max_short = min(M, i + 1)
                    for l in range(1, max_short + 1):
                        start = i - l + 1
                        num = int(s[start:i + 1])
                        if num % d == 0:
                            cnt += 1
                    if i + 1 > M:
                        startM = i - M + 1
                        numM = int(s[startM:i + 1])
                        if numM % d == 0:
                            cnt += i + 1 - M
                    ans += cnt
            elif d == 7:
                p = 6
                pow10_table = [0] * p
                pow10_table[0] = 1
                cur = 1
                for k in range(1, p):
                    cur = (cur * 10) % 7
                    pow10_table[k] = cur
                prefix_mod = 0
                freq = [[0] * 7 for _ in range(p)]
                freq[0][0] += 1
                local_ans = 0
                for i in range(n):
                    prefix_mod = (prefix_mod * 10 + int(s[i])) % 7
                    if int(s[i]) == 7:
                        count = 0
                        cur_pos_mod = (i + 1) % p
                        for cycle_res in range(p):
                            pow_val = pow10_table[cycle_res]
                            inv_pow = pow(pow_val, -1, 7)
                            req_prefix = (prefix_mod * inv_pow) % 7
                            req_j_p = (cur_pos_mod - cycle_res) % p
                            count += freq[req_j_p][req_prefix]
                        local_ans += count
                    pos_mod = (i + 1) % p
                    freq[pos_mod][prefix_mod] += 1
                ans += local_ans
            else:  # d=3,6,9
                modd = 3 if d == 6 else d
                prefix_mod = 0
                freq = [0] * modd
                freq[0] = 1
                local_ans = 0
                for i in range(n):
                    prefix_mod = (prefix_mod + int(s[i])) % modd
                    if int(s[i]) == d:
                        local_ans += freq[prefix_mod]
                    freq[prefix_mod] += 1
                ans += local_ans
        return ans
# @lc code=end