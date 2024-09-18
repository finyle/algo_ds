/*
 * 自然数拆分Lunatic版(完全背包，n种物品，有无数个，求最大价值)(自然数n拆分成若干个正整数相加的形式，参与加法运算的数允许重复，求拆分方案数)

 */
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAX_N = 10000;
unsigned int f[MAX_N + 1], n;
int main() {
    cin >> n;
    memset(f, 0, sizeof(f));
    f[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            f[j] = (f[j] + f[j - i]) % 2147483648u;
    cout << (f[n] > 0 ? f[n] - 1 : 2147483647) <<endl;
}

/*
 * input:
250
 * output:
1339230472
 */