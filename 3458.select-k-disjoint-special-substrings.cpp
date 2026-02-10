#
# @lc app=leetcode id=3458 lang=cpp
#
# [3458] Select K Disjoint Special Substrings
#

# @lc code=start
class Solution {
public:
    bool maxSubstringLength(string s, int k) {
        int n = s.size();
        if (k == 0) return true;
        vector<int> first_occ(26, n);
        vector<int> last_occ(26, -1);
        for (int i = 0; i < n; ++i) {
            int c = s[i] - 'a';
            first_occ[c] = min(first_occ[c], i);
            last_occ[c] = max(last_occ[c], i);
        }
        vector<int> starts, ends;
        for (int i = 0; i < n; ++i) {
            int c = s[i] - 'a';
            if (first_occ[c] == i) starts.push_back(i);
            if (last_occ[c] == i) ends.push_back(i);
        }
        vector<pair<int, int>> specials;  // {r, l}
        for (int l : starts) {
            for (int r : ends) {
                if (l > r) continue;
                bool valid = true;
                for (int pos = l; pos <= r; ++pos) {
                    int c = s[pos] - 'a';
                    if (first_occ[c] < l || last_occ[c] > r) {
                        valid = false;
                        break;
                    }
                }
                if (valid && !(l == 0 && r == n - 1)) {
                    specials.emplace_back(r, l);
                }
            }
        }
        sort(specials.begin(), specials.end());
        int count = 0;
        int prev_end = -1;
        for (auto& p : specials) {
            int cl = p.second;
            int cr = p.first;
            if (cl > prev_end) {
                ++count;
                prev_end = cr;
            }
        }
        return count >= k;
    }
};
# @lc code=end