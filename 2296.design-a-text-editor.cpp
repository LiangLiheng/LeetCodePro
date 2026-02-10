#
# @lc app=leetcode id=2296 lang=cpp
#
# [2296] Design a Text Editor
#
# @lc code=start
class TextEditor {
public:
    string left, right;  // left stores chars before cursor, right after
    
    TextEditor() {
        left = "";
        right = "";
    }
    
    void addText(string text) {
        left += text;
    }
    
    int deleteText(int k) {
        int deleted = min(k, (int)left.size());
        left = left.substr(0, left.size() - deleted);
        return deleted;
    }
    
    string cursorLeft(int k) {
        int moves = min(k, (int)left.size());
        for (int i = 0; i < moves; i++) {
            right += left.back();
            left.pop_back();
        }
        return getLeft();
    }
    
    string cursorRight(int k) {
        int moves = min(k, (int)right.size());
        for (int i = 0; i < moves; i++) {
            left += right.back();
            right.pop_back();
        }
        return getLeft();
    }
    
private:
    string getLeft() {
        int len = min(10, (int)left.size());
        return left.substr(left.size() - len, len);
    }
};

/**
 * Your TextEditor object will be instantiated and called as such:
 * TextEditor* obj = new TextEditor();
 * obj->addText(text);
 * int param_2 = obj->deleteText(k);
 * string param_3 = obj->cursorLeft(k);
 * string param_4 = obj->cursorRight(k);
 */
# @lc code=end