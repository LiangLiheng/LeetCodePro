#
# @lc app=leetcode id=2296 lang=cpp
#
# [2296] Design a Text Editor
#

# @lc code=start
class TextEditor {
public:
    TextEditor() {}

    void addText(string text) {
        for (char c : text) {
            left.push_back(c);
        }
    }

    int deleteText(int k) {
        int deleted = 0;
        for (int i = 0; i < k; ++i) {
            if (left.empty()) {
                break;
            }
            left.pop_back();
            ++deleted;
        }
        return deleted;
    }

    string cursorLeft(int k) {
        int steps = std::min(k, (int)left.size());
        for (int i = 0; i < steps; ++i) {
            right.push_front(left.back());
            left.pop_back();
        }
        return getScreen();
    }

    string cursorRight(int k) {
        int steps = std::min(k, (int)right.size());
        for (int i = 0; i < steps; ++i) {
            left.push_back(right.front());
            right.pop_front();
        }
        return getScreen();
    }

private:
    std::deque<char> left;
    std::deque<char> right;

    std::string getScreen() const {
        size_t n = left.size();
        if (n == 0) return "";
        size_t start = (n > 10 ? n - 10 : 0);
        std::string screen;
        screen.reserve(10);
        for (size_t i = start; i < n; ++i) {
            screen += left[i];
        }
        return screen;
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