#
# @lc app=leetcode id=3435 lang=python3
#
# [3435] Frequencies of Shortest Supersequences
#

# @lc code=start
from typing import List
from collections import deque

class Solution:
    def supersequences(self, words: List[str]) -> List[List[int]]:
        all_chars = set()
        for w in words:
            all_chars.update(w)
        if not all_chars:
            return []
        chars = sorted(all_chars)
        m = len(chars)
        cid = {chars[i]: i for i in range(m)}
        required_self = [False] * m
        incoming = [[] for _ in range(m)]
        pred_mask = [0] * m
        for w in words:
            u = cid[w[0]]
            v = cid[w[1]]
            if u == v:
                required_self[u] = True
            else:
                incoming[v].append(u)
                pred_mask[v] |= (1 << u)
        # POW3
        POW3 = [1] * (m + 1)
        for i in range(1, m + 1):
            POW3[i] = POW3[i - 1] * 3
        total_states = POW3[m]
        INF = 10**9
        dist = [INF] * total_states
        final_state = sum(2 * POW3[i] for i in range(m))
        dist[0] = 0
        q = deque([0])
        while q:
            state = q.popleft()
            d = dist[state]
            started_mask = 0
            for i in range(m):
                if (state // POW3[i]) % 3 >= 1:
                    started_mask |= (1 << i)
            for c in range(m):
                s_c = (state // POW3[c]) % 3
                if s_c == 2:
                    continue
                if s_c == 0:
                    # to 1
                    ns = state + POW3[c]
                    if dist[ns] > d + 1:
                        dist[ns] = d + 1
                        q.append(ns)
                    # to 2?
                    can = not required_self[c] and ((started_mask & pred_mask[c]) == pred_mask[c])
                    if can:
                        ns2 = state + 2 * POW3[c]
                        if dist[ns2] > d + 1:
                            dist[ns2] = d + 1
                            q.append(ns2)
                else:  # s_c == 1, to 2
                    can = ((started_mask & pred_mask[c]) == pred_mask[c])
                    if can:
                        ns3 = state + POW3[c]
                        if dist[ns3] > d + 1:
                            dist[ns3] = d + 1
                            q.append(ns3)
        min_L = dist[final_state]
        if min_L == INF:
            return []
        # base
        base_L = sum(2 if required_self[i] else 1 for i in range(m))
        extras = min_L - base_L
        non_self = [i for i in range(m) if not required_self[i]]
        k = len(non_self)
        res = []
        a = ord('a')
        for mask in range(1 << k):
            if bin(mask).count('1') != extras:
                continue
            dup = set()
            for j in range(k):
                if mask & (1 << j):
                    dup.add(non_self[j])
            f = [2 if required_self[i] or i in dup else 1 for i in range(m)]
            # build graph
            first_n = [-1] * m
            last_n = [-1] * m
            node_id = 0
            for i in range(m):
                first_n[i] = node_id
                node_id += 1
                if f[i] == 2:
                    last_n[i] = node_id
                    node_id += 1
                else:
                    last_n[i] = first_n[i]
            N = node_id
            graph = [[] for _ in range(N)]
            for i in range(m):
                if f[i] == 2:
                    graph[first_n[i]].append(last_n[i])
            for v in range(m):
                for u in incoming[v]:
                    graph[first_n[u]].append(last_n[v])
            # Kahn
            indeg = [0] * N
            for u in range(N):
                for v in graph[u]:
                    indeg[v] += 1
            q2 = deque(i for i in range(N) if indeg[i] == 0)
            cnt = 0
            while q2:
                u = q2.popleft()
                cnt += 1
                for v in graph[u]:
                    indeg[v] -= 1
                    if indeg[v] == 0:
                        q2.append(v)
            if cnt == N:
                freq = [0] * 26
                for i in range(m):
                    freq[ord(chars[i]) - a] = f[i]
                res.append(freq)
        return res

# @lc code=end