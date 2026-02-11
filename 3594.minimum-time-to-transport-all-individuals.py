#
# @lc app=leetcode id=3594 lang=python3
#
# [3594] Minimum Time to Transport All Individuals
#

# @lc code=start
class Solution:
    def minTime(self, n: int, k: int, m: int, time: List[int], mul: List[float]) -> float:
        from itertools import combinations
        import heapq
        import math

        INF = float('inf')
        full = (1 << n) - 1
        dist = [[[INF] * m for _ in range(2)] for _ in range(1 << n)]
        pq = []
        dist[0][0][0] = 0.0
        heapq.heappush(pq, (0.0, 0, 0, 0))  # time, mask, boat, stage

        while pq:
            cur_time, mask, boat, stage = heapq.heappop(pq)
            if cur_time > dist[mask][boat][stage]:
                continue

            if boat == 0:  # send group to dest
                base_people = [i for i in range(n) if (mask & (1 << i)) == 0]
                nb = len(base_people)
                if nb == 0:
                    continue
                for sz in range(1, min(k, nb) + 1):
                    for comb in combinations(base_people, sz):
                        max_t = max(time[i] for i in comb)
                        cross_time = max_t * mul[stage]
                        advance = int(math.floor(cross_time)) % m
                        new_stage = (stage + advance) % m
                        new_mask = mask
                        for i in comb:
                            new_mask |= (1 << i)
                        new_boat = 1
                        new_time = cur_time + cross_time
                        if new_time < dist[new_mask][new_boat][new_stage]:
                            dist[new_mask][new_boat][new_stage] = new_time
                            heapq.heappush(pq, (new_time, new_mask, new_boat, new_stage))
            else:  # boat == 1, return one if needed
                if mask == full:
                    continue
                dest_people = [i for i in range(n) if mask & (1 << i)]
                for r in dest_people:
                    ret_time = time[r] * mul[stage]
                    advance = int(math.floor(ret_time)) % m
                    new_stage = (stage + advance) % m
                    new_mask = mask & ~(1 << r)
                    new_boat = 0
                    new_time = cur_time + ret_time
                    if new_time < dist[new_mask][new_boat][new_stage]:
                        dist[new_mask][new_boat][new_stage] = new_time
                        heapq.heappush(pq, (new_time, new_mask, new_boat, new_stage))

        min_time = INF
        for b in range(2):
            for s in range(m):
                if dist[full][b][s] < min_time:
                    min_time = dist[full][b][s]
        return min_time if min_time < INF else -1.0

# @lc code=end