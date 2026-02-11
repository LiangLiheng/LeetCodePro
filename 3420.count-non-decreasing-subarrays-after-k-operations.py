#
# @lc app=leetcode id=3420 lang=python3
#
# [3420] Count Non-Decreasing Subarrays After K Operations
#

# @lc code=start
class Solution:
    def countNonDecreasingSubarrays(self, nums: List[int], k: int) -> int:
        n = len(nums)
        total = 0
        # Iterate over all possible subarrays
        for start in range(n):
            # Prepare to store the modified subarray to track increments
            modified = []
            ops = 0
            for end in range(start, n):
                val = nums[end]
                if not modified:
                    modified.append(val)
                else:
                    # The current element should be at least as large as the previous
                    if val < modified[-1]:
                        # Need to increment current element
                        ops += modified[-1] - val
                        modified.append(modified[-1])
                    else:
                        modified.append(val)
                # Only count subarrays needing k or fewer operations
                if ops <= k:
                    total += 1
                else:
                    # Further extension will require even more ops, so break
                    break
        return total
# @lc code=end