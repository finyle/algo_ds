package main

import (
	"fmt"
	"math"
)

// hash
func twoSum(nums []int, target int) []int {
	ht := map[int]int{}
	for i, x := range nums {
		if p, ok := ht[target-x]; ok {
			return []int{p, i}
		}
		ht[x] = i
	}
	return nil
}

// two pointer
func maxArea(height []int) (ans int) {
	left, right := 0, len(height)-1
	for left < right {
		area := (right - left) * min(height[left], height[right])
		ans = max(ans, area)
		if height[left] < height[right] {
			left++
		} else {
			right--
		}
	}
	return
}

// slide window
func lengthOfLongestSubstring(s string) (ans int) {
	window := [128]bool{}
	left := 0
	for right, c := range s {
		for window[c] {
			window[s[left]] = false
			left++
		}
		window[c] = true
		ans = max(ans, right-left+1)
	}
	return
}

// subarray
func subarraySum(nums []int, k int) (ans int) {
	s := 0
	cnt := map[int]int{0: 1}
	for _, x := range nums {
		s += x
		ans += cnt[s-k]
		cnt[s]++
	}
	return
}

// array
func maxSubArray(nums []int) int {
	ans := math.MinInt
	minPreSum := 0
	preSum := 0
	for _, x := range nums {
		preSum += x
		ans = max(ans, preSum-minPreSum)
		minPreSum = min(minPreSum, preSum)
	}
	return ans
}

// matrix

// graph

// backtrace
func permute(nums []int) (ans [][]int) {
	n := len(nums)
	path := make([]int, n)
	onPath := make([]bool, n)
	var dfs func(int)
	dfs = func(i int) {
		if i == n {
			ans = append(ans, append([]int(nil), path...))
			return
		}
		for j, on := range onPath {
			if !on {
				path[i] = nums[j]
				onPath[j] = true
				dfs(i + 1)
				onPath[j] = false
			}
		}
	}
	dfs(0)
	return
}

// bisect
func searchInsert(nums []int, target int) int {
	left, right := 0, len(nums)-1
	for left <= right {
		mid := left + (right-left)>>1
		if nums[mid] < target {
			left = mid + 1
		} else {
			right = mid - 1
		}
	}
	return left
}

// stack
func isValid(s string) bool {
	if len(s)%2 != 0 {
		return false
	}
	mp := map[rune]rune{')': '(', ']': '[', '}': '{'}
	st := []rune{}
	for _, c := range s {
		if mp[c] == 0 {
			st = append(st, c)
		} else {
			if len(st) == 0 || st[len(st)-1] != mp[c] {
				return false
			}
			st = st[:len(st)-1]
		}
	}
	return len(st) == 0
}

// queue
func findKthLargest(nums []int, k int) int {
	heapify(nums)
	for i := 0; i < k-1; i++ {
		pop(&nums)
	}
	return nums[0]
}
func heapify(nums []int) {
	n := len(nums)
	for i := n/2 - 1; i >= 0; i-- {
		down(nums, i, n)
	}
}
func down(nums []int, i, n int) bool {
	parent := i
	for {
		left := 2*parent + 1
		if left >= n || left < 1 {
			break
		}
		max := left
		if right := left + 1; right < n && nums[right] > nums[left] {
			max = right
		}
		if nums[max] < nums[parent] {
			break
		}
		nums[parent], nums[max] = nums[max], nums[parent]
		parent = max
	}
	return parent > i
}
func pop(nums *[]int) int {
	last := len(*nums) - 1
	(*nums)[0], (*nums)[last] = (*nums)[last], (*nums)[0]
	down(*nums, 0, last)
	rst := (*nums)[last]
	(*nums) = (*nums)[:last]
	return rst
}

// greedy
func maxProfit(prices []int) (ans int) {
	minPrice := prices[0]
	for _, p := range prices {
		ans = max(ans, p-minPrice)
		minPrice = min(minPrice, p)
	}
	return
}

// dp
func climbStars(n int) int {
	memo := make([]int, n+1)
	var dfs func(int) int
	dfs = func(i int) int {
		if i <= 1 { // 递归边界
			return 1
		}
		p := &memo[i]
		if *p != 0 { // 之前计算过
			return *p
		}
		res := dfs(i-1) + dfs(i-2)
		*p = res // 记忆化
		return res
	}
	return dfs(n)
}

func climbStairs_(n int) int {
	f := make([]int, n+1)
	f[0], f[1] = 1, 1
	for i := 2; i <= n; i++ {
		f[i] = f[i-1] + f[i-2]
	}
	return f[n]
}

// bit

// listnode
type ListNode struct {
	Val  int
	Next *ListNode
}

func reverseList(head *ListNode) *ListNode {
	var pre, cur *ListNode = nil, head
	for cur != nil {
		nxt := cur.Next
		cur.Next = pre
		pre = cur
		cur = nxt
	}
	return pre
}

// treenode
type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func inorderTraversal(root *TreeNode) (res []int) {
	var inorder func(node *TreeNode)
	inorder = func(node *TreeNode) {
		if node == nil {
			return
		}
		inorder(node.Left)
		res = append(res, node.Val)
		inorder(node.Right)
	}
	inorder(root)
	return
}

func main() {
	nums1 := []int{2, 7, 11, 15}
	fmt.Println(twoSum(nums1, 9))
	height11 := []int{1, 8, 6, 2, 5, 4, 8, 3, 7}
	fmt.Println(maxArea(height11))
	s3 := "abcabcbb"
	fmt.Println(lengthOfLongestSubstring(s3))
	nums560 := []int{1, 2, 3}
	fmt.Println(subarraySum(nums560, 3))
	nums53 := []int{-2, 1, -3, 4, -1, 2, 1, -5, 4}
	fmt.Println(maxSubArray(nums53))
	nums46 := []int{1, 2, 3}
	fmt.Println(permute(nums46))
	nums35 := []int{1, 3, 5, 6}
	fmt.Println(searchInsert(nums35, 5))
	s20 := "()[]{}"
	fmt.Println(isValid(s20))
	nums215 := []int{3, 2, 1, 5, 6, 4}
	fmt.Println(findKthLargest(nums215, 2))
	nums121 := []int{7, 1, 5, 3, 6, 4}
	fmt.Println(maxProfit(nums121))
	fmt.Println(climbStairs_(3))
	fmt.Println(climbStars(3))

	nums206 := []int{1, 2, 3, 4, 5}
	var arr2listNode = func(nums []int) *ListNode {
		if len(nums) == 0 {
			return nil
		}
		head := &ListNode{Val: nums[0]}
		tmp := head
		for i := 1; i < len(nums); i++ {
			tmp.Next = &ListNode{Val: nums[i]}
			tmp = tmp.Next
		}
		return head
	}
	l := arr2listNode(nums206)
	fmt.Println(reverseList(l).Val)

	nums94 := []int{1, 2, 3}
	arr2treeNode := func(nums []int) *TreeNode {
		if len(nums) == 0 {
			return nil
		}
		var arr2treeNodeHelper func(nums []int, start int, end int) *TreeNode
		arr2treeNodeHelper = func(nums []int, start int, end int) *TreeNode {
			if start > end {
				return nil
			}
			mid := (start + end) / 2
			node := &TreeNode{Val: nums[mid]}
			node.Left = arr2treeNodeHelper(nums, start, mid-1)
			node.Right = arr2treeNodeHelper(nums, mid+1, end)
			return node
		}
		return arr2treeNodeHelper(nums, 0, len(nums)-1)
	}
	r := arr2treeNode(nums94)
	fmt.Println(inorderTraversal(r))
}
