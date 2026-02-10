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
        
        // Calculate prefix sums of damage
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + damage[i];
        }
        
        long long total = 0;
        
        // For each room i, count its contribution to total score
        for (int i = 0; i < n; i++) {
            // Room i contributes to score(j) if:
            // hp - sum(damage[j:i+1]) >= requirement[i]
            // This translates to: prefix[j] >= prefix[i+1] - hp + requirement[i]
            long long threshold = prefix[i + 1] - hp + requirement[i];
            
            // Count starting positions j (0 to i) where prefix[j] >= threshold
            for (int j = 0; j <= i; j++) {
                if (prefix[j] >= threshold) {
                    total++;
                }
            }
        }
        
        return total;
    }
};
# @lc code=end