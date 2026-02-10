#
# @lc app=leetcode id=3510 lang=cpp
#
# [3510] Minimum Pair Removal to Sort Array II
#

# @lc code=start
class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;
        struct Node {
            long long sum;
            Node* prev;
            Node* next;
            bool active;
            long long order_key;
        };
        std::vector<Node*> nodes(n);
        for (int i = 0; i < n; ++i) {
            nodes[i] = new Node();
            nodes[i]->sum = nums[i];
            nodes[i]->order_key = i;
            nodes[i]->active = true;
            nodes[i]->prev = nullptr;
            nodes[i]->next = nullptr;
        }
        for (int i = 0; i < n; ++i) {
            if (i > 0) nodes[i]->prev = nodes[i - 1];
            if (i < n - 1) nodes[i]->next = nodes[i + 1];
        }
        int viol = 0;
        Node* cur = nodes[0];
        while (cur->next != nullptr) {
            if (cur->sum > cur->next->sum) ++viol;
            cur = cur->next;
        }
        using ll = long long;
        using T = std::tuple<ll, ll, Node*>;
        std::priority_queue<T, std::vector<T>, std::greater<T>> pq;
        for (int i = 0; i < n - 1; ++i) {
            Node* l = nodes[i];
            ll psum = l->sum + l->next->sum;
            pq.push({psum, l->order_key, l});
        }
        int ops = 0;
        while (viol > 0) {
            bool merged = false;
            while (!pq.empty() && !merged) {
                auto [csum, ckey, lptr] = pq.top(); pq.pop();
                if (!lptr->active || lptr->next == nullptr || !lptr->next->active) continue;
                if (lptr->sum + lptr->next->sum != csum) continue;
                merged = true;
                Node* left = lptr;
                Node* right = left->next;
                Node* pr = left->prev;
                bool has_prev = (pr != nullptr && pr->active);
                bool was_viol_prev = has_prev && (pr->sum > left->sum);
                bool was_viol_mid = (left->sum > right->sum);
                Node* nx = right->next;
                bool has_next = (nx != nullptr && nx->active);
                bool was_viol_next = has_next && (right->sum > nx->sum);
                viol -= static_cast<int>(was_viol_prev + was_viol_mid + was_viol_next);
                left->sum += right->sum;
                left->next = nx;
                if (nx != nullptr) nx->prev = left;
                right->active = false;
                right->prev = nullptr;
                right->next = nullptr;
                bool new_viol_prev = has_prev && (pr->sum > left->sum);
                bool new_viol_next = has_next && (left->sum > nx->sum);
                viol += static_cast<int>(new_viol_prev + new_viol_next);
                if (has_prev) {
                    pq.push({pr->sum + left->sum, pr->order_key, pr});
                }
                if (has_next) {
                    pq.push({left->sum + nx->sum, left->order_key, left});
                }
                ++ops;
            }
        }
        return ops;
    }
};
# @lc code=end