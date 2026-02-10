#
# @lc app=leetcode id=2296 lang=cpp
#
# [2296] Design a Text Editor
#
# @lc code=start
class TextEditor {
public:
    TextEditor() {

    }

    void addText(string text) {
        for (char c : text) {
            left_.push_back(c);
        }
    }

    int deleteText(int k) {
        int deleted = 0;
        while (deleted < k && !left_.empty()) {
            left_.pop_back();
            ++deleted;
        }
        return deleted;
    }

    string cursorLeft(int k) {
        while (k > 0 && !left_.empty()) {
            right_.push_front(left_.back());
            left_.pop_back();
            --k;
        }
        return getScreen();
    }

    string cursorRight(int k) {
        while (k > 0 && !right_.empty()) {
            left_.push_back(right_.front());
            right_.pop_front();
            --k;
        }
        return getScreen();
    }

private:
    std::deque<char> left_;
    std::deque<char> right_;

    string getScreen() {
        size_t len = left_.size();
        if (len <= 10) {
            return string(left_.begin(), left_.end());
        } else {
            return string(left_.begin() + len - 10, left_.end());
        }
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