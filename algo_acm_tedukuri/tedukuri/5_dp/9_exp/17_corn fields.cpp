
/*
 * corn fields(矩形农场种玉米，不能相邻块种植，，可选择的种植方案数)： 状态压缩dp/ 填充网格图形

 */

#include <cstdio>
#include <iostream>
using namespace std;
const int P = 100000000;
int m, n, a, x[13], f[13][1<<12], M, ans = 0;
bool v[1<<12];

int main() {
    cin >> m >> n;
    M = (1 << n);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            cin >> a;
            (x[i] <<= 1) += a;
        }
    for (int i = 0; i < M; i++) v[i] = !(i & (i << 1)) && !(i & (i >> 1));
    f[0][0] = 1;
    for (int i = 1; i <= m; i++)
        for (int j = 0; j < M; j++)
            if (v[j] && ((j & x[i]) == j))
                for (int k = 0; k < M; k++)
                    if (!(k & j)) f[i][j] = (f[i][j] + f[i-1][k]) % P;
    for (int i = 0; i < M; i++) (ans += f[m][i]) %= P;
    cout << ans << endl;
    return 0;
}


/*
 * input:
2 3
1 1 1
0 1 0
 * output:
9
 *
*/
