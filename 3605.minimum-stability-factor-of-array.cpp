#
# @lc app=leetcode id=3605 lang=cpp
#
# [3605] Minimum Stability Factor of Array
#

# @lc code=start
class Solution {
public:
    int minStable(vector<int>& nums, int maxC) {
        auto mygcd = [](int a, int b) -> int {
            while (b != 0) {
                int t = b;
                b = a % b;
                a = t;
            }
            return a;
        };
        int n = nums.size();
        if (n == 0) return 0;
        std::vector<int> logg(n + 1, 0);
        for (int i = 2; i <= n; ++i) {
            logg[i] = logg[i / 2] + 1;
        }
        int LOG = logg[n] + 1;
        std::vector<std::vector<int>> st(LOG, std::vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            st[0][i] = nums[i];
        }
        for (int j = 1; j < LOG; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                st[j][i] = mygcd(st[j - 1][i], st[j - 1][i + (1 << (j - 1))] );
            }
        }
        auto query = [&](int L, int R) -> int {
            int len = R - L + 1;
            int k = logg[len];
            return mygcd(st[k][L], st[k][R - (1 << k) + 1]);
        };
        auto can_achieve = [&](int K) -> bool {
            int cnt = 0;
            int last = -1;
            for (int i = 0; i <= n - K; ++i) {
                int g = query(i, i + K - 1);
                if (g >= 2) {
                    int s = i;
                    int e = i + K - 1;
                    if (last < s || last > e) {
                        last = e;
                        ++cnt;
                        if (cnt > maxC) {
                            return false;
                        }
                    }
                }
            }
            return cnt <= maxC;
        };
        int left = 0, right = n;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (can_achieve(mid + 1)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};
# @lc code=end