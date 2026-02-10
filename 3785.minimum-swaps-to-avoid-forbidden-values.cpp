#
# @lc app=leetcode id=3785 lang=cpp
#
# [3785] Minimum Swaps to Avoid Forbidden Values
#

# @lc code=start
class Solution {
public:
    int minSwaps(vector<int>& nums, vector<int>& forbidden) {
        int n = nums.size();
        std::map<int, int> cnt_num, cnt_forb, cnt_bad;
        int num_bad = 0;
        for (int i = 0; i < n; ++i) {
            cnt_num[nums[i]]++;
            cnt_forb[forbidden[i]]++;
            if (nums[i] == forbidden[i]) {
                cnt_bad[nums[i]]++;
                ++num_bad;
            }
        }
        for (const auto& p : cnt_num) {
            int v = p.first;
            int num_cnt = p.second;
            int forb_cnt = cnt_forb[v];
            if (num_cnt > n - forb_cnt) {
                return -1;
            }
        }
        if (num_bad == 0) {
            return 0;
        }
        int max_group = 0;
        for (const auto& p : cnt_bad) {
            max_group = std::max(max_group, p.second);
        }
        int max_pairs = std::min(num_bad / 2, num_bad - max_group);
        return num_bad - max_pairs;
    }
};
# @lc code=end