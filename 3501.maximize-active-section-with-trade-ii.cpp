#
# @lc app=leetcode id=3501 lang=cpp
#
# [3501] Maximize Active Section with Trade II
#
# @lc code=start
#include <bits/stdc++.h>
using namespace std;

struct Island {
  int a, b, sz, c, leftsz, d, rightsz, fullgain;
};

class SparseTable {
public:
  vector<vector<int>> st;
  int logn;
  bool is_max;
  SparseTable(vector<int>& arr, bool maxx) : is_max(maxx) {
    int nn = arr.size();
    logn = 0;
    while ((1 << logn) <= nn) ++logn;
    st.assign(logn, vector<int>(nn, is_max ? INT_MIN / 2 : INT_MAX / 2));
    for (int i = 0; i < nn; ++i) st[0][i] = arr[i];
    for (int k = 1; k < logn; ++k) {
      for (int i = 0; i + (1 << k) <= nn; ++i) {
        if (is_max) {
          st[k][i] = max(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
        } else {
          st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
        }
      }
    }
  }
  int query(int le, int ri) {
    if (le > ri) return is_max ? INT_MIN / 2 : INT_MAX / 2;
    int len = ri - le + 1;
    int k = 31 - __builtin_clz(len);
    if (is_max) {
      return max(st[k][le], st[k][ri - (1 << k) + 1]);
    } else {
      return min(st[k][le], st[k][ri - (1 << k) + 1]);
    }
  }
};

class Solution {
public:
  vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
    int n = s.size();
    int q = queries.size();
    vector<int> pref(n + 1, 0);
    for (int i = 0; i < n; ++i) {
      pref[i + 1] = pref[i] + (s[i] == '1');
    }
    vector<tuple<int, int, int>> zero_runs;
    vector<Island> islands;
    int i = 0;
    while (i < n) {
      int j = i;
      char ch = s[i];
      while (j < n && s[j] == ch) ++j;
      int len = j - i;
      if (ch == '0') {
        zero_runs.emplace_back(i, j - 1, len);
      } else {
        // left0sz
        int left_cnt = 0;
        int k = i - 1;
        while (k >= 0 && s[k] == '0') {
          ++left_cnt;
          --k;
        }
        int c = i - left_cnt;
        // right0sz
        int right_cnt = 0;
        int kk = j;
        while (kk < n && s[kk] == '0') {
          ++right_cnt;
          ++kk;
        }
        int d = j + right_cnt - 1;
        if (left_cnt >= 1 && right_cnt >= 1) {
          islands.push_back({i, j - 1, len, c, left_cnt, d, right_cnt, left_cnt + right_cnt});
        }
      }
      i = j;
    }
    int p = islands.size();
    int m = zero_runs.size();
    vector<int> a_list(p), b_list(p), c_span(p), d_span(p), isl_sz(p), span_fullg(p);
    for (int jj = 0; jj < p; ++jj) {
      a_list[jj] = islands[jj].a;
      b_list[jj] = islands[jj].b;
      c_span[jj] = islands[jj].c;
      d_span[jj] = islands[jj].d;
      isl_sz[jj] = islands[jj].sz;
      span_fullg[jj] = islands[jj].fullgain;
    }
    SparseTable smin_isl(isl_sz, false); // min
    SparseTable smax_span(span_fullg, true); // max
    vector<int> zc(m), zd(m), zsz(m);
    for (int kk = 0; kk < m; ++kk) {
      tie(zc[kk], zd[kk], zsz[kk]) = zero_runs[kk];
    }
    SparseTable smax_hole(zsz, true);
    vector<int> answer(q);
    for (int qi = 0; qi < q; ++qi) {
      int l = queries[qi][0];
      int r = queries[qi][1];
      int orig_sub = pref[r + 1] - pref[l];
      int outside_l = pref[l];
      int outside_r = pref[n] - pref[r + 1];
      // islands range
      auto it_al = lower_bound(a_list.begin(), a_list.end(), l + 1);
      int j_left = it_al - a_list.begin();
      auto it_brp1 = lower_bound(b_list.begin() + j_left, b_list.end(), r);
      int j_rightp1 = it_brp1 - b_list.begin();
      int j_right = j_rightp1 - 1;
      bool has_isl = (j_left <= j_right);
      int minisl = INT_MAX / 2;
      int max_hole = 0;
      int max_g1_reg = INT_MIN / 2;
      if (has_isl) {
        minisl = smin_isl.query(j_left, j_right);
        // regular spans
        auto it_cl = lower_bound(c_span.begin(), c_span.end(), l);
        int jl_reg = it_cl - c_span.begin();
        auto it_drp1 = lower_bound(d_span.begin() + jl_reg, d_span.end(), r + 1);
        int jr_regp1 = it_drp1 - d_span.begin();
        int jr_reg = jr_regp1 - 1;
        if (jl_reg <= jr_reg) {
          max_g1_reg = smax_span.query(jl_reg, jr_reg);
        }
        // max_hole
        auto it_zl = lower_bound(zc.begin(), zc.end(), l);
        int kl_h = it_zl - zc.begin();
        auto it_zdrp1 = lower_bound(zd.begin() + kl_h, zd.end(), r + 1);
        int kr_hp1 = it_zdrp1 - zd.begin();
        int kr_h = kr_hp1 - 1;
        if (kl_h <= kr_h) {
          max_hole = smax_hole.query(kl_h, kr_h);
        }
      }
      // special left
      int g_left = INT_MIN / 2;
      if (l < n && s[l] == '0') {
        auto it_zcl = lower_bound(zc.begin(), zc.end(), l + 1);
        int kl = (it_zcl - zc.begin()) - 1;
        if (kl >= 0 && zc[kl] <= l && zd[kl] >= l) {
          int na = zd[kl] + 1;
          if (na <= r) {
            auto it_ia = lower_bound(a_list.begin(), a_list.end(), na);
            int jjl = it_ia - a_list.begin();
            if (it_ia != a_list.end() && a_list[jjl] == na && islands[jjl].b <= r - 1) {
              int lt = islands[jjl].a - l;
              int rt = min(r - islands[jjl].b, islands[jjl].rightsz);
              g_left = lt + rt;
            }
          }
        }
      }
      // special right
      int g_right = INT_MIN / 2;
      if (r < n && s[r] == '0') {
        auto it_zcr = lower_bound(zc.begin(), zc.end(), r + 1);
        int kr = (it_zcr - zc.begin()) - 1;
        if (kr >= 0 && zc[kr] <= r && zd[kr] >= r) {
          int pb = zc[kr] - 1;
          auto it_ib = lower_bound(b_list.begin(), b_list.end(), pb);
          int jjr = it_ib - b_list.begin();
          if (it_ib != b_list.end() && b_list[jjr] == pb && islands[jjr].a >= l + 1) {
            int lt = min(islands[jjr].a - l, islands[jjr].leftsz);
            int rt = r - islands[jjr].b;
            g_right = lt + rt;
          }
        }
      }
      int maxg1 = 0;
      if (has_isl) {
        maxg1 = max({max_g1_reg, g_left, g_right});
        if (maxg1 < 0) maxg1 = 0;
      }
      int g2 = INT_MIN / 2;
      if (has_isl && max_hole > 0) {
        g2 = max_hole - minisl;
      }
      int bestgain = max({0, maxg1, g2});
      answer[qi] = outside_l + outside_r + orig_sub + bestgain;
    }
    return answer;
  }
};
# @lc code=end