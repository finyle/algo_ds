#include <malloc.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

// 1.哈希 两数之和
int* twoSum(int* nums, int numsSize, int target, int *returnSize) {
    for (int i = 0; i < numsSize; ++i) {
        for (int j = i + 1; j < numsSize; ++j) {
            if (nums[i] + nums[j] == target) {
                int* ret = malloc(sizeof(int) * 2);
                ret[0] = i, ret[1] = j;
                *returnSize = 2;
                return ret;
            }
        }
    }
    *returnSize = 0;
    return NULL;
}

struct hashTable {
    int key;
    int val;
    UT_hash_handle hh;
};
struct hashTable* hashtable;
struct hashTable* find(int ikey) {
    struct hashTable* tmp;
    HASH_FIND_INT(hashtable, &ikey, tmp);
    return tmp;
};
void insert(int ikey, int ival) {
    struct hashTable* it = find(ikey);
    if (it == NULL) {
        struct hashTable* tmp = malloc(sizeof(struct hashTable));
        tmp -> key = ikey, tmp -> val = ival;
        HASH_ADD_INT(hashtable, key, tmp);
    } else {
        it -> val = ival;
    }
}
int *twoSum_(int* nums, int numsSize, int target, int* returnSize) {
    hashtable = NULL;
    for (int i = 0; i < numsSize; ++i) {
        struct hashTable* it = find(target - nums[i]);
        if (it != NULL) {
            int* ret = malloc(sizeof(int) * 2);
            ret[0] = it -> val, ret[1] = i;
            *returnSize = 2;
            return ret;
        }
        insert(nums[i], i);
    }
    *returnSize = 0;
    return NULL;
}

//双指针 283. 移动零
void swap(int *a, int *b) {
    int t = *a;
    *a = *b, *b = t;
}

void moveZeroes(int *nums, int numsSize) {
    int left = 0, right = 0;
    while (right < numsSize) {
        if (nums[right]) {
            swap(nums + left, nums + right);
            left++;
        }
        right++;
    }
}

// 滑动窗口 3. 无重复最长子串
/*
输入: s = "abcabcbb"
输出: 3 */
int lengthOfLongestSubstring(char* s) {
    int ans = 0, left = 0;
    bool has[128] = {};
    int n = strlen(s);
    for (int right = 0; right < n; right++) {
        char c = s[right];
        while (has[c]) {
            has[s[left++]] = false;
        }
        has[c] = true;
        int len = right - left + 1;
        ans = len > ans ? len : ans;
    }
    return ans;
}

// 子串： 76 最小覆盖子串
/*
输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"*/
char* minWindow(char* s, char* t) {
    int map[256] = {0};
    int slen = strlen(s), tlen = strlen(t);
    int start = 0, sublen = 0, count = INT_MAX;
    for (int i = 0; i < tlen; ++i) map[t[i]]++;
    for (int left = 0, right = 0; right < slen; ++right) {
        if (map[s[right]]-- > 0) tlen--;
        while (tlen == 0) {
            sublen = right - left + 1;
            if (sublen < count) {
                count = sublen;
                start = left;
            }
            if (++map[s[left]] > 0) tlen++;
            left++;
        }
    }
    if (count != INT_MAX) {
        char *ans = (char*)malloc(sizeof(char)*(count+1));
        *ans = 0;
        strncat(ans, s + start, count);
        return ans;
    }
    return "";
}

// 数组： 53 最大子数组和
#define max(a, b) ((b) > (a) ? (b) : (a))
int maxSubArray(int* nums, int numsSize) {
    int* dp = malloc(numsSize * sizeof(int));
    dp[0] = nums[0];
    int ans = dp[0];
    for (int i = 1; i < numsSize; ++i) {
        dp[i] = max(dp[i - 1], 0) + nums[i];
        ans = max(ans, dp[i]);
    }
    free(dp);
    return ans;
}

// 二维数组： 73. 矩阵置零
void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
    int i, j;
    int* row = (int *)malloc(sizeof(int)*matrixSize);
    int* col = (int *)malloc(sizeof(int)*matrixColSize[0]);
    for (int i = 0; i < matrixSize; ++i) {
        for (j = 0; j < matrixColSize[0]; ++j) {
            if (matrix[i][j] == 0) {
                row[i] = 1;
                col[j] = 1;
            }
        }
    }
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixColSize[0]; ++j) {
            if (row[i] == 1 || col[j] == 1) matrix[i][j] = 0;
        }
    }
}

// 链表： 142. 环形链表2
struct ListNode {
    int val;
    struct ListNode *next;
};
struct ListNode *deleteCycle(struct ListNode *head) {
    struct ListNode * slow, * fast;
    slow = fast = head;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast){
            struct ListNode* n1 = fast;
		    struct ListNode* n2 = head;
		    while(n1 != n2)
		    {
		        n1 = n1->next;
		        n2 = n2->next;
		    }
		    return n1;
        }
    }
    return NULL;
}

// 二叉树 102。 二叉树的层序遍历
struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right
};
int** levelOrder(struct TreeNode* root, int* returnSize, int**returnColumnSizes) {
    int** ans=(int**)malloc(sizeof(int*)*2000);
    *returnSize=0;
    if(!root) return NULL;//要在return前给出*returnSize的取值不然过不去；！！
    int columnSizes[2000];//记录每一行的列数（每层结点数），因为要给出* returnColumnSizes
    struct TreeNode* queue[2000];//模拟队列
    int rear=0;int head=0;//记录队列头尾
    queue[rear++]=root;//录入根结点

    while(rear!=head){//队列不为空
        ans[(*returnSize)]=(int*)malloc(sizeof(int)*(rear-head));
        columnSizes[(*returnSize)]=rear-head;
        int start=head;//记录遍历开始位置，即为本层的头
        head=rear;//本层的尾部成为下次的头，因为所有的元素均弹出队列
        //在这里下层的头head同时作为遍历结束的位置，因为在遍历中rear会不断改变，成为下层的尾
        for(int i=start;i<head;i++){//弹出start到未变化的rear（即为head）之间的所有元素
            ans[(*returnSize)][i-start]=queue[i]->val;
            if(queue[i]->left) queue[rear++]=queue[i]->left;
            if(queue[i]->right) queue[rear++]=queue[i]->right;//rear不断改变
        }
        (*returnSize)++;//一层遍历完*returnSize加一；

    }
    *returnColumnSizes=(int*)malloc(sizeof(int)*(*returnSize));//给出*returnColumnSizes
    for(int i=0;i<*returnSize;i++) (*returnColumnSizes)[i]=columnSizes[i];
    return ans;
}

// 图论 200 岛屿数量
void dfs(char** grid, int i, int j, int m, int n) {
    if (i < 0 || i >= m || j < 0 || j >= n) return;
    if (grid[i][j] == '1') grid[i][j] = '0';
    else return;
    dfs(grid, i + 1, j, m, n);
    dfs(grid, i - 1, j, m, n);
    dfs(grid, i, j + 1, m, n);
    dfs(grid, i, j - 1, m, n);
    return;
}
int numsIslands(char** grid, int gridSize, int* gridColSize) {
    int m =  gridSize; int n = gridColSize[0];
    int sum = 0; int i, j;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '1') {
                sum++;
                dfs(grid, i, j, m, n);
            }
        }
    }
    return sum;
}

// 回溯： 46 全排列

// 二分： 33. 搜索旋转排序数组
int search(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1, mid = 0;
    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (nums[0] <= nums[mid]) {
            if (nums[0] <= target && target < nums[mid]) {
                right = mid + 1;
            } else {
                left = mid + 1;
            }
        } else {
            if (nums[0] > target && target >= nums[mid]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return target == nums[left - 1] ? left - 1 : -1;
}

// 栈： 20. 有效括号
char pairs(char a) {
    if (a == '}') return '{';
    if (a == ']') return '[';
    if (a == ')') return '(';
    return 0;
}
bool isValid(char* s) {
    int n = strlen(s);
    if (n % 2 == 1) {return false}
    int stk[n + 1], top = 0;
    for (int i = 0; i < n; ++i) {
        char ch = pairs(s[i]);
        if (ch) {
            if (top == 0 || stk[top - 1] != ch) {return false;}
            --top;
        } else stk[++top] = s[i];
    }
    return top == 0;
}

// 队列： 215. 数组中第k个最大元素
void heap(int a[], int pos, int length) {
    int tmp = a[pos];
    for (int i = 2 * pos + 1; i < length; pos = i, i = i * 2 + 1) {
        if ((i + 1) < length && a[i] > a[i + 1]) ++i;
        if (tmp > a[i]) a[pos] = a[i];
        else break;
    }
    a[pos] = tmp;
}
int findKthLargest(int* a, int numsSize, int k) {
    for (int i = k / 2 - 1; i >= 0; --i) {
        heap(a, i, k);
    }
    for (int i = k; i < numsSize; ++i) {
        if (a[0] < a[i]) a[0] = a[i];
        heap(a, 0, k);
    }
    return a[0];
}

// 贪心： 55. 跳跃游戏
bool canJump(int* nums, int numsSize) {
    int potentialEnergy = -1;
    for (int i = 0; i < numsSize - 1; ++i) {
        if (nums[i] >= potentialEnergy) {
            potentialEnergy = nums[i];
        } else {
            potentialEnergy = (potentialEnergy - 1 > nums[i]) ? (potentialEnergy - 1) : (nums[i]);
        }
        if (potentialEnergy == 0) return false;
    }
    return true;
}


// dp： 32. 最长有效括号
int longestValidParentheses(char* s) {
    if(!s)
    return 0;
    int lens = strlen(s);
    int stack[lens+1];
    int max = 0, top = -1 , temp = 0;
    /*栈低第一个元素为-1，这样才能匹配*/
    stack[++top] = -1;
    for(int j = 0;j<lens;j++){
        /*入栈*/
        if(s[j]=='('){
            stack[++top] = j;
        }
        else{
          --top;
          if(top == -1){
              stack[++top] = j;
          }
          else{
              temp = j - stack[top];
              max = max<temp?temp:max;
          }
        }
    }
    return max;
}

// 多维dp： 72 编辑距离
#define min(a,b) ((a) > (b) ? (b) : (a))
int minDistance(char* word1, char* word2) {
    int len1 = strlen(word1), len2 = strlen(word2);
    __int64_t dp[len1 + 1][len2 + 1];
    for (int i = 0; i <= len2; ++i) dp[0][i] = i;
    for (int j = 1; j <= len1; ++j) dp[j][0] = j;
    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <=len2; ++j) {
            if (word1[i - 1] == word2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            else dp[i][j] = min(dp[i][j - 1], min(dp[i - 1][j], dp[i - 1][j - 1])) + 1;
        }
    }
    return dp[len1][len2];
}



int main() {
    int arr[] = {1,2,3};
    int length = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < length; i ++) {
        printf("%d ", arr[i]);
    }


    int nums1[] = {2,7,11,15};
    printf("%d %d", twoSum(nums1, 4, 9, (int*)2));

    return 0;
}