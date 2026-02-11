#
# @lc app=leetcode id=1670 lang=python3
#
# [1670] Design Front Middle Back Queue
#

# @lc code=start
class FrontMiddleBackQueue:
    def __init__(self):
        self.left = []
        self.right = []

    def pushFront(self, val: int) -> None:
        self.left.insert(0, val)
        self._rebalance()

    def pushMiddle(self, val: int) -> None:
        self.left.append(val)
        self._rebalance()

    def pushBack(self, val: int) -> None:
        self.right.append(val)
        self._rebalance()

    def popFront(self) -> int:
        if not self.left and not self.right:
            return -1
        if self.left:
            val = self.left.pop(0)
        else:
            val = self.right.pop(0)
        self._rebalance()
        return val

    def popMiddle(self) -> int:
        if not self.left and not self.right:
            return -1
        if len(self.left) >= len(self.right):
            val = self.left.pop()
        else:
            val = self.right.pop(0)
        self._rebalance()
        return val

    def popBack(self) -> int:
        if not self.left and not self.right:
            return -1
        if self.right:
            val = self.right.pop()
        else:
            val = self.left.pop()
        self._rebalance()
        return val

    def _rebalance(self):
        # Maintain: len(self.left) == len(self.right) or len(self.left) == len(self.right) + 1
        while len(self.left) > len(self.right) + 1:
            self.right.insert(0, self.left.pop())
        while len(self.left) < len(self.right):
            self.left.append(self.right.pop(0))

# @lc code=end