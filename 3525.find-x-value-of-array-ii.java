#
# @lc app=leetcode id=3525 lang=java
#
# [3525] Find X Value of Array II
#

# @lc code=start
class Solution {
    static class Node {
        int[] cnt;
        int total;
        Node(int k) {
            cnt = new int[k];
            total = 0;
        }
    }

    private Node[] tree;
    private int KK;

    private void merge(Node parent, Node left, Node right) {
        parent.total = (int) ((long) left.total * right.total % KK);
        System.arraycopy(left.cnt, 0, parent.cnt, 0, KK);
        int[] temp = new int[KK];
        for (int rem = 0; rem < KK; rem++) {
            int comb = (int) ((long) left.total * rem % KK);
            temp[comb] += right.cnt[rem];
        }
        for (int i = 0; i < KK; i++) {
            parent.cnt[i] += temp[i];
        }
    }

    private Node getNeutral() {
        Node neu = new Node(KK);
        neu.total = 1;
        return neu;
    }

    private void build(int node, int start, int end, int[] mods) {
        if (start == end) {
            tree[node] = new Node(KK);
            tree[node].cnt[mods[start]] = 1;
            tree[node].total = mods[start];
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node, start, mid, mods);
        build(2 * node + 1, mid + 1, end, mods);
        tree[node] = new Node(KK);
        merge(tree[node], tree[2 * node], tree[2 * node + 1]);
    }

    private void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = new Node(KK);
            tree[node].cnt[val] = 1;
            tree[node].total = val;
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = new Node(KK);
        merge(tree[node], tree[2 * node], tree[2 * node + 1]);
    }

    private Node query(int node, int start, int end, int l, int r) {
        if (l > end || r < start) {
            return getNeutral();
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        Node left = query(2 * node, start, mid, l, r);
        Node right = query(2 * node + 1, mid + 1, end, l, r);
        Node res = new Node(KK);
        merge(res, left, right);
        return res;
    }

    public int[] resultArray(int[] nums, int k, int[][] queries) {
        int n = nums.length;
        KK = k;
        int[] mods = new int[n];
        for (int i = 0; i < n; i++) {
            mods[i] = (int) ((long) nums[i] % k);
        }
        tree = new Node[4 * n + 10];
        build(1, 0, n - 1, mods);
        int[] ans = new int[queries.length];
        for (int i = 0; i < queries.length; i++) {
            int idx = queries[i][0];
            int val = queries[i][1];
            int sti = queries[i][2];
            int xi = queries[i][3];
            int newm = (int) ((long) val % k);
            update(1, 0, n - 1, idx, newm);
            Node res = query(1, 0, n - 1, sti, n - 1);
            ans[i] = res.cnt[xi];
        }
        return ans;
    }
}
# @lc code=end