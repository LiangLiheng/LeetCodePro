#
# @lc app=leetcode id=2296 lang=java
#
# [2296] Design a Text Editor
#

# @lc code=start
import java.util.*;
class TextEditor {
    Deque<Character> leftStack;
    Deque<Character> rightStack;
    public TextEditor() {
        leftStack = new ArrayDeque<>();
        rightStack = new ArrayDeque<>();
    }

    public void addText(String text) {
        for (char c : text.toCharArray()) {
            leftStack.push(c);
        }
    }

    public int deleteText(int k) {
        int deleted = 0;
        while (deleted < k && !leftStack.isEmpty()) {
            leftStack.pop();
            deleted++;
        }
        return deleted;
    }

    public String cursorLeft(int k) {
        int moves = 0;
        while (moves < k && !leftStack.isEmpty()) {
            rightStack.push(leftStack.pop());
            moves++;
        }
        return getLeftString();
    }

    public String cursorRight(int k) {
        int moves = 0;
        while (moves < k && !rightStack.isEmpty()) {
            leftStack.push(rightStack.pop());
            moves++;
        }
        return getLeftString();
    }

    private String getLeftString() {
        Iterator<Character> it = leftStack.descendingIterator();
        StringBuilder sb = new StringBuilder();
        int cnt = 0;
        while (it.hasNext() && cnt < 10) {
            sb.append(it.next());
            cnt++;
        }
        return sb.reverse().toString();
    }
}

/**
 * Your TextEditor object will be instantiated and called as such:
 * TextEditor obj = new TextEditor();
 * obj.addText(text);
 * int param_2 = obj.deleteText(k);
 * String param_3 = obj.cursorLeft(k);
 * String param_4 = obj.cursorRight(k);
 */
# @lc code=end