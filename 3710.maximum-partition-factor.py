#
# @lc app=leetcode id=3710 lang=python3
#
# [3710] Maximum Partition Factor
#

# @lc code=start
class Solution:
    def maxPartitionFactor(self, points: List[List[int]]) -> int:
        n = len(points)
        if n == 2:
            return 0

        # Precompute all pairwise Manhattan distances
        dists = [[0]*n for _ in range(n)]
        all_d = set()
        for i in range(n):
            for j in range(i+1, n):
                d = abs(points[i][0]-points[j][0]) + abs(points[i][1]-points[j][1])
                dists[i][j] = dists[j][i] = d
                all_d.add(d)

        # Binary search for the answer
        all_factors = sorted(list(all_d))
        left, right = 1, max(all_factors)+2
        result = 0
        def is_valid_partition(f):
            # Build graph: edge if d < f
            graph = [[] for _ in range(n)]
            for i in range(n):
                for j in range(i+1, n):
                    if dists[i][j] < f:
                        graph[i].append(j)
                        graph[j].append(i)
            color = [0]*n
            group_counts = [0, 0]  # color 1, -1
            for start in range(n):
                if color[start] == 0:
                    stack = [start]
                    color[start] = 1
                    group_counts[0] += 1
                    while stack:
                        node = stack.pop()
                        for nei in graph[node]:
                            if color[nei] == 0:
                                color[nei] = -color[node]
                                group_counts[0 if color[nei]==1 else 1] += 1
                                stack.append(nei)
                            elif color[nei] == color[node]:
                                return False
            # Ensure both groups are non-empty
            if group_counts[0] == 0 or group_counts[1] == 0:
                # All nodes went to one color, so split at least one node to the other group
                if n > 1:
                    return True  # Can always move one node to make two non-empty groups
                else:
                    return False
            return True

        while left < right:
            mid = (left + right) // 2
            if is_valid_partition(mid):
                result = mid
                left = mid + 1
            else:
                right = mid
        return result-1
# @lc code=end