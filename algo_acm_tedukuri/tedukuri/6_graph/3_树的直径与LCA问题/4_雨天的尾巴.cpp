
/*
 *
 */

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
const int SIZE = 100010;
struct SegmentTree {
    int lc, rc, dat, pos;
} tr[SIZE * 20 * 4];
int f[SIZE][20], d[SIZE], root[SIZE], ans[SIZE];
int ver[2 * SIZE], Next[2 * SIZE], head[SIZE];
int X[SIZE], Y[SIZE], Z[SIZE], val[SIZE];
int T, n, m, tot, t, num, cnt;
queue<int> q;

inline char gc() {
    static char buf[1 << 16], *S, *T;
    if (T == S) { T = (S = buf) + fread(buf, 1, 1 << 16, stdin); if (T == S) return EOF; }
    return *S++;
}
inline int read() {
    int x = 0, f = 1; char ch = gc();
    while (ch<'0' || ch>'9') { if (ch == '-') f = -1; ch = gc(); }
    while (ch >= '0'&&ch <= '9') x = x * 10 + ch - '0', ch = gc();
    return x * f;
}

void add(int x, int y) {
    ver[++tot] = y; Next[tot] = head[x]; head[x] = tot;
}

void bfs() {
    q.push(1); d[1] = 1;
    while (q.size()) {
        int x = q.front(); q.pop();
        for (int i = head[x]; i; i = Next[i]) {
            int y = ver[i];
            if (d[y]) continue;
            d[y] = d[x] + 1;
            f[y][0] = x;
            for (int j = 1; j <= t; j++)
                f[y][j] = f[f[y][j - 1]][j - 1];
            q.push(y);
        }
    }
}

int lca(int x, int y) {
    if (d[x] > d[y]) swap(x, y);
    for (int i = t; i >= 0; i--)
        if (d[f[y][i]] >= d[x]) y = f[y][i];
    if (x == y) return x;
    for (int i = t; i >= 0; i--)
        if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    return f[x][0];
}

void insert(int p, int l, int r, int val, int delta) {
    if (l == r) {
        tr[p].dat += delta;
        tr[p].pos = tr[p].dat ? l : 0;
        return;
    }
    int mid = (l + r) >> 1;
    if (val <= mid) {
        if (!tr[p].lc) tr[p].lc = ++num;
        insert(tr[p].lc, l, mid, val, delta);
    }
    else {
        if (!tr[p].rc) tr[p].rc = ++num;
        insert(tr[p].rc, mid + 1, r, val, delta);
    }
    tr[p].dat = max(tr[tr[p].lc].dat, tr[tr[p].rc].dat);
    tr[p].pos = tr[tr[p].lc].dat >= tr[tr[p].rc].dat ? tr[tr[p].lc].pos : tr[tr[p].rc].pos;
}

int merge(int p, int q, int l, int r) {
    if (!p) return q;
    if (!q) return p;
    if (l == r) {
        tr[p].dat += tr[q].dat;
        tr[p].pos = tr[p].dat ? l : 0;
        return p;
    }
    int mid = (l + r) >> 1;
    tr[p].lc = merge(tr[p].lc, tr[q].lc, l, mid);
    tr[p].rc = merge(tr[p].rc, tr[q].rc, mid + 1, r);
    tr[p].dat = max(tr[tr[p].lc].dat, tr[tr[p].rc].dat);
    tr[p].pos = tr[tr[p].lc].dat >= tr[tr[p].rc].dat ? tr[tr[p].lc].pos : tr[tr[p].rc].pos;
    return p;
}

void dfs(int x) {
    for (int i = head[x]; i; i = Next[i]) {
        int y = ver[i];
        if (d[y] <= d[x]) continue;
        dfs(y);
        root[x] = merge(root[x], root[y], 1, cnt);
    }
    ans[x] = tr[root[x]].pos;
}

int main() {
    n = read(), m = read();
    t = (int)(log(n) / log(2)) + 1;
    for (int i = 1; i < n; i++) {
        int x = read(), y = read();
        add(x, y), add(y, x);
    }
    bfs();
    for (int i = 1; i <= n; i++) root[i] = ++num;
    for (int i = 1; i <= m; i++) {
        X[i] = read(), Y[i] = read(), Z[i] = read();
        val[i] = Z[i];
    }
    sort(val + 1, val + m + 1);
    cnt = unique(val + 1, val + m + 1) - val - 1;
    for (int i = 1; i <= m; i++) {
        int x = X[i], y = Y[i];
        int z = lower_bound(val + 1, val + cnt + 1, Z[i]) - val;
        int p = lca(x, y);
        insert(root[x], 1, cnt, z, 1);
        insert(root[y], 1, cnt, z, 1);
        insert(root[p], 1, cnt, z, -1);
        if (f[p][0]) insert(root[f[p][0]], 1, cnt, z, -1);
    }
    dfs(1);
    for (int i = 1; i <= n; i++) printf("%d\n", val[ans[i]]);
}

/*
 * input:
50 100
19 12
1 19
30 12
33 19
46 33
25 30
50 33
14 33
36 25
4 12
2 50
37 12
27 37
20 12
29 14
44 12
13 33
18 2
22 37
26 22
7 37
8 14
10 19
28 12
5 20
32 18
17 44
9 25
48 22
34 48
40 22
42 32
3 14
15 28
43 8
45 7
21 12
47 42
49 7
31 37
38 34
16 14
35 17
23 31
41 32
39 22
11 29
6 38
24 17
20 41 1422
32 18 3427
22 32 3927
10 28 493
7 48 60
37 16 5387
34 20 7794
29 22 8691
30 4 5737
21 19 6650
16 41 1422
47 24 9173
46 47 28
22 6 5737
39 15 6650
42 1 60
1 35 7794
25 15 493
7 44 28
28 16 5737
37 33 28
38 29 3927
8 25 887
9 46 1422
38 36 60
19 29 6916
12 29 1422
27 5 6916
14 14 9173
7 41 7794
19 29 6650
20 18 3427
47 25 6916
21 34 2363
50 23 8336
45 41 8336
40 5 5387
20 33 2778
15 48 493
6 5 6650
12 23 6650
50 44 5387
19 41 2778
12 11 8336
2 12 2363
29 6 9384
37 45 5387
23 16 6650
17 33 9173
25 38 2778
25 1 541
3 50 5737
1 19 28
24 32 887
31 34 7764
11 14 5737
32 50 541
10 24 60
19 41 3927
27 17 7794
41 41 7794
27 43 541
8 46 541
30 19 493
13 49 8691
10 10 541
11 43 493
7 2 60
23 22 3927
20 50 887
5 40 28
41 18 8336
29 28 2363
35 9 9384
25 23 1422
47 32 2363
35 43 8691
23 1 8336
36 23 5737
41 43 9173
14 49 2363
25 41 1422
32 20 541
33 6 7764
5 30 1422
24 27 2363
6 11 2778
30 35 60
6 22 493
5 14 887
5 27 5737
45 3 2778
7 35 887
43 19 6650
40 23 6650
9 49 541
9 4 6650
4 34 60
49 41 7764
18 47 6650

 * output:
28
1422
2778
60
28
493
60
541
541
60
493
1422
8691
5737
493
1422
60
1422
887
887
2363
60
6650
60
1422
0
541
493
493
1422
6650
1422
1422
60
60
60
6650
2778
6650
28
1422
28
493
60
2778
28
28
60
541
1422
 *
 */