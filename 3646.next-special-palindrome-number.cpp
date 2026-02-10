#
# @lc app=leetcode id=3646 lang=cpp
#
# [3646] Next Special Palindrome Number
#
# @lc code=start
class Solution {
public:
    long long specialPalindrome(long long n) {
        string nstr = to_string(n);
        string ansstr;
        bool found = false;
        auto num_cmp = [&](const string& a, const string& b) -> int {
            if (a.size() != b.size()) {
                return a.size() > b.size() ? 1 : -1;
            }
            if (a > b) return 1;
            if (a < b) return -1;
            return 0;
        };
        auto try_update = [&](const string& cand) {
            int cn = num_cmp(cand, nstr);
            if (cn <= 0) return;
            int ca = found ? num_cmp(cand, ansstr) : -1;
            if (!found || ca < 0) {
                ansstr = cand;
                found = true;
            }
        };
        vector<int> evens{2, 4, 6, 8};
        vector<int> odds{1, 3, 5, 7, 9};
        // Even length (no odd)
        for (int m = 0; m < 16; ++m) {
            string ms;
            int L = 0;
            for (int i = 0; i < 4; ++i) {
                if (m & (1 << i)) {
                    int d = evens[i];
                    L += d;
                    ms.append(d / 2, '0' + d);
                }
            }
            if (L == 0) continue;
            int H = L / 2;
            if (ms.size() != static_cast<size_t>(H)) continue;
            sort(ms.begin(), ms.end());
            do {
                string left = ms;
                string revl(left.rbegin(), left.rend());
                string full = left + revl;
                try_update(full);
                if (found && num_cmp(full, ansstr) >= 0) break;
            } while (next_permutation(ms.begin(), ms.end()));
        }
        // Odd length
        for (int o : odds) {
            for (int m = 0; m < 16; ++m) {
                string ms;
                int L = o;
                int ho = (o - 1) / 2;
                ms.append(ho, '0' + o);
                for (int i = 0; i < 4; ++i) {
                    if (m & (1 << i)) {
                        int d = evens[i];
                        L += d;
                        ms.append(d / 2, '0' + d);
                    }
                }
                if (L == 0) continue;
                int H = L / 2;
                if (ms.size() != static_cast<size_t>(H)) continue;
                char midc = '0' + o;
                sort(ms.begin(), ms.end());
                do {
                    string left = ms;
                    string revl(left.rbegin(), left.rend());
                    string full = left + midc + revl;
                    try_update(full);
                    if (found && num_cmp(full, ansstr) >= 0) break;
                } while (next_permutation(ms.begin(), ms.end()));
            }
        }
        return stoll(ansstr);
    }
};
# @lc code=end