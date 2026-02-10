#
# @lc app=leetcode id=3414 lang=cpp
#
# [3414] Maximum Score of Non-overlapping Intervals
#

# @lc code=start
class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if (n == 0) return {};

        struct Interval {
            int l, r, w, idx;
        };

        vector<Interval> inters(n);
        for (int i = 0; i < n; ++i) {
            inters[i].l = intervals[i][0];
            inters[i].r = intervals[i][1];
            inters[i].w = intervals[i][2];
            inters[i].idx = i;
        }

        std::sort(inters.begin(), inters.end(), [](const Interval& a, const Interval& b) {
            return a.r < b.r;
        });

        using ll = long long;
        using State = std::pair<ll, std::vector<int>>;
        std::vector<std::vector<State>> dp(n + 1, std::vector<State>(5, {-1LL, {}}));
        dp[0][0] = {0LL, {}};

        for (int i = 0; i < n; ++i) {
            // skip
            for (int j = 0; j <= 4; ++j) {
                dp[i + 1][j] = dp[i][j];
            }

            // find largest prev_idx < i with inters[prev_idx].r < inters[i].l
            int left = 0, right = i - 1;
            int prev_idx = -1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (inters[mid].r < inters[i].l) {
                    prev_idx = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }

            int prev_n = (prev_idx == -1 ? 0 : prev_idx + 1);
            for (int j = 1; j <= 4; ++j) {
                State prev_state = dp[prev_n][j - 1];
                if (prev_state.first != -1LL) {
                    ll new_score = prev_state.first + inters[i].w;
                    std::vector<int> new_path = prev_state.second;
                    new_path.push_back(inters[i].idx);
                    std::sort(new_path.begin(), new_path.end());

                    State& curr_state = dp[i + 1][j];
                    bool update = false;
                    if (new_score > curr_state.first) {
                        update = true;
                    } else if (new_score == curr_state.first) {
                        if (new_path < curr_state.second) {
                            update = true;
                        }
                    }
                    if (update) {
                        curr_state.first = new_score;
                        curr_state.second = std::move(new_path);
                    }
                }
            }
        }

        // find best
        ll max_score = 0;
        std::vector<int> ans;
        for (int j = 0; j <= 4; ++j) {
            State cand = dp[n][j];
            if (cand.first == -1LL) continue;
            if (cand.first > max_score || (cand.first == max_score && cand.second < ans)) {
                max_score = cand.first;
                ans = cand.second;
            }
        }
        return ans;
    }
};
# @lc code=end