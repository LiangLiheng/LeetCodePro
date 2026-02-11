#
# @lc app=leetcode id=3782 lang=python3
#
# [3782] Last Remaining Integer After Alternating Deletion Operations
#

# @lc code=start
class Solution:
    def lastInteger(self, n: int) -> int:
        start = 1
        step = 1
        length = n
        is_left_turn = True
        while length > 1:
            new_length = (length + 1) // 2
            if not is_left_turn:
                # Operation 2 (right delete): shift start if even length
                if length % 2 == 0:
                    start += step
            # Always double step for both operations
            step *= 2
            length = new_length
            is_left_turn = not is_left_turn
        return start

# @lc code=end