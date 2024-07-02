import java.util.*;

//package leetcode_hot_100;
public class leetcode_100 {
    // hash
    public static int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> ht = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            if (ht.containsKey(target - nums[i])) {
                return new int[]{ht.get(target - nums[i]), i};
            }
            ht.put(nums[i], i);
        }
        return new int[0];
    }
    // two pointer
    public static int maxArea(int[] height) {
        int ans = 0, left = 0, right = height.length - 1;
        while (left < right) {
            int area = (right - left) * Math.min(height[left], height[right]);
            ans = Math.max(ans, area);
            if (height[left] < height[right]) ++left;
            else --right;
        }
        return ans;
    }
    // sliding window
    public static int lengthOfLongestSubstring(String S) {
        char[] s = S.toCharArray();
        int n = s.length, ans = 0, left = 0;
        boolean[] has = new boolean[128];
        for (int right = 0; right < n; right++) {
            char c = s[right];
            while (has[c]) {
                has[s[left++]] = false;
            }
            has[c] = true;
            ans = Math.max(ans, right - left + 1);
        }
        return ans;
    }

    // subarray
    public static int subarraySum(int[] nums, int k) {
        int ans = 0, s = 0;
        Map<Integer, Integer> cnt = new HashMap<>(nums.length + 1);
        cnt.put(0, 1);
        for (int x : nums) {
            s += x;
            ans += cnt.getOrDefault(s - k, 0);
            cnt.merge(s, 1, Integer::sum);
        }
        return ans;
    }

    // array
    public static int maxSubArray(int[] nums) {
        int ans = Integer.MIN_VALUE;
        int f = 0;
        for (int x: nums) {
            f = Math.max(f, 0) + x;
            ans = Math.max(ans, f);
        }
        return ans;
    }

    // matrix
    public static int[][] setZeroes(int[][] matrix) {
        int m = matrix.length, n = matrix[0].length;
        boolean[] row = new boolean[m];
        boolean[] col = new boolean[n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    row[i] = col[j] = true;
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (row[i] || col[j]) {
                    matrix[i][j] = 0;
                }
            }
        }
        return matrix;
    }

    // graph
    static void dfs(String[][] grid, int r, int c) {
        int nr = grid.length;
        int nc = grid[0].length;
        if (r < 0 || c < 0 || r >= nr || c >= nc || grid[r][c] == "0") {
            return;
        }
        grid[r][c] = "0";
        dfs(grid, r - 1, c);
        dfs(grid, r + 1, c);
        dfs(grid, r, c - 1);
        dfs(grid, r, c + 1);
    }
    public static int numsIslands(String[][] grid) {
        if (grid == null || grid.length == 0) {
            return 0;
        }
        int nr = grid.length;
        int nc = grid[0].length;
        int num_islands = 0;
        for (int r = 0; r < nr; ++r) {
            for (int c = 0; c < nc; ++c) {
                if (grid[r][c] == "1") {
                    ++num_islands;
                    dfs(grid, r, c);
                }
            }
        }
        return num_islands;
    }

    // backtrace
    private static int[] nums;
    private static List<Integer> path;
    private static boolean[] onPath;
    private static final List<List<Integer>> ans = new ArrayList<>();

    public List<List<Integer>> permute(int[] nums) {
        this.nums = nums;
        path = Arrays.asList(new Integer[nums.length]);
        onPath = new boolean[nums.length];
        dfs(0);
        return ans;
    }

    private static void dfs(int i) {
        if (i == nums.length) {
            ans.add(new ArrayList<>(path));
            return;
        }
        for (int j = 0; j < nums.length; ++j) {
            if (!onPath[j]) {
                path.set(i, nums[j]);
                onPath[j] = true;
                dfs(i + 1);
                onPath[j] = false; // 恢复现场
            }
        }
    }

    // bisect
    public int searchInsert(int[] nums, int target) {
//        return Arrays.binarySearch(nums, target);
        int left = 0, right = nums.length - 1;
        while (left <= right) {
            int mid = left + (right - left); // 2;
            if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return left;
    }

    // stack
    public boolean isValid(String s) {
        if (s.length() % 2 != 0) { // s 长度必须是偶数
            return false;
        }
        Map<Character, Character> mp = new HashMap<Character, Character>() {{
            put(')', '(');
            put(']', '[');
            put('}', '{');
        }};
        Deque<Character> st = new ArrayDeque<>();
        for (char c : s.toCharArray()) {
            if (!mp.containsKey(c)) { // c 是左括号
                st.push(c); // 入栈
            } else if (st.isEmpty() || st.pop() != mp.get(c)) { // c 是右括号
                return false; // 没有左括号，或者左括号类型不对
            }
        }
        return st.isEmpty(); // 所有左括号必须匹配完毕
    }

    // queue
    public int findKthLargest(int[] nums, int k) {
        int heapSize = nums.length;
        buildMaxHeap(nums, heapSize);
        for (int i = nums.length - 1; i >= nums.length - k + 1; --i) {
            swap(nums, 0, i);
            --heapSize;
            maxHeapify(nums, 0, heapSize);
        }
        return nums[0];
    }
    public void buildMaxHeap(int[] a, int heapSize) {
        for (int i = heapSize / 2; i >= 0; --i) {
            maxHeapify(a, i, heapSize);
        }
    }
    public void maxHeapify(int[] a, int i, int heapSize) {
        int l = i * 2 + 1, r = i * 2 + 2, largest = i;
        if (l < heapSize && a[l] > a[largest]) {
            largest = l;
        }
        if (r < heapSize && a[r] > a[largest]) {
            largest = r;
        }
        if (largest != i) {
            swap(a, i, largest);
            maxHeapify(a, largest, heapSize);
        }
    }
    public void swap(int[] a, int i, int j) {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
    // greedy

    // dp

    // bit

    // listnode
    class ListNode {
        int val;
        ListNode next;
        ListNode() {};
        ListNode(int val) {this.val = val;}
        ListNode(int val, ListNode next) {this.val = val; this.next = next; }
    }
    public ListNode arr2ListNode(int[] nums) {
        ListNode head = new ListNode(nums[0]);
        ListNode tmp = head;
        for (int i = 1; i < nums.length; ++i) {
            tmp.next = new ListNode(nums[i]);
            tmp = tmp.next;
        }
        return head;
    }
    public ListNode reverseList(ListNode head) {
        ListNode pre = null, cur = head;
        while (cur != null) {
            ListNode nxt = cur.next;
            cur.next = pre;
            pre = cur;
            cur = nxt;
        }
        return pre;
    }
    // treenode
    class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;
        TreeNode() {};
        TreeNode(int val) {this.val = val;}
        TreeNode(int val, TreeNode left, TreeNode right) {
            this.val = val;
            this.left = left;
            this.right = right;
        }
    }
    TreeNode arr2TreeNodeHelper(int[] nums, int start, int end) {
        if (start > end) return null;
        int mid = (start + end) >> 1;
        TreeNode root = new TreeNode(nums[mid]);
        root.left = arr2TreeNodeHelper(nums, start, mid - 1);
        root.right = arr2TreeNodeHelper(nums, mid + 1, end);
        return root;
    }
    TreeNode arr2TreeNode(int[] nums) {
        return arr2TreeNodeHelper(nums, 0, nums.length - 1);
    }

    public List<Integer> inorderTraversal(TreeNode root) {
        List<Integer> res = new ArrayList<Integer>();
        inorder(root, res);
        return res;
    }
    public void inorder(TreeNode root, List<Integer> res) {
        if (root == null) {
            return;
        }
        inorder(root.left, res);
        res.add(root.val);
        inorder(root.right, res);
    }
    public static void main(String[] args) {
        int[] nums1 = {2,7,11,15};
        System.out.println(Arrays.toString(twoSum(nums1, 9)));
        int[] height11 = {1,8,6,2,5,4,8,3,7};
        System.out.println(maxArea(height11));
        String s3 = "abcabcbb";
        System.out.println(lengthOfLongestSubstring(s3));
        int[] nums560 = {1,1,1};
        System.out.println(subarraySum(nums560, 2));
        int[] nums53 = {-2,1,-3,4,-1,2,1,-5,4};
        System.out.println(maxSubArray(nums53));
        int[][] matrix73 = {{1,1,1},{1,0,1},{1,1,1}};
        Arrays.stream(setZeroes(matrix73)).map(item -> Arrays.toString(item)).forEach(System.out::println);
        String[][] grid200 = {{"1","1","1","1","0"},{"1","1","0","1","0"},{"1","1","0","0","0"},{"0","0","0","0","0"}};
        System.out.println(numsIslands(grid200));
        leetcode_100 l = new leetcode_100();
        int[] nums46 = {1,2,3};
        System.out.println(l.permute(nums46));
        int[] nums35 = {1,3,5,6};
        System.out.println(l.searchInsert(nums35, 5));
        String s20 = "{{}}()";
        System.out.println(l.isValid(s20));
        int[] nums215 = {3,2,1,5,6,4};
        System.out.println(l.findKthLargest(nums215, 2));

        int[] nums206 = {1,2,3,4,5};
        ListNode t = l.arr2ListNode(nums206);
        System.out.println(l.reverseList(t).val);

        int[] nums94 = {1,0, 2, 3};
        TreeNode t1 = l.arr2TreeNode(nums94);
        System.out.println(l.inorderTraversal(t1));


//        System.out.println("hi");
    }

}
