#
# @lc app=leetcode id=3398 lang=cpp
#
# [3398] Smallest Substring With Identical Characters I
#
# @lc code=start
class Solution {
public:
    int minLength(string s, int numOps) {
        int n = s.length();
        
        // Special case: check if we can make it alternating (k=1)
        int flips0 = 0, flips1 = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] != ((i % 2 == 0) ? '0' : '1')) flips0++;
            if (s[i] != ((i % 2 == 0) ? '1' : '0')) flips1++;
        }
        if (min(flips0, flips1) <= numOps) return 1;
        
        // Find all consecutive runs
        vector<int> runs;
        int count = 1;
        for (int i = 1; i < n; i++) {
            if (s[i] == s[i-1]) {
                count++;
            } else {
                runs.push_back(count);
                count = 1;
            }
        }
        runs.push_back(count);
        
        // Binary search on answer (starting from 2 since we checked 1 above)
        int left = 2, right = *max_element(runs.begin(), runs.end());
        int answer = right;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            if (canAchieve(runs, mid, numOps)) {
                answer = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return answer;
    }
    
    bool canAchieve(vector<int>& runs, int k, int numOps) {
        int flipsNeeded = 0;
        for (int len : runs) {
            if (len > k) {
                flipsNeeded += len / (k + 1);
            }
        }
        return flipsNeeded <= numOps;
    }
};
# @lc code=end