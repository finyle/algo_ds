/*
 *  largest rectangle in a histogram(单调栈:及时排除不可能的选项，保持策略集合的高度有效性和秩序性): 直方图中的最大矩形

 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 100006;
int n, a[N], s[N], w[N];

void Largest(int n) {
    memset(s, 0, sizeof(s));
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    a[n+1] = 0;
    int p = 0;
    ll ans = 0;
    for (int i = 1; i <= n + 1; i++)
        if (a[i] > s[p]) {
            s[++p] = a[i];
            w[p] = 1;
        } else {
            int wid = 0;
            while (s[p] > a[i]) {
                wid += w[p];
                ans = max(ans, (ll)wid * s[p]);
                p--;
            }
            s[++p] = a[i];
            w[p] = wid + 1;
        }
    cout << ans << endl;
}

int main() {
    while (cin >> n && n) Largest(n);
    return 0;
}

/*
 * input:
7 2 1 4 5 1 3 3
 * output:
8
 */
