# Trie, Heap, Skiplist, BS, UF 
# LRU LFU(ListNode) B+Tree 
# Segment Tree 

import random
from typing import List
import collections


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

# skipList
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

class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Codec:
    def serialize(self, root):
        if not root:
            return 'None,'
        return str(root.val) + ',' + self.serialize(root.left) + self.serialize(root.right)

    def deserialize(self, data):
        def buildTree(vals):
            try: val = next(vals)
            except: return
            if val == 'null':
                return
            node = TreeNode(int(val))
            node.left = buildTree(vals)
            node.right = buildTree(vals)
            return node
        vals = iter(data.split(','))
        return buildTree(vals)

class BalanceTree:
    pass

# segmentTree
class Node:
    def __init__(self, startIndex, endIndex, val):
        self.start = startIndex
        self.end = endIndex
        self.val = val
        # lazy
        self.lazyVal = None
        self.left = None
        self.right = None
class SegmentTree:
    def __init__(self, data):
        self.data = data
        self.root = self._buildTree(0, len(self.data) - 1)
    def _buildTree(self, start, end):
        if start == end:
            return Node(start, end, self.data[start])
        root = Node(start, end, 0)
        mid = (start + end) >> 1
        root.left = self._buildTree(start, end)
        root.right = self._buildTree(mid + 1, end)
        root.val = max(root.left.val, root.right.val)
        return root
    def updateRange(self, i, j, val):
        self._updateRange(self.root, i, j, val)
    def _updateRange(self, root, i, j, val):
        start, end = root.start, root.end
        if i == start and j == end:
            root.val = val
            root.lazyVal = val
            return
        if root.lazyVal is not None:
            self._pushDown(root)
        mid = (start + end) // 2
        if j <= mid:
            self._updateRange(root.left, i, j, val)
        elif i >= mid + 1:
            self._updateRange(root.right, i, j, val)
        else:
            self._updateRange(root.left, i, mid, val)
            self._updateRange(root.right, mid + 1, val)
    def getRange(self, i, j):
        return self._getRange(self.root, i, j)
    def _getRange(self, root, i, j):
        start, end = root.start, root.end
        if i == start and j == end:
            return root.val
        if root.lazyVal is not None:
            self._pushDown(root)
        mid = (start + end) // 2
        if j <= mid:
            return self._getRange(root.left, i, j)
        if i >= mid + 1:
            return self._getRange(root.right, i, j)
        return max(self._getRange(root.left, i, mid), self._getRange(root.right, mid + 1, j))
    def _pushDown(self, root):
        if root.left:
            root.left.val = root.lazyVal
            root.left.lazyVal = root.lazyVal
        if root.right:
            root.right.val = root.lazyVal
            root.right.lazyVal = root.lazyVal
        root.lazyVal = None


class Node:
    def __init__(self, startIndex, endIndex, val):
        self.start = startIndex
        self.end = endIndex
        self.val = val
        # lazy更新法
        self.lazyVal = None
        self.left = None
        self.right = None

class MultiOverwriteSegmentTree:
    def __init__(self, data):
        self.data = data
        self.root = self._buildTree(0, len(self.data) - 1)

    def _buildTree(self, start, end):
        if start == end:
            return Node(start, end, self.data[start])

        root = Node(start, end, 0)
        mid = (start + end) // 2
        root.left = self._buildTree(start, mid)
        root.right = self._buildTree(mid + 1, end)
        root.val = max(root.left.val, root.right.val)
        return root

    def updateRange(self, i, j, val):
        self._updateRange(self.root, i, j, val)

    def _updateRange(self, root, i, j, val):
        start, end = root.start, root.end
        if i == start and j == end:
            root.val = val
            root.lazyVal = val
            return

        # 当node的lazyVal不为空的时候，需要将缓存的lazy值下推给子node
        if root.lazyVal is not None:
            self._pushDown(root)

        mid = (start + end) // 2
        if j <= mid:
            self._updateRange(root.left, i, j, val)
        elif i >= mid + 1:
            self._updateRange(root.right, i, j, val)
        else:
            self._updateRange(root.left, i, mid, val)
            self._updateRange(root.right, mid + 1, j, val)

    def getRange(self, i, j):
        return self._getRange(self.root, i, j)

    def _getRange(self, root, i, j):
        start, end = root.start, root.end
        if i == start and j == end:
            return root.val

        # 当node的lazyVal不为空的时候，需要将缓存的lazy值下推给子node
        if root.lazyVal is not None:
            self._pushDown(root)

        mid = (start + end) // 2
        if j <= mid:
            return self._getRange(root.left, i, j)
        if i >= mid + 1:
            return self._getRange(root.right, i, j)
        return max(self._getRange(root.left, i, mid), self._getRange(root.right, mid + 1, j))

    def _pushDown(self, root):
        if root.left:
            root.left.val = root.lazyVal
            root.left.lazyVal = root.lazyVal
        if root.right:
            root.right.val = root.lazyVal
            root.right.lazyVal = root.lazyVal
        root.lazyVal = None

if __name__ == '__main__':
    uf = UF(10)
    trie = Trie(); trie.insert("apple");
    print(trie.searchsWith("app"))

    treeList = TreeList([1,3,5]);
    print(treeList.sumRange(0, 2))

    skipList = SkipList(); skipList.put(1);
    print(skipList.get(1))

    segmentTree = MultiOverwriteSegmentTree([1,2,3,4,5]);
    print(segmentTree.getRange(0,0))

    ser = Codec(); deser = Codec()
    print(deser.deserialize("1,2,3,null,null,4,5").val)
    # print(deser.deserialize(ser.serialize()).deserialize( "1,2,3,null,null,4,5"))





