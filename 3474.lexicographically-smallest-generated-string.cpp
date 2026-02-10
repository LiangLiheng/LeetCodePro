#
# @lc app=leetcode id=3474 lang=cpp
#
# [3474] Lexicographically Smallest Generated String
#

# @lc code=start
class Solution {
public:
    std::string generateString(std::string str1, std::string str2) {
        size_t n = str1.size();
        size_t m = str2.size();
        size_t L = n + m - 1;
        std::string word(L, '\0');
        // Step 2: Propagate 'T' constraints
        for (size_t i = 0; i < n; ++i) {
            if (str1[i] != 'T') continue;
            for (size_t j = 0; j < m; ++j) {
                size_t pos = i + j;
                char req = str2[j];
                if (word[pos] != '\0' && word[pos] != req) {
                    return "";
                }
                word[pos] = req;
            }
        }
        // Step 3: Check forced 'F' matches
        for (size_t i = 0; i < n; ++i) {
            if (str1[i] != 'F') continue;
            bool mismatch = false;
            bool has_free = false;
            for (size_t j = 0; j < m; ++j) {
                size_t pos = i + j;
                if (word[pos] == '\0') {
                    has_free = true;
                    continue;
                }
                if (word[pos] != str2[j]) {
                    mismatch = true;
                }
            }
            if (!mismatch && !has_free) {
                return "";
            }
        }
        // Step 4: Greedily fill free positions
        for (size_t k = 0; k < L; ++k) {
            if (word[k] != '\0') continue;
            bool forbidden[26] = {};
            size_t i_start = std::max(static_cast<size_t>(0), k + 1 - m);
            size_t i_max = std::min(n - 1, k);
            for (size_t i = i_start; i <= i_max; ++i) {
                if (str1[i] != 'F') continue;
                size_t j = k - i;
                // Check prefix match
                bool prefix_ok = true;
                for (size_t p = 0; p < j; ++p) {
                    if (word[i + p] != str2[p]) {
                        prefix_ok = false;
                        break;
                    }
                }
                if (!prefix_ok) continue;
                // Check future fully fixed and match
                bool future_ok = true;
                for (size_t p = j + 1; p < m; ++p) {
                    size_t pos = i + p;
                    if (word[pos] == '\0' || word[pos] != str2[p]) {
                        future_ok = false;
                        break;
                    }
                }
                if (future_ok) {
                    forbidden[str2[j] - 'a'] = true;
                }
            }
            // Choose smallest allowed
            bool found = false;
            for (char c = 'a'; c <= 'z'; ++c) {
                if (!forbidden[c - 'a']) {
                    word[k] = c;
                    found = true;
                    break;
                }
            }
            if (!found) {
                return "";
            }
        }
        // Step 5: Verify all constraints
        for (size_t i = 0; i < n; ++i) {
            bool is_match = true;
            for (size_t j = 0; j < m; ++j) {
                if (word[i + j] != str2[j]) {
                    is_match = false;
                    break;
                }
            }
            if ((str1[i] == 'T' && !is_match) || (str1[i] == 'F' && is_match)) {
                return "";
            }
        }
        return word;
    }
};
# @lc code=end