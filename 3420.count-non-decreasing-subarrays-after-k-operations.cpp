#
# @lc app=leetcode id=3420 lang=cpp
#
# [3420] Count Non-Decreasing Subarrays After K Operations
#

# @lc code=start
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        long long K = k;
        vector<long long> pref(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            pref[i] = pref[i - 1] + nums[i - 1];
        }
        vector<int> nextg(n);
        stack<int> st;
        for (int i = n - 1; i >= 0; --i) {
            while (!st.empty() && nums[st.top()] <= nums[i]) {
                st.pop();
            }
            nextg[i] = st.empty() ? n : st.top();
            st.push(i);
        }
        long long ans = 0;
        int left = 0;
        deque<int> leaders;
        long long cur_cost = 0;
        for (int r = 0; r < n; ++r) {
            long long prev_req = leaders.empty() ? (long long)nums[r] : (long long)nums[leaders.back()];
            long long add_cost = max(prev_req - (long long)nums[r], 0LL);
            cur_cost += add_cost;
            if (leaders.empty() || nums[r] > nums[leaders.back()]) {
                leaders.push_back(r);
            }
            while (cur_cost > K && left <= r) {
                int old_l = left;
                ++left;
                if (!leaders.empty() && leaders.front() == old_l) {
                    int next_pos = (leaders.size() >= 2 ? leaders[1] : r + 1);
                    leaders.pop_front();
                    int seg_s = old_l + 1;
                    int seg_e = next_pos - 1;
                    long long old_contrib = 0;
                    if (seg_s <= seg_e) {
                        long long seg_len = (long long)seg_e - seg_s + 1;
                        long long sum_seg = pref[seg_e + 1] - pref[seg_s];
                        old_contrib = seg_len * (long long)nums[old_l] - sum_seg;
                        cur_cost -= old_contrib;
                        // rebuild new_contrib and nleaders using nextg
                        long long new_contrib = 0;
                        deque<int> nleaders;
                        int cur_pos = seg_s;
                        nleaders.push_back(cur_pos);
                        while (true) {
                            int nxt = nextg[cur_pos];
                            if (nxt > seg_e) break;
                            // contrib cur_pos+1 to nxt-1
                            int si = cur_pos + 1;
                            int ei = nxt - 1;
                            long long tms = (long long)ei - si + 1;
                            if (tms > 0) {
                                long long mval = nums[cur_pos];
                                long long ssum = pref[ei + 1] - pref[si];
                                new_contrib += tms * mval - ssum;
                            }
                            cur_pos = nxt;
                            nleaders.push_back(cur_pos);
                        }
                        // last cur_pos+1 to seg_e
                        int si = cur_pos + 1;
                        int ei = seg_e;
                        long long tms = (long long)ei - si + 1;
                        if (tms > 0) {
                            long long mval = nums[cur_pos];
                            long long ssum = pref[ei + 1] - pref[si];
                            new_contrib += tms * mval - ssum;
                        }
                        cur_cost += new_contrib;
                        // prepend reverse
                        for (auto it = nleaders.rbegin(); it != nleaders.rend(); ++it) {
                            leaders.push_front(*it);
                        }
                    } else {
                        // no change
                    }
                }
            }
            ans += (long long)(r - left + 1);
        }
        return ans;
    }
};
# @lc code=end