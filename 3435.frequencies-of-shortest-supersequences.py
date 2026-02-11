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
        let_set = set()
        for w in words:
            let_set.update(w)
        chars = sorted(let_set)
        m = len(chars)
        if m == 0:
            return []
        char_to_id = {ch: i for i, ch in enumerate(chars)}
        preds = [[] for _ in range(m)]
        for w in words:
            xid = char_to_id[w[0]]
            yid = char_to_id[w[1]]
            preds[yid].append(xid)
        valid = []
        for emask in range(1 << m):
            r = bin(emask).count('1')
            # build graph
            graph = [[] for _ in range(32)]
            indeg = [0] * 32
            node_id = 0
            finish_node = [-1] * m
            for i in range(m):
                finish_node[i] = node_id
                node_id += 1
            start_node = [-1] * m
            for i in range(m):
                if emask & (1 << i):
                    start_node[i] = node_id
                    node_id += 1
            num_nodes = node_id
            # start -> finish
            for i in range(m):
                if start_node[i] != -1:
                    s = start_node[i]
                    f = finish_node[i]
                    graph[s].append(f)
                    indeg[f] += 1
            # preds for finish
            for c in range(m):
                fnode = finish_node[c]
                for x in preds[c]:
                    first_n = start_node[x] if start_node[x] != -1 else finish_node[x]
                    graph[first_n].append(fnode)
                    indeg[fnode] += 1
            # Kahn
            q = deque([i for i in range(num_nodes) if indeg[i] == 0])
            cnt = 0
            temp_indeg = indeg[:]  # copy because we modify
            while q:
                u = q.popleft()
                cnt += 1
                for v in graph[u]:
                    temp_indeg[v] -= 1
                    if temp_indeg[v] == 0:
                        q.append(v)
            if cnt == num_nodes:
                valid.append((r, emask))
        if not valid:
            return []
        min_r = min(rr for rr, _ in valid)
        result = []
        for rr, emask in valid:
            if rr == min_r:
                freq = [0] * 26
                for i in range(m):
                    aid = ord(chars[i]) - ord('a')
                    freq[aid] = 2 if (emask & (1 << i)) else 1
                result.append(freq)
        return result

# @lc code=end