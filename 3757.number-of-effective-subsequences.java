class Solution {
    static final int MOD = 1_000_000_007;
    public int countEffective(int[] nums) {
        int n = nums.length;
        int allOr = 0;
        for (int num : nums) allOr |= num;
        List<Integer> bits = new ArrayList<>();
        for (int b = 0; b < 32; ++b) if (((allOr >> b) & 1) != 0) bits.add(b);
        int m = bits.size();
        List<List<Integer>> contributors = new ArrayList<>();
        for (int i = 0; i < m; ++i) contributors.add(new ArrayList<>());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (((nums[i] >> bits.get(j)) & 1) != 0) contributors.get(j).add(i);
            }
        }
        long res = 0;
        for (int mask = 1; mask < (1 << m); ++mask) {
            Set<Integer> set = new HashSet<>();
            int sign = Integer.bitCount(mask) % 2 == 1 ? 1 : -1;
            for (int j = 0; j < m; ++j) if (((mask >> j) & 1) != 0) set.addAll(contributors.get(j));
            long ways = pow2(set.size()) - 1;
            if (ways < 0) ways += MOD;
            res = (res + sign * ways + MOD) % MOD;
        }
        return (int)res;
    }
    private long pow2(int n) {
        long res = 1, base = 2;
        while (n > 0) {
            if ((n & 1) == 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            n >>= 1;
        }
        return res;
    }
}