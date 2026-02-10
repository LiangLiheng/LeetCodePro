#
# @lc app=leetcode id=3367 lang=python3
#
# [3367] Maximize Sum of Weights after Edge Removals
#

# @lc code=start
class Solution:
    def maximizeSumOfWeights(self, edges: List[List[int]], k: int) -> int:
        n = len(edges) + 1
        selected_deg = [0] * n
        edges.sort(key=lambda e: -e[2])
        ans = 0
        for edge in edges:
            u, v, w = edge
            if selected_deg[u] < k and selected_deg[v] < k:
                ans += w
                selected_deg[u] += 1
                selected_deg[v] += 1
        return ans
# @lc code=end