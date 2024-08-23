// 树状数组：维护序列的前缀和。对于给定的序列a，建立一个数组c，其中c[x]保存序列a的区间[x-lowbit(x) + 1, x]中所有数的和
// 两个基本操作：
// 1. 查询前缀和： 序列a第1~x个数的和
// 2. 单点增加： 给序列中的一个数a[x]加上y，同时正确维护序列的前缀和


// 1. 树状数组与逆序对
// exp: 楼兰图腾： 平面上有n个点； 每个点的横纵坐标范围：1~N，任意两个带你的横纵坐标不相同
// 若三个点(x1,y1) (x2,y2) (x3,y3) 满足： x1 < x2 < x3, 且 y3 > y2; y1 > y2, 构成v字图腾
// 若三个点(x1,y1) (x2,y2) (x3,y3) 满足： x1 < x2 < x3, 且 y3 < y2; y1 < y2, 构成倒v字图腾

// 2. 树状数组的扩展应用
// exp: a tiny problem with integers
// exp: a simple problem with integers
// exp: lost cows： n头奶牛，身高从1~n各不相同，但不知道每头牛的具体身高；n头牛站成一列，已知第i头牛前面有Ai头比它低，求每头牛的身高；



// 线段树：基于分治思想的二叉树结构：用于在区间上进行信息统计； 与按照二进制位(2的次幂)进行区间划分的树状数组相比，线段树是一种更加通用的数据结构：
// 建树：
//# can you answer on these queries
//# interval GCD
//# a simple problem with integers
//# atlantis
//# stars in your window
