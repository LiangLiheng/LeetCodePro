#
# @lc app=leetcode id=1206 lang=python3
#
# [1206] Design Skiplist
#

import random

class Node:
    def __init__(self, val, level):
        self.val = val
        self.forward = [None] * (level + 1)

class Skiplist:
    MAX_LEVEL = 16
    P = 0.5

    def __init__(self):
        self.head = Node(-1, self.MAX_LEVEL)
        self.level = 0

    def randomLevel(self):
        lvl = 0
        while random.random() < self.P and lvl < self.MAX_LEVEL:
            lvl += 1
        return lvl

    def search(self, target: int) -> bool:
        node = self.head
        for i in reversed(range(self.level + 1)):
            while node.forward[i] and node.forward[i].val < target:
                node = node.forward[i]
        node = node.forward[0]
        return node is not None and node.val == target

    def add(self, num: int) -> None:
        update = [None] * (self.MAX_LEVEL + 1)
        node = self.head
        for i in reversed(range(self.level + 1)):
            while node.forward[i] and node.forward[i].val < num:
                node = node.forward[i]
            update[i] = node
        lvl = self.randomLevel()
        if lvl > self.level:
            for i in range(self.level + 1, lvl + 1):
                update[i] = self.head
            self.level = lvl
        new_node = Node(num, lvl)
        for i in range(lvl + 1):
            new_node.forward[i] = update[i].forward[i]
            update[i].forward[i] = new_node

    def erase(self, num: int) -> bool:
        update = [None] * (self.MAX_LEVEL + 1)
        node = self.head
        for i in reversed(range(self.level + 1)):
            while node.forward[i] and node.forward[i].val < num:
                node = node.forward[i]
            update[i] = node
        node = node.forward[0]
        if node is None or node.val != num:
            return False
        for i in range(self.level + 1):
            if update[i].forward[i] != node:
                continue
            update[i].forward[i] = node.forward[i]
        while self.level > 0 and self.head.forward[self.level] is None:
            self.level -= 1
        return True

# @lc code=end