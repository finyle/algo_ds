/*
 * genius ACM：给定整数m，对于任意一个整数集合S，定义校验值如下：
 * 从集合S中取出M对数，使得每对数的差的平方之和最大，这个最大值就称为集合s的校验值；给定长度为n的数列A和一个整数T，把A分成若干段，使得每段的校验值都不超过t，最少需要分成几段？
 */
#include <cstdio>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 500006;
int n, m, w;
ll k, a[N], b[N], c[N];

void gb(int l, int mid, int r) { // 遍历
    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++)
        if (j > r || (i <= mid && b[i] <= b[j])) c[k] = b[i++];
        else c[k] = b[j++];
}

ll f(int l, int r) {
    if (r > n) r = n;
    int t = min(m, (r - l + 1) >> 1);
    for (int i = w + 1; i <= r; i++) b[i] = a[i];
    sort(b + w + 1, b + r + 1);
    gb(l, w, r); //
    ll ans = 0;
    for (int i = 0; i < t; i++)
        ans += (c[r-i] - c[l+i]) * (c[r-i] - c[l+i]);
    return ans;
}

void Genius_ACM() {
    cin >> n >> m;
    cin >> k;
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    int ans = 0, l = 1, r = 1;
    w = 1;
    b[1] = a[1];
    while (l <= n) {
        int p = 1;
        while (p) {
            ll num = f(l, r + p); //
            if (num <= k) {
                w = r = min(r + p, n);
                for (int i = l; i <= r; i++) b[i] = c[i];
                if (r == n) break;
                p <<= 1;
            } else p >>= 1;
        }
        ans++;
        l = r + 1;
    }
    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) Genius_ACM();
    return 0;
}

/*
 * input:
3
5 1 49
8 2 1 7 9
5 1 64
8 2 1 7 9
5 1 0
8 2 1 7 9

 * output:
2
1
5

 *
 */