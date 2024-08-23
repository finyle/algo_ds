// n个盘子，4座塔的汉诺塔问题； 按顺序叠大小不一的盘子的最少移动步数

#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

const int N = 15;
ll d[N], f[N];

int main() {
    int n = 12;
    memset(f, 0x3f, sizeof(f));
    d[1] = f[1] = 1;
    for (int i = 2; i <= n; i++) d[i] = 2 * d[i - 1] + 1;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j < i; j++)
            f[i] = min(f[i], 2 * f[j] + d[i - j]); // dp求解， 递推公式
    for (int i = 1; i <= n; i++) cout << i << " " << f[i] << endl;
    return 0;
}

/*
 * input:
输入分别为 [1,12] 座塔的汉诺塔问题步数
 * output:
1
3
5
9
13
17
25
33
41
49
65
81
 */