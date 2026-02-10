#
# @lc app=leetcode id=1206 lang=cpp
#
# [1206] Design Skiplist
#

# @lc code=start
#include <vector>
#include <cstdlib>

class Skiplist {
private:
    struct Node {
        int value;
        std::vector<Node*> forward;
        Node(int _value, int level) : value(_value), forward(level + 1, nullptr) {}
    };

    static const int MAX_LEVEL = 16;
    Node* head;

    int getRandomLevel() {
        int level = 0;
        while ((rand() % 2 == 0) && level < MAX_LEVEL - 1) {
            level++;
        }
        return level;
    }

public:
    Skiplist() {
        head = new Node(-1, MAX_LEVEL);
    }
    
    bool search(int target) {
        Node* current = head;
        for (int i = MAX_LEVEL; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < target) {
                current = current->forward[i];
            }
            if (current->forward[i] != nullptr && current->forward[i]->value == target) {
                return true;
            }
        }
        return false;
    }
    
    void add(int num) {
        std::vector<Node*> update(MAX_LEVEL + 1, head);
        Node* current = head;
        for (int i = MAX_LEVEL; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < num) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        int random_level = getRandomLevel();
        Node* new_node = new Node(num, random_level);
        for (int i = 0; i <= random_level; i++) {
            new_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = new_node;
        }
    }
    
    bool erase(int num) {
        std::vector<Node*> update(MAX_LEVEL + 1, head);
        Node* current = head;
        for (int i = MAX_LEVEL; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < num) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        Node* candidate = update[0]->forward[0];
        if (candidate != nullptr && candidate->value == num) {
            int level = static_cast<int>(candidate->forward.size()) - 1;
            for (int i = 0; i <= level; i++) {
                if (update[i]->forward[i] == candidate) {
                    update[i]->forward[i] = candidate->forward[i];
                }
            }
            delete candidate;
            return true;
        }
        return false;
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