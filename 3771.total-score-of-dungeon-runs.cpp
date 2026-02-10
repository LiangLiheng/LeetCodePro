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
        vector<long long> cumDamage(n + 1, 0);
        
        // Compute cumulative damage
        for (int i = 0; i < n; i++) {
            cumDamage[i + 1] = cumDamage[i] + damage[i];
        }
        
        long long totalScore = 0;
        multiset<long long> seen;
        seen.insert(0);  // cumDamage[0]
        
        // For each room i
        for (int i = 0; i < n; i++) {
            long long threshold = cumDamage[i + 1] + requirement[i] - hp;
            
            // Count how many values in seen are >= threshold
            auto it = seen.lower_bound(threshold);
            totalScore += distance(it, seen.end());
            
            // Add cumDamage[i + 1] for next iteration
            seen.insert(cumDamage[i + 1]);
        }
        
        return totalScore;
    }
};
# @lc code=end