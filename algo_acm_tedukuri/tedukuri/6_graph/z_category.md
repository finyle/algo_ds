# 最短路
# 4. Telephone Lines (单源最短路)
# 5. 最优贸易
# 6. 道路与航线 
# 1. Cow Replays (任意两点间的最短路径)
# 2. Sightseeing Trip
# 3. Sorting It All Out

# 最小生成树
# 1. Picnic Planning
# 2. 最优比率生成树
# 3. 走廊泼水节
# 4. 黑暗城堡

# 树的直径与最近公共祖先
# 1. 严格次小生成树
# 2. 天天爱跑步
# 3. 巡逻
# 4. 异象石
# 5. 树网的核
# 6. 疫情控制
# 7. 音的连锁
# 8. 雨天的尾巴

# ########################################
# 基环树
# 1. freda的传呼机
# 2. 创世纪
# 3. 岛屿

# 负环与差分约束
# 1. interval(西瓜种植)
# 2. sightseeing cows

# ##########################################
# tarjan算法与无向图连通性
# 1. BLO
# 2. Knights of the Round Table
# 3. Network
# 4. Watchcow

# tarjan算法与有向图连通性
# 1. Katu Puzzle
# 2. Network of school
# 3. PKU ACM Team's Excursion
# 4. Priest ACM Team's Excurison
# 5. 银河

# 二分图的匹配
# 1. Ants
# 2. 关押罪犯
# 3. 导弹防御塔
# 4. 棋盘覆盖
# 5. 车的放置

# 二分图的覆盖与独立集
# 1. machine schedule
# 2. muddy fields
# 2. Vani 和 Cl2 捉迷藏
# 4. 骑士放置
# 网络流初步
# 总结与练习

# ##############################################
# A 网络流初步
# 1. cable TV Network
# 2. k取方格数
# 3. 舞动的夜晚

# #####################################################################################
# 知识点：
# 最短路
## 图的基本概念，图的邻接矩阵与邻接表存储
## 单源最短路问题；Dijkstra算法及堆优化，Bellman-Ford, SPFA算法
## 单源最短路各算法的适用范围，单元最短路问题的变形与扩展
## 任意两点间最短路径问题，Floyd算法的本质及应用
## 传递闭包，无向图最小环问题

# 最小生成树
## 最小生成树的定义与基本性质，Kruskal算法，Prim算法
## 最小生成树问题的变形与扩展

# 树的直径与最近公共祖先
## 树的直径的定义与计算：动态规划或两次BFS
## 树的直径的性质与应用：直径的最长性
## LCA的定义与计算，向上标记法，树上倍增法，LCA的Tarjan算法
## LCA的扩展与应用：树上差分算法
## 树上倍增发的应用：次小生成树

# ###################################
# 基环树：
## 基环树，外向树，内向树的定义，基环树的处理方法

# 负环与差分约束
## 最短路中负环的判定方法
## 差分约束系统的求解，差分约束到最短路的转换

# ###################################
# Tarjan算法与无向图连通性
## 无向图的搜索树，时间戳与追溯值，割点与割边判定法则
## Tarjan算法求割点，割边，点双连通分量，边双连通分量
## 双连通分量的性质与应用，缩点
## 欧拉图的判定，欧拉路的计算

# Tarjan算法与有向图连通性
## 有向图的搜索树，边的分类，Tarjan算法求强连通分量
## 强连通分量的性质，应用，缩点
## 有向无环图的必经点与必经边，路径条数取模法
## 2-SAT问题的判定，自底向上拓扑排序构造方案

# ###################################
# 二分图匹配
## 二分图的判定：染色法判定是否存在奇环
## 二分图最大匹配：匈牙利(增广路)算法
## 二分图匹配的模型构建方法：0要素 与 1要素，二分图多重匹配
## 二分图带权最大匹配：KM算法

# 二分图覆盖与独立集
## 二分图最小点覆盖，模型构建的2要素
## 二分图最大独立集，团与独立集的对应关系，补图转化思想
## 有向无环图的最小路径点覆盖，最小路径可重复点覆盖

# ####################################
# 网络流初步
## 网络流定义：容量限制，斜对称，流量守恒 三条基本定律
## 最大流的Edmonds-Karp增广路算法与Dinic算法
## 网络流求解二分图匹配，二分图最大匹配的必须边，可行边判定
## 最小割的定义，最大流最小割定理，”点边转化“技巧
## 费用流的Edmonds-Karp增广路算法及其应用