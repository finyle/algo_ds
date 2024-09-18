
/*
 * 干草堆(给定数组表示干草堆宽度，求解层层叠加的最高高度)： 单调队列优化dp/ 贪心

 */

#include <cstdio>
#include <iostream>
using namespace std;
const int N = 100006;
int n, a[N], s[N], q[N], d[N], f[N];

int main() {
    cin >> n;
    for (int i = n; i; i--) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) s[i] = s[i-1] + a[i];
    int l = 1, r = 0;
    for (int i = 1; i <= n; i++) {
        while (l <= r && s[i] - s[q[l]] >= f[q[l]]) ++l;
        f[i] = s[i] - s[q[l-1]];
        d[i] = d[q[l-1]] + 1;
        while (l <= r && f[i] - f[q[r]] <= s[q[r]] - s[i]) --r;
        q[++r] = i;
    }
    cout << d[n] << endl;
    return 0;
}


/*
 * input:
3
1
2
3
 * output:
2
 */