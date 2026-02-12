class Solution {
    public long specialPalindrome(long n) {
        long[] minResult = new long[] { Long.MAX_VALUE };
        generateDigitMultisets(n, new int[10], 1, 0, minResult);
        return minResult[0];
    }

    // Explore all combinations of digit counts for digits 1-9
    private void generateDigitMultisets(long n, int[] counts, int digit, int length, long[] minResult) {
        if (digit == 10) {
            if (length == 0) return; // Skip empty multiset
            if (canFormPalindrome(counts)) {
                buildPalindromes(n, counts, minResult);
            }
            return;
        }
        // Option 1: Do not use this digit
        generateDigitMultisets(n, counts, digit + 1, length, minResult);
        // Option 2: Use this digit exactly k times
        counts[digit] = digit;
        generateDigitMultisets(n, counts, digit + 1, length + digit, minResult);
        counts[digit] = 0;
    }

    // Check if the digit counts can form a palindrome
    private boolean canFormPalindrome(int[] counts) {
        int odd = 0;
        for (int d = 1; d <= 9; ++d) {
            if (counts[d] % 2 != 0) odd++;
        }
        return odd <= 1;
    }

    // Generate all palindromic numbers from the digit counts
    private void buildPalindromes(long n, int[] counts, long[] minResult) {
        int len = 0;
        for (int d = 1; d <= 9; ++d) len += counts[d];
        int[] halfCounts = new int[10];
        int midDigit = -1;
        for (int d = 1; d <= 9; ++d) {
            halfCounts[d] = counts[d] / 2;
            if (counts[d] % 2 == 1) midDigit = d;
        }
        List<Integer> half = new ArrayList<>();
        generateHalfPermutations(halfCounts, len / 2, half, midDigit, n, minResult);
    }

    // Recursively construct all unique half-side permutations for palindromes
    private void generateHalfPermutations(int[] halfCounts, int remaining, List<Integer> path, int midDigit, long n, long[] minResult) {
        if (remaining == 0) {
            if (!path.isEmpty() && path.get(0) == 0) return; // No leading zeros
            StringBuilder sb = new StringBuilder();
            for (int d : path) sb.append(d);
            String halfStr = sb.toString();
            StringBuilder palindrome = new StringBuilder(halfStr);
            if (midDigit != -1) palindrome.append(midDigit);
            palindrome.append(new StringBuilder(halfStr).reverse());
            long candidate = Long.parseLong(palindrome.toString());
            if (candidate > n && candidate < minResult[0]) {
                minResult[0] = candidate;
            }
            return;
        }
        for (int d = 1; d <= 9; ++d) {
            if (halfCounts[d] > 0) {
                halfCounts[d]--;
                path.add(d);
                generateHalfPermutations(halfCounts, remaining - 1, path, midDigit, n, minResult);
                path.remove(path.size() - 1);
                halfCounts[d]++;
            }
        }
    }
}