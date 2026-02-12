#
# @lc app=leetcode id=3387 lang=java
#
# [3387] Maximize Amount After Two Days of Conversions
#
# @lc code=start
import java.util.*;
class Solution {
    public double maxAmount(String initialCurrency, List<List<String>> pairs1, double[] rates1, List<List<String>> pairs2, double[] rates2) {
        // Build graph for day 1
        Map<String, List<Pair>> g1 = buildGraph(pairs1, rates1);
        // Amounts after day 1 for each currency
        Map<String, Double> afterDay1 = bfsMax(initialCurrency, 1.0, g1);

        // Build graph for day 2
        Map<String, List<Pair>> g2 = buildGraph(pairs2, rates2);
        double max = 1.0; // At least we can keep the original 1.0
        // For each currency and amount after day 1, propagate max on day 2
        for (Map.Entry<String, Double> entry : afterDay1.entrySet()) {
            String currency = entry.getKey();
            double amount = entry.getValue();
            Map<String, Double> afterDay2 = bfsMax(currency, amount, g2);
            // Try to convert back to initialCurrency
            max = Math.max(max, afterDay2.getOrDefault(initialCurrency, 0.0));
        }
        // Explicit verification step: ensure doing nothing is considered
        max = Math.max(max, 1.0);
        return max;
    }

    // Helper: build bidirectional graph
    private Map<String, List<Pair>> buildGraph(List<List<String>> pairs, double[] rates) {
        Map<String, List<Pair>> g = new HashMap<>();
        for (int i = 0; i < pairs.size(); ++i) {
            String from = pairs.get(i).get(0);
            String to = pairs.get(i).get(1);
            double rate = rates[i];
            g.computeIfAbsent(from, k -> new ArrayList<>()).add(new Pair(to, rate));
            g.computeIfAbsent(to, k -> new ArrayList<>()).add(new Pair(from, 1.0 / rate));
        }
        return g;
    }

    // Helper: BFS/Bellman-Ford-style max propagation
    private Map<String, Double> bfsMax(String start, double startAmount, Map<String, List<Pair>> g) {
        Map<String, Double> maxAmount = new HashMap<>();
        Queue<Pair2> queue = new LinkedList<>();
        queue.offer(new Pair2(start, startAmount));
        maxAmount.put(start, startAmount);
        while (!queue.isEmpty()) {
            Pair2 curr = queue.poll();
            String currency = curr.currency;
            double amount = curr.amount;
            if (!g.containsKey(currency)) continue;
            for (Pair neighbor : g.get(currency)) {
                double newAmount = amount * neighbor.rate;
                if (newAmount > maxAmount.getOrDefault(neighbor.currency, 0.0) + 1e-9) {
                    maxAmount.put(neighbor.currency, newAmount);
                    queue.offer(new Pair2(neighbor.currency, newAmount));
                }
            }
        }
        return maxAmount;
    }

    private static class Pair {
        String currency;
        double rate;
        Pair(String c, double r) { currency = c; rate = r; }
    }
    private static class Pair2 {
        String currency;
        double amount;
        Pair2(String c, double a) { currency = c; amount = a; }
    }
}
# @lc code=end