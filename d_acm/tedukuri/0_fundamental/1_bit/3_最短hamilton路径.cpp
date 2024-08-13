/*
 * 最短hamilton路径(二进制状态压缩：将一个长度为m的bool数组用一个m位二进制整数表示并存储的方法)：
 * 给定n个点的带权无向图，从起点0到终点n-1的最短hamilton路径：不重不满的经过每个点恰好一次：
 * 枚举n个节点的全排列，计算路径长度的最小值，复杂度位O(n*n!); 使用二进制状态压缩dp O(n^2 * 2 ^ n)
 */

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int f[1 << 20][20], weight[20][20], n; // n个节点小于20个

int hamilton(int n, int weight[20][20]) {
    memset(f, 0x3f, sizeof(f));  // 将数值0x3f以单个字符逐个拷贝的方式放到指针变量f所指的内存中，cpp引用传递
    f[1][0] = 0;
    for (int i = 1; i < 1 << n; i++) // 二进制状态压缩
        for (int j = 0; j < n; j++) if (i >> j & 1)
                for (int k = 0; k < n; k++) if ((i^1<<j) >> k & 1)
                        f[i][j] = min(f[i][j], f[i^1<<j][k]+weight[k][j]); // 状压dp
    return f[(1 << n) - 1][n - 1];
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &weight[i][j]);
    cout << hamilton(n, weight) << endl;
}

/*
 * input:
5
0 2 4 5 1
2 0 6 5 3
4 6 0 8 3
5 5 8 0 5
1 3 3 5 0

 * output:
18

 */