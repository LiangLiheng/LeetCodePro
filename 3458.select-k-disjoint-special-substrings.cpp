#
# @lc app=leetcode id=3458 lang=cpp
#
# [3458] Select K Disjoint Special Substrings
#
# @lc code=start
class Solution {
public:
    bool maxSubstringLength(string s, int k) {
        if (k == 0) return true;
        
        int n = s.length();
        
        // Find first and last occurrence of each character
        vector<int> first(26, n), last(26, -1);
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            first[c] = min(first[c], i);
            last[c] = i;
        }
        
        // Find all valid special substrings represented as intervals [start, end)
        vector<pair<int, int>> intervals;
        
        for (int start = 0; start < n; start++) {
            int minStart = start;
            int maxEnd = start;
            
            for (int end = start; end < n; end++) {
                int c = s[end] - 'a';
                minStart = min(minStart, first[c]);
                maxEnd = max(maxEnd, last[c]);
                
                // Check if [start, end] is a valid special substring
                // Valid if all characters in [start, end] have their full range within [start, end]
                // and it's not the entire string
                if (minStart == start && maxEnd == end && (start > 0 || end < n - 1)) {
                    intervals.push_back({start, end + 1});
                }
            }
        }
        
        // Find maximum number of disjoint intervals using interval scheduling
        if (intervals.empty()) return false;
        
        // Sort by end position for greedy algorithm
        sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        });
        
        int count = 0;
        int lastEnd = 0;
        for (const auto& interval : intervals) {
            if (interval.first >= lastEnd) {
                count++;
                lastEnd = interval.second;
            }
        }
        
        return count >= k;
    }
};
# @lc code=end