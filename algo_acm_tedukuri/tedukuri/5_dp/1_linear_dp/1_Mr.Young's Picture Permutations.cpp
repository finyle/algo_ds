// 1. 线性dp
// lis, lca, 数字三角形(三角矩阵左上到右下移动最大路径和)

// 2. 背包dp
// 2.1 01背包
// exp: 数字组合
// 2.2 完全背包
// exp: 自然数拆分； JuryCompromise
// 2.3 多重背包
// exp: coins
// 2.4 分组背包

// 3. 区间dp: 以”区间长度"作为dp的阶段，使用两个坐标描述每个维度，区间dp中一个状态由若干个比它更小且包含与它的区间所代表的状态转移而来
// exp: 石子合并；Polygon；金字塔


/*
 * # Mr. Young's Picture Permutations(n个学生排k行队，左端对齐，身高从左到右，从上到下递减，共多少种排队方式，数字三角形排列)
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;
int n[6], k;

void work() {
    for (int i = 1; i <= k; i++) cin >> n[i];
    while (k < 5) n[++k] = 0;
    ll f[n[1]+1][n[2]+1][n[3]+1][n[4]+1][n[5]+1];
    memset(f, 0, sizeof(f));
    f[0][0][0][0][0] = 1;
    for (int i = 0; i <= n[1]; i++)
        for (int j = 0; j <= n[2]; j++)
            for (int k = 0; k <= n[3]; k++)
                for (int l = 0; l <= n[4]; l++)
                    for (int m = 0; m <= n[5]; m++) {
                        if (i < n[1]) f[i+1][j][k][l][m] += f[i][j][k][l][m];
                        if (j < n[2] && i > j) f[i][j+1][k][l][m] += f[i][j][k][l][m];
                        if (k < n[3] && j > k) f[i][j][k+1][l][m] += f[i][j][k][l][m];
                        if (l < n[4] && k > l) f[i][j][k][l+1][m] += f[i][j][k][l][m];
                        if (m < n[5] && l > m) f[i][j][k][l][m+1] += f[i][j][k][l][m];
                    }
    cout << f[n[1]][n[2]][n[3]][n[4]][n[5]] << endl;
}

int main() {
    while (cin >> k && k) work();
    return 0;
}

/*
 * in:
 * 1
30
5
1 1 1 1 1
3
3 2 1
4
5 3 3 1
5
6 5 4 3 2
2
15 15
4
11 4 4 4
2
14 10
3
9 9 5
3
10 10 3
4
6 6 6 6
3
17 8 3
3
7 7 6
4
10 5 3 3
5
5 5 5 2 1
2
18 6
3
20 5 3
3
15 8 3
2
15 9
3
23 4 3
3
13 6 6
4
9 9 3 2
3
19 5 5
3
18 4 4
3
23 4 3
5
5 5 5 5 5
2
22 8
4
8 8 8 2
3
12 10 4
5
6 6 6 6 1
0

 output:
 1
1
16
4158
141892608
9694845
205931880
653752
44618574
16224936
140229804
1105104000
1385670
73256400
2333760
92092
57264480
349949600
572033
20900880
235350720
283936380
480720240
13813800
20900880
701149020
3817125
3866943080
1014058500
2103447060

 */