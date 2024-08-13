/*
 * Blocks: Blocks(四种颜色的金属块排成一列，相同颜色的相邻金属块合并得分为个数的平方，求一列色块的最大得分
 */

#include<bits/stdc++.h>
using namespace std;
int f[205][205][205]; // f[l][r][cnt]: l~r合并，其中剩下cnt个与a[l],a[r]同色的最后一起合并
int T, n, m, a[205], b[205]; // a: 颜色，b: 数量
int main() {
    cin >> T;
    for (int C = 1; C <= T; C++) {
        cin >> n;
        m = 0;
        for (int i = 1; i <= n; i++) {
            int x; scanf("%d", &x);
            if (x == a[m]) b[m]++; else a[++m] = x, b[m] = 1; // 合并连续同色块
        }
        memset(f, 0xcc, sizeof(f));
        for (int i = 1; i <= m; i++)
            f[i][i][0] = b[i] * b[i], f[i][i][b[i]] = 0;
        for (int len = 2; len <= m; len++)
            for (int l = 1; l <= m - len + 1; l++) {
                int r = l + len - 1;
                for (int k = l; k < r; k++)
                    f[l][r][0] = max(f[l][r][0], f[l][k][0] + f[k + 1][r][0]);
                if (a[l] != a[r]) continue;
                int tot = b[l] + b[r]; // 控制一下循环上界，减小常数，避免超时
                for (int k = l + 1; k < r; k++)
                    if (a[k] == a[l]) tot += b[k];
                for (int cnt = b[l] + b[r]; cnt <= tot; cnt++) {
                    for (int k = l + 1; k <= r; k++)
                        if (a[l] == a[k])
                            f[l][r][cnt] = max(f[l][r][cnt], f[l + 1][k - 1][0] + f[k][r][cnt - b[l]]);
                    f[l][r][0] = max(f[l][r][0], f[l][r][cnt] + cnt * cnt);
                }
            }
        printf("Case %d: %d\n", C, f[1][m][0]);
    }
}


/*
 * input:
3
10
2 1 8 8 5 2 8 7 8 5
10
5 3 4 5 6 4 2 3 6 3
10
3 4 3 2 4 3 4 1 3 3
 * output:
Case 1: 22
Case 2: 18
Case 3: 30
 */