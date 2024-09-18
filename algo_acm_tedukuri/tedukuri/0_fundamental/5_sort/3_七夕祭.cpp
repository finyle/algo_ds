/*
 * 七夕祭： n*m的矩阵，只对t个感兴趣，交换相邻的点,使得各行，各列中t数量一样多，至少需要交换多少次
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 100006;
int n, m, t, x[N], y[N], a[N], s[N];

int main() {
    cin >> n >> m >> t;
    for (int i = 1; i <= t; i++) scanf("%d %d", &x[i], &y[i]);
    bool row = !(t % n), column = !(t % m);
    if (row) {
        if (column) cout << "both ";
        else cout << "row ";
    } else {
        if (column) cout << "column ";
        else {
            cout << "impossible" << endl;
            return 0;
        }
    }
    ll ans = 0;
    if (row) { // 左右交换，使得每列中的摊点数相同
        int num = t / n;
        memset(a, 0, sizeof(a));
        for (int i = 1; i <= t; i++) a[x[i]]++;
        for (int i = 1; i <= n; i++) a[i] -= num;
        s[0] = 0;
        for (int i = 1; i <= n; i++) s[i] = s[i-1] + a[i];
        sort(s + 1, s + n + 1);
        for (int i = 1; i <= n / 2; i++) ans += s[n-i+1] - s[i];
    }
    if (column) { // 上下交换, 使得每行中摊点数相同
        int num = t / m;
        memset(a, 0, sizeof(a));
        for (int i = 1; i <= t; i++) a[y[i]]++;
        for (int i = 1; i <= m; i++) a[i] -= num;
        s[0] = 0;
        for (int i = 1; i <= m; i++) s[i] = s[i-1] + a[i];
        sort(s + 1, s + m + 1);
        for (int i = 1; i <= m / 2; i++) ans += s[m-i+1] - s[i];
    }
    cout << ans << endl;
    return 0;
}

/*
 * input:
10 10 50
6 3
10 5
8 8
5 3
8 9
2 9
6 6
9 1
4 7
2 3
9 9
1 5
6 9
4 4
10 4
9 2
1 10
8 1
10 9
6 4
4 9
1 3
6 1
7 5
8 6
8 7
2 7
10 8
4 10
7 7
7 10
10 10
6 10
5 9
3 3
3 9
9 4
1 2
5 8
4 5
8 5
6 2
7 2
10 3
8 10
9 6
9 8
6 8
8 2
10 2
 * output:
both 33

 */