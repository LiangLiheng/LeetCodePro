#
# @lc app=leetcode id=3474 lang=cpp
#
# [3474] Lexicographically Smallest Generated String
#
# @lc code=start
class Solution {
public:
    string generateString(string str1, string str2) {
        int n = str1.length();
        int m = str2.length();
        int len = n + m - 1;
        string result(len, 'a');
        
        for (int pos = 0; pos < len; pos++) {
            bool found = false;
            for (char ch = 'a'; ch <= 'z'; ch++) {
                result[pos] = ch;
                
                // Check all constraints that are now complete at this position
                bool valid = true;
                for (int i = max(0, pos - m + 1); i <= min(pos, n - 1); i++) {
                    // Constraint i affects substring [i, i+m-1]
                    if (i + m - 1 == pos) {
                        // This constraint is complete, check it
                        string sub = result.substr(i, m);
                        if (str1[i] == 'T' && sub != str2) {
                            valid = false;
                            break;
                        }
                        if (str1[i] == 'F' && sub == str2) {
                            valid = false;
                            break;
                        }
                    }
                }
                
                if (valid) {
                    found = true;
                    break;
                }
            }
            
            if (!found) {
                return "";
            }
        }
        
        return result;
    }
};
# @lc code=end