#
# @lc app=leetcode id=3425 lang=python3
#
# [3425] Longest Special Path
#

# @lc code=start
class Solution:
    def longestSpecialPath(self, edges: List[List[int]], nums: List[int]) -> List[int]:
        n = len(nums)
        adj = [[] for _ in range(n)]
        for a, b, c in edges:
            adj[a].append((b, c))
            adj[b].append((a, c))
        self.max_len = 0
        self.min_nodes = n + 1
        path_values = []
        path_dist = []
        last_pos = {}
        window_left = [0]
        def dfs(u, p, dist):
            old_left = window_left[0]
            old_pos_val = last_pos.get(nums[u], -1)
            conflict = last_pos.get(nums[u], -1)
            new_left = window_left[0]
            if conflict >= window_left[0]:
                new_left = conflict + 1
            window_left[0] = new_left
            last_pos[nums[u]] = len(path_values)
            path_values.append(nums[u])
            path_dist.append(dist)
            curr_depth = len(path_values) - 1
            curr_len = path_dist[curr_depth] - path_dist[window_left[0]]
            curr_nodes = curr_depth - window_left[0] + 1
            if curr_len > self.max_len:
                self.max_len = curr_len
                self.min_nodes = curr_nodes
            elif curr_len == self.max_len:
                self.min_nodes = min(self.min_nodes, curr_nodes)
            for v, w in adj[u]:
                if v != p:
                    dfs(v, u, dist + w)
            path_values.pop()
            path_dist.pop()
            window_left[0] = old_left
            if old_pos_val == -1:
                last_pos.pop(nums[u])
            else:
                last_pos[nums[u]] = old_pos_val
        import sys
        sys.setrecursionlimit(10**5 + 10)
        dfs(0, -1, 0)
        return [self.max_len, self.min_nodes]

# @lc code=end