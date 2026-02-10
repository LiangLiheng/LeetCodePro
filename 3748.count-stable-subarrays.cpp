#
# @lc app=leetcode id=3748 lang=cpp
#
# [3748] Count Stable Subarrays
#

# @lc code=start
class Solution {
public:
    vector<long long> countStableSubarrays(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        if (n == 0) return {};
        vector<int> run_start_pos(n), run_end_pos(n), run_id(n);
        vector<long long> full_contrib;
        int rid = 0;
        for (int i = 0; i < n; ) {
            int j = i;
            while (j + 1 < n && nums[j] <= nums[j + 1]) {
                ++j;
            }
            long long len = static_cast<long long>(j - i + 1);
            full_contrib.push_back(len * (len + 1) / 2);
            for (int k = i; k <= j; ++k) {
                run_start_pos[k] = i;
                run_end_pos[k] = j;
                run_id[k] = rid;
            }
            ++rid;
            i = j + 1;
        }
        int num_runs = rid;
        vector<long long> prefix(num_runs + 1, 0LL);
        for (int k = 1; k <= num_runs; ++k) {
            prefix[k] = prefix[k - 1] + full_contrib[k - 1];
        }
        int qsize = queries.size();
        vector<long long> ans(qsize);
        for (int qi = 0; qi < qsize; ++qi) {
            int l = queries[qi][0];
            int r = queries[qi][1];
            int jid = run_id[l];
            int mid = run_id[r];
            long long res = 0LL;
            // left partial
            int le_start = l;
            int le_end = std::min(r, run_end_pos[l]);
            long long le_len = static_cast<long long>(le_end - le_start + 1);
            res += le_len * (le_len + 1) / 2;
            if (jid != mid) {
                // full runs jid+1 to mid-1
                if (jid + 1 <= mid - 1) {
                    res += prefix[mid] - prefix[jid + 1];
                }
                // right partial
                int ri_start = run_start_pos[r];
                int ri_end = r;
                long long ri_len = static_cast<long long>(ri_end - ri_start + 1);
                res += ri_len * (ri_len + 1) / 2;
            }
            ans[qi] = res;
        }
        return ans;
    }
};
# @lc code=end