/*
 *  making the grade(给定序列a，构造长度为n的序列b，满足：b非严格单调，可以递增也可以递减，有重复元素；sum(ai-bi)的值最小)；至少需要修改多少个数？
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2010, INF = 0x3f3f3f3f;

int n;
int a[N], b[N];
int f[N][N];

int work()
{
    for (int i = 1; i <= n; i ++ ) b[i] = a[i];
    sort(b + 1, b + n + 1);  // 离散化，用索引代表数值进行DP

    for (int i = 1; i <= n; i ++ )
    {
        int minv = INF;
        for (int j = 1; j <= n; j ++ )
        {
            minv = min(minv, f[i - 1][j]);
            f[i][j] = minv + abs(a[i] - b[j]);
        }
    }

    int res = INF;
    for (int i = 1; i <= n; i ++ ) res = min(res, f[n][i]);

    return res;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);

    int res = work();
    reverse(a + 1, a + n + 1);
    res = min(res, work());

    printf("%d\n", res);

    return 0;
}

/*
 * input:
 * 7
1
3
2
4
5
3
9
 * output:
 * 3
 *
 */