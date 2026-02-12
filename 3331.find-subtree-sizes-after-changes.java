#
# @lc app=leetcode id=3331 lang=java
#
# [3331] Find Subtree Sizes After Changes
#

# @lc code=start
class Solution {
    public int[] findSubtreeSizes(int[] parent, String s) {
        int n = parent.length;
        // Step 1: Build initial tree
        List<Integer>[] tree = new ArrayList[n];
        for (int i = 0; i < n; ++i) tree[i] = new ArrayList<>();
        for (int i = 1; i < n; ++i) tree[parent[i]].add(i);

        // Step 2: Find new parents for each node if needed (separating identification from application)
        int[] newParent = parent.clone();
        Map<Character, Deque<Integer>> charStack = new HashMap<>();
        for (char c = 'a'; c <= 'z'; ++c) charStack.put(c, new ArrayDeque<>());
        int[] closestAncestor = new int[n];
        Arrays.fill(closestAncestor, -1);
        dfsFind(0, -1, s, charStack, closestAncestor, tree);
        for (int x = 1; x < n; ++x) {
            if (closestAncestor[x] != -1) newParent[x] = closestAncestor[x];
        }

        // Step 3: Validate updated parent array represents a valid tree (omitted: would be a check in practice)

        // Step 4: Build new tree from updated parents
        List<Integer>[] newTree = new ArrayList[n];
        for (int i = 0; i < n; ++i) newTree[i] = new ArrayList<>();
        for (int i = 1; i < n; ++i) newTree[newParent[i]].add(i);
        // (Optional: validation of the new tree structure)

        // Step 5: Compute subtree sizes
        int[] ans = new int[n];
        dfsSize(0, newTree, ans);
        // (Optional: verify correctness of subtree sizes)
        return ans;
    }

    // Helper to find closest ancestor with same char for each node
    private void dfsFind(int node, int parent, String s, Map<Character, Deque<Integer>> cs, int[] ca, List<Integer>[] tree) {
        char c = s.charAt(node);
        if (!cs.get(c).isEmpty()) ca[node] = cs.get(c).peek();
        cs.get(c).push(node);
        for (int child : tree[node]) {
            dfsFind(child, node, s, cs, ca, tree);
        }
        cs.get(c).pop();
    }

    // Helper to compute subtree sizes
    private int dfsSize(int node, List<Integer>[] tree, int[] ans) {
        int size = 1;
        for (int child : tree[node]) {
            size += dfsSize(child, tree, ans);
        }
        ans[node] = size;
        return size;
    }
}
# @lc code=end