#
# @lc app=leetcode id=3474 lang=python3
#
# [3474] Lexicographically Smallest Generated String
#

# @lc code=start
class Solution:
    def generateString(self, str1: str, str2: str) -> str:
        n = len(str1)
        m = len(str2)
        L = n + m - 1
        req = [None] * L
        # Propagate 'T' constraints
        for i in range(n):
            if str1[i] == 'T':
                for j in range(m):
                    k = i + j
                    if req[k] is not None and req[k] != str2[j]:
                        return ''
                    req[k] = str2[j]
        # Check fully forced matching 'F' windows
        for i in range(n):
            if str1[i] == 'F':
                fully_match = True
                for j in range(m):
                    k = i + j
                    if req[k] is None or req[k] != str2[j]:
                        fully_match = False
                        break
                if fully_match:
                    return ''
        # Precompute constrain[i][s]: suffix after i+s fully forced and matches str2[s+1:]
        constrain = [[False] * m for _ in range(n)]
        for i in range(n):
            constrain[i][m - 1] = True
            for s in range(m - 2, -1, -1):
                pos = i + s + 1
                if req[pos] is None:
                    constrain[i][s] = False
                else:
                    constrain[i][s] = (req[pos] == str2[s + 1]) and constrain[i][s + 1]
        # Double hash setup
        MOD1 = 1000000007
        MOD2 = 1000000009
        BASE1 = 31
        BASE2 = 37
        pow1 = [1] * (L + 1)
        pow2 = [1] * (L + 1)
        for i in range(1, L + 1):
            pow1[i] = pow1[i - 1] * BASE1 % MOD1
            pow2[i] = pow2[i - 1] * BASE2 % MOD2
        # str2 hashes
        h1 = [0] * (m + 1)
        h2 = [0] * (m + 1)
        for j in range(m):
            val = ord(str2[j]) - ord('a') + 1
            h1[j + 1] = (h1[j] * BASE1 + val) % MOD1
            h2[j + 1] = (h2[j] * BASE2 + val) % MOD2
        def get_str2_hash(left: int, right: int) -> tuple[int, int]:
            len_ = right - left
            hh1 = (h1[right] - h1[left] * pow1[len_] % MOD1 + MOD1) % MOD1
            hh2 = (h2[right] - h2[left] * pow2[len_] % MOD2 + MOD2) % MOD2
            return hh1, hh2
        # word
        word = [''] * L
        wh1 = [0] * (L + 1)
        wh2 = [0] * (L + 1)
        def get_word_hash(a: int, b: int) -> tuple[int, int]:
            len_ = b - a
            hh1 = (wh1[b] - wh1[a] * pow1[len_] % MOD1 + MOD1) % MOD1
            hh2 = (wh2[b] - wh2[a] * pow2[len_] % MOD2 + MOD2) % MOD2
            return hh1, hh2
        for k in range(L):
            if req[k] is not None:
                word[k] = req[k]
                val = ord(word[k]) - ord('a') + 1
                wh1[k + 1] = (wh1[k] * BASE1 + val) % MOD1
                wh2[k + 1] = (wh2[k] * BASE2 + val) % MOD2
            else:
                forbidden = set()
                maxs = min(k, m - 1)
                for s in range(maxs + 1):
                    i = k - s
                    if not (0 <= i < n and str1[i] == 'F'):
                        continue
                    if not constrain[i][s]:
                        continue
                    if s == 0:
                        prefix_match = True
                    else:
                        ph1, ph2 = get_word_hash(i, k)
                        sh1, sh2 = get_str2_hash(0, s)
                        prefix_match = ph1 == sh1 and ph2 == sh2
                    if prefix_match:
                        forbidden.add(str2[s])
                chosen = None
                for cc in range(26):
                    c = chr(ord('a') + cc)
                    if c not in forbidden:
                        chosen = c
                        break
                if chosen is None:
                    return ''
                word[k] = chosen
                val = ord(chosen) - ord('a') + 1
                wh1[k + 1] = (wh1[k] * BASE1 + val) % MOD1
                wh2[k + 1] = (wh2[k] * BASE2 + val) % MOD2
        return ''.join(word)

# @lc code=end