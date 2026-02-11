#
# @lc app=leetcode id=3501 lang=python3
#
# [3501] Maximize Active Section with Trade II
#

# @lc code=start
class Solution:
    def maxActiveSectionsAfterTrade(self, s: str, queries: List[List[int]]) -> List[int]:
        def get_blocks(t):
            # Returns list of (char, start, end) for contiguous blocks
            blocks = []
            prev = t[0]
            start = 0
            for i in range(1, len(t)):
                if t[i] != prev:
                    blocks.append((prev, start, i-1))
                    prev = t[i]
                    start = i
            blocks.append((prev, start, len(t)-1))
            return blocks
        
        def count_active_sections(t):
            # Counts the number of contiguous blocks of '1' in t (excluding augmented ends)
            count = 0
            in_section = False
            for ch in t[1:-1]:
                if ch == '1' and not in_section:
                    count += 1
                    in_section = True
                elif ch == '0':
                    in_section = False
            return count

        ans = []
        for li, ri in queries:
            substr = s[li:ri+1]
            t = '1' + substr + '1'
            blocks = get_blocks(t)
            # Initial count: number of '1' sections in t[1:-1]
            max_active = count_active_sections(t)
            # Try all valid trades: remove a block of '1's surrounded by '0's, then flip a block of '0's surrounded by '1's
            for i, (ch1, l1, r1) in enumerate(blocks):
                if ch1 == '1':
                    # Check if this block is surrounded by '0's
                    if i > 0 and i < len(blocks)-1 and blocks[i-1][0] == '0' and blocks[i+1][0] == '0':
                        # Remove this block (set to '0's)
                        t_list = list(t)
                        for j in range(l1, r1+1):
                            t_list[j] = '0'
                        t2 = ''.join(t_list)
                        blocks2 = get_blocks(t2)
                        for j, (ch2, l2, r2) in enumerate(blocks2):
                            if ch2 == '0' and j > 0 and j < len(blocks2)-1 and blocks2[j-1][0] == '1' and blocks2[j+1][0] == '1':
                                # Flip this block to '1's
                                t3_list = list(t2)
                                for k in range(l2, r2+1):
                                    t3_list[k] = '1'
                                t3 = ''.join(t3_list)
                                # Verification: count number of active sections (blocks of '1') in t3[1:-1]
                                cnt = count_active_sections(t3)
                                if cnt > max_active:
                                    max_active = cnt
            ans.append(max_active)
        return ans
# @lc code=end