import random
from typing import List


class UF:
    def __init__(self, n:int):
        self.cnt = n
        self.fa = [x for x in range(n)]
    def find(self, x:int) -> int:
        if self.fa[x] != x:
            self.fa[x] = self.find(self.fa[x])
        return self.parent[x]
    def union(self, x:int, y:int):
        if self.find(y) != self.find(x):
            self.fa[self.find(y)] = self.find(x)
            self.cnt -= 1
class Trie:
    def __init__(self):
        self.children = [None] * 26
        self.isEnd = False
    def _searchPrefix(self, prefix: str) -> "Trie":
        node = self
        for ch in prefix:
            ch = ord(ch) - ord('a')
            if not node.children[ch]:
                return None
            node = node.children[ch]
        return node
    def insert(self, word: str) -> None:
        node = self
        for ch in word:
            ch = ord(ch) - ord('a')
            if not node.children[ch]:
                node.children[ch] = Trie()
            node = node.children[ch]
        node.isEnd = True
    def search(self, word: str) -> bool:
        node = self._searchPrefix(word)
        return node is not None and node.isEnd
    def searchsWith(self, prefix: str) -> bool:
        return self._searchPrefix(prefix) is not None

class Heap:
    def __init__(self):
        pass
    def sink(self):
        pass
    def swap(self):
        pass
# O(nlog(n))
class TreeList:
    __slots__ = "nums", "tree"
    def __init__(self, nums: List[int]):
        n = len(nums)
        self.nums = [0] * n
        self.tree = [0] * (n + 1)
        for i, x in enumerate(nums):
            self.update(i, x)
    def update(self, index:int, val:int) -> None:
        delta = val - self.nums[index]
        self.nums[index] = val
        i = index + 1
        while i < len(self.tree):
            self.tree[i] += delta
            i += i & -i
    def prefixSum(self, i:int) -> int:
        s = 0
        while i:
            s += self.tree[i]
            i &= i - 1
        return s
    def sumRange(self, left:int, right:int) -> int:
        return self.prefixSum(right + 1) - self.prefixSum(left)
# O(n)
class NumArray:
    __slots__ = 'nums', 'tree'
    def __init__(self, nums: List[int]):
        n = len(nums)
        tree = [0] * (n + 1)
        for i, x in enumerate(nums, 1):  # i 从 1 开始
            tree[i] += x
            nxt = i + (i & -i)  # 下一个关键区间的右端点
            if nxt <= n:
                tree[nxt] += tree[i]
        self.nums = nums
        self.tree = tree
    def update(self, index: int, val: int) -> None:
        delta = val - self.nums[index]
        self.nums[index] = val
        i = index + 1
        while i < len(self.tree):
            self.tree[i] += delta
            i += i & -i
    def prefixSum(self, i: int) -> int:
        s = 0
        while i:
            s += self.tree[i]
            i &= i - 1  # i -= i & -i 的另一种写法
        return s
    def sumRange(self, left: int, right: int) -> int:
        return self.prefixSum(right + 1) - self.prefixSum(left)

class LRU:
    pass
class LFU:
    pass
class LinkedList:
    pass

#  consistent hash
class RingList:
    pass
MAX_LEVEL = 32
P_FACTOR = 0.25
class SkipListNode:
    __slots__ = 'val', 'forward'
    def __init__(self, val:int, max_level = MAX_LEVEL):
        self.val = val
        self.forward = [None] * max_level
class SkipList:
    def __init__(self):
        self.head = SkipListNode(-1)
        self.level = 0
    def _random_level(self) -> int:
        lv = 1
        while lv < MAX_LEVEL and random.random() < P_FACTOR:
            lv += 1
        return lv
    def put(self, num:int) -> None:
        update = [self.head] * MAX_LEVEL
        curr = self.head
        for i in range(self.level - 1, -1, -1):
            while curr.forward[i] and curr.forward[i].val < num:
                curr = curr.forward[i]
            update[i] = curr
        lv = self._random_level()
        self.level = max(self.level, lv)
        new_node = SkipListNode(num, lv)
        for i in range(lv):
            new_node.forward[i] = update[i].forward[i]
            update[i].forward[i] = new_node
    def get(self, target:int) -> bool:
        curr = self.head
        for i in range(self.level - 1, -1, -1):
            while curr.forward[i] and curr.forward[i].val < target:
                curr = curr.forward[i]
        curr = curr.forward[0]
        return curr is not None and curr.val == target
    def delete(self, num:int) -> bool:
        update = [None] * MAX_LEVEL
        curr = self.head
        for i in range(self.level - 1, -1 -1):
            while curr.forward[i] and curr.forward[i].val < num:
                curr = curr.forward[i]
            update[i] = curr
        curr = curr.forward[0]
        if curr is None or curr.val != num:
            return False
        for i in range(self.level):
            if update[i].forwad[i] != curr:
                break
            update[i].forward[i] = curr.forward[i]
        while self.level > 1 and self.head.forward[self.level - 1] is None:
            self.level -= 1
        return True
    def range_find(self, x, y):
        pass
    def ceil(self, x):
        pass
    def floor(self, x):
        pass

class BinaryTree:
    pass
class BalanceTree:
    pass
class SegmentTree:
    pass

if __name__ == '__main__':
    uf = UF(10)
    trie = Trie(); trie.insert("apple");
    print(trie.searchsWith("app"))
    treeList = TreeList([1,3,5]);
    print(treeList.sumRange(0, 2))
    skipList = SkipList(); skipList.put(1);
    print(skipList.get(1))




