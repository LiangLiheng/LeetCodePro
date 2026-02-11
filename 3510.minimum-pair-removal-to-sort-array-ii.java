#
# @lc app=leetcode id=3510 lang=java
#
# [3510] Minimum Pair Removal to Sort Array II
#

# @lc code=start
class Solution {
  public int minimumPairRemoval(int[] nums) {
    if (nums.length <= 1) return 0;
    class Node {
      long val;
      Node prev, next;
      int leftmost;
      boolean deleted;
      Node(long v, int l) {
        val = v;
        leftmost = l;
        deleted = false;
      }
    }
    class Pair {
      long sum;
      Node left, right;
      int leftPos;
      Pair(long s, Node l, Node r, int p) {
        sum = s;
        left = l;
        right = r;
        leftPos = p;
      }
    }
    Node head = new Node((long) nums[0], 0);
    Node prevNode = head;
    for (int i = 1; i < nums.length; ++i) {
      Node node = new Node((long) nums[i], i);
      prevNode.next = node;
      node.prev = prevNode;
      prevNode = node;
    }
    java.util.PriorityQueue<Pair> pq = new java.util.PriorityQueue<>((a, b) -> {
      int cmp = java.lang.Long.compare(a.sum, b.sum);
      if (cmp != 0) return cmp;
      return java.lang.Integer.compare(a.leftPos, b.leftPos);
    });
    for (Node t = head; t.next != null; t = t.next) {
      pq.offer(new Pair(t.val + t.next.val, t, t.next, t.leftmost));
    }
    int numViol = 0;
    for (Node t = head; t.next != null; t = t.next) {
      if (t.val > t.next.val) ++numViol;
    }
    if (numViol == 0) return 0;
    int ops = 0;
    int curLen = nums.length;
    while (numViol > 0 && curLen > 1) {
      Pair pair = null;
      while (pq.size() > 0) {
        pair = pq.poll();
        if (!pair.left.deleted && !pair.right.deleted && pair.left.next == pair.right) {
          break;
        }
      }
      if (pair == null) break;
      Node L = pair.left;
      Node R = pair.right;
      long newVal = L.val + R.val;
      Node newNode = new Node(newVal, L.leftmost);
      Node pr = L.prev;
      Node nx = R.next;
      // subtract old violations
      if (pr != null) {
        if (pr.val > L.val) --numViol;
      }
      if (L.val > R.val) --numViol;
      if (nx != null) {
        if (R.val > nx.val) --numViol;
      }
      // relink
      newNode.prev = pr;
      newNode.next = nx;
      if (pr != null) {
        pr.next = newNode;
        if (pr.val > newVal) ++numViol;
      } else {
        head = newNode;
      }
      if (nx != null) {
        nx.prev = newNode;
        if (newVal > nx.val) ++numViol;
      }
      L.deleted = true;
      R.deleted = true;
      // add new pairs
      if (pr != null) {
        pq.offer(new Pair(pr.val + newVal, pr, newNode, pr.leftmost));
      }
      if (nx != null) {
        pq.offer(new Pair(newVal + nx.val, newNode, nx, newNode.leftmost));
      }
      ++ops;
      --curLen;
    }
    return ops;
  }
}
# @lc code=end