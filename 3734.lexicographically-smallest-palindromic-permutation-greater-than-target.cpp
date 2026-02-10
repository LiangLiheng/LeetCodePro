#
# @lc app=leetcode id=3734 lang=cpp
#
# [3734] Lexicographically Smallest Palindromic Permutation Greater Than Target
#
# @lc code=start
class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.length();
        std::array<int, 26> freq = {0};
        for (char c : s) {
            ++freq[c - 'a'];
        }
        std::vector<char> odds;
        for (int i = 0; i < 26; ++i) {
            if (freq[i] % 2 == 1) {
                odds.push_back('a' + i);
            }
        }
        bool odd_length = (n % 2 == 1);
        if ((odd_length && odds.size() != 1) || (!odd_length && odds.size() != 0)) {
            return "";
        }
        char middle = odd_length ? odds[0] : '\0';
        int half = n / 2;
        std::array<int, 26> pairs = {0};
        for (int i = 0; i < 26; ++i) {
            pairs[i] = freq[i] / 2;
        }
        auto can_exceed = [&](int pos, const std::vector<char>& lft, const std::array<int, 26>& rem) -> bool {
            int midpos = n / 2;
            bool hasmid = odd_length;
            char midc = middle;
            for (int d = 0; d < n; ++d) {
                char pd = '\0';
                bool det = false;
                if (d < static_cast<int>(lft.size())) {
                    pd = lft[d];
                    det = true;
                } else if (d >= n - 1 - pos) {
                    int j = n - 1 - d;
                    pd = lft[j];
                    det = true;
                } else if (hasmid && d == midpos) {
                    pd = midc;
                    det = true;
                }
                if (!det) {
                    int rlen = half - (pos + 1);
                    std::vector<char> rlist;
                    for (int i = 0; i < 26; ++i) {
                        rlist.insert(rlist.end(), rem[i], static_cast<char>('a' + i));
                    }
                    std::sort(rlist.rbegin(), rlist.rend());
                    std::vector<char> full = lft;
                    full.insert(full.end(), rlist.begin(), rlist.end());
                    std::string pmax(n, '\0');
                    for (int j = 0; j < half; ++j) {
                        pmax[j] = full[j];
                        pmax[n - 1 - j] = full[j];
                    }
                    if (hasmid) {
                        pmax[midpos] = midc;
                    }
                    return pmax > target;
                }
                if (pd != target[d]) {
                    return pd > target[d];
                }
            }
            return false;
        };
        std::vector<char> lhalf;
        std::array<int, 26> rem_pairs = pairs;
        bool success = true;
        for (int pos = 0; pos < half; ++pos) {
            bool found = false;
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                int idx = ch - 'a';
                if (rem_pairs[idx] > 0) {
                    --rem_pairs[idx];
                    lhalf.push_back(ch);
                    if (can_exceed(pos, lhalf, rem_pairs)) {
                        found = true;
                        break;
                    }
                    ++rem_pairs[idx];
                    lhalf.pop_back();
                }
            }
            if (!found) {
                success = false;
                break;
            }
        }
        if (!success) {
            return "";
        }
        std::string result(n, '\0');
        for (int j = 0; j < half; ++j) {
            result[j] = lhalf[j];
            result[n - 1 - j] = lhalf[j];
        }
        if (odd_length) {
            result[n / 2] = middle;
        }
        if (result > target) {
            return result;
        } else {
            return "";
        }
    }
};
# @lc code=end