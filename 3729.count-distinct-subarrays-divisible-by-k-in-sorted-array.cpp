#
# @lc app=leetcode id=3729 lang=cpp
#
# [3729] Count Distinct Subarrays Divisible by K in Sorted Array
#

# @lc code=start
class Solution {
public:
    long long numGoodSubarrays(vector<int>& nums, int k) {
        long long K = k;
        int n = nums.size();
        std::map<long long, long long> freq;
        freq[0] = 1;
        long long pref = 0;
        long long total = 0;
        for (int num : nums) {
            long long val = num;
            pref = (pref + val % K) % K;
            total += freq[pref];
            freq[pref]++;
        }
        // Compress into groups
        std::vector<std::pair<long long, int>> groups;
        for (int start = 0; start < n; ) {
            long long val = nums[start];
            int end = start;
            while (end < n && nums[end] == val) ++end;
            groups.emplace_back(val, end - start);
            start = end;
        }
        // GCD lambda
        auto gcd_func = [&](long long a, long long b) -> long long {
            while (b != 0) {
                long long t = b;
                b = a % b;
                a = t;
            }
            return a;
        };
        long long single_total = 0;
        long long single_distinct = 0;
        for (auto& g : groups) {
            long long vmod = g.first % K;
            long long gg = gcd_func(vmod, K);
            long long period = K / gg;
            long long cnt = g.second;
            long long num_good_lengths = cnt / period;
            single_distinct += num_good_lengths;
            if (num_good_lengths > 0) {
                long long sum_j = num_good_lengths * (num_good_lengths + 1) / 2;
                long long group_total = num_good_lengths * (cnt + 1LL) - period * sum_j;
                single_total += group_total;
            }
        }
        long long multi_good = total - single_total;
        return multi_good + single_distinct;
    }
};
# @lc code=end