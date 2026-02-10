#
# @lc app=leetcode id=3534 lang=cpp
#
# [3534] Path Existence Queries in a Graph II
#

# @lc code=start
class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int, int>> nodes(n);
        for (int i = 0; i < n; ++i) {
            nodes[i] = {nums[i], i};
        }
        sort(nodes.begin(), nodes.end());
        vector<int> sorted_pos(n);
        for (int j = 0; j < n; ++j) {
            sorted_pos[nodes[j].second] = j;
        }
        vector<int> comp_id(n);
        if (n > 0) {
            comp_id[0] = 0;
            int cur_comp = 0;
            for (int i = 1; i < n; ++i) {
                if ((long long)nodes[i].first - nodes[i - 1].first > maxDiff) {
                    ++cur_comp;
                }
                comp_id[i] = cur_comp;
            }
        }
        // Compute r[i]
        vector<int> r(n);
        int cur_right = 0;
        for (int i = 0; i < n; ++i) {
            while (cur_right < n && (long long)nodes[cur_right].first - nodes[i].first <= maxDiff) {
                ++cur_right;
            }
            r[i] = cur_right - 1;
        }
        // Binary lifting
        const int LOG = 18;
        vector<vector<int>> jump(n, vector<int>(LOG));
        for (int i = 0; i < n; ++i) {
            jump[i][0] = r[i];
        }
        for (int b = 1; b < LOG; ++b) {
            for (int i = 0; i < n; ++i) {
                int mid = jump[i][b - 1];
                jump[i][b] = jump[mid][b - 1];
            }
        }
        // Process queries
        int qn = queries.size();
        vector<int> answer(qn);
        auto compute_reach = [&](int start, int jumps) -> int {
            int pos = start;
            for (int b = LOG - 1; b >= 0; --b) {
                if (jumps & (1 << b)) {
                    pos = jump[pos][b];
                }
            }
            return pos;
        };
        for (int qi = 0; qi < qn; ++qi) {
            int u = queries[qi][0], v = queries[qi][1];
            if (u == v) {
                answer[qi] = 0;
                continue;
            }
            int pu = sorted_pos[u], pv = sorted_pos[v];
            if (pu > pv) swap(pu, pv);
            if (comp_id[pu] != comp_id[pv]) {
                answer[qi] = -1;
                continue;
            }
            // Binary search min k
            int lo = 1, hi = pv - pu;
            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;
                if (compute_reach(pu, mid) >= pv) {
                    hi = mid;
                } else {
                    lo = mid + 1;
                }
            }
            answer[qi] = lo;
        }
        return answer;
    }
};
# @lc code=end