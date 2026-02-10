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
        long long total = 0;
        long long currentPrefix = 0;
        
        multiset<long long> prefixSet;
        prefixSet.insert(0);  // prefix[0] = 0
        
        for (int i = 0; i < n; i++) {
            currentPrefix += damage[i];
            long long threshold = currentPrefix - hp + requirement[i];
            
            // Count how many prefix values are >= threshold
            auto it = prefixSet.lower_bound(threshold);
            total += distance(it, prefixSet.end());
            
            prefixSet.insert(currentPrefix);
        }
        
        return total;
    }
};
# @lc code=end