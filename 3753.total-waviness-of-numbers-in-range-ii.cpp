#
# @lc app=leetcode id=3753 lang=cpp
#
# [3753] Total Waviness of Numbers in Range II
#

# @lc code=start
class Solution {
public:
    long long totalWaviness(long long num1, long long num2) {
        auto calc = [&](long long n) -> long long {
            if (n <= 0) return 0LL;
            std::string S = std::to_string(n);
            int D = S.size();
            const int MP = 11;
            const int MSP = 17;
            const int MT = 2;
            const int MPOS = 17;
            int stride_p2 = MP;
            int stride_sp = MP * MP;
            int stride_t = MSP * stride_sp;
            int stride_pos = MT * stride_t;
            int TS = MPOS * stride_pos;
            std::vector<std::pair<long long, long long>> mem(TS, {-1LL, -1LL});
            auto getidx = [&](int posi, int ti, int spi, int p2i, int p1i) -> int {
                return posi * stride_pos + ti * stride_t + spi * stride_sp + p2i * stride_p2 + p1i;
            };
            std::function<std::pair<long long, long long>(int, int, int, int, int)> dfs =
                [&](int pos, int tig, int sp, int p2, int p1) -> std::pair<long long, long long> {
                if (pos == D) {
                    return {1LL, 0LL};
                }
                int spi = sp + 1;
                int p2i = p2 + 1;
                int p1i = p1 + 1;
                int idx = getidx(pos, tig, spi, p2i, p1i);
                if (mem[idx].first != -1LL) {
                    return mem[idx];
                }
                long long tcnt = 0;
                long long twav = 0;
                int up = tig ? (S[pos] - '0') : 9;
                for (int d = 0; d <= up; ++d) {
                    int ntig = tig && (d == up);
                    int nsp = sp;
                    int np2 = p2;
                    int np1 = p1;
                    long long contrib = 0;
                    if (sp == -1) {
                        if (d == 0) {
                            nsp = -1;
                            np2 = -1;
                            np1 = -1;
                        } else {
                            nsp = pos;
                            np2 = -1;
                            np1 = d;
                        }
                    } else {
                        int mlen = D - sp;
                        int caidx = pos - sp;
                        int paidx = caidx - 1;
                        if (paidx >= 1 && paidx <= mlen - 2) {
                            int leftv = p2;
                            int midv = p1;
                            int rightv = d;
                            if (midv > leftv && midv > rightv) {
                                contrib = 1;
                            } else if (midv < leftv && midv < rightv) {
                                contrib = 1;
                            }
                        }
                        np2 = p1;
                        np1 = d;
                    }
                    auto sub = dfs(pos + 1, ntig, nsp, np2, np1);
                    tcnt += sub.first;
                    twav += sub.second + contrib * sub.first;
                }
                mem[idx] = {tcnt, twav};
                return mem[idx];
            };
            return dfs(0, 1, -1, -1, -1).second;
        };
        return calc(num2) - calc(num1 - 1LL);
    }
};
# @lc code=end