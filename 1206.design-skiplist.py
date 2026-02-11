#
# @lc app=leetcode id=1206 lang=python3
#
# [1206] Design Skiplist
#

# @lc code=start
import random

class Skiplist:

    class Node:
        def __init__(self, val: int):
            self.val = val
            self.forward = None

    def __init__(self):
        self.MAX_LEVEL = 16
        self.head = self.Node(-1)
        self.head.forward = [None] * self.MAX_LEVEL

    def _random_level(self) -> int:
        level = 1
        while random.random() < 0.5 and level < self.MAX_LEVEL:
            level += 1
        return level

    def search(self, target: int) -> bool:
        cur = self.head
        for lvl in range(self.MAX_LEVEL - 1, -1, -1):
            while cur.forward[lvl] is not None and cur.forward[lvl].val < target:
                cur = cur.forward[lvl]
        cur = cur.forward[0]
        return cur is not None and cur.val == target

    def add(self, num: int) -> None:
        level = self._random_level()
        update = [None] * self.MAX_LEVEL
        cur = self.head
        for i in range(self.MAX_LEVEL - 1, -1, -1):
            while cur.forward[i] is not None and cur.forward[i].val < num:
                cur = cur.forward[i]
            update[i] = cur
        new_node = self.Node(num)
        new_node.forward = [None] * self.MAX_LEVEL
        for i in range(level):
            new_node.forward[i] = update[i].forward[i]
            update[i].forward[i] = new_node

    def erase(self, num: int) -> bool:
        update = [None] * self.MAX_LEVEL
        cur = self.head
        for i in range(self.MAX_LEVEL - 1, -1, -1):
            while cur.forward[i] is not None and cur.forward[i].val < num:
                cur = cur.forward[i]
            update[i] = cur
        cur = update[0].forward[0]
        if cur is None or cur.val != num:
            return False
        for i in range(self.MAX_LEVEL):
            if update[i].forward[i] == cur:
                update[i].forward[i] = cur.forward[i]
        return True


# Your Skiplist object will be instantiated and called as such:
# obj = Skiplist()
# param_1 = obj.search(target)
# obj.add(num)
# param_3 = obj.erase(num)
# @lc code=end