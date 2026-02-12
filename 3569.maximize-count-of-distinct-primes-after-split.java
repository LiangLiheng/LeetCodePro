import java.util.*;

class Solution {
    static final int MAX = 100005;
    static BitSet sieve = new BitSet(MAX);
    static {
        sieve.set(2, MAX, true);
        for (int i = 2; i * i < MAX; i++) {
            if (sieve.get(i)) {
                for (int j = i * i; j < MAX; j += i) sieve.set(j, false);
            }
        }
    }

    class SegTree {
        int n;
        BitSet[] tree;
        int size;
        SegTree(int[] nums) {
            n = nums.length;
            size = 1; while (size < n) size <<= 1;
            tree = new BitSet[size << 1];
            for (int i = 0; i < (size << 1); i++) tree[i] = new BitSet(MAX);
            build(nums);
        }
        void build(int[] nums) {
            for (int i = 0; i < n; i++) {
                if (sieve.get(nums[i])) tree[i + size].set(nums[i]);
            }
            for (int i = size - 1; i > 0; i--) {
                tree[i].or(tree[i << 1]);
                tree[i].or(tree[(i << 1) | 1]);
            }
        }
        void update(int idx, int val) {
            int pos = idx + size;
            tree[pos].clear();
            if (sieve.get(val)) tree[pos].set(val);
            for (pos >>= 1; pos > 0; pos >>= 1) {
                tree[pos].clear();
                tree[pos].or(tree[pos << 1]);
                tree[pos].or(tree[(pos << 1) | 1]);
            }
        }
        BitSet query(int l, int r) {
            BitSet res = new BitSet(MAX);
            l += size; r += size;
            while (l < r) {
                if ((l & 1) == 1) { res.or(tree[l++]); }
                if ((r & 1) == 1) { res.or(tree[--r]); }
                l >>= 1; r >>= 1;
            }
            return res;
        }
    }

    public int[] maximumCount(int[] nums, int[][] queries) {
        int n = nums.length;
        SegTree seg = new SegTree(nums);
        int[] res = new int[queries.length];
        for (int qi = 0; qi < queries.length; qi++) {
            int idx = queries[qi][0], val = queries[qi][1];
            seg.update(idx, val);
            int max = 0;
            for (int k = 1; k < n; k++) {
                BitSet prefix = seg.query(0, k);
                BitSet suffix = seg.query(k, n);
                int cnt = prefix.cardinality() + suffix.cardinality();
                max = Math.max(max, cnt);
            }
            res[qi] = max;
        }
        return res;
    }
}