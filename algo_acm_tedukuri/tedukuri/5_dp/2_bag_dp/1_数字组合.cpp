
/*
 * 数字组合(0/1背包，n个物品，体积价值矩阵为[v,w],容器容量m，不超过最大容量的物品的最大价值正整数序列中子序列和为m的子序列数；n个数，子序列和为m的选择方案数)

 */
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAX_M = 10000;
int f[MAX_M+1];
int n, m, a[MAX_M+1];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    memset(f, 0, sizeof(f));
    f[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= a[i]; j--)
            f[j] += f[j - a[i]];
    cout << f[m] <<endl;
}

/*
 * input:
3 5
2 3 3
 * output:
2

 */