#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

// 给定一棵n个节点的树，每个节点有一个权值A[i]。 把这棵树的节点全部染色，规则：根节点可以随时染色，被染色之前它的父节点必须已经染上了色，
// 每次的染色代价为T*A[i],T代表当前是第几次染色。求把这棵树染色的最小总代价。
const int N = 1006;
int n, r, fa[N], nxt[N], lst[N], num[N];
double c[N], d[N], tot[N];
bool v[N];

void Color_a_Tree() {
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &c[i]);
        nxt[i] = i;
        lst[i] = i;
        num[i] = 1;
        tot[i] = c[i];
    }
    memcpy(d, c, sizeof(d));
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        fa[b] = a;
    }
    memset(v, 0, sizeof(v));
    for (int i = 1; i < n; i++) {
        int p;
        double k = 0;
        for (int j = 1; j <= n; j++)
            if (j != r && !v[j] && c[j] > k) {
                k = c[j];
                p = j;
            }
        int f = fa[p];
        while (v[f]) fa[p] = f = fa[f];
        nxt[lst[f]] = p;
        lst[f] = lst[p];
        num[f] += num[p];
        tot[f] += tot[p];
        c[f] = tot[f] / num[f];
        v[p] = 1;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += i * d[r];
        r = nxt[r];
    }
    cout << ans << endl;
}

int main() {
    while (cin >> n >> r && n && r) Color_a_Tree();
    return 0;
}

/*
 * input:
10 6
593 716 845 603 858 545 848 424 624 646
4 5
3 9
1 10
3 4
3 8
3 1
7 3
2 7
6 2
 * output:
35230
 *
 */