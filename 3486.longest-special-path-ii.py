#
# @lc app=leetcode id=3486 lang=python3
#
# [3486] Longest Special Path II
#

# @lc code=start
from typing import List
import sys
from collections import deque

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
        MAX_VAL = 50010
        freq = [0] * MAX_VAL
        path_values = []
        cum_len = []
        left = 0
        max_len = 0
        min_nodes = float('inf')
        num_dupes = 0
        num_over = 0

        def add(pos):
            nonlocal num_dupes, num_over
            val = path_values[pos]
            old = freq[val]
            freq[val] += 1
            newv = freq[val]
            if old == 1 and newv == 2:
                num_dupes += 1
            elif old == 2 and newv == 3:
                num_dupes -= 1
                num_over += 1

        def remove(pos):
            nonlocal num_dupes, num_over
            val = path_values[pos]
            old = freq[val]
            freq[val] -= 1
            newv = freq[val]
            if old == 2 and newv == 1:
                num_dupes -= 1
            elif old == 3 and newv == 2:
                num_over -= 1
                num_dupes += 1

        def is_valid():
            return num_over == 0 and num_dupes <= 1

        def update_global(plen, pnodes):
            nonlocal max_len, min_nodes
            if plen > max_len or (plen == max_len and pnodes < min_nodes):
                max_len = plen
                min_nodes = pnodes

        sys.setrecursionlimit(100010)

        def dfs(u: int, par: int, w_from_par: int):
            nonlocal left
            path_values.append(nums[u])
            if len(cum_len) == 0:
                cum_len.append(0)
            else:
                cum_len.append(cum_len[-1] + w_from_par)
            curr_pos = len(path_values) - 1
            add(curr_pos)
            while left <= curr_pos and not is_valid():
                remove(left)
                left += 1
            plen = cum_len[-1] - (cum_len[left - 1] if left > 0 else 0)
            pnodes = curr_pos - left + 1
            update_global(plen, pnodes)
            saved_left = left
            for v, w in children[u]:
                dfs(v, u, w)
                for i in range(saved_left, left):
                    add(i)
                left = saved_left
            remove(curr_pos)
            path_values.pop()
            cum_len.pop()

        dfs(0, -1, 0)
        return [max_len, int(min_nodes)]
# @lc code=end