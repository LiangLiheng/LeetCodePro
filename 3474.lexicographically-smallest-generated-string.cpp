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
        string result(len, '?');
        
        for (int j = 0; j < len; j++) {
            char required = 0;
            
            // Check all 'T' constraints that affect position j
            for (int i = max(0, j - m + 1); i <= min(j, n - 1); i++) {
                if (str1[i] == 'T') {
                    int pos_in_str2 = j - i;
                    if (required == 0) {
                        required = str2[pos_in_str2];
                    } else if (required != str2[pos_in_str2]) {
                        return "";
                    }
                }
            }
            
            // Validate character against ALL constraint types
            if (required != 0) {
                result[j] = required;
                
                // Validate against F constraints even when determined by T constraints
                bool valid = true;
                for (int i = max(0, j - m + 1); i <= j && i < n; i++) {
                    if (str1[i] == 'F' && i + m - 1 == j) {
                        bool matches = true;
                        for (int k = 0; k < m; k++) {
                            if (result[i + k] != str2[k]) {
                                matches = false;
                                break;
                            }
                        }
                        if (matches) {
                            valid = false;
                            break;
                        }
                    }
                }
                
                if (!valid) {
                    return "";
                }
            } else {
                // Try characters in lexicographic order
                bool found = false;
                for (char c = 'a'; c <= 'z'; c++) {
                    result[j] = c;
                    
                    bool valid = true;
                    for (int i = max(0, j - m + 1); i <= j && i < n; i++) {
                        if (str1[i] == 'F' && i + m - 1 == j) {
                            bool matches = true;
                            for (int k = 0; k < m; k++) {
                                if (result[i + k] != str2[k]) {
                                    matches = false;
                                    break;
                                }
                            }
                            if (matches) {
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
        }
        
        return result;
    }
};
# @lc code=end