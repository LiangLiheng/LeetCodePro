#
# @lc app=leetcode id=3435 lang=cpp
#
# [3435] Frequencies of Shortest Supersequences
#
# @lc code=start
class Solution {
public:
    vector<vector<int>> supersequences(vector<string>& words) {
        int n = words.size();
        
        // State: vector of positions for each word (0, 1, or 2)
        // Use map to store: state -> set of frequency arrays
        map<vector<int>, set<vector<int>>> current_level;
        
        vector<int> initial(n, 0);
        vector<int> empty_freq(26, 0);
        current_level[initial].insert(empty_freq);
        
        vector<int> final_state(n, 2);
        
        // BFS level by level
        while (true) {
            // Check if we've reached final state
            if (current_level.count(final_state)) {
                vector<vector<int>> result(
                    current_level[final_state].begin(),
                    current_level[final_state].end()
                );
                return result;
            }
            
            map<vector<int>, set<vector<int>>> next_level;
            
            for (auto& [state, freq_set] : current_level) {
                // Collect all characters that need to be matched
                set<char> chars;
                for (int i = 0; i < n; i++) {
                    if (state[i] < 2) {
                        chars.insert(words[i][state[i]]);
                    }
                }
                
                // Try each character
                for (char c : chars) {
                    vector<int> next_state = state;
                    for (int i = 0; i < n; i++) {
                        if (state[i] < 2 && words[i][state[i]] == c) {
                            next_state[i]++;
                        }
                    }
                    
                    // Update frequencies
                    for (auto freq : freq_set) {
                        freq[c - 'a']++;
                        next_level[next_state].insert(freq);
                    }
                }
            }
            
            current_level = next_level;
        }
        
        return {};
    }
};
# @lc code=end