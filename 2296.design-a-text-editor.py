#
# @lc app=leetcode id=2296 lang=python3
#
# [2296] Design a Text Editor
#

# @lc code=start
class TextEditor:
    def __init__(self):
        self.left = []  # characters to the left of the cursor
        self.right = []  # characters to the right of the cursor

    def addText(self, text: str) -> None:
        for c in text:
            self.left.append(c)

    def deleteText(self, k: int) -> int:
        cnt = 0
        while self.left and cnt < k:
            self.left.pop()
            cnt += 1
        return cnt

    def cursorLeft(self, k: int) -> str:
        for _ in range(min(k, len(self.left))):
            self.right.append(self.left.pop())
        return ''.join(self.left[-10:])

    def cursorRight(self, k: int) -> str:
        for _ in range(min(k, len(self.right))):
            self.left.append(self.right.pop())
        return ''.join(self.left[-10:])
# @lc code=end