#
# @lc app=leetcode id=3445 lang=python3
#
# [3445] Maximum Difference Between Even and Odd Frequency II
#

# @lc code=start
class Solution:
    def maxDifference(self, s: str, k: int) -> int:
        import bisect
        n = len(s)
        prefix = [[0] * 5 for _ in range(n + 1)]
        for i in range(1, n + 1):
            c = ord(s[i - 1]) - ord('0')
            prefix[i] = prefix[i - 1][:]
            prefix[i][c] += 1
        ans = -10**9 - 1
        for a in range(5):
            for b in range(5):
                if a == b:
                    continue
                pa_list = [prefix[i][a] % 2 for i in range(n + 1)]
                pb_list = [prefix[i][b] % 2 for i in range(n + 1)]
                dp = [prefix[i][a] - prefix[i][b] for i in range(n + 1)]
                groups = [[] for _ in range(4)]
                for i in range(n + 1):
                    state = (pa_list[i] << 1) | pb_list[i]
                    groups[state].append(i)
                prefix_mins = []
                for st in range(4):
                    poss = groups[st]
                    if not poss:
                        prefix_mins.append([])
                        continue
                    m = len(poss)
                    pm = [0] * m
                    pm[0] = dp[poss[0]]
                    for j in range(1, m):
                        pm[j] = min(pm[j - 1], dp[poss[j]])
                    prefix_mins.append(pm)
                for right_idx in range(k, n + 1):
                    target_pa_left = 1 ^ pa_list[right_idx]
                    target_pb_left = pb_list[right_idx]
                    target_st = (target_pa_left << 1) | target_pb_left
                    max_l_len = right_idx - k
                    if max_l_len < 0:
                        continue
                    max_cb = prefix[right_idx][b] - 2
                    if max_cb < 0:
                        continue
                    # bin search largest <= max_l_len with prefix[..][b] <= max_cb
                    l, r = 0, max_l_len + 1
                    while l < r:
                        mid = (l + r) // 2
                        if prefix[mid][b] <= max_cb:
                            l = mid + 1
                        else:
                            r = mid
                    l_max_cb = l - 1
                    if l_max_cb < 0 or prefix[l_max_cb][b] > max_cb:
                        continue
                    l_max = min(max_l_len, l_max_cb)
                    poss = groups[target_st]
                    if not poss:
                        continue
                    j = bisect.bisect_right(poss, l_max) - 1
                    if j < 0:
                        continue
                    min_dpl = prefix_mins[target_st][j]
                    cur = dp[right_idx] - min_dpl
                    ans = max(ans, cur)
        return -1 if ans == -10**9 - 1 else ans

# @lc code=end