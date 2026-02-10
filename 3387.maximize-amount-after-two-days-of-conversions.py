#
# @lc app=leetcode id=3387 lang=python3
#
# [3387] Maximize Amount After Two Days of Conversions
#

# @lc code=start
class Solution:
    def maxAmount(self, initialCurrency: str, pairs1: List[List[str]], rates1: List[float], pairs2: List[List[str]], rates2: List[float]) -> float:
        all_curs = set([initialCurrency])
        for pairs in [pairs1, pairs2]:
            for pair in pairs:
                all_curs.add(pair[0])
                all_curs.add(pair[1])
        currencies = sorted(list(all_curs))
        idx = {c: i for i, c in enumerate(currencies)}
        k = len(currencies)
        s = idx[initialCurrency]

        def compute_dist(pairs, rates):
            dist = [[0.0] * k for _ in range(k)]
            for i in range(k):
                dist[i][i] = 1.0
            n = len(pairs)
            for i in range(n):
                a, b = pairs[i]
                r = rates[i]
                ia = idx[a]
                ib = idx[b]
                dist[ia][ib] = max(dist[ia][ib], r)
                dist[ib][ia] = max(dist[ib][ia], 1.0 / r)
            # Floyd-Warshall for max product
            for kk in range(k):
                for ii in range(k):
                    for jj in range(k):
                        cand = dist[ii][kk] * dist[kk][jj]
                        if cand > dist[ii][jj]:
                            dist[ii][jj] = cand
            return dist

        dist1 = compute_dist(pairs1, rates1)
        dist2 = compute_dist(pairs2, rates2)
        max_amount = 1.0
        for i in range(k):
            total = dist1[s][i] * dist2[i][s]
            if total > max_amount:
                max_amount = total
        return max_amount
# @lc code=end