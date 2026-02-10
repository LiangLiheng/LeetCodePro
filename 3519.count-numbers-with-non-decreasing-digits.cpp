#
# @lc app=leetcode id=3519 lang=cpp
#
# [3519] Count Numbers with Non-Decreasing Digits
#

# @lc code=start
class Solution {
public:
    int countNumbers(string l, string r, int b) {
        const long long MOD = 1000000007LL;
        auto mod_pow = [&](long long a, long long e) -> long long {
            long long res = 1;
            a %= MOD;
            while (e > 0) {
                if (e & 1) res = res * a % MOD;
                a = a * a % MOD;
                e >>= 1;
            }
            return res;
        };
        auto decrement_str = [&](string s) -> string {
            string res = s;
            int n = res.size();
            int i = n - 1;
            while (i >= 0) {
                if (res[i] > '0') {
                    res[i]--;
                    break;
                }
                res[i] = '9';
                i--;
            }
            size_t start = 0;
            while (start < res.size() && res[start] == '0') ++start;
            if (start == res.size()) return "0";
            return res.substr(start);
        };
        auto get_base_digits = [&](string num, int base_b) -> vector<int> {
            vector<int> digs;
            while (num != "0") {
                int rem = 0;
                string nextn = "";
                bool lead = true;
                for (char ch : num) {
                    int dgt = ch - '0';
                    int tempv = rem * 10 + dgt;
                    int q = tempv / base_b;
                    rem = tempv % base_b;
                    if (q != 0 || !lead) {
                        nextn += '0' + q;
                        lead = false;
                    }
                }
                if (nextn.empty()) nextn = "0";
                digs.push_back(rem);
                num = nextn;
            }
            reverse(digs.begin(), digs.end());
            if (digs.empty()) digs = {0};
            return digs;
        };
        auto solve = [&](string num_str, int base_b) -> long long {
            if (num_str == "0") return 0LL;
            vector<int> digits = get_base_digits(num_str, base_b);
            int LL = digits.size();
            const int MAXF = 400;
            vector<long long> fact(MAXF + 1, 1LL);
            for (int i = 1; i <= MAXF; ++i) {
                fact[i] = fact[i - 1] * i % MOD;
            }
            auto combi = [&](int nn, int kk) -> long long {
                if (kk < 0 || kk > nn) return 0LL;
                return fact[nn] * mod_pow(fact[kk], MOD - 2) % MOD * mod_pow(fact[nn - kk], MOD - 2) % MOD;
            };
            int mm = base_b - 1;
            long long smalll = 0;
            for (int kk = 1; kk < LL; ++kk) {
                smalll = (smalll + combi(kk + mm - 1, kk)) % MOD;
            }
            vector<vector<vector<long long>>> mem(LL + 1, vector<vector<long long>>(base_b + 1, vector<long long>(2, -1LL)));
            auto dfs = [&](auto&& self, int pos, int preev, int tiig) -> long long {
                if (pos == LL) return 1LL;
                if (mem[pos][preev][tiig] != -1LL) return mem[pos][preev][tiig];
                long long resu = 0;
                int upp = tiig ? digits[pos] : base_b - 1;
                int loww = (preev == 0 ? 1 : preev);
                for (int dd = loww; dd <= upp; ++dd) {
                    int new_tiig = tiig && (dd == upp);
                    resu = (resu + self(self, pos + 1, dd, new_tiig)) % MOD;
                }
                mem[pos][preev][tiig] = resu;
                return resu;
            };
            long long samelen = dfs(dfs, 0, 0, 1);
            return (smalll + samelen) % MOD;
        };
        string lmi = decrement_str(l);
        long long anss = (solve(r, b) - solve(lmi, b) + MOD) % MOD;
        return static_cast<int>(anss);
    }
};
# @lc code=end