#
# @lc app=leetcode id=3771 lang=cpp
#
# [3771] Total Score of Dungeon Runs
#

# @lc code=start
class Solution {
public:
    long long totalScore(int hp, vector<int>& damage, vector<int>& requirement) {
        int n = damage.size();
        vector<long long> prefix(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            prefix[i] = prefix[i - 1] + damage[i - 1];
        }
        long long ans = 0;
        for (int i = 1; i <= n; ++i) {
            long long thresh = prefix[i] + (long long)requirement[i - 1] - hp;
            auto it = lower_bound(prefix.begin(), prefix.begin() + i, thresh);
            int pos = it - prefix.begin();
            ans += (i - pos);
        }
        return ans;
    }
};
# @lc code=end