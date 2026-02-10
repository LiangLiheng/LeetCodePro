#
# @lc app=leetcode id=3621 lang=cpp
#
# [3621] Number of Integers With Popcount-Depth Equal to K I
#
# @lc code=start
class Solution {
public:
    map<int, int> depthCache;
    
    int getDepth(int x) {
        if (x == 1) return 0;
        if (depthCache.count(x)) return depthCache[x];
        return depthCache[x] = 1 + getDepth(__builtin_popcount(x));
    }
    
    long long countWithPopcount(long long n, int targetBits) {
        if (n <= 0 || targetBits <= 0) return 0;
        
        vector<int> binary;
        long long temp = n;
        while (temp > 0) {
            binary.push_back(temp & 1);
            temp >>= 1;
        }
        reverse(binary.begin(), binary.end());
        
        int len = binary.size();
        vector<vector<vector<long long>>> dp(len + 1, vector<vector<long long>>(targetBits + 1, vector<long long>(2, -1)));
        
        function<long long(int, int, int)> solve = [&](int pos, int count, int tight) -> long long {
            if (count > targetBits) return 0;
            if (pos == len) {
                return (count == targetBits) ? 1 : 0;
            }
            
            if (dp[pos][count][tight] != -1) return dp[pos][count][tight];
            
            int limit = tight ? binary[pos] : 1;
            long long result = 0;
            
            for (int digit = 0; digit <= limit; digit++) {
                result += solve(pos + 1, count + digit, tight && (digit == limit));
            }
            
            return dp[pos][count][tight] = result;
        };
        
        return solve(0, 0, 1);
    }
    
    long long popcountDepth(long long n, int k) {
        if (k == 0) {
            return (n >= 1) ? 1 : 0;
        }
        
        long long result = 0;
        
        for (int pc = 1; pc <= 60; pc++) {
            if (getDepth(pc) == k - 1) {
                long long count = countWithPopcount(n, pc);
                
                if (pc == 1 && n >= 1) {
                    count--;
                }
                
                result += count;
            }
        }
        
        return result;
    }
};
# @lc code=end