#
# @lc app=leetcode id=3777 lang=java
#
# [3777] Minimum Deletions to Make Alternating Substring
#

# @lc code=start
class Solution {
    static class Fenwick {
        private int[] tree;
        public Fenwick(int n) {
            tree = new int[n + 1];
        }
        public void update(int idx, int delta) {
            while (idx < tree.length) {
                tree[idx] += delta;
                idx += idx & -idx;
            }
        }
        public int query(int idx) {
            int sum = 0;
            while (idx > 0) {
                sum += tree[idx];
                idx -= idx & -idx;
            }
            return sum;
        }
    }

    public int[] minDeletions(String s, int[][] queries) {
        int n = s.length();
        char[] str = s.toCharArray();
        Fenwick ft = new Fenwick(n);
        for (int i = 0; i < n - 1; i++) {
            ft.update(i + 1, (str[i] != str[i + 1]) ? 1 : 0);
        }
        int m = 0;
        for (int[] q : queries) {
            if (q[0] == 2) m++;
        }
        int[] answer = new int[m];
        int aidx = 0;
        for (int[] query : queries) {
            if (query[0] == 1) {
                int j = query[1];
                char old = str[j];
                str[j] = (old == 'A' ? 'B' : 'A');
                if (j > 0) {
                    int pos = j;
                    int oldDiff = (str[j - 1] != old ? 1 : 0);
                    int newDiff = (str[j - 1] != str[j] ? 1 : 0);
                    ft.update(pos, newDiff - oldDiff);
                }
                if (j < n - 1) {
                    int pos = j + 1;
                    int oldDiff = (old != str[j + 1] ? 1 : 0);
                    int newDiff = (str[j] != str[j + 1] ? 1 : 0);
                    ft.update(pos, newDiff - oldDiff);
                }
            } else {
                int l = query[1];
                int r = query[2];
                int deletions = 0;
                if (l < r) {
                    int changes = ft.query(r) - ft.query(l);
                    deletions = (r - l) - changes;
                }
                answer[aidx++] = deletions;
            }
        }
        return answer;
    }
}
# @lc code=end