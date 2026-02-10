#
# @lc app=leetcode id=1206 lang=cpp
#
# [1206] Design Skiplist
#

# @lc code=start
class Skiplist {
private:
    struct Node {
        int val;
        Node* forward[16];
        Node(int v) : val(v) {
            memset(forward, 0, sizeof(forward));
        }
    };

    Node* head;
    static const int MAX_LEVEL = 16;

    int getRandomLevel() {
        int level = 1;
        while ((rand() % 2 == 0) && level < MAX_LEVEL) {
            ++level;
        }
        return level;
    }
public:
    Skiplist() {
        head = new Node(-1);
    }

    bool search(int target) {
        Node* curr = head;
        for (int i = MAX_LEVEL - 1; i >= 0; --i) {
            while (curr->forward[i] && curr->forward[i]->val < target) {
                curr = curr->forward[i];
            }
        }
        curr = curr->forward[0];
        return curr && curr->val == target;
    }

    void add(int num) {
        Node* update[MAX_LEVEL];
        memset(update, 0, sizeof(update));
        Node* curr = head;
        for (int i = MAX_LEVEL - 1; i >= 0; --i) {
            while (curr->forward[i] && curr->forward[i]->val < num) {
                curr = curr->forward[i];
            }
            update[i] = curr;
        }
        Node* newnode = new Node(num);
        int rlevel = getRandomLevel();
        for (int i = 0; i < rlevel; ++i) {
            newnode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newnode;
        }
    }

    bool erase(int num) {
        Node* update[MAX_LEVEL];
        memset(update, 0, sizeof(update));
        Node* curr = head;
        for (int i = MAX_LEVEL - 1; i >= 0; --i) {
            while (curr->forward[i] && curr->forward[i]->val < num) {
                curr = curr->forward[i];
            }
            update[i] = curr;
        }
        curr = curr->forward[0];
        if (!curr || curr->val != num) {
            return false;
        }
        for (int i = 0; i < MAX_LEVEL; ++i) {
            if (update[i]->forward[i] == curr) {
                update[i]->forward[i] = curr->forward[i];
            } else {
                break;
            }
        }
        delete curr;
        return true;
    }
};

/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */
# @lc code=end