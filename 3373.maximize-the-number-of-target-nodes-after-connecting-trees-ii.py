#
# @lc app=leetcode id=3373 lang=python3
#
# [3373] Maximize the Number of Target Nodes After Connecting Trees II
#

# @lc code=start
from collections import defaultdict, deque
from typing import List

class Solution:
    def maxTargetNodes(self, edges1: List[List[int]], edges2: List[List[int]]) -> List[int]:
        n = len(edges1) + 1
        m = len(edges2) + 1
        adj1 = defaultdict(list)
        adj2 = defaultdict(list)
        for a, b in edges1:
            adj1[a].append(b)
            adj1[b].append(a)
        for u, v in edges2:
            adj2[u].append(v)
            adj2[v].append(u)

        def get_depths_and_parity_counts(adj, size):
            depth = [0] * size
            visited = [False] * size
            even_count = 0
            odd_count = 0
            q = deque([(0, 0)])
            visited[0] = True
            while q:
                node, d = q.popleft()
                depth[node] = d
                if d % 2 == 0:
                    even_count += 1
                else:
                    odd_count += 1
                for nei in adj[node]:
                    if not visited[nei]:
                        visited[nei] = True
                        q.append((nei, d+1))
            assert even_count + odd_count == size
            return depth, even_count, odd_count

        depth1, even1, odd1 = get_depths_and_parity_counts(adj1, n)
        depth2, even2, odd2 = get_depths_and_parity_counts(adj2, m)
        assert even1 + odd1 == n
        assert even2 + odd2 == m
        answer = []
        for i in range(n):
            my_parity = depth1[i] % 2
            same_parity_in_tree1 = even1 if my_parity == 0 else odd1
            same_parity_in_tree2 = even2
            opp_parity_in_tree2 = odd2
            ans1 = same_parity_in_tree1 + same_parity_in_tree2
            ans2 = same_parity_in_tree1 + opp_parity_in_tree2
            answer.append(max(ans1, ans2))
        # Sanity check: no node should have answer larger than n + m
        for val in answer:
            assert 0 < val <= n + m
        return answer
# @lc code=end