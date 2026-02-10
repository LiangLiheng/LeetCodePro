#
# @lc app=leetcode id=3501 lang=cpp
#
# [3501] Maximize Active Section with Trade II
#
# @lc code=start
class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        vector<int> result;
        
        for (auto& query : queries) {
            int l = query[0], r = query[1];
            string t = s.substr(l, r - l + 1);
            int len = t.length();
            
            // Augment with '1' at both ends
            string aug = "1" + t + "1";
            int n = aug.length();
            
            // Base case: no trade
            int maxCount = 0;
            for (int i = 1; i <= len; i++) {
                if (aug[i] == '1') maxCount++;
            }
            
            // Find all segments of '1's in positions 1 to len
            vector<pair<int, int>> oneSegments;
            for (int i = 1; i <= len; ) {
                if (aug[i] == '1') {
                    int j = i;
                    while (j <= len && aug[j] == '1') j++;
                    oneSegments.push_back({i, j - 1});
                    i = j;
                } else {
                    i++;
                }
            }
            
            // Try each '1' segment
            for (auto [start, end] : oneSegments) {
                // Check if surrounded by '0's
                bool leftZero = (aug[start - 1] == '0');
                bool rightZero = (aug[end + 1] == '0');
                
                if (leftZero && rightZero) {
                    // Valid trade: convert this '1' segment to '0'
                    string temp = aug;
                    for (int k = start; k <= end; k++) {
                        temp[k] = '0';
                    }
                    
                    // Find the merged '0' segment
                    int mergedStart = start, mergedEnd = end;
                    while (mergedStart > 0 && temp[mergedStart - 1] == '0') mergedStart--;
                    while (mergedEnd < n - 1 && temp[mergedEnd + 1] == '0') mergedEnd++;
                    
                    // Check if this merged '0' segment is surrounded by '1's
                    bool leftOne = (mergedStart == 0 || temp[mergedStart - 1] == '1');
                    bool rightOne = (mergedEnd == n - 1 || temp[mergedEnd + 1] == '1');
                    
                    if (leftOne && rightOne) {
                        // Convert positions within range [1, len] to '1'
                        for (int k = max(mergedStart, 1); k <= min(mergedEnd, len); k++) {
                            temp[k] = '1';
                        }
                        
                        // Count '1's in positions 1 to len
                        int cnt = 0;
                        for (int k = 1; k <= len; k++) {
                            if (temp[k] == '1') cnt++;
                        }
                        maxCount = max(maxCount, cnt);
                    }
                }
            }
            
            result.push_back(maxCount);
        }
        
        return result;
    }
};
# @lc code=end