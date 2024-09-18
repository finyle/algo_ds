/*
 * 最长公共上升递增子序列 求两个数列的最长公共上升子序列
 *
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 3006;
int n, a[N], b[N], f[N][N];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
    for (int i = 1; i <= n; i++) {
        int val = 0;
        for (int j = 1; j <= n; j++) {
            f[i][j] = (a[i] == b[j] ? val + 1 : f[i-1][j]);
            if (b[j] < a[i]) val = max(val, f[i-1][j]);
        }
    }
    int ans = 0;
    for (int j = 1; j <= n; j++) ans = max(ans, f[n][j]);
    cout << ans << endl;
    return 0;
}

/*
 * input:
 * 4
2 2 1 3
2 1 2 3

 output:
 2
 */