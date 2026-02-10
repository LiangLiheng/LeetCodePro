#
# @lc app=leetcode id=3594 lang=cpp
#
# [3594] Minimum Time to Transport All Individuals
#
# @lc code=start
class Solution {
public:
    double minTime(int n, int k, int m, vector<int>& time, vector<double>& mul) {
        // Edge case: if boat carries only 1 and n > 1, impossible
        if (k == 1 && n > 1) return -1.0;
        
        // Use Dijkstra's algorithm with state: (base_mask, stage)
        // base_mask: bitmask indicating which people are at base
        // stage: current environmental stage
        
        priority_queue<tuple<double, int, int>, 
                      vector<tuple<double, int, int>>, 
                      greater<tuple<double, int, int>>> pq;
        
        map<pair<int, int>, double> visited;
        
        int initial_mask = (1 << n) - 1; // all at base
        pq.push({0.0, initial_mask, 0});
        
        while (!pq.empty()) {
            auto [curr_time, base_mask, stage] = pq.top();
            pq.pop();
            
            auto state = make_pair(base_mask, stage);
            if (visited.count(state)) continue;
            visited[state] = curr_time;
            
            // Goal: all people at destination (base_mask = 0)
            if (base_mask == 0) {
                return curr_time;
            }
            
            // Try all possible groups to send
            for (int group = 1; group < (1 << n); group++) {
                // Check if group is subset of base_mask
                if ((group & base_mask) != group) continue;
                // Check if group size <= k
                if (__builtin_popcount(group) > k) continue;
                
                // Find max time in group
                int max_time_val = 0;
                for (int i = 0; i < n; i++) {
                    if (group & (1 << i)) {
                        max_time_val = max(max_time_val, time[i]);
                    }
                }
                
                // Calculate crossing time
                double cross_time = max_time_val * mul[stage];
                int next_stage = (stage + (int)cross_time) % m;
                double next_time = curr_time + cross_time;
                
                // Update base mask (remove sent people)
                int new_base_mask = base_mask ^ group;
                
                if (new_base_mask == 0) {
                    // All at destination
                    auto next_state = make_pair(0, next_stage);
                    if (!visited.count(next_state)) {
                        pq.push({next_time, 0, next_stage});
                    }
                } else {
                    // Someone must return
                    for (int ret = 0; ret < n; ret++) {
                        if (!(group & (1 << ret))) continue;
                        
                        double ret_time = time[ret] * mul[next_stage];
                        int final_stage = (next_stage + (int)ret_time) % m;
                        double final_time = next_time + ret_time;
                        
                        int final_base_mask = new_base_mask | (1 << ret);
                        
                        auto final_state = make_pair(final_base_mask, final_stage);
                        if (!visited.count(final_state)) {
                            pq.push({final_time, final_base_mask, final_stage});
                        }
                    }
                }
            }
        }
        
        return -1.0;
    }
};
# @lc code=end