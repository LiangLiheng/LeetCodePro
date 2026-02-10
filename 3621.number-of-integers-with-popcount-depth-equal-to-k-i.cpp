#
# @lc app=leetcode id=3621 lang=cpp
#
# [3621] Number of Integers With Popcount-Depth Equal to K I
#
# @lc code=start
class Solution {
public:
    long long popcountDepth(long long n, int k) {
        if (k == 0) {
            return n >= 1 ? 1 : 0; // Only x=1 has depth 0
        }
        
        // Step 1: Precompute depth for popcount values
        unordered_map<int, int> depth;
        depth[1] = 0;
        
        function<int(int)> getDepth = [&](int val) -> int {
            if (val == 1) return 0;
            if (depth.count(val)) return depth[val];
            int pc = __builtin_popcount(val);
            return depth[val] = getDepth(pc) + 1;
        };
        
        // Compute depth for all values from 2 to 60
        for (int i = 2; i <= 60; i++) {
            getDepth(i);
        }
        
        // Step 2: Find popcount values that lead to depth k
        // We want popcount values p such that depth(p) = k - 1
        set<int> target_popcounts;
        for (int i = 1; i <= 60; i++) {
            if (depth[i] == k - 1) {
                target_popcounts.insert(i);
            }
        }
        
        if (target_popcounts.empty()) return 0;
        
        // Step 3: Count numbers with those popcounts using digit DP
        vector<int> bits;
        long long temp = n;
        while (temp > 0) {
            bits.push_back(temp & 1);
            temp >>= 1;
        }
        reverse(bits.begin(), bits.end());
        
        long long result = 0;
        
        for (int pc : target_popcounts) {
            map<tuple<int, int, bool>, long long> dp;
            
            function<long long(int, int, bool)> solve = [&](int pos, int ones, bool tight) -> long long {
                if (ones > pc) return 0;
                if (pos == bits.size()) {
                    return ones == pc ? 1 : 0;
                }
                
                auto key = make_tuple(pos, ones, tight);
                if (dp.count(key)) return dp[key];
                
                int maxDigit = tight ? bits[pos] : 1;
                long long res = 0;
                
                for (int d = 0; d <= maxDigit; d++) {
                    res += solve(pos + 1, ones + d, tight && (d == maxDigit));
                }
                
                return dp[key] = res;
            };
            
            long long count = solve(0, 0, true);
            
            // Special case: if pc = 1 and k > 0, exclude x = 1
            if (pc == 1 && k > 0 && n >= 1) {
                count--;
            }
            
            result += count;
        }
        
        return result;
    }
};
# @lc code=end