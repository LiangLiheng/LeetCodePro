#
# @lc app=leetcode id=3387 lang=python3
#
# [3387] Maximize Amount After Two Days of Conversions
#

# @lc code=start
from typing import List, Dict
from collections import defaultdict, deque

class Solution:
    def maxAmount(self, initialCurrency: str, pairs1: List[List[str]], rates1: List[float], pairs2: List[List[str]], rates2: List[float]) -> float:
        def build_graph(pairs, rates):
            graph = defaultdict(list)
            for (a, b), rate in zip(pairs, rates):
                graph[a].append((b, rate))
                graph[b].append((a, 1.0 / rate))
            return graph

        def maximize_amount(graph, start, initial_amt):
            max_amt = defaultdict(float)
            max_amt[start] = initial_amt
            queue = deque([start])
            in_queue = set([start])
            while queue:
                cur = queue.popleft()
                in_queue.discard(cur)
                for nxt, rate in graph[cur]:
                    new_amt = max_amt[cur] * rate
                    if new_amt > max_amt[nxt] + 1e-9:
                        max_amt[nxt] = new_amt
                        if nxt not in in_queue:
                            queue.append(nxt)
                            in_queue.add(nxt)
            return max_amt

        graph1 = build_graph(pairs1, rates1)
        graph2 = build_graph(pairs2, rates2)

        # Step 1: Compute max amounts for all currencies after Day 1
        max_after_day1 = maximize_amount(graph1, initialCurrency, 1.0)

        result = 1.0  # Always consider the original amount (no conversion)
        # Step 2: For each reachable currency after Day 1, maximize return to initialCurrency on Day 2
        for currency, amt in max_after_day1.items():
            max_after_day2 = maximize_amount(graph2, currency, amt)
            if initialCurrency in max_after_day2:
                result = max(result, max_after_day2[initialCurrency])
        # Step 3: Verification - ensure result is at least as large as initial (should be true in maximization problems)
        return result
# @lc code=end