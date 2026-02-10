#
# @lc app=leetcode id=3563 lang=cpp
#
# [3563] Lexicographically Smallest String After Adjacent Removals
#
# @lc code=start
class Solution {
public:
    string lexicographicallySmallestString(string s) {
        unordered_set<string> visited;
        queue<string> q;
        q.push(s);
        visited.insert(s);
        string result = s;
        
        while (!q.empty()) {
            string curr = q.front();
            q.pop();
            
            // Update result if current is smaller
            if (curr < result) {
                result = curr;
            }
            
            // Try all possible removals of adjacent consecutive characters
            for (int i = 0; i < (int)curr.length() - 1; i++) {
                if (isConsecutive(curr[i], curr[i+1])) {
                    string next = curr.substr(0, i) + curr.substr(i+2);
                    if (visited.find(next) == visited.end()) {
                        visited.insert(next);
                        q.push(next);
                    }
                }
            }
        }
        
        return result;
    }
    
private:
    bool isConsecutive(char a, char b) {
        // Check if two characters are consecutive in the alphabet
        // Including circular: 'a' and 'z' are consecutive
        return (a - b == 1) || (b - a == 1) || (a == 'a' && b == 'z') || (a == 'z' && b == 'a');
    }
};
# @lc code=end