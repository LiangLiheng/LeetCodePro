#
# @lc app=leetcode id=2296 lang=python3
#
# [2296] Design a Text Editor
#

# @lc code=start
class TextEditor:

    def __init__(self):
        self.left = []
        self.right = []

    def addText(self, text: str) -> None:
        for c in text:
            self.left.append(c)

    def deleteText(self, k: int) -> int:
        cnt = 0
        for _ in range(k):
            if self.left:
                self.left.pop()
                cnt += 1
            else:
                break
        return cnt

    def cursorLeft(self, k: int) -> str:
        for _ in range(k):
            if self.left:
                self.right.append(self.left.pop())
        return ''.join(self.left[-10:])

    def cursorRight(self, k: int) -> str:
        for _ in range(k):
            if self.right:
                self.left.append(self.right.pop())
        return ''.join(self.left[-10:])


# Your TextEditor object will be instantiated and called as such:
# obj = TextEditor()
# obj.addText(text)
# param_2 = obj.deleteText(k)
# param_3 = obj.cursorLeft(k)
# param_4 = obj.cursorRight(k)
# @lc code=end