#
# @lc app=leetcode id=1206 lang=python3
#
# [1206] Design Skiplist
#

# @lc code=start
import random

class Node:
    def __init__(self, val):
        self.val = val
        self.forward = []

class Skiplist:

    def __init__(self):
        self.maxLevel = 16
        self.head = Node(-1)
        self.head.forward = [None] * self.maxLevel


    def _randomLevel(self):
        level = 1
        while random.random() < 0.5 and level < self.maxLevel:
            level += 1
        return level

    def search(self, target: int) -> bool:
        cur = self.head
        for lv in range(self.maxLevel - 1, -1, -1):
            while cur.forward[lv] is not None and cur.forward[lv].val < target:
                cur = cur.forward[lv]
        cur = cur.forward[0]
        return cur is not None and cur.val == target

    def add(self, num: int) -> None:
        updates = [None] * self.maxLevel
        cur = self.head
        for lv in range(self.maxLevel - 1, -1, -1):
            while cur.forward[lv] is not None and cur.forward[lv].val < num:
                cur = cur.forward[lv]
            updates[lv] = cur
        new_level = self._randomLevel()
        new_node = Node(num)
        new_node.forward = [None] * new_level
        for lv in range(new_level):
            new_node.forward[lv] = updates[lv].forward[lv]
            updates[lv].forward[lv] = new_node

    def erase(self, num: int) -> bool:
        updates = [None] * self.maxLevel
        cur = self.head
        for lv in range(self.maxLevel - 1, -1, -1):
            while cur.forward[lv] is not None and cur.forward[lv].val < num:
                cur = cur.forward[lv]
            updates[lv] = cur
        if updates[0].forward[0] is None or updates[0].forward[0].val != num:
            return False
        node = updates[0].forward[0]
        for lv in range(self.maxLevel):
            if updates[lv].forward[lv] == node:
                updates[lv].forward[lv] = node.forward[lv]
            else:
                break
        return True


# Your Skiplist object will be instantiated and called as such:
# obj = Skiplist()
# param_1 = obj.search(target)
# obj.add(num)
# param_3 = obj.erase(num)
# @lc code=end