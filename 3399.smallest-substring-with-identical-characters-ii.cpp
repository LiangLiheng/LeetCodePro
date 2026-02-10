#
# @lc app=leetcode id=3399 lang=cpp
#
# [3399] Smallest Substring With Identical Characters II
#
# @lc code=start
class Solution {
public:
    int minLength(string s, int numOps) {
        int n = s.length();
        if (n == 0) return 0;
        if (n == 1) return 1;
        
        // Special case: check if we can achieve alternating pattern (length 1)
        int ops1 = 0, ops2 = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] != ('0' + (i % 2))) ops1++;
            if (s[i] != ('1' - (i % 2))) ops2++;
        }
        int minOpsForOne = min(ops1, ops2);
        
        if (minOpsForOne <= numOps) return 1;
        
        // Find all runs of consecutive identical characters
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
        
        // Find maximum run length
        int maxRun = *max_element(runs.begin(), runs.end());
        if (maxRun == 1) return 1;
        
        // Binary search on the answer
        int left = 2, right = maxRun;
        int result = maxRun;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (canAchieve(runs, mid, numOps)) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return result;
    }
    
private:
    bool canAchieve(vector<int>& runs, int maxLen, int numOps) {
        int opsNeeded = 0;
        
        for (int run : runs) {
            if (run > maxLen) {
                opsNeeded += run / (maxLen + 1);
                if (opsNeeded > numOps) return false;
            }
        }
        
        return opsNeeded <= numOps;
    }
};
# @lc code=end