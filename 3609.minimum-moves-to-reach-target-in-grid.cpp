#
# @lc app=leetcode id=3609 lang=cpp
#
# [3609] Minimum Moves to Reach Target in Grid
#

# @lc code=start
class Solution {
public:
    int minMoves(int sx, int sy, int tx, int ty) {
        using ll = long long;
        using pll = pair<ll, ll>;
        ll SX = sx;
        ll SY = sy;
        ll TX = tx;
        ll TY = ty;
        queue<pair<pll, int>> q;
        set<pll> vis;
        q.push({{TX, TY}, 0});
        vis.insert({TX, TY});
        while (!q.empty()) {
            auto front = q.front(); q.pop();
            ll cx = front.first.first;
            ll cy = front.first.second;
            int d = front.second;
            if (cx == SX && cy == SY) {
                return d;
            }
            // Previous assuming last added to x
            {
                ll px = -1;
                ll pyx = cy;
                if (cx % 2 == 0 && cx / 2 >= cy) {
                    px = cx / 2;
                } else if (cx < 2LL * cy && cx >= cy) {
                    px = cx - cy;
                }
                if (px != -1 && px >= SX && pyx >= SY) {
                    pll np = {px, pyx};
                    if (vis.find(np) == vis.end()) {
                        vis.insert(np);
                        q.push({np, d + 1});
                    }
                }
            }
            // Previous assuming last added to y
            {
                ll py_ = -1;
                ll pxx = cx;
                if (cy % 2 == 0 && cy / 2 >= cx) {
                    py_ = cy / 2;
                } else if (cy < 2LL * cx && cy >= cx) {
                    py_ = cy - cx;
                }
                if (py_ != -1 && pxx >= SX && py_ >= SY) {
                    pll np = {pxx, py_};
                    if (vis.find(np) == vis.end()) {
                        vis.insert(np);
                        q.push({np, d + 1});
                    }
                }
            }
        }
        return -1;
    }
};
# @lc code=end