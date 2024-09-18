#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

//程序自动分析: 判断一些约束条件是否能被同时满足，判定是可以分别为每个变量赋予恰当的值，使得上述所有约束条件同时被满足。

const int N = 100006;
int n, m, a[N*2], fa[N*2];
struct P {
    int i, j;
    bool e;
} p[N];

int get(int x) {
    if (x == fa[x]) return x;
    return fa[x] = get(fa[x]);
}

int find(int x) {
    return lower_bound(a + 1, a + m + 1, x) - a;
}

void cxzdfx() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i].i >> p[i].j;
        cin >> p[i].e;
        a[2*i-1] = p[i].i;
        a[2*i] = p[i].j;
    }
    sort(a + 1, a + 2 * n + 1);
    m = unique(a + 1, a + 2 * n + 1) - (a + 1);
    for (int i = 1; i <= m; i++) fa[i] = i;
    for (int i = 1; i <= n; i++)
        if (p[i].e) fa[get(find(p[i].i))] = get(find(p[i].j));
    for (int i = 1; i <= n; i++)
        if (!p[i].e && get(find(p[i].i)) == get(find(p[i].j))) {
            puts("NO");
            return;
        }
    puts("YES");
}

int main() {
    int t;
    cin >> t;
    while (t--) cxzdfx();
    return 0;
}
