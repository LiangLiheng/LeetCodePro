#
# @lc app=leetcode id=1670 lang=cpp
#
# [1670] Design Front Middle Back Queue
#

# @lc code=start
class FrontMiddleBackQueue {
public:
    FrontMiddleBackQueue() {

    }

    void pushFront(int val) {
        q.push_front(val);
    }

    void pushMiddle(int val) {
        size_t idx = q.size() / 2;
        q.insert(q.begin() + idx, val);
    }

    void pushBack(int val) {
        q.push_back(val);
    }

    int popFront() {
        if (q.empty()) return -1;
        int val = q.front();
        q.pop_front();
        return val;
    }

    int popMiddle() {
        size_t s = q.size();
        if (s == 0) return -1;
        size_t idx = (s - 1) / 2;
        int val = q[idx];
        q.erase(q.begin() + idx);
        return val;
    }

    int popBack() {
        if (q.empty()) return -1;
        int val = q.back();
        q.pop_back();
        return val;
    }
private:
    deque<int> q;
};

/**
 * Your FrontMiddleBackQueue object will be instantiated and called as such:
 * FrontMiddleBackQueue* obj = new FrontMiddleBackQueue();
 * obj->pushFront(val);
 * obj->pushMiddle(val);
 * obj->pushBack(val);
 * int param_4 = obj->popFront();
 * int param_5 = obj->popMiddle();
 * int param_6 = obj->popBack();
 */
# @lc code=end