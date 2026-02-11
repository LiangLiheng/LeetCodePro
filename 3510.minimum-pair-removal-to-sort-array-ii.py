#
# @lc app=leetcode id=3510 lang=python3
#
# [3510] Minimum Pair Removal to Sort Array II
#

# @lc code=start
class Solution:
    def minimumPairRemoval(self, nums: List[int]) -> int:
        import heapq
        n = len(nums)
        if n <= 1:
            return 0
        class Node:
            def __init__(self, val: int):
                self.val = val
                self.prev = None
                self.next = None
                self.id = 0
        nodes = [Node(num) for num in nums]
        for i in range(n - 1):
            nodes[i].next = nodes[i + 1]
            nodes[i + 1].prev = nodes[i]
        node_dict = {i: nodes[i] for i in range(n)}
        for i in range(n):
            nodes[i].id = i
        heap = []
        for i in range(n - 1):
            s = nodes[i].val + nodes[i + 1].val
            heapq.heappush(heap, (s, nodes[i].id))
        bad_count = 0
        for i in range(n - 1):
            if nodes[i].val > nodes[i + 1].val:
                bad_count += 1
        ops = 0
        while bad_count > 0:
            left_node = None
            right_node = None
            while heap:
                s, lid = heapq.heappop(heap)
                if lid not in node_dict:
                    continue
                left_node = node_dict[lid]
                if left_node.next is None:
                    continue
                right_node = left_node.next
                if right_node.prev != left_node:
                    continue
                if left_node.val + right_node.val != s:
                    continue
                break
            else:
                return ops
            # merge
            P = left_node.prev
            N = right_node.next
            # Step 4: Subtract old bad contributions (P-L, L-R, R-N)
            if P is not None and P.val > left_node.val:
                bad_count -= 1
            if left_node.val > right_node.val:
                bad_count -= 1
            if N is not None and right_node.val > N.val:
                bad_count -= 1
            # new node
            new_val = left_node.val + right_node.val
            new_node = Node(new_val)
            new_node.id = left_node.id
            new_node.prev = P
            new_node.next = N
            if P is not None:
                P.next = new_node
            if N is not None:
                N.prev = new_node
            # Step 4: Add new bad contributions (P-new, new-N)
            if P is not None and P.val > new_node.val:
                bad_count += 1
            if N is not None and new_node.val > N.val:
                bad_count += 1
            # dict
            node_dict[left_node.id] = new_node
            del node_dict[right_node.id]
            # new heap entries for adjacent pairs
            if P is not None:
                ns = P.val + new_node.val
                heapq.heappush(heap, (ns, P.id))
            if N is not None:
                ns = new_node.val + N.val
                heapq.heappush(heap, (ns, new_node.id))
            ops += 1
        return ops

# @lc code=end