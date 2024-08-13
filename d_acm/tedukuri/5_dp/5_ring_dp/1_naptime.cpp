/*
 * naptime(环形结构动态规划)： i个小时睡觉回复ui点体力，每天n个小时，需要休息8个小时，回复最多体力
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

const int N = 4000, M = 4000;
int n, m, f[2][M][2], w[N], ans;

int main ()
{
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++)
        scanf ("%d", &w[i]);
    if (m == 0)
    { printf ("0"); exit (0); }
    memset (f, 0x80, sizeof f);
    f[1 & 1][0][0] = 0;
    f[1 & 1][1][1] = 0;
    for (int i = 2; i <= n; i ++)
        for (int j = 0; j <= m; j ++)
        {
            f[i & 1][j][0] = max (f[(i - 1) & 1][j][0], f[(i - 1) & 1][j][1]);
            if (j - 1 >= 0) f[i & 1][j][1] = max (f[(i - 1) & 1][j - 1][0], f[(i - 1) & 1][j - 1][1] + w[i]);
        }
    ans = max (f[n & 1][m][1], f[n & 1][m][0]);
    memset (f, 0x80, sizeof f);
    f[1 & 1][1][1] = w[1];
    for (int i = 2; i <= n; i ++)
        for (int j = 0; j <= m; j ++)
        {
            f[i & 1][j][0] = max (f[(i - 1) & 1][j][0], f[(i - 1) & 1][j][1]);
            if (j - 1 >= 0) f[i & 1][j][1] = max (f[(i - 1) & 1][j - 1][0], f[(i - 1) & 1][j - 1][1] + w[i]);
        }
    ans = max (ans, f[n & 1][m][1]);
    printf ("%d", ans);
    return 0;
}

/*
 * input:
5 3
2
0
3
1
4

 * output:
6

 */