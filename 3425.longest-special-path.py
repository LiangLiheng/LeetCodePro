#
# @lc app=leetcode id=3425 lang=python3
#
# [3425] Longest Special Path
#

# @lc code=start
from typing import List
from collections import deque, defaultdict
import sys

sys.setrecursionlimit(10**5 + 10)

class Solution:
    def longestSpecialPath(self, edges: List[List[int]], nums: List[int]) -> List[int]:
        n = len(nums)
        adj = [[] for _ in range(n)]
        for a, b, w in edges:
            adj[a].append((b, w))
            adj[b].append((a, w))
        children = [[] for _ in range(n)]
        visited = [False] * n
        q = deque([0])
        visited[0] = True
        while q:
            u = q.popleft()
            for v, w in adj[u]:
                if not visited[v]:
                    visited[v] = True
                    children[u].append((v, w))
                    q.append(v)
        self.ans = [0, 1]
        path_prefix = []
        last_pos = {}
        self._dfs(0, 0, path_prefix, 0, last_pos, nums, children)
        return self.ans
    
    def _dfs(self, u: int, w_from_par: int, path_prefix: List[int], curr_start: int, last_pos: dict, nums: List[int], children: List[List]):
        index = len(path_prefix)
        old_pos = last_pos.get(nums[u], -1)
        new_start = curr_start
        if old_pos >= new_start:
            new_start = old_pos + 1
        last_pos[nums[u]] = index
        new_prefix = (path_prefix[-1] + w_from_par if path_prefix else 0)
        path_prefix.append(new_prefix)
        # update ans
        path_len = new_prefix - path_prefix[new_start]
        path_nodes = index - new_start + 1
        if path_len > self.ans[0]:
            self.ans[0] = path_len
            self.ans[1] = path_nodes
        elif path_len == self.ans[0]:
            self.ans[1] = min(self.ans[1], path_nodes)
        # recurse
        for v, w in children[u]:
            self._dfs(v, w, path_prefix, new_start, last_pos, nums, children)
        # backtrack
        path_prefix.pop()
        if old_pos == -1:
            del last_pos[nums[u]]
        else:
            last_pos[nums[u]] = old_pos

# @lc code=end