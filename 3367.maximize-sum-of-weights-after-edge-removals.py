#
# @lc app=leetcode id=3367 lang=python3
#
# [3367] Maximize Sum of Weights after Edge Removals
#

# @lc code=start
class Solution:
    def maximizeSumOfWeights(self, edges: List[List[int]], k: int) -> int:
        # Step 1: Build adjacency list to represent the tree
        # (node: list of (neighbor, edge_weight, edge_index))
        from collections import defaultdict
        n = len(edges) + 1
        adj = defaultdict(list)
        for idx, (u, v, w) in enumerate(edges):
            adj[u].append((v, w, idx))
            adj[v].append((u, w, idx))

        # Step 2: Track degrees and edge usage
        degrees = [len(adj[i]) for i in range(n)]
        used = [True] * (n - 1)  # Keep track of which edges are kept

        # Step 3: For nodes with degree > k, remove lowest-weight edges first
        import heapq
        over_deg = set(i for i in range(n) if degrees[i] > k)
        while over_deg:
            node = over_deg.pop()
            # Gather all edges from this node that have not been removed
            edge_list = []
            for neighbor, w, idx in adj[node]:
                if used[idx]:
                    edge_list.append((w, neighbor, idx))
            # If degree > k, remove (degree - k) smallest-weight edges
            remove_cnt = degrees[node] - k
            edge_list.sort()
            for i in range(remove_cnt):
                w, neighbor, idx = edge_list[i]
                if used[idx]:
                    used[idx] = False
                    degrees[node] -= 1
                    degrees[neighbor] -= 1
                    # If neighbor's degree now exceeds k, add to over_deg
                    if degrees[neighbor] > k:
                        over_deg.add(neighbor)
            # After removals, if still over degree, re-add to set
            if degrees[node] > k:
                over_deg.add(node)

        # Step 4: Sum the weights of remaining edges
        total = 0
        for i, flag in enumerate(used):
            if flag:
                total += edges[i][2]
        # Step 5: Final verification: all degrees <= k
        # (optional assertion for debugging)
        # for i in range(n):
        #     assert sum(used[idx] for _, _, idx in adj[i]) <= k
        return total
# @lc code=end