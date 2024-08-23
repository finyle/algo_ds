from typing import List, Optional
from collections import defaultdict, deque, Counter
import heapq
from bisect import bisect_left
import random
from functools import cache, reduce
from math import inf, comb

class ListNode:
    def __init__(self, x):
        self.val = x 
        self.next = None 
        
class TreeNode:
    def __init__(self, x):
        self.val = x 
        self.left = None 
        self.right = None 

class Solution:
    # hash 
    def twoSum_1(self, nums:List[int], target:int) -> List[int]:
        ht = dict()
        for i, num in enumerate(nums):
            if target - num in ht:
                return [ht[target - num], i]
            ht[num] = i 
        return []
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        ht_l = defaultdict(list)
        for st in strs:
            cnt = [0] * 26 
            for ch in st:
                cnt[ord(ch) - ord('a')] += 1
            ht_l[tuple(cnt)].append(st)
        return list(ht_l.values())
        # ht_l = defaultdict(list)
        # for st in strs:
        #     ht_l["".join(sorted(st))].append(st)
        # return list(ht_l.values())
    def longestConsecutive_128(self, nums:List[int]) -> int:
        streak = 0
        num_set = set(nums)
        for num in nums:
            if num - 1 not in num_set:
                current_num = num 
                current_streak = 1 
                while current_num + 1 in num_set:
                    current_num += 1
                    current_streak += 1
                streak = max(streak, current_streak)
        return streak
    
    # two pointer 
    def moveZeros_283(self, nums:List[int]) -> None:
        n = len(nums)
        left = right = 0 
        while right < n:
            if nums[right] != 0:
                nums[left], nums[right] = nums[right], nums[left]
                left += 1
            right += 1
        return nums 
    def maxAres_11(self, nums:List[int]) -> int:
        l, r = 0, len(nums) - 1
        ans = 0 
        while l < r:
            area = min(nums[l], nums[r]) * (r - l)
            ans = max(ans, area)
            if (nums[l] <= nums[r]): l += 1
            else: r -= 1
        return ans 
    def threeSum(self, nums:List[int]) -> List[List[int]]:
        n = len(nums)
        nums.sort()
        ans = list()
        for fisrt in range(n):
            if fisrt > 0 and nums[fisrt] == nums[fisrt - 1]: continue
            third = n - 1
            target = -nums[fisrt] 
            for second in range(fisrt + 1, n):
                if second > fisrt + 1 and nums[second] == nums[second - 1]: continue
                while second < third and nums[second] + nums[third] > target: third -= 1
                if second == third: break
                if nums[second] + nums[third] == target:
                    ans.append([nums[fisrt], nums[second], nums[third]])
        return ans 
    def trap(self, height:List[int]) -> int:
        ans = 0
        l, r = 0, len(height) - 1
        leftMax = rightMax = 0
        while l < r:
            leftMax = max(leftMax, height[l])
            rightMax = max(rightMax, height[r])
            if height[l] < height[r]:
                ans += leftMax - height[l]
                l += 1
            else:
                ans += rightMax - height[r]
                r -= 1
        return ans 
    
    # sliding window
    def lengthOfLongestSubstring(self, s: str) -> int:
        occ = set(); n = len(s)
        rk, ans = -1, 0
        for i in range(n):
            if i != 0:
                occ.remove(s[i - 1])
            while rk + 1 < n and s[rk + 1] not in occ:
                occ.add(s[rk + 1])
                rk += 1
            ans = max(ans, rk - i + 1)
        return ans 
    def findAnagrams(self, s: str, p:str) -> List[int]:
        s_len, p_len = len(s), len(p)
        if s_len < p_len: return []
        ans = []
        s_cnt = [0] * 26
        p_cnt = [0] * 26
        for i in range(p_len):
            s_cnt[ord(s[i]) - 97] += 1
            p_cnt[ord(p[i]) - 97] += 1
        if s_cnt == p_cnt: ans.append(0)
        for i in range(s_len - p_len):
            s_cnt[ord(s[i]) - 97] -= 1
            s_cnt[ord(s[i + p_len]) - 97] += 1
            if s_cnt == p_cnt:
                ans.append(i + 1)
        return ans 

    # subArray 
    def subarraySum(self,nums:List[int], k:int):
        ans = s = 0
        cnt = defaultdict(int)
        cnt[0] = 1
        for x in nums:
            s += x 
            ans += cnt[s - k]
            cnt[s] += 1
        return ans

    def maxSlidingWindow(self, nums:List[int], k:int):
        n = len(nums)
        q = [(-nums[i], i) for i in range(k)]
        heapq.heapify(q)
        ans = [-q[0][0]]
        for i in range(k, n):
            heapq.heappush(q, (-nums[i], i))
            while q[0][1] <= i - k:
                heapq.heappop(q)
            ans.append(-q[0][0])
        return ans 
    
    def maxSlidingWindow_(self, nums:List[int], k:int):
        n = len(nums)
        q = deque()
        for i in range(k):
            while q and nums[i] >= nums[q[-1]]:
                q.pop()
            q.append(i)

        ans = [nums[q[0]]]
        for i in range(k, n):
            while q and nums[i] >= nums[q[-1]]:
                q.pop()
            q.append(i)
            while q[0] <= i - k:
                q.popleft()
            ans.append(nums[q[0]])
        return ans
    def maxSlidingWindow__(self, nums:List[int], k:int):
        n = len(nums)
        prefixMax, suffixMax = [0] * n, [0] * n
        for i in range(n):
            if i % k == 0:
                prefixMax[i] = nums[i]
            else:
                prefixMax[i] = max(prefixMax[i - 1], nums[i])
        for i in range(n - 1, -1, -1):
            if i == n - 1 or (i + 1) % k == 0:
                suffixMax[i] = nums[i]
            else:
                suffixMax[i] = max(suffixMax[i + 1], nums[i])

        ans = [max(suffixMax[i], prefixMax[i + k - 1]) for i in range(n - k + 1)]
        return ans

    def minWindow(self, s:str, t:str):
        ans_left, ans_right = -1, len(s)
        left = 0
        cnt_s = Counter()
        cnt_t = Counter(t)
        for right, c in enumerate(s):
            cnt_s[c] += 1
            while cnt_s >= cnt_t:
                if right - left < ans_right - ans_left:
                    ans_left, ans_right = left, right
                cnt_s[s[left]] -= 1
                left += 1
        return "" if ans_left < 0 else s[ans_left: ans_right + 1]
    
    # array
    def maxSubArray(self, nums: List[int]) -> int:
        pre = 0
        maxAns = nums[0]
        for i in nums:
            pre = max(pre + i, i)
            maxAns = max(maxAns, pre)
        return maxAns
    def merge(self, intervals:List[List[int]]) -> List[List[int]]:
        intervals.sort(key = lambda x: x[0])
        merged = []
        for interval in intervals:
            if not merged or merged[-1][1] < interval[0]:
                merged.append(interval)
            else:
                merged[-1][1] = max(merged[-1][1], interval[1])
        return merged
    def rorate(self, nums:List[int], k:int)-> List[int]:
        def reverse(i:int, j:int) -> None:
            while i < j:
                nums[i], nums[j] = nums[j], nums[i]
                i += 1
                j -= 1
        n = len(nums)
        k %= n 
        reverse(0, n - 1)
        reverse(0, k - 1)
        reverse(k, n - 1)
        return nums
    def productExceptSelf(self, nums: List[int]) -> int:
        n = len(nums)
        ans = [0] * n 
        ans[0] = 1 
        for i in range(1, n):
            ans[i] = nums[i - 1] * ans[i - 1]
        R = 1
        for i in reversed(range(n)):
            ans[i] = ans[i] * R 
            R *= nums[i]
        return ans 
    def firstMissingPositive(self, nums: List[int]) -> int:
        n = len(nums)
        for i in range(n):
            if nums[i] <= 0: nums[i] = n + 1 
        for i in range(n):
            num = abs(nums[i])
            if num <= n: nums[num - 1] = -abs(nums[num - 1])
        for i in range(n):
            if nums[i] > 0: return i + 1 
        return n + 1 
    
    # matrix
    def setZero(self, matrix: List[List[int]]) -> None:
        m, n = len(matrix), len(matrix[0])
        flag_col0 = False 
        for i in range(m):
            if matrix[i][0] == 0: 
                flag_col0 = True
            for j in range(1, n):
                if matrix[i][j] == 0: 
                    matrix[i][0] = matrix[0][j] = 0
        for i in range(m - 1, -1, -1):
            for j in range(1, n):
                if matrix[i][0] == 0 or matrix[0][j] == 0: 
                    matrix[i][j] = 0 
            if flag_col0: 
                matrix[i][0] = 0
        return matrix
    
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        if not matrix or not matrix[0]:
            return list()
        rows, columns = len(matrix), len(matrix[0])
        visited = [[False] * columns for _ in range(rows)]
        total = rows * columns
        order = [0] * total
        directions = [[0, 1], [1, 0], [0, -1], [-1, 0]]
        row, column = 0, 0
        directionIndex = 0
        for i in range(total):
            order[i] = matrix[row][column]
            visited[row][column] = True
            nextRow, nextColumn = row + directions[directionIndex][0], column + directions[directionIndex][1]
            if not (0 <= nextRow < rows and 0 <= nextColumn < columns and not visited[nextRow][nextColumn]):
                directionIndex = (directionIndex + 1) % 4
            row += directions[directionIndex][0]
            column += directions[directionIndex][1]
        return order
    
    def rotate_48(self, matrix:List[List[int]]) -> None:
        n = len(matrix)
        for i in range(n // 2):
            for j in range((n + 1) // 2):
                matrix[i][j], matrix[n - j - 1][i], matrix[n - i - 1][n - j - 1], matrix[j][n - i - 1] \
                    = matrix[n - j - 1][i], matrix[n - i - 1][n - j - 1], matrix[j][n - i - 1], matrix[i][j]
        return matrix 

    def searchMatrix(self, matrix:List[List[int]], target:int) -> bool:
        m, n = len(matrix), len(matrix[0])
        x, y = 0, n - 1 
        while x < m and y >= 0:
            if matrix[x][y] == target: return True 
            if matrix[x][y] > target:
                y -= 1
            else: x += 1 
        return False 
    
    # graph
    def numsIslands(self, grid:List[List[str]]) -> int:
        def dfs(grid, r, c):
            grid[r][c] = 0
            nr, nc = len(grid), len(grid[0])
            for x, y in [(r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)]:
                if 0 <= x < nr and 0 <= y < nc and grid[x][y] == "1":
                    dfs(grid, x, y)
        nr, nc = len(grid), len(grid[0])
        if nr == 0: return 0
        num_islands = 0 
        for r in range(nr):
            for c in range(nc):
                if grid[r][c] == "1":
                    num_islands += 1 
                    dfs(grid, r, c)
        return num_islands
        
    def numsIslands_(self, grid:List[List[str]]) -> int:
        nr, nc = len(grid), len(grid[0])
        if nr == 0: return 0 
        num_islands = 0 
        for r in range(nr):
            for c in range(nc):
                if grid[r][c] == "1":
                    num_islands += 1
                    grid[r][c] = "0"
                    neighbors = deque([(r, c)])
                    while neighbors:
                        r, c = neighbors.popleft()
                        for x, y in [(r - 1, c), (r, c - 1), (r, c + 1), (r + 1, c)]:
                            if 0 <= x < nr and 0 <= y < nc and grid[x][y] == "1":
                                neighbors.append((x, y))
                                grid[x][y] = "0"
        return num_islands
    
    def orangesRotting(self, grid:List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        fresh = 0
        q = []
        for i, row in enumerate(grid):
            for j, x in enumerate(row):
                if x == 1:
                    fresh += 1  # 统计新鲜橘子个数
                elif x == 2:
                    q.append((i, j))  # 一开始就腐烂的橘子
        ans = -1
        while q:
            ans += 1  # 经过一分钟
            tmp = q
            q = []
            for x, y in tmp:  # 已经腐烂的橘子
                for i, j in (x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1):  # 四方向
                    if 0 <= i < m and 0 <= j < n and grid[i][j] == 1:  # 新鲜橘子
                        fresh -= 1
                        grid[i][j] = 2  # 变成腐烂橘子
                        q.append((i, j))
        return -1 if fresh else max(ans, 0)

    def canFinish(self, numCourses: int, prerequisites:List[List[int]]) -> bool:
        edges = defaultdict(list)
        visited = [0] * numCourses
        result = list()
        valid = True
        for info in prerequisites:
            edges[info[1]].append(info[0])
        def dfs(u: int):
            nonlocal valid
            visited[u] = 1
            for v in edges[u]:
                if visited[v] == 0:
                    dfs(v)
                    if not valid:
                        return
                elif visited[v] == 1:
                    valid = False
                    return
            visited[u] = 2
            result.append(u)
        for i in range(numCourses):
            if valid and not visited[i]:
                dfs(i)
        return valid

    def canFinish_(self, numCourses:int, prerequisites:List[List[int]]) -> bool:
        edges = defaultdict(list)
        indeg = [0] * numCourses

        for info in prerequisites:
            edges[info[1]].append(info[0])
            indeg[info[0]] += 1
        
        q = deque([u for u in range(numCourses) if indeg[u] == 0])
        visited = 0

        while q:
            visited += 1
            u = q.popleft()
            for v in edges[u]:
                indeg[v] -= 1
                if indeg[v] == 0:
                    q.append(v)

        return visited == numCourses
    
    class Trie:
        def __init__(self):
            self.children = [None] * 26
            self.isEnd = False
        
        def searchPrefix(self, prefix: str) -> "Trie":
            node = self
            for ch in prefix:
                ch = ord(ch) - ord("a")
                if not node.children[ch]:
                    return None
                node = node.children[ch]
            return node

        def insert(self, word: str) -> None:
            node = self
            for ch in word:
                ch = ord(ch) - ord("a")
                if not node.children[ch]:
                    node.children[ch] = Trie()
                node = node.children[ch]
            node.isEnd = True

        def search(self, word: str) -> bool:
            node = self.searchPrefix(word)
            return node is not None and node.isEnd

        def startsWith(self, prefix: str) -> bool:
            return self.searchPrefix(prefix) is not None
    
    # divide 
    def permute(self, nums:List[int]) -> List[List[int]]:
        n = len(nums)
        ans = []
        path = [0] * n 
        on_path = [False] * n 
        def dfs(i:int) -> None:
            if i == n:
                ans.append(path.copy())
                return 
            for j, on in enumerate(on_path):
                if not on:
                    path[i] = nums[j]
                    on_path[j] = True 
                    dfs(i + 1)
                    on_path[j] = False 
        dfs(0)
        return ans 
    
    def subsets(self, nums:List[int]) -> List[List[int]]:
        ans = []
        path = []
        n = len(nums)
        def dfs(i:int) -> None:
            if i == n:
                ans.append(path.copy())
                return 
            dfs(i + 1)
            path.append(nums[i])
            dfs(i + 1)
            path.pop()
        dfs(0)
        return ans 
    
    def letterCombinations(self, digits:str) -> List[str]:
        MAPPING = "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
        n = len(digits)
        if n == 0: return []
        ans = []
        path = [''] * n 
        def dfs(i:int) -> None:
            if i == n:
                ans.append("".join(path))
                return 
            for c in MAPPING[int(digits[i])]:
                path[i] = c 
                dfs(i + 1)
        dfs(0)
        return ans 
    
    def combinationSum(self, candidates:List[int], target:int) -> List[List[int]]:
        ans = []
        path = []
        def dfs(i:int, left:int) -> None:
            if left == 0: 
                ans.append(path.copy())
                return 
            if i == len(candidates) or left < 0:
                return 
            dfs(i + 1, left)
            path.append(candidates[i])
            dfs(i, left - candidates[i])
            path.pop()
        dfs(0, target)
        return ans 
    
    def generateParentthesis(self, n:int) -> List[str]:
        m = n * 2 
        ans = []
        path = [''] * m 
        def dfs(i:int, open:int) -> None:
            if i == m:
                ans.append("".join(path))
                return
            if open < n:
                path[i] = '('
                dfs(i + 1, open + 1)
            if i - open < open:
                path[i] = ')'
                dfs(i + 1, open)
        dfs(0, 0)
        return ans 
    
    def exist(self, board:List[List[str]], word:str) -> bool:
        directions = [(0, 1), (0, -1), (1, 0), (1, 0)]
        def check(i:int, j:int, k:int) -> bool:
            if board[i][j] != word[k]: return False 
            if k == len(word) - 1: return True 
            visited.add((i, j))
            res = False 
            for di, dj in directions:
                ni, nj = i + di, j + dj 
                if 0 <= ni < len(board) and 0 <= nj < len(board[0]):
                    if (ni, nj) not in visited:
                        if check(ni, nj, k + 1):
                            res = True 
                            break 
            visited.remove((i, j))
            return res 
        h, w = len(board), len(board[0])
        visited = set()
        for i in range(h):
            for j in range(w):
                if check(i, j, 0):
                    return True 
        return False 

    def partitions(self, s:str) -> List[List[str]]:
        ans = []
        path = []
        n = len(s)
        # start 表示当前这段回文子串的开始位置
        def dfs(i: int, start: int) -> None:
            if i == n:
                ans.append(path.copy())  # 复制 path
                return
            # 不选 i 和 i+1 之间的逗号（i=n-1 时一定要选）
            if i < n - 1:
                dfs(i + 1, start)
            # 选 i 和 i+1 之间的逗号（把 s[i] 作为子串的最后一个字符）
            t = s[start: i + 1]
            if t == t[::-1]:  # 判断是否回文
                path.append(t)
                dfs(i + 1, i + 1)  # 下一个子串从 i+1 开始
                path.pop()  # 恢复现场
        dfs(0, 0)
        return ans
    
    def partition_(self, s: str) -> List[List[str]]:
        ans = []
        path = []
        n = len(s)
        def dfs(i: int) -> None:
            if i == n:
                ans.append(path.copy())  # 复制 path
                return
            for j in range(i, n):  # 枚举子串的结束位置
                t = s[i: j + 1]
                if t == t[::-1]:  # 判断是否回文
                    path.append(t)
                    dfs(j + 1)
                    path.pop()  # 恢复现场
        dfs(0)
        return ans

    def solveNQueues(self, n:int) -> List[List[str]]:
        m = n * 2 - 1
        ans = []
        col = [0] * n
        on_path, diag1, diag2 = [False] * n, [False] * m, [False] * m
        def dfs(r: int) -> None:
            if r == n:
                ans.append(['.' * c + 'Q' + '.' * (n - 1 - c) for c in col])
                return
            for c, on in enumerate(on_path):
                if not on and not diag1[r + c] and not diag2[r - c]:
                    col[r] = c
                    on_path[c] = diag1[r + c] = diag2[r - c] = True
                    dfs(r + 1)
                    on_path[c] = diag1[r + c] = diag2[r - c] = False  # 恢复现场
        dfs(0)
        return ans

    # bisect 
    def searchInsert(self, nums: List[int], target: int) -> int: 
        left, right = 0, len(nums) - 1 
        while left <= right:
            mid = (left + right) >> 1
            if nums[mid] < target:
                left = mid + 1 
            else:
                right = mid - 1 
        return left 

    def searchMatrix(self, matrix:List[List[int]], target:int) -> bool:
        m, n = len(matrix), len(matrix[0])
        l, r = -1, m * n 
        while l + 1 < r:
            mid = (l + r) >> 1 
            x = matrix[mid // n][mid % n]
            if x == target: return True 
            if x < target: l = mid 
            else: r = mid 
        return False 
    
    def searchRange(self, nums:List[int], target: int) -> List[int]:
        start = bisect_left(nums, target)
        if start == len(nums) or nums[start] != target:
            return [-1, -1]
        end = bisect_left(nums, target + 1) - 1 
        return [start, end]
    
    def searchRorate(self, nums: List[int], target: int) -> int:
        def is_blue(i:int) -> bool:
            end = nums[-1]
            if nums[i] > end:
                return target > end and nums[i] >= target 
            else:
                return target > end or nums[-1] >= target 
        ans = bisect_left(nums, target)
        return ans if nums[ans] == target else -1 

    def findMin(self, nums:List[int]) -> int:
        left, right = -1, len(nums) - 1  # 开区间 (-1, n-1)
        while left + 1 < right:  # 开区间不为空
            mid = (left + right) // 2
            if nums[mid] < nums[-1]:  # 蓝色
                right = mid
            else:  # 红色
                left = mid
        return nums[right]

    def findMedianSortedArrays(self, nums1:List[int], nums2:List[int]) -> float:
        def getKthElement(k):
            index1, index2 = 0, 0
            while True:
                # 特殊情况
                if index1 == m:
                    return nums2[index2 + k - 1]
                if index2 == n:
                    return nums1[index1 + k - 1]
                if k == 1:
                    return min(nums1[index1], nums2[index2])

                # 正常情况
                newIndex1 = min(index1 + k // 2 - 1, m - 1)
                newIndex2 = min(index2 + k // 2 - 1, n - 1)
                pivot1, pivot2 = nums1[newIndex1], nums2[newIndex2]
                if pivot1 <= pivot2:
                    k -= newIndex1 - index1 + 1
                    index1 = newIndex1 + 1
                else:
                    k -= newIndex2 - index2 + 1
                    index2 = newIndex2 + 1
        m, n = len(nums1), len(nums2)
        totalLength = m + n
        if totalLength % 2 == 1:
            return getKthElement((totalLength + 1) // 2)
        else:
            return (getKthElement(totalLength // 2) + getKthElement(totalLength // 2 + 1)) / 2

    # stack 
    def isValid(self, s:str) -> bool:
        if len(s) % 2 == 1: return False 
        pairs = {")":"(", "]":"[", "}":"{"}
        st = list()
        for ch in s:
            if ch in pairs:
                if not st or st[-1] != pairs[ch]:
                    return False 
                st.pop()
            else:
                st.append(ch)
        return not st 
    class MinStack:
        def __init__(self):
            self.stack = []
            self.min_stack = [math.inf]

        def push(self, x: int) -> None:
            self.stack.append(x)
            self.min_stack.append(min(x, self.min_stack[-1]))

        def pop(self) -> None:
            self.stack.pop()
            self.min_stack.pop()

        def top(self) -> int:
            return self.stack[-1]

        def getMin(self) -> int:
            return self.min_stack[-1]
        
    def decodeString(self, s: str) -> str:
        stack, res, multi = [], "", 0
        for c in s:
            if c == '[':
                stack.append([multi, res])
                res, multi = "", 0
            elif c == ']':
                cur_multi, last_res = stack.pop()
                res = last_res + cur_multi * res
            elif '0' <= c <= '9':
                multi = multi * 10 + int(c)            
            else:
                res += c
        return res
    
    def dailyTemperatures(self, temperatures:List[int]) -> List[int]:
        n = len(temperatures)
        ans = [0] * n 
        st = []
        for i in range(n - 1, -1, -1):
            t = temperatures[i]
            while st and t >= temperatures[st[-1]]:
                st.pop()
            if st:
                ans[i] = st[-1] - i 
            st.append(i)
        return ans 
    
    def largestRectangleArea(self, heights:List[int]) -> int:
        n = len(heights)
        left = [-1] * n 
        st = []
        for i, x in enumerate(heights):
            while st and x <= heights[st[-1]]:
                st.pop()
            if st:
                left[i] = st[-1]
            st.append(i)
        right = [n] * n 
        st.clear()
        for i in range(n - 1, -1, -1):
            x = heights[i]
            while st and x <= heights[st[-1]]:
                st.pop()
            if st:
                right[i] = st[-1]
            st.append(i)
        ans = 0 
        for h, l, r in zip(heights, left, right):
            ans = max(ans, h * (r - l - 1))
        return ans 

    # queue
    def findKthLargest(self, nums:List[int], k:int) -> int:
        def quick_select(nums, k):
            pivot = random.choice(nums)
            big, equal, small = [], [], []
            for num in nums:
                if num > pivot:
                    big.append(num)
                elif num < pivot:
                    small.append(num)
                else:
                    equal.append(num)
            if k <= len(big):
                return quick_select(big, k)
            if len(nums) - len(small) < k:
                return quick_select(small, k - len(nums) + len(small))
            return pivot 
        return quick_select(nums, k)
    
    def findKthLargest_(self, nums:List[int], k:int) -> int:
        heap = []
        for num in nums:
            heapq.heappush(heap, num)
            if len(heap) > k:
                heapq.heappop(heap)
        return heap[0]
    
    def topKFrequent(self, nums:List[int], k:int) -> List[int]:
        cnt = Counter(nums)
        heap = []
        for key, val in cnt.items():
            if len(heap) < k:
                heapq.heappush(heap, (val, key))
            else:
                if val > heap[0][0]:
                    heapq.heappop(heap)
                    heapq.heappush(heap, (val, key))
        return [key for val, key in heap]

    class MedianFinder:

        def __init__(self):
            self.queMin = list()
            self.queMax = list()

        def addNum(self, num: int) -> None:
            queMin_ = self.queMin
            queMax_ = self.queMax

            if not queMin_ or num <= -queMin_[0]:
                heapq.heappush(queMin_, -num)
                if len(queMax_) + 1 < len(queMin_):
                    heapq.heappush(queMax_, -heapq.heappop(queMin_))
            else:
                heapq.heappush(queMax_, num)
                if len(queMax_) > len(queMin_):
                    heapq.heappush(queMin_, -heapq.heappop(queMax_))
            
        def findMedian(self) -> float:
            queMin_ = self.queMin
            queMax_ = self.queMax

            if len(queMin_) > len(queMax_):
                return -queMin_[0]
            return (-queMin_[0] + queMax_[0]) / 2

    # greedy
    def maxProfix(self, prices:List[int]) -> int:
        ans = 0
        min_price = prices[0]
        for p in prices:
            ans = max(ans, p - min_price)
            min_price = min(min_price, p)
        return ans 
    
    def canJump(self, nums:List[int]) -> bool:
        mx = 0 
        for i, jump in enumerate(nums):
            if i > mx: return False 
            mx = max(mx, i + jump)
        return True 

    def canJump_(self, nums:List[int]) -> int:
        end, max_pos = 0, 0 
        steps = 0 
        for i in range(len(nums) - 1):
            max_pos = max(max_pos, nums[i] + i)
            if i == end:
                end = max_pos 
                steps += 1 
        return steps 
    
    def partitionLabels(self, s: str) -> List[int]:
        last = {c: i for i, c in enumerate(s)}
        ans = []
        start = end = 0 
        for i, c in enumerate(s):
            end = max(end, last[c])
            if end == i:
                ans.append(end - start + 1)
                start = i + 1 
        return ans 
    
    # dp
    def climbStairs(self, n:int) -> int:
        @cache 
        def dfs(i:int) -> int:
            if i <= 1: return 1 
            return dfs(i - 1) + dfs(i - 2)
        return dfs(n)
    def climbStairs_(self, n:int) -> int:
        f0 = f1 = 1 
        for _ in range(2, n + 1):
            f0, f1 = f1, f1 + f0 
        return f1 
    
    def generate_118(self, numRows) -> List[List[int]]:
        c = [[1] * (i + 1) for i in range(numRows)]
        for i in range(2, numRows):
            for j in range(1, i):
                c[i][j] = c[i - 1][j - 1] + c[i - 1][j]
        return c 

    def rob(self, nums:List[List[int]]) -> int:
        @cache
        def dfs(i:int) -> int:
            if i < 0: return 0 
            return max(dfs(i - 1), dfs(i - 2) + nums[i])
        return dfs(len(nums) - 1)
    def rob_(self, nums:List[int]) -> int:
        f0 = f1 = 0 
        for x in nums:
            f0, f1 = f1, max(f1, f0 + x)
        return f1 
    
    def numsSquares(self, n:int) -> int: 
        def gen_coins(n):
            coins = []
            for i in range(1, 101):
                if i * i <= n: coins.append(i * i)
                else: break 
            return coins 
        amount = n 
        coins = gen_coins(n)
        n = len(coins)
        f = [[inf] * (amount + 1) for _ in range(n + 1)]
        f[0][0] = 0 
        for i, x in enumerate(coins):
            for c in range(amount + 1):
                if c < x:
                    f[i + 1][c] = f[i][c]
                else:
                    f[i + 1][c] = min(f[i][c], f[i + 1][c - x] + 1)
        ans = f[n][amount]
        return ans if ans < inf else -1 

    def coinChange(self, coins:List[int], amount:int) -> int:
        @cache
        def dfs(i:int, c:int) -> int:
            if i < 0: return 0 if c == 0 else inf 
            if c < coins[i]: return dfs(i - 1, c)
            return min(dfs(i - 1, c), dfs(i, c - coins[i]) + 1)
        ans = dfs(len(coins) - 1, amount) 
        return ans if ans < inf else -1 
    def coinChange_(self, coins:List[int], amount:int) -> int:
        f = [0] + [inf] * amount 
        for x in coins:
            for c in range(x, amount + 1):
                f[c] = min(f[c], f[c - x] + 1)
        ans = f[amount]
        return ans if ans < inf else -1 
    
    def wordBreak(self, s:str, wordDict:List[str]) -> bool:
        @cache
        def dfs(s):
            if not s: return True 
            res = False 
            for i in range(1, len(s) + 1):
                if s[:i] in wordDict:
                    res = dfs(s[i:]) or res 
            return res 
        return dfs(s)

    def wordBreak_(self, s:str, wordDict:List[str]) -> bool:
        n = len(s)
        dp = [False] * (n + 1)
        dp[0] = True 
        for i in range(n):
            for j in range(i + 1, n + 1):
                if dp[i] and s[i:j] in wordDict:
                    dp[j] = True 
        return dp[-1]
    
    def lengthOfLIS(self, nums:List[int]) -> int:
        @cache
        def dfs(i:int) -> int:
            res = 0 
            for j in range(i):
                if nums[j] < nums[i]:
                    res = max(res, dfs(j))
            return res + 1
        return max(dfs(i) for i in range(len(nums)))
    
    def lengthOfLIS_(self, nums:List[int]) -> int:
        f = [0] * len(nums)
        for i, x in enumerate(nums):
            for j, y in enumerate(nums[:i]):
                if x > y:
                    f[i] = max(f[i], f[j])
            f[i] += 1 
        return max(f)
    def lengthOfLIS__(self, nums:List[int]) -> int:
        ng = 0 
        for x in nums:
            j = bisect_left(nums, x, 0, ng)
            nums[j] = x 
            if j == ng: ng += 1 
        return ng 
    
    def maxProduct(self, nums:List[int]) -> int:
        maxF = nums[0]
        minF = nums[0]
        ans = nums[0]
        for i in range(1, len(nums)):
            mx = maxF
            mn = minF 
            maxF = max(mx * nums[i], max(nums[i], mn * nums[i]))
            minF = max(mn * nums[i], min(nums[i], mx * nums[i]))
            ans = max(maxF, ans)
        return ans 
    
    def canPartition(self, nums:List[int]) -> bool:
        @cache 
        def dfs(i:int, j:int) -> bool:
            if i < 0: return j == 0 
            return j >= nums[i] and dfs(i - 1, j - nums[i]) or dfs(i - 1, j)
        s = sum(nums)
        return s % 2 == 0 and dfs(len(nums) - 1, s // 2)
    
    def canPartition_(self, nums:List[int]) -> bool:
        s = sum(nums)
        if s % 2: return False 
        s //= 2 
        f = [True] + [False] * s 
        s2 = 0 
        for i, x in enumerate(nums):
            s2 = min(s2 + x, s)
            for j in range(s2, x - 1, -1):
                f[j] = f[j] or f[j - x]
        return f[j]
    
    def longestValidParentheses(self, s:str) -> int:
        ans = 0
        n = len(s)
        dp = [0] * n 
        for i in range(n):
            if s[i] == ')':
                if s[i - 1] == '(':
                    dp[i] = dp[i - 2] if i >= 2 else 0 + 2 
                elif i - dp[i - 1] > 0 and s[i - dp[i - 1] - 1] == '(':
                    dp[i] = dp[i - 1] + dp[i - dp[i - 1] - 2] if ((i - dp[i - 1]) >= 2 ) else 0 + 2
            ans = max(ans, dp[i])
        return ans 
    
    def longestValidParentheses_(self, s:str) -> int:
        a=[-1]
        ans=0
        for i in range(len(s)):
            if s[i]=='(':
                a.append(i)
            else:
                a.pop()
                if not a:
                    a.append(i)
                else:
                    ans=max(ans,i-a[-1])
        return ans

    # multi dp 
    def uniquePaths(self, m:int, n:int) -> int:
        dp = [1] * n 
        for i in range(1, m):
            for j in range(1, n):
                dp[j] += dp[j - 1]
        return dp[n - 1]
    
    def uniquePaths(self, m:int, n:int) -> int:
        return comb(m + n - 2, n - 1)
    
    def minPathSum(self, grid:List[List[int]]) -> int:
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if i == j == 0: continue
                elif i == 0:  grid[i][j] = grid[i][j - 1] + grid[i][j]
                elif j == 0:  grid[i][j] = grid[i - 1][j] + grid[i][j]
                else: grid[i][j] = min(grid[i - 1][j], grid[i][j - 1]) + grid[i][j]
        return grid[-1][-1]

    def longestPalindrome(self, s:str) -> str:
        n = len(s)
        if n < 2:
            return s
        max_len = 1
        begin = 0
        # dp[i][j] 表示 s[i..j] 是否是回文串
        dp = [[False] * n for _ in range(n)]
        for i in range(n):
            dp[i][i] = True
        # 递推开始
        # 先枚举子串长度
        for L in range(2, n + 1):
            # 枚举左边界，左边界的上限设置可以宽松一些
            for i in range(n):
                # 由 L 和 i 可以确定右边界，即 j - i + 1 = L 得
                j = L + i - 1
                # 如果右边界越界，就可以退出当前循环
                if j >= n:
                    break                   
                if s[i] != s[j]:
                    dp[i][j] = False 
                else:
                    if j - i < 3:
                        dp[i][j] = True
                    else:
                        dp[i][j] = dp[i + 1][j - 1]
                # 只要 dp[i][L] == true 成立，就表示子串 s[i..L] 是回文，此时记录回文长度和起始位置
                if dp[i][j] and j - i + 1 > max_len:
                    max_len = j - i + 1
                    begin = i
        return s[begin:begin + max_len]

    def longestCommonSubsequence(self, s:str, t:str) -> int:
        m, n = len(s), len(t)
        @cache
        def dfs(i, j):
            if i < 0 or j < 0: return 0 
            if s[i] == t[j]: return dfs(i - 1, j - 1) + 1
            return max(dfs(i - 1, j), dfs(i, j - 1))
        return dfs(m - 1, n - 1)
    
    def longestCommonSubsequence_(self, s: str, t: str) -> int:
        f = [0] * (len(t) + 1)
        for x in s:
            pre = 0  # f[0]
            for j, y in enumerate(t):
                tmp = f[j + 1]
                f[j + 1] = pre + 1 if x == y else max(f[j + 1], f[j])
                pre = tmp
        return f[-1]
    
    def minDistance(self, word1:str, word2:str) -> int:
        m, n = len(word1), len(word2)
        @cache
        def dfs(i, j):
            if i < 0: return j + 1 
            if j < 0: return i + 1 
            if word1[i] == word2[j]: return dfs(i - 1, j - 1)
            return min(dfs(i - 1, j), dfs(i, j - 1), dfs(i - 1, j - 1)) + 1
        return dfs(m - 1, n - 1)

    def minDistance_(self, word1:str, word2:str) -> int:
        f = list(range(len(t) + 1))
        for x in s:
            pre = f[0]
            f[0] += 1
            for j, y in enumerate(t):
                tmp = f[j + 1]
                f[j + 1] = pre if x == y else min(f[j + 1], f[j], pre) + 1
                pre = tmp
        return f[-1]

    # bit 
    def singleNumber(self, nums:List[int]) -> int:
        return reduce(lambda x, y: x ^ y, nums)
    
    def majorityElement(self, nums:List[int]) -> int:
        cnt = Counter(nums)
        return max(cnt.keys(), key = cnt.get)
    
    def sortColors(self, nums:List[int]) -> None:
        n = len(nums)
        p0, p2 = 0, n - 1
        i = 0
        while i <= p2:
            while i <= p2 and nums[i] == 2:
                nums[i], nums[p2] = nums[p2], nums[i]
                p2 -= 1
            if nums[i] == 0:
                nums[i], nums[p0] = nums[p0], nums[i]
                p0 += 1
            i += 1
        return nums 
    def nextPermutations(self, nums:List[int]) -> List[int]:
        i = len(nums) - 2
        while i >= 0 and nums[i] >= nums[i + 1]:
            i -= 1
        if i >= 0:
            j = len(nums) - 1
            while j >= 0 and nums[i] >= nums[j]:
                j -= 1
            nums[i], nums[j] = nums[j], nums[i]
        
        left, right = i + 1, len(nums) - 1
        while left < right:
            nums[left], nums[right] = nums[right], nums[left]
            left += 1
            right -= 1
        return nums 
    def findDuplicate(self, nums:List[int]) -> int:
        n = len(nums)
        l, r = 1, n - 1
        ans = -1 
        while l <= r:
            mid = (l + r) >> 1
            cnt = sum(1 for num in nums if num <= mid)
            if cnt <= mid:
                l = mid + 1 
            else:
                r = mid - 1 
                ans = mid 
        return ans 

    # listnode 
    def getIntersectionNode(self, headA:ListNode, headB:ListNode) -> Optional[ListNode]:
        a, b = headA, headB
        while a != b:
            a = a.next if a else headB
            b = b.next if b else headA
        return a

    def reverseList(self, head:Optional[ListNode]) -> Optional[ListNode]:
        pre = None 
        cur = head 
        while cur:
            nxt = cur.next 
            cur.next = pre 
            pre = cur 
            cur = nxt 
        return pre 

    # treenode 
    def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        def dfs(cur):
            if not cur: return 
            res.append(cur.val)
            dfs(cur.left)
            dfs(cur.right)
        res = []
        dfs(root)
        return res    


if __name__ == "__main__":
    s = Solution()
    nums = [1,3,4,5]; target = 4
    print(s.twoSum_1(nums, target))
    strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
    print(s.groupAnagrams(strs))
    nums_128 = [100,4,200,1,3,2]
    print(s.longestConsecutive_128(nums_128))
    nums_283 = [0,1,0,3,12]
    print(s.moveZeros_283(nums_283))
    nums_11 = [1,8,6,2,5,4,8,3,7]
    print(s.maxAres_11(nums_11))
    nums_15 = [-1,0,1,2,-1,-4]
    print(s.threeSum(nums_15))
    height = [0,1,0,2,1,0,1,3,2,1,2,1]
    print(s.trap(height))
    s_3 = "abcabcbb"
    print(s.lengthOfLongestSubstring(s_3))
    s_438 = "cbaebabacd"; p_438 = "abc"
    print(s.findAnagrams(s_438, p_438))
    nums_560 = [1,1,1]; k_560 = 2
    print(s.subarraySum(nums_560, k_560))
    nums_239 = [1,3,-1,-3,5,3,6,7]; k_239 = 3
    print(s.maxSlidingWindow(nums_239, k_239))
    print(s.maxSlidingWindow_(nums_239, k_239))
    s_76 = "ADOBECODEBANC"; t_76 = "ABC"
    print(s.minWindow(s_76, t_76))

    nums_53 = [-2,1,-3,4,-1,2,1,-5,4]
    print(s.maxSubArray(nums_53))

    intervals = [[1,3],[2,6],[8,10],[15,18]]
    print(s.merge(intervals))
    nums_189 = [1,2,3,4,5,6,7]; k_189 = 3
    print(s.rorate(nums_189, k_189))
    nums_238 = [1,2,3,4]
    print(s.productExceptSelf(nums_238))
    nums_41 = [3,4,-1,1]
    print(s.firstMissingPositive(nums_41))
    matrix_73 = [[1,1,1],[1,0,1],[1,1,1]]
    print(s.setZero(matrix_73))
    matrix_54 = [[1,2,3],[4,5,6],[7,8,9]]
    print(s.spiralOrder(matrix_54))
    matrix_48 = [[1,2,3],[4,5,6],[7,8,9]]
    print(s.rotate_48(matrix_48))
    matrix_240 = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]]; target_240 = 5
    print(s.searchMatrix(matrix_240, target_240))
    grid_200 = [["1","1","0","0","0"],["1","1","0","0","0"],["0","0","1","0","0"],["0","0","0","1","1"]]
    # print(s.numsIslands(grid_200))
    print(s.numsIslands_(grid_200))
    grid_994 = [[2,1,1],[1,1,0],[0,1,1]]
    print(s.orangesRotting(grid_994))

    numCourses = 2; prerequisites = [[1,0]]
    print(s.canFinish(numCourses, prerequisites))

    nums_46 = [1,2,3]
    print(s.permute(nums_46))
    print(s.subsets(nums_46))

    digits_17 = "23"
    print(s.letterCombinations(digits_17))

    candidates_39 = [2,3,6,7]; target_39 = 7
    print(s.combinationSum(candidates_39, target_39))

    n_22 = 4 
    print(s.generateParentthesis(n_22))

    board_79 = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]]; word_79 = "ABCCED"
    print(s.exist(board_79, word_79))

    s_131 = "aab"
    print(s.partitions(s_131))

    n_51 = 5
    print(s.solveNQueues(n_51))

    nums_35 = [1,3,5,6]; target_35 = 5
    print(s.searchInsert(nums_35, target_35))

    matrix_74 = [[1,3,5,7],[10,11,16,20],[23,30,34,60]]; target_74 = 3
    print(s.searchMatrix(matrix_74, target_74))

    nums_34 = [5,7,7,8,8,10]; target_34 = 8
    print(s.searchRange(nums_34, target_34))

    nums1_4 = [1,2]; nums2_4 = [3,4]
    print(s.findMedianSortedArrays(nums1_4, nums2_4))

    s_20 = "()[]{}"
    print(s.isValid(s_20))

    s_394 = "3[a]2[bc]"
    print(s.decodeString(s_394))

    temperatures_739 = [73,74,75,71,69,72,76,73]
    print(s.dailyTemperatures(temperatures_739))

    heights_84 = [2,1,5,6,2,3]
    print(s.largestRectangleArea(heights_84))

    nums_215 = [3,2,3,1,2,4,5,5,6]; k_215 = 4
    print(s.findKthLargest(nums_215, k_215))

    nums_347 = [1,1,1,2,2,3]; k_347 = 2
    print(s.topKFrequent(nums_347, k_347))

    prices_121 = [7,1,5,3,6,4]
    print(s.maxProfix(prices_121))

    s_763 = "ababcbacadefegdehijhklij"
    print(s.partitionLabels(s_763))

    n_70 = 45
    print(s.climbStairs(n_70))

    numRows_118 = 5
    print(s.generate_118(numRows_118))

    nums_198 = [2,7,9,3,1]
    print(s.rob(nums_198))

    n_279 = 13
    print(s.numsSquares(n_279))

    coins_322 = [1, 2, 5]; amount_322 = 11
    print(s.coinChange(coins_322, amount_322))

    s_139 = "leetcode"; wordDict_139 = ["leet", "code"]
    print(s.wordBreak(s_139, wordDict_139))

    nums_300 = [10,9,2,5,3,7,101,18]
    print(s.lengthOfLIS(nums_300))

    nums_152 = [2,3,-2,4]
    print(s.maxProduct(nums_152))

    nums_416 = [1,5,11,5]
    print(s.canPartition(nums_416))

    s_32 = ")()())"
    print(s.longestValidParentheses_(s_32))

    m_62 = 3; n_62 = 7
    print(s.uniquePaths(m_62, n_62))

    grid_64 = [[1,3,1],[1,5,1],[4,2,1]]
    print(s.minPathSum(grid_64))

    s_5 =  "babad"
    print(s.longestPalindrome(s_5))

    text1_1143 = "abcde"; text2_1143 = "ace" 
    print(s.longestCommonSubsequence(text1_1143, text2_1143))

    word1_72 = "horse"; word2_72 = "ros"
    print(s.minDistance(word1_72, word2_72))


    nums_136 = [4,1,2,1,2]
    print(s.singleNumber(nums_136))
    nums_169 = [3,2,3]
    print(s.majorityElement(nums_169))
    nums_75 = [2,0,2,1,1,0]
    print(s.sortColors(nums_75))
    nums_31 = [1,2,3]
    print(s.nextPermutations(nums_31))
    nums_287 = [1,3,4,2,2]
    print(s.findDuplicate(nums_287))

    # listnode 
    numsA = [4,1,8,4,5]; numsB = [5,6,1,8,4,5]
    def nums2listNode(nums):
        head = ListNode(nums[0])
        tmp = head 
        for i in nums[1:]: 
            tmp.next = ListNode(i)
            tmp = tmp.next
        return head

    def printVal(ld):
        while ld:
            print(ld.val)
            ld = ld.next 
    a = nums2listNode(numsA)
    b = nums2listNode(numsB)
    print(s.getIntersectionNode(a, b))
    print(s.reverseList(a))


    # treenode 
    numsTree_94 = [1, None, 2, 3]
    def nums2treeNode(nums):
        if not nums: return None 
        root = TreeNode(nums[0])
        left_children = nums[1::2]
        right_children = nums[2::2]
        root.left = nums2treeNode(left_children)
        root.right = nums2treeNode(right_children)
        return root 
    print(nums2treeNode(numsTree_94))
    print(s.inorderTraversal(nums2treeNode(numsTree_94)))

    # 