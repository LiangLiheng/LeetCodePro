#
# @lc app=leetcode id=3419 lang=python3
#
# [3419] Minimize the Maximum Edge Weight of Graph
#

# @lc code=start
from typing import List
from collections import defaultdict, deque

class Solution:
    def minMaxWeight(self, n: int, edges: List[List[int]], threshold: int) -> int:
        def is_possible(max_weight):
            # Step 1: Build subgraph with edges weight <= max_weight
            out_edges = defaultdict(list)
            for u, v, w in edges:
                if w <= max_weight:
                    out_edges[u].append((w, v))
            # Step 2: For each node, keep up to threshold smallest outgoing edges
            trimmed_out = defaultdict(list)
            for u in out_edges:
                trimmed = sorted(out_edges[u])[:threshold]
                trimmed_out[u] = trimmed
                # Explicitly verify outgoing edges constraint
                if len(trimmed_out[u]) > threshold:
                    return False
            # Step 3: Build reverse graph for reachability check
            rev_graph = defaultdict(list)
            for u in trimmed_out:
                for w, v in trimmed_out[u]:
                    rev_graph[v].append(u)
            # Step 4: BFS to check if all nodes reach node 0
            visited = [False] * n
            queue = deque([0])
            visited[0] = True
            while queue:
                curr = queue.popleft()
                for nei in rev_graph[curr]:
                    if not visited[nei]:
                        visited[nei] = True
                        queue.append(nei)
            # Step 5: Explicitly verify reachability constraint
            return all(visited)

        left, right = 1, max(w for _, _, w in edges)
        answer = -1
        while left <= right:
            mid = (left + right) // 2
            if is_possible(mid):
                answer = mid
                right = mid - 1
            else:
                left = mid + 1
        return answer
# @lc code=end