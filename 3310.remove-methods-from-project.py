#
# @lc app=leetcode id=3310 lang=python3
#
# [3310] Remove Methods From Project
#

# @lc code=start
class Solution:
    def remainingMethods(self, n: int, k: int, invocations: List[List[int]]) -> List[int]:
        from collections import deque, defaultdict
        graph = defaultdict(list)
        for a, b in invocations:
            graph[a].append(b)
        # Step 1: Identify suspicious methods using BFS from k
        suspicious = set()
        queue = deque([k])
        while queue:
            node = queue.popleft()
            if node in suspicious:
                continue
            suspicious.add(node)
            for nei in graph[node]:
                if nei not in suspicious:
                    queue.append(nei)
        # Step 2: Check for any invocation from non-suspicious to suspicious method
        for a, b in invocations:
            if a not in suspicious and b in suspicious:
                return list(range(n))
        # Step 3: Handle edge cases and return result
        if len(suspicious) == n:
            return []
        return [i for i in range(n) if i not in suspicious]
# @lc code=end