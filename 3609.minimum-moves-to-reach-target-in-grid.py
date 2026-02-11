#
# @lc app=leetcode id=3609 lang=python3
#
# [3609] Minimum Moves to Reach Target in Grid
#

# @lc code=start
class Solution:
    def minMoves(self, sx: int, sy: int, tx: int, ty: int) -> int:
        moves = 0
        while tx > sx or ty > sy:
            if tx > ty:
                m = max(tx, ty)
                prev_tx = tx - m
                if prev_tx >= sx and m == ty:
                    tx = prev_tx
                else:
                    return -1
            elif ty > tx:
                m = max(tx, ty)
                prev_ty = ty - m
                if prev_ty >= sy and m == tx:
                    ty = prev_ty
                else:
                    return -1
            else:
                # tx == ty, can't move further unless at start
                break
            moves += 1
        if tx == sx and ty == sy:
            return moves
        else:
            return -1
# @lc code=end