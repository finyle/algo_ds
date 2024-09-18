// 分形街道： 求解编号为m的房屋在n级城市中的位置

#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

pair<long long, long long> calc(int n, long long m) {
    if (n == 0) return make_pair(0, 0);
    long long len = 1ll << (n - 1), cnt = 1ll << (2 * n - 2);
    pair<long long, long long> pos = calc(n - 1, m % cnt); // 递归求解求出的位置
    long long x = pos.first, y = pos.second;
    long long z = m / cnt;
    if (z == 0) return make_pair(y, x); // 确定四座城中的具体一座
    if (z == 1) return make_pair(x, y + len);
    if (z == 2) return make_pair(x + len, y + len);
    if (z == 3) return make_pair(2 * len - y - 1, len - x - 1);
}

int main () {
    int data; for (scanf("%d", &data); data; --data) {
        int n; long long h, o;
        scanf("%d %I64d %I64d", &n, &h, &o);
        pair<long long, long long> hp = calc(n, h - 1);
        pair<long long, long long> op = calc(n, o - 1);
        long long dx = hp.first - op.first, dy = hp.second - op.second;
        printf("%.0f\n", (double)sqrt(dx * dx + dy * dy) * 10);
    }
    return 0;
}

/*
 * input:
10
3 62 11
5 252 21
3 57 27
3 32 47
3 46 56
3 21 42
5 802 297
5 507 802
5 403 555
3 53 35
 * output:
36
92
63
30
32
61
228
136
152
20
 */