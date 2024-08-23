# 1. 两数之和： 数组nums, 数字target, 返回元素和为target 的元素位置：  一次遍历，存哈希表并查表，空间换时间：O(n)
# 49. 字母异位词分组： 字符串数组strs, 将异位词元素合并为一组返回结果: 二维字符串数组， 一次遍历，建哈希表，存表，返回结果 O(n)
# 128. 最长连续序列： 数组nums， 返回最长的连续元素长度： 一次遍历， 建哈希表，判断目标元素是否存在 O(n)

# 283. 移动零： 数组nums，将所有元素0移动至数组末尾，且所有元素相对位置不变，无额外空间，双指针原地交换 O(n) 
# 11. 盛水最多的容器： 数组nums， 代表数轴高度，围成的最大矩形面积 O(n), 双指针，无需额外空间
# 15. 三数之和： 数组nums， 和为0的三元组， 双指针 O(n2)
# 42. 接雨水： 数组nums, 代表宽度为1的矩形高度，接水面积； 双指针O(n)， 一次遍历且空间复杂度O(1)

# 3. 无重复字符串最长子串： 字符串s中无重复字符最长子串： 双指针一次遍历
# 438. 字符串中所有异位词的子串： 字符串s，p， 求s中所有p的异位词的子串的起始索引： 滑动窗口一次遍历O(m + n)

# 560. 和为k的子数组： 数组nums和整数k，统计并返回nums中和为k的子数组个数， 一次遍历，建哈希表 + 前缀和， 前缀和 + 哈希表优化 O(n)
# 239. 滑动窗口最大值： 数组nums， k， 求nums中长度为k的滑动窗口的所有最大值 优先队列O(n(log(n))), 单调队列O(n)
# 76. 最小覆盖子串: 字符串s, p; s中覆盖p的最短子串长度： O(m + n), 滑动窗口 while + for一次遍历， 复杂度计算为 m + n 

# 53. 最大子数组和： 数组nums，返回有最大和的子数组： dp | 分治 -> 线段树 O(n)
# 56. 合并区间：s 二维数组n*2的二维数组 matrix， 合并所有重叠区间, 按子区间左端点排序 O(log(n)n)
# 189. 轮转数组： 数组 nums, 向右折k个元素： 原地旋转 O(n) O(1)
# 238. 除自身以外的乘积： 数组nums, 返回ans数组，每个元素为除自身之外的所有元素乘积 O(n) 两轮遍历 前后缀分解
# 41. 缺失的第一个正数： 数组nums, 返回其中没有出现的最小的正整数： O(n) O(k), 哈希表， 三轮遍历

# 73. 矩阵置零: 01矩阵matrix, 将0所在的行和列的元素都替换为0，标记变量 O(mn) O(1)
# 54. 螺旋矩阵: 螺旋遍历数组
# 旋转图像： 矩阵元素旋转
# 搜索二维矩阵： 

# ##########################################################
# // 链表： 
# 相交链表
# 反转链表
# 回文链表
# 环形链表
# 合并两个有序链表
# 两数相加
# 删除链表的倒数第k个节点
# 两两交换链表中的节点
# h k个一组反转链表
# 随机链表的复制
# 排序链表
# h 合并k个升序链表
# LRU缓存

# ##########################################################
# // 二叉树
# // 中序遍历
# 最大深度
# 反转二叉树
# 对称二叉树
# 二叉树的直径
# 二叉树的层序遍历
# 将有序数组转换为二叉搜索树
# 验证二叉树
# 二叉搜索树中第k小的元素
# 二叉树的右视图
# 二叉树展开为链表
# 从前序遍历和中序遍历构造二叉树
# 路径总和
# 二叉树最近公共祖先
# 二叉树中的最大路径和

# ##########################################################
# 图 200. 岛屿数量: 01矩阵matrix， 1上下左右相连的连通块数： dfs, bfs, uf O(mn)
# 994. 腐烂的橘子： 012矩阵matrix, 1好橘子2烂橘子，上下左右相连传递：所有橘子都变烂的最短时间：bfs O(mn)
# 207. 课程表：n * 2的矩阵，表示课程先后关系，判断有向图中受否存在环：bfs, dfs O(m+n) 
# 208. 实现Trie树(Trie): 实现前缀树： insert, search, serachPrefix, 前缀区间查询 O(1)

# ##########################################################
# // 回溯
# 全排列
# 子集
# 电话号码的字母组合
# 组合总数
# 括号生成
# 单词搜索
# 分割回文串
# N皇后

# ##########################################################
# // 二分
# 搜索插入位置
# 搜索二维矩阵
# 在排序数组中查找元素的第一个和最后一个位置
# 搜索旋转排序数组
# 寻找需按照排序数组中的最小值
# 寻找两个正序数组的中位数

# ##########################################################
# // 栈
# 有效括号
# 最小栈
# 字符串解码
# 每日温度
# h 柱状图中最大矩形

# ##########################################################
# // 堆
# 数组中的第k个最大元素
# 前k个高频元素
# 数据流中的中位数

# ##########################################################
# // 贪心
# 买卖股票的最佳时机
# 跳跃游戏
# 跳跃游戏2
# 划分字母区间

# ##########################################################
# // dp
# 爬楼梯
# 杨辉三角
# 打家劫舍
# 完全平方数
# 零钱兑换
# 单词拆分
# 最长递增子序列
# 乘积最大的子数组
# 分割等和子集
# h 最长有效括号

# ##########################################################
# // dp+ 
# 不同路径
# 最小路径和
# 最长回文子串
# 最长公共子序列
# 编辑距离

# ##########################################################
# // 位运算
# 只出现一次的数字
# 多数元素
# 颜色分类
# 下一个排列
# 寻找重复数


# #######################################################
# 1114. 按序打印: foobar

# 1115. 交替打印 FooBar: for_range

# 1116. 打印零与奇偶数: zeroEvenOdd

# 1117. H2O 生成: hydrogen2, oxygen1, barrier; 

# 1188. 设计有限阻塞队列: push, pop, size, get

# 1195. 交替打印字符串: fizzBuzz, %3, %5

# 1226. 哲学家进餐: uid, pickleftfork, pickright, putleft, putrigght

# 1242. 多线程网页爬虫: existCheck

# 1279. 红绿灯路口: deadlock 