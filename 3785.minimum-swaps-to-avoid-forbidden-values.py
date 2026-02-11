#
# @lc app=leetcode id=3785 lang=python3
#
# [3785] Minimum Swaps to Avoid Forbidden Values
#

# @lc code=start
class Solution:
    def minSwaps(self, nums: List[int], forbidden: List[int]) -> int:
        from collections import Counter, defaultdict, deque
        n = len(nums)
        # Step 1: Feasibility check
        freq_nums = Counter(nums)
        freq_forbidden = Counter(forbidden)
        for val in freq_forbidden:
            if freq_forbidden[val] > freq_nums[val]:
                return -1
        # Step 2: Build a target arrangement
        # For each index, try to assign a value from nums not forbidden at that index
        # Start with the multiset of nums values
        values = Counter(nums)
        target = [None]*n
        for i in range(n):
            # Try to assign any value except forbidden[i] that is available
            found = False
            for val in values:
                if val != forbidden[i] and values[val] > 0:
                    target[i] = val
                    values[val] -= 1
                    found = True
                    break
            if not found:
                # Should not happen due to previous check, but safeguard
                return -1
        # Step 3: Map from original nums to target - find cycles
        # For each index, if nums[i] != target[i], it's part of a cycle
        visited = [False]*n
        pos_in_nums = defaultdict(deque)
        for idx, val in enumerate(nums):
            pos_in_nums[val].append(idx)
        # Build mapping from current index to target index for needed swaps
        index_map = [-1]*n
        used_in_target = set()
        for i in range(n):
            if nums[i] == target[i]:
                visited[i] = True
                used_in_target.add(i)
            else:
                # Find a position where nums[pos] == target[i]
                while pos_in_nums[target[i]]:
                    pos = pos_in_nums[target[i]].popleft()
                    if pos not in used_in_target and pos != i:
                        index_map[i] = pos
                        used_in_target.add(pos)
                        break
        # Step 4: Count cycles
        swaps = 0
        for i in range(n):
            if not visited[i] and index_map[i] != -1:
                # Start a new cycle
                cycle_len = 0
                j = i
                while not visited[j]:
                    visited[j] = True
                    j = index_map[j]
                    cycle_len += 1
                if cycle_len > 0:
                    swaps += cycle_len - 1
        # Step 5: Verify final state
        # Simulate swaps (optional in this structure, as cycles guarantee assignment)
        # Check that for all i, target[i] != forbidden[i]
        for i in range(n):
            if target[i] == forbidden[i]:
                return -1
        return swaps
# @lc code=end