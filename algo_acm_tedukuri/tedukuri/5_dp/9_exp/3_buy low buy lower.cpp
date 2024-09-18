/*
 * buy low buy lower(一维数组表示股价序列，统计递减子串) 线性dp/统计LIS方案数
 */


#include<bits/stdc++.h>
using namespace std;
int n, a[5005], f[5005], c[5005], ans, tot;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    a[0] = 1 << 30;
    memset(f, 0xcc, sizeof(f));
    f[0] = 0, c[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            if (a[j] > a[i]) {
                if (f[i] < f[j] + 1) f[i] = f[j] + 1, c[i] = c[j];
                else if (f[i] == f[j] + 1) c[i] += c[j];
            }
            else if (a[j] == a[i]) c[j] = 0;
    for (int i = 1; i <= n; i++)
        if (f[i] > ans) ans = f[i], tot = c[i];
        else if (f[i] == ans) tot += c[i];
    cout << ans << ' ' << tot << endl;
}


/*
 * input:
12
68 69 54 64 68 64 70 67 78 62 98 87
 * output:
4 2
 */