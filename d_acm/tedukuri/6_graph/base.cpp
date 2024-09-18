#include<bits/stdc++.h>

using namespace std;

class Solution {
public:

//    最短路
//      最有贸易
    const int MAX_N = 100005, MAX_M = 1000005;
    int head[MAX_N], ver[MAX_M], edge[MAX_M], nxt[MAX_M], tot;
    int n, m, a[MAX_N], d[MAX_N]/*前缀min*/, f[MAX_N]/*后缀max*/;
    bool v[MAX_N]; // 点是否在队列中
    queue<int> q;

    void add(int x, int y, int z) {
        tot++;
        ver[tot] = y;
        edge[tot] = z; // 1表示只能正着走，-1表示只能倒着走，2表示正反都可以
        nxt[tot] = head[x];
        head[x] = tot;
    }

// 求d数组，从st出发，只有标记为z和2的边可以用
    void spfa(int* d, int st, int z) {
        d[st] = a[st];
        q.push(st); v[st] = true;
        while (!q.empty()) {
            int x = q.front();
            q.pop(); v[x] = false;
            for (int i = head[x]; i; i = nxt[i])
                if (edge[i] == z || edge[i] == 2) {
                    int y = ver[i];
                    int val = z == 1 ? min(d[x], a[y]) : max(d[x], a[y]);
                    if (z == 1 && d[y] > val || z == -1 && d[y] < val) {
                        d[y] = val;
                        if (!v[y]) { q.push(y); v[y] = true; }
                    }
                }
        }
    }

//    道路与航线：

    const int MAX_N = 25005, MAX_M = 150005;
    int head[MAX_N], ver[MAX_M], edge[MAX_M], mark[MAX_M], nxt[MAX_M], tot;
    int n, m, p, s, c[MAX_N], cnt, deg[MAX_N], d[MAX_N];
    bool v[MAX_N];
    queue<int> q; // 存的是块号
    vector<int> a[MAX_N]; // 每个“道路”连通块中的点
    priority_queue<pair<int, int>> heap;

    void add(int x, int y, int z, int k) { // k==0双向, k==1单向
        ver[++tot] = y, edge[tot] = z, mark[tot] = k;
        nxt[tot] = head[x], head[x] = tot;
    }

    void dfs(int x) {
        c[x] = cnt;
        a[cnt].push_back(x);
        for (int i = head[x]; i; i = nxt[i]) {
            if (mark[i] == 1) continue;
            int y = ver[i];
            if (!c[y]) dfs(y);
        }
    }

    void dijkstra(int k) { // 算k这一块的最短路
        for (int j = 0; j < a[k].size(); j++) { // for (auto x : a[k]) {
            int x = a[k][j]; // x是点号，k这块里面的所有点
            heap.push(make_pair(-d[x], x));
        }
        while (!heap.empty()) {
            int x = heap.top().second;
            heap.pop();
            if (v[x]) continue;
            v[x] = 1;
            for (int i = head[x]; i; i = nxt[i]) {
                int y = ver[i];
                if (mark[i] == 0) { // 正常的dijkstra模板
                    if (d[y] > d[x] + edge[i]) {
                        d[y] = d[x] + edge[i];
                        heap.push(make_pair(-d[y], y));
                    }
                } else {
                    d[y] = min(d[y], d[x] + edge[i]);
                    if (--deg[c[y]] == 0) q.push(c[y]); // 拓扑排序的更新
                }
            }
        }
    }

//    cow replays
    int n, t, s, e, len[105], a[105], b[105];
    int vals[205], m, p; // p: 离散化之后的总点数
    int ver[205], nxt[205], edge[205], head[205], tot;
    int f[205], d[205];
/*
void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, nxt[tot] = head[x], head[x] = tot;
}
*/
    int main() {
        cin >> n >> t >> s >> e;
        // 离散化
        vals[++m] = s;
        vals[++m] = s;
        for (int i = 1; i <= t; i++) {
            scanf("%d%d%d", &len[i], &a[i], &b[i]);
            vals[++m] = a[i];
            vals[++m] = b[i];
        }
        sort(vals + 1, vals + m + 1);
        p = unique(vals + 1, vals + m + 1) - (vals + 1);
        s = lower_bound(vals + 1, vals + p + 1, s) - vals;
        e = lower_bound(vals + 1, vals + p + 1, e) - vals;
        for (int i = 1; i <= t; i++) {
            a[i] = lower_bound(vals + 1, vals + p + 1, a[i]) - vals;
            b[i] = lower_bound(vals + 1, vals + p + 1, b[i]) - vals;
            // add(a[i], b[i], len[i]);
            // add(b[i], a[i], len[i]);
        }

        memset(d, 0x3f, sizeof(d));
        d[s] = 0;
        for (int i = 1; i <= n; i++) { // 实际上是Bellman-Ford
            memcpy(f, d, sizeof(f));
            memset(d, 0x3f, sizeof(d));
            /*for (int j = 1; j <= p; j++) {
                for (int k = head[j]; k; k = nxt[k])
                    if (d[j] > f[ver[k]] + edge[k]) d[j] = f[ver[k]] + edge[k];
            }*/
            for (int i = 1; i <= t; i++) {
                if (d[b[i]] > f[a[i]] + len[i]) d[b[i]] = f[a[i]] + len[i];
                if (d[a[i]] > f[b[i]] + len[i]) d[a[i]] = f[b[i]] + len[i];
            }
        }
        cout << d[e] << endl;
    }

//    sightseeing trip
    int a[310][310], d[310][310], pos[310][310];
    int n, m, ans = 0x3f3f3f3f;
    vector<int> path; //具体方案
    void get_path(int x, int y) {
        if (pos[x][y] == 0) return;
        get_path(x, pos[x][y]);
        path.push_back(pos[x][y]);
        get_path(pos[x][y], y);
    }
    int main() {
        cin >> n >> m;
        memset(a, 0x3f, sizeof(a));
        for (int i = 1; i <= n; i++) a[i][i] = 0;
        for (int i = 1; i <= m; i++) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            a[y][x] = a[x][y] = min(a[x][y], z);
        }
        memcpy(d, a, sizeof(a));
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i < k; i++)
                for (int j = i + 1; j < k; j++)
                    if ((long long)d[i][j] + a[j][k] + a[k][i] < ans) {
                        ans = d[i][j] + a[j][k] + a[k][i];
                        path.clear();
                        path.push_back(i);
                        get_path(i, j);
                        path.push_back(j);
                        path.push_back(k);
                    }
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (d[i][j] > d[i][k] + d[k][j]) {
                        d[i][j] = d[i][k] + d[k][j];
                        pos[i][j] = k;
                    }
        }
        if (ans == 0x3f3f3f3f) {
            puts("No solution.");
            return 0;
        }
        for (int i = 0; i < path.size(); i++)
            printf("%d ", path[i]);
        puts("");
    }

//    sorting it all out
    const int N = 30;
    int n, m, d[N][N], e[N][N];

    int floyd() {
        memcpy(e, d, sizeof(e));
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) {
                    e[i][j] |= e[i][k] & e[k][j];
                    if (e[i][j] == e[j][i] && e[i][j] && i != j) return -1;
                }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (e[i][j] == e[j][i] && !e[i][j] && i != j) return 0;
        return 1;
    }

    void Sorting_It_All_Out() {
        memset(d, 0, sizeof(d));
        bool flag = 1;
        for (int i = 1; i <= m; i++) {
            char s[6];
            scanf("%s", s);
            d[s[0]-'A'][s[2]-'A'] = 1;
            if (flag) {
                int now = floyd();
                if (now == -1) {
                    printf("Inconsistency found after %d relations.\n", i);
                    flag = 0;
                } else if (now == 1) {
                    printf("Sorted sequence determined after %d relations: ", i);
                    pair<int, char> ans[N];
                    for (int j = 0; j < n; j++) {
                        ans[j].first = 0;
                        ans[j].second = 'A' + j;
                    }
                    for (int j = 0; j < n; j++)
                        for (int k = 0; k < n; k++)
                            if (e[j][k]) ++ans[j].first;
                    sort(ans, ans + n);
                    for (int j = n - 1; j >= 0; j--) printf("%c", ans[j].second);
                    puts(".");
                    flag = 0;
                }
            }
        }
        if (flag) puts("Sorted sequence cannot be determined.");
    }

//    最小生成树
//      走廊泼水节
    struct rec { int x, y, z; } edge[6010];
    int fa[6010], s[6010], n, T;
    long long ans;
    bool operator <(rec a, rec b) {
        return a.z < b.z;
    }
    int get(int x) {
        if (x == fa[x]) return x;
        return fa[x] = get(fa[x]);
    }
    int main() {
        cin >> T;
        while (T--) {
            cin >> n;
            for (int i = 1; i < n; i++)
                scanf("%d%d%d", &edge[i].x, &edge[i].y, &edge[i].z);
            sort(edge + 1, edge + n);
            for (int i = 1; i <= n; i++)
                fa[i] = i, s[i] = 1;
            ans = 0;
            for (int i = 1; i < n; i++) {
                int x = get(edge[i].x);
                int y = get(edge[i].y);
                if (x == y) continue;
                ans += (long long)(edge[i].z + 1) * (s[x] * s[y] - 1);
                fa[x] = y;
                s[y] += s[x];
            }
            cout << ans << endl;
        }
    }

//      picnic planning
    int n, m, s, deg, ans;
    int a[32][32], d[32], conn[32];
    bool v[32], c[32];
    int tree[32][32];
    int ver[32], p;
    int f[32], fx[32], fy[32]; // (fx[i], fy[i])就是1~i路径上的最大边，边权是f[i]

    void read() {
        map<string, int> h;
        cin >> m;
        h["Park"] = 1; n = 1;
        memset(a, 0x3f, sizeof(a)); // 原图对应的邻接矩阵
        for (int i = 1; i <= m; i++) {
            int x, y, z;
            char sx[12], sy[12];
            scanf("%s%s%d", sx, sy, &z);
            if (!h[sx]) h[sx] = ++n;
            if (!h[sy]) h[sy] = ++n;
            x = h[sx], y = h[sy];
            a[x][y] = min(a[x][y], z);
            a[y][x] = min(a[y][x], z);
        }
        cin >> s;
    }

    void prim(int root) { // 对ver中的p个点求最小生成树
        d[root] = 0;
        for (int i = 1; i <= p; i++) {
            int x = 0;
            for (int j = 1; j <= p; j++)
                if (!v[ver[j]] && (x == 0 || d[ver[j]] < d[x])) x = ver[j];
            v[x] = true; // 进入已选集合
            for (int j = 1; j <= p; j++) {
                int y = ver[j];
                if (!v[y] && d[y] > a[x][y])
                    d[y] = a[x][y], conn[y] = x;
            }
        }
        // 连通块内部的最小生成树，连边
        int closest = root;
        for (int i = 1; i <= p; i++) {
            int x = ver[i];
            if (root == x) continue;
            ans += d[x];
            tree[conn[x]][x] = tree[x][conn[x]] = d[x];
            if (a[1][x] < a[1][closest]) closest = x;
        }
        // 每个连通块跟1号点连1条边
        deg++;
        ans += a[1][closest];
        tree[1][closest] = tree[closest][1] = a[1][closest];
    }

    void dfs(int x) { // 找连通块
        ver[++p] = x;
        c[x] = true;
        for (int y = 1; y <= n; y++)
            if (a[x][y] != 0x3f3f3f3f && !c[y]) dfs(y);
    }

    void prim_for_all_comp() {
        memset(d, 0x3f, sizeof(d));
        memset(v, 0, sizeof(v));
        memset(tree, 0x3f, sizeof(tree)); // 最小生成树对应的邻接矩阵
        c[1] = true;
        for (int i = 2; i <= n; i++)
            if (!c[i]) {
                p = 0;
                dfs(i);
                // ver中保存了连通块里面的点
                prim(i);
            }
    }

    void dp(int x) {
        v[x] = true;
        for (int y = 2; y <= n; y++)
            if (tree[x][y] != 0x3f3f3f3f && !v[y]) {
                if (f[x] > tree[x][y]) {
                    f[y] = f[x];
                    fx[y] = fx[x], fy[y] = fy[x];
                } else {
                    f[y] = tree[x][y];
                    fx[y] = x, fy[y] = y;
                }
                dp(y);
            }
        v[x] = false;
    }

    bool solve() {
        int min_val = 1 << 30, mini;
        for (int i = 2; i <= n; i++) { // 枚举从1出发的非树边(1, i)，看加哪一条
            if (tree[1][i] != 0x3f3f3f3f || a[1][i] == 0x3f3f3f3f) continue;
            // 加入非树边(1, i)，删去树边(fx[i], fy[i])
            if (a[1][i] - tree[fx[i]][fy[i]] < min_val) {
                min_val = a[1][i] - tree[fx[i]][fy[i]];
                mini = i;
            }
        }
        if (min_val >= 0) return false;
        ans += min_val;
        tree[1][mini] = tree[mini][1] = a[1][mini];
        tree[fx[mini]][fy[mini]] = tree[fy[mini]][fx[mini]] = 0x3f3f3f3f;
        // 重新计算以mini为根的子树的dp状态
        f[mini] = a[1][mini];
        fx[mini] = 1, fy[mini] = mini;
        v[1] = true;
        dp(mini);
        return true;
    }

//      最有比率生成树
    const int N = 1006, INF = 0x3f3f3f3f;
    const double eps = 1e-6;
    int n;
    struct P {
        int x, y, z;
    } p[N];
    double a[N][N], b[N][N], c[N][N], d[N];
    bool v[N];

    inline double s(int i, int j) {
        return sqrt((p[i].x - p[j].x) * (p[i].x - p[j].x) + (p[i].y - p[j].y) * (p[i].y - p[j].y));
    }

    double work(double k) {
        for (int i = 1; i <= n; i++)
            for (int j = i; j <= n; j++)
                if (i == j) c[i][j] = INF;
                else c[i][j] = c[j][i] = a[i][j] - k * b[i][j];
        memset(v, 0, sizeof(v));
        for (int i = 1; i <= n; i++) d[i] = INF;
        d[1] = 0;
        double ans = 0;
        while (1) {
            int x = 0;
            for (int i = 1; i <= n; i++)
                if (!v[i] && (!x || d[x] > d[i])) x = i;
            if (!x) break;
            v[x] = 1;
            ans += d[x];
            for (int i = 1; i <= n; i++) d[i] = min(d[i], c[x][i]);
        }
        return ans;
    }

    void Desert_King() {
        for (int i = 1; i <= n; i++)
            scanf("%d %d %d", &p[i].x, &p[i].y, &p[i].z);
        double num = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                num += (a[i][j] = a[j][i] = abs(p[i].z - p[j].z));
                b[i][j] = b[j][i] = s(i, j);
            }
        double l = 0, r = num;
        while (l + eps <= r) {
            double mid = (l + r) / 2;
            if (work(mid) >= 0) l = mid;
            else r = mid;
        }
        printf("%.3f\n", l);
    }

//    黑暗城堡
#define ll long long
    using namespace std;
    const int N = 1006;
    const ll P = (1ll << 31) - 1;
    int n, m, a[N][N], d[N];
    bool v[N];

    int main() {
        cin >> n >> m;
        memset(a, 0x3f, sizeof(a));
        for (int i = 1; i <= n; i++) a[i][i] = 0;
        for (int i = 1; i <= m; i++) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            a[x][y] = a[y][x] = min(a[x][y], z);
        }
        memset(d, 0x3f, sizeof(d));
        d[1] = 0;
        for (int i = 1; i < n; i++) {
            int t = 0;
            for (int j = 1; j <= n; j++)
                if (!v[j] && (!t || d[j] < d[t])) t = j;
            v[t] = 1;
            for (int j = 1; j <= n; j++)
                d[j] = min(d[j], d[t] + a[t][j]);
        }
        memset(v, 0, sizeof(v));
        v[1] = 1;
        ll ans = 1;
        for (int i = 1; i < n; i++) {
            int t = 0, k = 0;
            for (int j = 2; j <= n; j++)
                if (!v[j] && (!t || d[j] < d[t])) t = j;
            for (int j = 1; j <= n; j++)
                if (v[j] && d[j] + a[j][t] == d[t]) ++k;
            v[t] = 1;
            (ans *= k) %= P;
        }
        cout << ans << endl;
        return 0;
    }

//      树的直径与最近公共祖先
//      巡逻
    const int MAXN = 100005;
    int ver[2*MAXN], nxt[2*MAXN], edge[2*MAXN], head[MAXN], tot;
    int n, k;
    queue<int> q;
    int d[MAXN], pre[MAXN], L2;

    void add(int x, int y) {
        ver[++tot]=y, edge[tot]=1, nxt[tot]=head[x], head[x]=tot;
    }

    int bfs(int s) {
        memset(d, -1, sizeof(d));
        q.push(s); d[s] = 0;
        while (!q.empty()) {
            int x=q.front();
            q.pop();
            for (int i=head[x];i;i=nxt[i]) {
                int y=ver[i];
                if (d[y]==-1) {
                    d[y]=d[x]+1;
                    pre[y]=i;
                    q.push(y);
                }
            }
        }
        int p=s;
        for(int i=1;i<=n;i++)
            if(d[i]>d[p]) p=i;
        return p;
    }

    void update(int q, int p) {
        while (q!=p) {
            edge[pre[q]] = -1;
            edge[pre[q]^1] = -1;
            q = ver[pre[q]^1];
        }
    }

    void dp(int x, int fa) {
        for (int i=head[x];i;i=nxt[i]) {
            int y=ver[i];
            if (y == fa) continue;
            dp(y, x);
            L2 = max(L2, d[y] + edge[i] + d[x]);
            d[x] = max(d[x], d[y] + edge[i]);
        }
    }

//      树网的核
    const int MAXN = 500005;
    int ver[2*MAXN], nxt[2*MAXN], edge[2*MAXN], head[MAXN], tot;
    int n, s, t;
    queue<int> q;
    int d[MAXN], pre[MAXN], a[MAXN], b[MAXN], f[MAXN], sum[MAXN];
    bool v[MAXN];

    void add(int x, int y, int z) {
        ver[++tot]=y, edge[tot]=z, nxt[tot]=head[x], head[x]=tot;
    }

    int bfs(int s) {
        memset(d, -1, sizeof(d));
        q.push(s); d[s] = 0;
        while (!q.empty()) {
            int x=q.front();
            q.pop();
            for (int i=head[x];i;i=nxt[i]) {
                int y=ver[i];
                if (d[y]==-1) {
                    d[y]=d[x]+edge[i];
                    pre[y]=i;
                    q.push(y);
                }
            }
        }
        int p=s;
        for(int i=1;i<=n;i++)
            if(d[i]>d[p]) p=i;
        return p;
    }

    void dfs(int x) {
        v[x] = true;
        for (int i=head[x];i;i=nxt[i]) {
            int y=ver[i];
            if (v[y]) continue;
            dfs(y);
            f[x] = max(f[x], f[y] + edge[i]);
        }
    }

};

//      音的锁链
const int N = 100006;
int n, m, fa[N], ans[N<<1], v[N], d[N], f[N], ANS = 0;
int Head[N], Edge[N<<1], Next[N<<1], tot = 0;
vector<pair<int, int> > q[N];
pair<int, int> Q[N<<1];

inline void add(int x, int y) {
    Edge[++tot] = y;
    Next[tot] = Head[x];
    Head[x] = tot;
}

int get(int x) {
    if (x == fa[x]) return x;
    return fa[x] = get(fa[x]);
}

void tarjan(int x) {
    v[x] = 1;
    for (int i = Head[x]; i; i = Next[i]) {
        int y = Edge[i];
        if (v[y]) continue;
        tarjan(y);
        fa[y] = x;
    }
    for (unsigned int i = 0; i < q[x].size(); i++) {
        int y = q[x][i].first, id = q[x][i].second;
        if (v[y] == 2) ans[id] = get(y);
    }
    v[x] = 2;
}

void dfs(int x) {
    v[x] = 1;
    for (int i = Head[x]; i; i = Next[i]) {
        int y = Edge[i];
        if (v[y]) continue;
        dfs(y);
        f[x] += f[y];
    }
    f[x] += d[x];
    if (!f[x]) ANS += m;
    else if (f[x] == 1) ++ANS;
}

//      雨天的尾巴
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

//      天天爱跑步
const int SIZE = 300010;
int ver[SIZE * 2], Next[SIZE * 2], head[SIZE], tot;
int f[SIZE][20], d[SIZE], w[SIZE], v[SIZE];
int c1[SIZE * 2], c2[SIZE * 2], ans[SIZE];
int n, m, t;
queue<int> q;
vector<int> a1[SIZE], b1[SIZE], a2[SIZE], b2[SIZE];

void add(int x, int y) {
    ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void bfs() {
    t = log(n) / log(2);
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

void dfs(int x) {
    int val1 = c1[d[x] + w[x]], val2 = c2[w[x] - d[x] + n];
    v[x] = 1;
    for (int i = head[x]; i; i = Next[i]) {
        int y = ver[i];
        if (v[y]) continue;
        dfs(y);
    }
    for (int i = 0; i < a1[x].size(); i++) c1[a1[x][i]]++;
    for (int i = 0; i < b1[x].size(); i++) c1[b1[x][i]]--;
    for (int i = 0; i < a2[x].size(); i++) c2[a2[x][i] + n]++;
    for (int i = 0; i < b2[x].size(); i++) c2[b2[x][i] + n]--;
    ans[x] += c1[d[x] + w[x]] - val1 + c2[w[x] - d[x] + n] - val2;
}

//      异相石
const int N = 100006;
int n, m, t, f[N][20], dep[N], dfn[N], tot;
vector<pair<int, ll> > e[N];
ll d[N], ans;
set<pair<int, int> > st;
set<pair<int, int> >::iterator it;

inline int lca(int x, int y) {
    if (dep[x] > dep[y]) swap(x, y);
    for (int i = t; i >= 0; i--)
        if (dep[f[y][i]] >= dep[x]) y = f[y][i];
    if (x == y) return x;
    for (int i = t; i >= 0; i--)
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    return f[x][0];
}

inline ll path(int x, int y) {
    return d[x] + d[y] - (d[lca(x,y)] << 1);
}

inline void Insert(int x) {
    st.insert(make_pair(dfn[x], x));
    it = st.find(make_pair(dfn[x], x));
    set<pair<int, int> >::iterator l = it == st.begin() ? --st.end() : --it;
    it = st.find(make_pair(dfn[x], x));
    set<pair<int, int> >::iterator r = it == --st.end() ? st.begin() : ++it;
    it = st.find(make_pair(dfn[x], x));
    ans -= path((*l).second, (*r).second);
    ans += path((*l).second, (*it).second) + path((*it).second, (*r).second);
}

inline void Remove(int x) {
    it = st.find(make_pair(dfn[x], x));
    set<pair<int, int> >::iterator l = it == st.begin() ? --st.end() : --it;
    it = st.find(make_pair(dfn[x], x));
    set<pair<int, int> >::iterator r = it == --st.end() ? st.begin() : ++it;
    it = st.find(make_pair(dfn[x], x));
    ans += path((*l).second, (*r).second);
    ans -= path((*l).second, (*it).second) + path((*it).second, (*r).second);
    st.erase(make_pair(dfn[x], x));
}

void dfs(int x) {
    dfn[x] = ++tot;
    for (unsigned int i = 0; i < e[x].size(); i++) {
        int y = e[x][i].first;
        if (dep[y]) continue;
        dep[y] = dep[x] + 1;
        ll z = e[x][i].second;
        d[y] = d[x] + z;
        f[y][0] = x;
        for (int j = 1; j <= t; j++)
            f[y][j] = f[f[y][j-1]][j-1];
        dfs(y);
    }
}

//      严格次小生成树
const int N = 100006, M = 300006;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, m, t, fa[N], d[N], f[N][20];
struct P {
    int x, y;
    ll z;
    bool k;
    bool operator < (const P w) const {
        return z < w.z;
    }
} p[M];
ll g[N][20][2], sum, ans = INF;
vector<pair<int, ll> > e[N];

int get(int x) {
    if (x == fa[x]) return x;
    return fa[x] = get(fa[x]);
}

void kruskal() {
    sort(p + 1, p + m + 1);
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= m; i++) {
        int x = get(p[i].x), y = get(p[i].y);
        if (x == y) continue;
        fa[x] = y;
        sum += p[i].z;
        p[i].k = 1;
    }
}

void dfs(int x) {
    for (unsigned int i = 0; i < e[x].size(); i++) {
        int y = e[x][i].first;
        if (d[y]) continue;
        d[y] = d[x] + 1;
        f[y][0] = x;
        int z = e[x][i].second;
        g[y][0][0] = z;
        g[y][0][1] = -INF;
        for (int j = 1; j <= t; j++) {
            f[y][j] = f[f[y][j-1]][j-1];
            g[y][j][0] = max(g[y][j-1][0], g[f[y][j-1]][j-1][0]);
            if (g[y][j-1][0] == g[f[y][j-1]][j-1][0])
                g[y][j][1] = max(g[y][j-1][1], g[f[y][j-1]][j-1][1]);
            else if (g[y][j-1][0] < g[f[y][j-1]][j-1][0])
                g[y][j][1] = max(g[y][j-1][0], g[f[y][j-1]][j-1][1]);
            else g[y][j][1] = max(g[y][j-1][1], g[f[y][j-1]][j-1][0]);
        }
        dfs(y);
    }
}

inline void lca(int x, int y, ll &val1, ll &val2) {
    if (d[x] > d[y]) swap(x, y);
    for (int i = t; i >= 0; i--)
        if (d[f[y][i]] >= d[x]) {
            if (val1 > g[y][i][0]) val2 = max(val2, g[y][i][0]);
            else {
                val1 = g[y][i][0];
                val2 = max(val2, g[y][i][1]);
            }
            y = f[y][i];
        }
    if (x == y) return;
    for (int i = t; i >= 0; i--)
        if (f[x][i] != f[y][i]) {
            val1 = max(val1, max(g[x][i][0], g[y][i][0]));
            val2 = max(val2, g[x][i][0] != val1 ? g[x][i][0] : g[x][i][1]);
            val2 = max(val2, g[y][i][0] != val1 ? g[y][i][0] : g[y][i][1]);
            x = f[x][i];
            y = f[y][i];
        }
    val1 = max(val1, max(g[x][0][0], g[y][0][0]));
    val2 = max(val2, g[x][0][0] != val1 ? g[x][0][0] : g[x][0][1]);
    val2 = max(val2, g[y][0][0] != val1 ? g[y][0][0] : g[y][0][1]);
}

//      疫情控制
const int MAXN = 50005;
int ver[2*MAXN], edge[2*MAXN], nxt[2*MAXN], head[MAXN], tot;
int d[MAXN], f[MAXN][18], son[MAXN], army[MAXN];
long long dist[MAXN];
int n, m, cnt, p;
queue<int> q;
long long l, r;
pair<long long, int> a[MAXN]; // <rest, s>
bool has[MAXN], cover[MAXN], used[MAXN];

void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, nxt[tot] = head[x], head[x] = tot;
}

void bfs() {
    d[1] = 1;
    q.push(1);
    while (q.size()) {
        int x = q.front(); q.pop();
        for (int i=head[x]; i; i=nxt[i]) {
            int y = ver[i];
            if (!d[y]) {
                q.push(y);
                d[y] = d[x] + 1;
                dist[y] = dist[x] + edge[i];
                f[y][0] = x;
                for (int k = 1; k <= 17; k++)
                    f[y][k] = f[f[y][k-1]][k-1];
            }
        }
    }
}

pair<long long, int> go(int x, long long mid) {
    for (int i = 17; i >= 0; i--)
        if (f[x][i] > 1 && dist[x] - dist[f[x][i]] <= mid) {
            mid -= dist[x] - dist[f[x][i]];
            x = f[x][i];
        }
    return make_pair(mid, x);
}

void dfs(int x) {
    bool all_child_covered = true;
    bool is_leaf = true;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (d[y] <= d[x]) continue;
        dfs(y);
        all_child_covered &= cover[y];
        is_leaf = false;
        if (x == 1 && !cover[y]) son[++p] = y;
    }
    cover[x] = has[x] || (!is_leaf && all_child_covered);
}

bool cmp(int x, int y) {
    return dist[x] < dist[y];
}

bool solve(long long mid) {
    memset(has, 0, sizeof(has));
    memset(cover, 0, sizeof(cover));
    memset(used, 0, sizeof(used));
    cnt = p = 0;
    for (int i = 1; i <= m; i++) {
        pair<long long, int> pr = go(army[i], mid);
        long long rest = pr.first;
        int pos = pr.second;
        if (rest <= dist[pos]) has[pos] = true; // 一类军队
        else a[++cnt] = make_pair(rest - dist[pos], pos); // 二类军队（减去到根的时间）
    }
    dfs(1);
    sort(a + 1, a + cnt + 1);
    for (int i = 1; i <= cnt; i++) {
        long long rest = a[i].first;
        int s = a[i].second;
        if (!cover[s] && rest < dist[s])
            cover[s] = used[i] = true; // 上去就下不来了，就不要上去
    }
    sort(son + 1, son + p + 1, cmp);
    for (int i = 1, j = 1; i <= p; i++) {
        int s = son[i];
        if (cover[s]) continue;
        while (j <= cnt && (used[j] || a[j].first < dist[s])) j++;
        if (j > cnt) return false;
        j++; // 用j管辖s
    }
    return true;
}

//      基环树
//          freda 的传呼机
const int MAXN = 12005;
int ver[4*MAXN], nxt[4*MAXN], edge[4*MAXN], head[MAXN], tot;
int d[MAXN], dist[MAXN], f[MAXN][20], dfn[MAXN], fa[MAXN], sum[MAXN], in[MAXN], len_cycle[MAXN];
bool broken[4*MAXN], v[MAXN];
int n, m, t, num, cnt;
queue<int> q;

void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, nxt[tot] = head[x], head[x] = tot;
}

void spfa() {
    memset(dist, 0x7f, sizeof(dist));
    dist[1] = 0;
    q.push(1); v[1] = true;
    while (!q.empty()) {
        int x = q.front();
        q.pop(); v[x] = false;
        for (int i = head[x]; i; i = nxt[i]) {
            int y = ver[i], z = edge[i];
            if (dist[y] > dist[x] + z) {
                dist[y] = dist[x] + z;
                if (!v[y]) { q.push(y); v[y] = true; }
            }
        }
    }
}

// s1, s2, ..., sp即为环上点
void get_cycle(int x, int y, int i) {
    cnt++; // 环的数量+1
    sum[y] = edge[i];
    broken[i] = broken[i ^ 1] = true;
    while (y != x) {
        in[y] = cnt;
        int next_y = ver[fa[y] ^ 1];
        sum[next_y] = sum[y] + edge[fa[y]];
        broken[fa[y]] = broken[fa[y] ^ 1] = true;
        add(x, y, dist[y] - dist[x]), add(y, x, dist[y] - dist[x]);
        y = next_y;
    }
    in[x] = cnt;
    len_cycle[cnt] = sum[x]; // 环总长度
}

void dfs(int x) {
    dfn[x] = ++num;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (!dfn[y]) {
            fa[y] = i;
            dfs(y);
        } else if ((i ^ 1) != fa[x] && dfn[y] >= dfn[x])
            get_cycle(x, y, i);
    }
}

void bfs() {
    d[1] = 1;
    q.push(1);
    while (q.size()) {
        int x = q.front(); q.pop();
        for (int i=head[x]; i; i=nxt[i]) {
            int y = ver[i];
            if (!d[y] && !broken[i]) {
                q.push(y);
                d[y] = d[x] + 1;
                f[y][0] = x;
                for (int k = 1; k <= 19; k++)
                    f[y][k] = f[f[y][k-1]][k-1];
            }
        }
    }
}

int calc(int x, int y) {
    if (d[x] < d[y]) swap(x, y);
    int ox = x, oy = y;
    for (int i = 19; i >= 0; i--)
        if (d[f[x][i]] >= d[y]) x = f[x][i];
    if (x == y) return dist[ox] - dist[oy];
    for (int i = 19; i >= 0; i--)
        if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    if (!in[x] || in[x] != in[y])
        return dist[ox] + dist[oy] - 2 * dist[f[x][0]];
    int l = abs(sum[y] - sum[x]); // 环上某个方向的距离
    return dist[ox] - dist[x] + dist[oy] - dist[y] + min(l, len_cycle[in[x]] - l);
}

//      创世纪
const int N = 1000005;
int ver[N * 2], nxt[N * 2], head[N], tot;
int n, p, num, dfn[N], fa[N], a[N], ans_tot;
int f[N][2], root, broken;
bool v[N];

void add(int x, int y) {
    ver[++tot] = y, nxt[tot] = head[x], head[x] = tot;
}

void get_cycle(int x, int y, int i) {
    if (a[x] == y) root = x; // x-->y
    else root = y; // y-->x
    broken = i;
}

void dfs(int x) {
    dfn[x] = ++num;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (!dfn[y]) {
            fa[y] = i;
            dfs(y);
        } else if ((i ^ 1) != fa[x] && dfn[y] >= dfn[x]) // 加上等于号处理自环
            get_cycle(x, y, i);
    }
}

void dp(int x, int times) {
    f[x][0] = f[x][1] = 0;
    v[x] = true;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (!v[y] && i != broken && (i ^ 1) != broken) {
            dp(y, times);
            f[x][0] += max(f[y][0], f[y][1]);
        }
    }
    if (times == 2 && x == a[root]) {
        f[x][1] = f[x][0] + 1;
    } else {
        for (int i = head[x]; i; i = nxt[i]) {
            int y = ver[i];
            if (!v[y] && i != broken && (i ^ 1) != broken) {
                f[x][1] = max(f[x][1], f[y][0] + f[x][0] - max(f[y][0], f[y][1]) + 1);
            }
        }
    }
    v[x] = false;
}

//      岛屿
const int N = 1000006;
int Head[N], Edge[N<<1], Leng[N<<1], Next[N<<1], tot;
int n, du[N], c[N], q[N<<1];
ll f[N], d[N], a[N<<1], b[N<<1], ans;
bool v[N];

inline void add(int x, int y, int z) {
    Edge[++tot] = y;
    Leng[tot] = z;
    Next[tot] = Head[x];
    Head[x] = tot;
    ++du[y];
}

void bfs(int s, int t) {
    int l = 1, r = 1;
    c[q[1]=s] = t;
    while (l <= r) {
        for (int i = Head[q[l]]; i; i = Next[i])
            if (!c[Edge[i]]) c[q[++r]=Edge[i]] = t;
        ++l;
    }
}

void topsort() {
    int l = 1, r = 0;
    for (int i = 1; i <= n; i++)
        if (du[i] == 1) q[++r] = i;
    while (l <= r) {
        for (int i = Head[q[l]]; i; i = Next[i])
            if (du[Edge[i]] > 1) {
                d[c[q[l]]] = max(d[c[q[l]]], f[q[l]] + f[Edge[i]] + Leng[i]);
                f[Edge[i]] = max(f[Edge[i]], f[q[l]] + Leng[i]);
                if (--du[Edge[i]] == 1) q[++r] = Edge[i];
            }
        ++l;
    }
}

void dp(int t, int x) {
    int m = 0, y = x, k, z = 0;
    do {
        a[++m] = f[y];
        du[y] = 1;
        for (k = Head[y]; k; k = Next[k])
            if (du[Edge[k]] > 1) {
                b[m+1] = b[m] + Leng[k];
                y = Edge[k];
                break;
            }
    } while (k);
    if (m == 2) {
        for (int i = Head[y]; i; i = Next[i])
            if (Edge[i] == x) z = max(z, Leng[i]);
        d[t] = max(d[t], f[x] + f[y] + z);
        return;
    }
    for (int i = Head[y]; i; i = Next[i])
        if (Edge[i] == x) {
            b[m+1] = b[m] + Leng[i];
            break;
        }
    for (int i = 1; i < m; i++) {
        a[m+i] = a[i];
        b[m+i] = b[m+1] + b[i];
    }
    int l = 1, r = 1;
    q[1] = 1;
    for (int i = 2; i < (m << 1); i++) {
        if (l <= r && i - q[l] >= m) ++l;
        d[t] = max(d[t], a[i] + a[q[l]] + b[i] - b[q[l]]);
        while (l <= r && a[q[r]] - b[q[r]] <= a[i] - b[i]) --r;
        q[++r] = i;
    }
}

//      interval
const int MAX_N = 50005;
int head[MAX_N], ver[3 * MAX_N], edge[3 * MAX_N], nxt[3 * MAX_N], tot;
int n, d[MAX_N], cnt[MAX_N];
bool v[MAX_N];
queue<int> q;

void add(int x, int y, int z) {
    tot++;
    ver[tot] = y;
    edge[tot] = z;
    nxt[tot] = head[x];
    head[x] = tot;
}

inline int num(int x) {
    return x == -1 ? 50001 : x;
}

bool spfa() {
    memset(d, 0xcc, sizeof(d));
    d[num(-1)] = 0;
    q.push(num(-1)); v[num(-1)] = true;
    while (!q.empty()) {
        int x = q.front();
        q.pop(); v[x] = false;
        for (int i = head[x]; i; i = nxt[i]) {
            int y = ver[i], z = edge[i];
            if (d[y] < d[x] + z) {
                d[y] = d[x] + z;
                cnt[y] = cnt[x] + 1;
                if (cnt[y] >= 50002) return true;
                if (!v[y]) { q.push(y); v[y] = true; }
            }
        }
    }
    return false;
}


//      sightseeing cows
const int MAX_N = 1005, MAX_M = 5005;
int fun[MAX_N];
struct {int x, y, time;} a[MAX_M];
int head[MAX_N], ver[MAX_M], nxt[MAX_M], cnt[MAX_N], tot;
double edge[MAX_M], d[MAX_N];
int n, m;
bool v[MAX_N]; // 点是否在队列中
queue<int> q;

// 插入一条从x到y长度z的有向边
void add(int x, int y, double z) {
    tot++;
    ver[tot] = y;
    edge[tot] = z;
    nxt[tot] = head[x]; // 在head[x]这条链的开头插入新点
    head[x] = tot;
}

// 判断有没有负环
bool spfa_neg_cycle() {
    while (!q.empty()) q.pop();
    for (int i = 1; i <= n; i++) {
        d[i] = 0; cnt[i] = 0;
        q.push(i);
        v[i] = true;
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop(); v[x] = false;
        for (int i = head[x]; i; i = nxt[i]) {
            int y = ver[i];
            double z = edge[i];
            if (d[y] > d[x] + z) {
                d[y] = d[x] + z;
                cnt[y] = cnt[x] + 1;
                if (cnt[y] >= n) return true;
                if (!v[y]) { q.push(y); v[y] = true; }
            }
        }
    }
    return false;
}

//      tarjan 与 无向图
//      blo
const int N = 100010, M = 500010;
int head[N], ver[M * 2], Next[M * 2];
int dfn[N], low[N], Size[N];
long long ans[N];
bool cut[N];
int n, m, tot, num;

void add(int x, int y) {
    ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void tarjan(int x) {
    dfn[x] = low[x] = ++num;
    Size[x] = 1;
    int flag = 0, sum = 0;
    for (int i = head[x]; i; i = Next[i]) {
        int y = ver[i];
        if (!dfn[y]) {
            tarjan(y);
            Size[x] += Size[y];
            low[x] = min(low[x], low[y]);
            if (low[y] >= dfn[x]) {
                flag++;
                ans[x] += (long long)Size[y] * (n - Size[y]);
                sum += Size[y];
                if (x != 1 || flag > 1) cut[x] = true;
            }
        }
        else low[x] = min(low[x], dfn[y]);
    }
    if (cut[x])
        ans[x] += (long long)(n - sum - 1)*(sum + 1) + (n - 1);
    else
        ans[x] = 2 * (n - 1);
}

//      knights of the round
const int N = 1010, M = 2000010;
int head[N], ver[M], Next[M];
int dfn[N], low[N], stack[N];
int c[N], v[N], able[N];
int n, m, tot, num, top, cnt, now;
bool hate[N][N], flag;
vector<int> dcc[N];

void add(int x, int y) {
    ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void tarjan(int x, int root) {
    dfn[x] = low[x] = ++num;
    stack[++top] = x;
    if (x == root && head[x] == 0) { // ������
        dcc[++cnt].push_back(x);
        return;
    }
    for (int i = head[x]; i; i = Next[i]) {
        int y = ver[i];
        if (!dfn[y]) {
            tarjan(y, root);
            low[x] = min(low[x], low[y]);
            if (low[y] >= dfn[x]) {
                cnt++;
                int z;
                do {
                    z = stack[top--];
                    dcc[cnt].push_back(z);
                } while (z != y);
                dcc[cnt].push_back(x);
            }
        }
        else low[x] = min(low[x], dfn[y]);
    }
}

void dfs(int x, int color) {
    c[x] = color;
    for (int i = head[x]; i; i = Next[i]) {
        int y = ver[i];
        if (v[y] != now) continue;
        if (c[y] && c[y] == color) {
            flag = 1;
            return;
        }
        if (!c[y]) dfs(y, 3 - color);
    }
}

//      networks
const int N = 100005, M = 200005;
int ver[M*2], nxt[M*2], head[N], tot;
int vc[M*2], nc[M*2], hc[N], tc;
int dfn[N], low[N], c[N], n, m, q, num, dcc, ans, T;
int fa[N]/*并查集中的父节点*/, d[N], go[N]/*缩点之后的树上的父节点*/;
bool bridge[M*2];

void add(int x, int y) {
    ver[++tot] = y, nxt[tot] = head[x], head[x] = tot;
}
void add_c(int x, int y) {
    vc[++tc] = y, nc[tc] = hc[x], hc[x] = tc;
}

void tarjan(int x, int in_edge) {
    dfn[x] = low[x] = ++num;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (!dfn[y]) { // 树边
            tarjan(y, i);
            low[x] = min(low[x], low[y]);
            if (dfn[x] < low[y]) bridge[i] = bridge[i ^ 1] = true;
        }
        else if (i != (in_edge ^ 1))
            low[x] = min(low[x], dfn[y]);
    }
}

void dfs(int x) {
    c[x] = dcc;
    for (int i = head[x]; i; i = nxt[i])
        if (!bridge[i] && !c[ver[i]]) dfs(ver[i]);
}

void dfs_c(int x) {
    for (int i = hc[x]; i; i = nc[i]) {
        int y = vc[i];
        if (!d[y]) {
            d[y] = d[x] + 1;
            go[y] = x;
            dfs_c(y);
        }
    }
}

int get(int x) {
    return x == fa[x] ? x : (fa[x] = get(fa[x]));
}

void calc(int x, int y) {
    x = get(x), y = get(y);
    while (x != y) {
        if (d[x] < d[y]) swap(x, y);
        if (x == 1) break;
        // x到go[x]的边从桥边变为非桥边
        fa[x] = get(go[x]);
        ans--;
        x = get(x);
    }
}

//      watchcow
int head[10010], ver[100010], Next[100010], tot; // �ڽӱ�
int stack[100010], ans[100010]; // ģ��ϵͳջ����ջ
bool vis[100010];
int n, m, top, t;

void add(int x, int y) {
    ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void euler() {
    stack[++top] = 1;
    while (top > 0) {
        int x = stack[top], i = head[x];
        // �ҵ�һ����δ���ʵı�
        while (i && vis[i]) i = Next[i];
        // ����������ģ��ݹ���̣���Ǹñߣ������±�ͷ
        if (i) {
            stack[++top] = ver[i];
            head[x] = Next[i];
            // vis[i] = vis[i ^ 1] = true;
        }
            // ��x���������б߾��ѷ��ʣ�ģ����ݹ��̣�����¼
        else {
            top--;
            ans[++t] = x;
        }
    }
}

//      tarjan 与 有向图
//      network of schools
const int N = 105, M = 10005;
int head[N], ver[M], nxt[M], tot;
int dfn[N], low[N], c[N], s[N], n, num, top, cnt;
int in[N], out[N];
bool ins[N];

void add(int x, int y) {
    ver[++tot] = y, nxt[tot] = head[x], head[x] = tot;
}

void tarjan(int x) {
    low[x] = dfn[x] = ++num;
    s[++top] = x; ins[x] = true;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        }
        else if (ins[y])
            low[x] = min(low[x], dfn[y]);
    }
    if (dfn[x] == low[x]) {
        cnt++; // 找到了一个SCC
        int y;
        do {
            y = s[top--];
            ins[y] = false;
            c[y] = cnt;
            // scc[cnt].push_back(y);
        } while (x != y);
    }
}


//      银河
const int N = 100005, M = 300005;
int head[N], edge[M], ver[M], nxt[M], tot;
int hc[N], ec[M], vc[M], nc[M], tc;
int dfn[N], low[N], c[N], s[N], n, m, num, top, cnt;
int in[N], d[N];
bool ins[N];
queue<int> q;

void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, nxt[tot] = head[x], head[x] = tot;
}

void add_c(int x, int y, int z) {
    vc[++tc] = y, ec[tc] = z, nc[tc] = hc[x], hc[x] = tc;
    in[y]++;
}

void tarjan(int x) {
    low[x] = dfn[x] = ++num;
    s[++top] = x; ins[x] = true;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        }
        else if (ins[y])
            low[x] = min(low[x], dfn[y]);
    }
    if (dfn[x] == low[x]) {
        cnt++; // 找到了一个SCC
        int y;
        do {
            y = s[top--];
            ins[y] = false;
            c[y] = cnt;
            // scc[cnt].push_back(y);
        } while (x != y);
    }
}

void topsort() {
    q.push(c[0]);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int i = hc[x]; i; i = nc[i]) {
            int y = vc[i];
            d[y] = max(d[y], d[x] + ec[i]);
            if (--in[y] == 0) q.push(y);
        }
    }
}

//      pku acm  team's excursion
const int N = 100005, M = 200005, mod = 1000000007;
int ver[M*2], edge[M*2], nxt[M*2], head[N], tot;
int f[2][N], deg[2][N], d[N], pre[N], n, m, s, t, bus;
bool bridge[M*2];
int a[N], b[N], cnt; // 长度、是不是桥
int sum[N], sum_bri[N], ds[N], dt[N], ds_min[N];
int occur[N], first_occur[N];
queue<int> q;

void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, nxt[tot] = head[x], head[x] = tot;
}

void topsort(int s, int bit) {
    if (bit == 0) { // 只有正图需要求最短路
        memset(d, 0x3f, sizeof(d));
        d[s] = 0;
    }
    f[bit][s] = 1;
    for (int i = 1; i <= n; i++)
        if (deg[bit][i] == 0) q.push(i);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int i = head[x]; i; i = nxt[i])
            if ((i & 1) == bit) {
                int y = ver[i];
                f[bit][y] = (f[bit][y] + f[bit][x]) % mod; // 路径条数
                if (bit == 0 && d[y] > d[x] + edge[i]) {  // 最短路
                    d[y] = d[x] + edge[i];
                    pre[y] = i;
                }
                if (--deg[bit][y] == 0) q.push(y);
            }
    }
}

//      katu puzzle
const int N = 1006;
int n, m, dfn[N], low[N], num, st[N], top, c[N], cnt;
bool ins[N];
vector<int> e[N<<1];

inline void add(int x, int y) {
    e[x].push_back(y);
}

void tarjan(int x) {
    dfn[x] = low[x] = ++num;
    st[++top] = x;
    ins[x] = 1;
    for (unsigned int i = 0; i < e[x].size(); i++) {
        int y = e[x][i];
        if (!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if (ins[y])
            low[x] = min(low[x], dfn[y]);
    }
    if (dfn[x] == low[x]) {
        ++cnt;
        int y;
        do {
            y = st[top--];
            ins[y] = 0;
            c[y] = cnt;
        } while (x != y);
    }
}

//      priest john's busiest day
const int u = 2010, w = 3000010;
int ver[w], Next[w], head[u], dfn[u], low[u], c[u], s[u], ins[u];
int ver2[w], Next2[w], head2[u], val[u], deg[u], opp[u];
int S[u], T[u], D[u], ex[w], ey[w];
int n, m, tot, tot2, num, t, p, e;
queue<int> q;

// ԭͼ�ӱ�
void add(int x, int y) {
    ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
    ex[++e] = x, ey[e] = y;
}

// ������ͼ�ӱ�
void add2(int x, int y) {
    ver2[++tot2] = y, Next2[tot2] = head2[x], head2[x] = tot2;
}

void tarjan(int x) {
    dfn[x] = low[x] = ++num;
    s[++p] = x, ins[x] = 1;
    for (int i = head[x]; i; i = Next[i])
        if (!dfn[ver[i]]) {
            tarjan(ver[i]);
            low[x] = min(low[x], low[ver[i]]);
        }
        else if (ins[ver[i]])
            low[x] = min(low[x], low[ver[i]]);
    if (dfn[x] == low[x]) {
        t++; int y;
        do { y = s[p--], ins[y] = 0; c[y] = t; } while (x != y);
    }
}

void topsort() {
    memset(val, -1, sizeof(val));
    // ���㣬����ͼ
    for (int i = 1; i <= e; i++)
        if (c[ex[i]] != c[ey[i]])
            add2(c[ey[i]], c[ex[i]]), deg[c[ex[i]]]++;
    // ����ȵ����
    for (int i = 1; i <= t; i++)
        if (!deg[i]) q.push(i);
    // ��������
    while (q.size()) {
        int k = q.front(); q.pop();
        // ��ֵ���
        if (val[k] == -1) val[k] = 0, val[opp[k]] = 1;
        for (int i = head2[k]; i; i = Next2[i])
            if (--deg[ver2[i]] == 0) q.push(ver2[i]);
    }
    // ������ս��
    for (int i = 1; i <= n; i++)
        if (val[c[i]] == 0) printf("%02d:%02d %02d:%02d\n",
                                   S[i] / 60, S[i] % 60,
                                   (S[i] + D[i]) / 60, (S[i] + D[i]) % 60);
        else printf("%02d:%02d %02d:%02d\n",
                    (T[i] - D[i]) / 60, (T[i] - D[i]) % 60,
                    T[i] / 60, T[i] % 60);
}

bool overlap(int a, int b, int c, int d) {
    if (a >= c&&a<d || b>c&&b <= d || a <= c&&b >= d) return 1;
    return 0;
}

//      二分图的匹配
//      关押罪犯
const int N = 20006, M = 200006;
struct P {
    int x, y, z;
    bool operator < (const P w) const {
        return z > w.z;
    }
} p[M];
int n, m, v[N];
vector<pair<int, int> > e[N];

bool dfs(int x, int color) {
    v[x] = color;
    for (unsigned int i = 0; i < e[x].size(); i++) {
        int y = e[x][i].first;
        if (v[y]) {
            if (v[y] == color) return 0;
        } else {
            if (!dfs(y, 3 - color)) return 0;
        }
    }
    return 1;
}

inline bool pd(int now) {
    for (int i = 1; i <= n; i++) e[i].clear();
    for (int i = 1; i <= m; i++) {
        if (p[i].z <= now) break;
        e[p[i].x].push_back(make_pair(p[i].y, p[i].z));
        e[p[i].y].push_back(make_pair(p[i].x, p[i].z));
    }
    memset(v, 0, sizeof(v));
    for (int i = 1; i <= n; i++)
        if (!v[i] && !dfs(i, 1)) return 0;
    return 1;
}

//      棋盘覆盖
const int N = 106;
const int dx[4] = {0,0,1,-1};
const int dy[4] = {1,-1,0,0};
int n, m, ans, f[N*N];
bool b[N][N], v[N*N];
vector<int> e[N*N];

bool dfs(int x) {
    for (unsigned int i = 0; i < e[x].size(); i++) {
        int y = e[x][i];
        if (v[y]) continue;
        v[y] = 1;
        if (f[y] == -1 || dfs(f[y])) {
            f[y] = x;
            return 1;
        }
    }
    return 0;
}

//      车的位置
int n, m, t, ans, fa[205];
bool a[205][205], v[205];

bool dfs(int x) {
    for (int y = 1; y <= m; y++) {
        if (v[y] || a[x][y]) continue;
        v[y] = 1;
        if (fa[y] == 0 || dfs(fa[y])) {
            fa[y] = x;
            return true;
        }
    }
    return false;
}

//      导弹防御塔
const int N = 55;
const double eps = 1e-10;
int v[N*N], match[N*N], n, m;
double T1, T2, V;
struct {int x, y;} a[N], b[N];
double dist[N][N];
vector<int> ver[N];

bool dfs(int x) {
    for (int i = 0; i < ver[x].size(); i++) {
        int y = ver[x][i];
        if (v[y]) continue;
        v[y] = 1;
        if (!match[y] || dfs(match[y])) {
            match[y] = x;
            return true;
        }
    }
    return false;
}

//      ants
const int N = 105;
const double eps = 1e-10;
double w[N][N]; // 边权
double la[N], lb[N], upd[N]; // 左、右部点的顶标
bool va[N], vb[N]; // 访问标记：是否在交错树中
int match[N]; // 右部点匹配了哪一个左部点
int last[N]; // 右部点在交错树中的上一个右部点，用于倒推得到交错路
int n;
struct {int x, y;} a[N], b[N];

bool dfs(int x, int fa) {
    va[x] = 1;
    for (int y = 1; y <= n; y++)
        if (!vb[y])
            if (fabs(la[x] + lb[y] - w[x][y]) < eps) { // 相等子图
                vb[y] = 1; last[y] = fa;
                if (!match[y] || dfs(match[y], y)) {
                    match[y] = x;
                    return true;
                }
            }
            else if (upd[y] > la[x] + lb[y] - w[x][y] + eps) {
                upd[y] = la[x] + lb[y] - w[x][y];
                last[y] = fa;
            }
    return false;
}

void KM() {
    for (int i = 1; i <= n; i++) {
        la[i] = -1e100;
        lb[i] = 0;
        for (int j = 1; j <= n; j++)
            la[i] = max(la[i], w[i][j]);
    }
    for (int i = 1; i <= n; i++) {
        memset(va, 0, sizeof(va));
        memset(vb, 0, sizeof(vb));
        for (int j = 1; j <= n; j++) upd[j] = 1e10;
        // 从右部点st匹配的左部点match[st]开始dfs，一开始假设有一条0-i的匹配
        int st = 0; match[0] = i;
        while (match[st]) { // 当到达一个非匹配点st时停止
            double delta = 1e10;
            if (dfs(match[st], st)) break;
            for (int j = 1; j <= n; j++)
                if (!vb[j] && delta > upd[j]) {
                    delta = upd[j];
                    st = j; // 下一次直接从最小边开始DFS
                }
            for (int j = 1; j <= n; j++) { // 修改顶标
                if (va[j]) la[j] -= delta;
                if (vb[j]) lb[j] += delta; else upd[j] -= delta;
            }
            vb[st] = true;
        }
        while (st) { // 倒推更新增广路
            match[st] = match[last[st]];
            st = last[st];
        }
    }
}

//      二分图的覆盖
//      machine schedule
const int N = 106;
int n, m, k, f[N], ans;
bool v[N];
vector<int> e[N];

bool dfs(int x) {
    for (unsigned int i = 0; i < e[x].size(); i++) {
        int y = e[x][i];
        if (v[y]) continue;
        v[y] = 1;
        if (!f[y] || dfs(f[y])) {
            f[y] = x;
            return 1;
        }
    }
    return 0;
}

inline void Machine_Schedule() {
    cin >> m >> k;
    for (int i = 1; i < n; i++) e[i].clear();
    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d %d %d", &i, &x, &y);
        if (x && y) e[x].push_back(y);
    }
    memset(f, 0, sizeof(f));
    ans = 0;
    for (int i = 1; i < n; i++) {
        memset(v, 0, sizeof(v));
        ans += dfs(i);
    }
    cout << ans << endl;
}

//      muddy fields
const int N = 56;
int n, m, tot = 1, a[N][N][2], f[N*N], ans;
char s[N][N];
bool v[N*N];
vector<int> e[N*N];

bool dfs(int x) {
    for (unsigned int i = 0; i < e[x].size(); i++) {
        int y = e[x][i];
        if (v[y]) continue;
        v[y] = 1;
        if (!f[y] || dfs(f[y])) {
            f[y] = x;
            return 1;
        }
    }
    return 0;
}

//      骑士放置
int n, m, t, ans, fx[105][105], fy[105][105];
bool a[105][105], v[105][105];
const int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

bool dfs(int x, int y) {
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 1 || ny < 1 || nx > n || ny > m || a[nx][ny]) continue;
        if (v[nx][ny]) continue;
        v[nx][ny] = 1;
        if (fx[nx][ny] == 0 || dfs(fx[nx][ny], fy[nx][ny])) {
            fx[nx][ny] = x, fy[nx][ny] = y;
            return true;
        }
    }
    return false;
}
//      vani 和 cl2 捉迷藏
bool cl[222][222]; // �ڽӾ���
int match[222], n, m;
bool vis[222], succ[222];
int hide[222]; // �����㼯��

bool dfs(int x) {
    for (int i = 1; i <= n; i++)
        if (cl[x][i] && !vis[i]) {
            vis[i] = true;
            if (!match[i] || dfs(match[i])) {
                match[i] = x;
                return true;
            }
        }
    return false;
}

int main() {
    // ����
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        cl[x][y] = 1;
    }
    // Floyd ���ݱհ�
    for (int i = 1; i <= n; i++) cl[i][i] = 1;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cl[i][j] |= cl[i][k] && cl[k][j];
    for (int i = 1; i <= n; i++) cl[i][i] = 0;
    // �ڲ�����ͼ�������ƥ��
    int ans = n;
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        ans -= dfs(i);
    }
    cout << ans <<endl;
    // ���췽�����Ȱ�����·���յ㣨�󲿷�ƥ��㣩��Ϊ������
    for (int i = 1; i <= n; i++) succ[match[i]] = true;
    for (int i = 1, k = 0; i <= n; i++)
        if (!succ[i]) hide[++k] = i;
    memset(vis, 0, sizeof(vis));
    bool modify = true;
    while (modify) {
        modify = false;
        // ��� next(hide)
        for (int i = 1; i <= ans; i++)
            for (int j = 1; j <= n; j++)
                if (cl[hide[i]][j]) vis[j] = true;
        for (int i = 1; i <= ans; i++)
            if (vis[hide[i]]) {
                modify = true;
                // ���������ƶ�
                while (vis[hide[i]]) hide[i] = match[hide[i]];
            }
    }
    for (int i = 1; i <= ans; i++) printf("%d ", hide[i]);
    cout << endl;
}

//      网络流初步
//      舞动的夜晚
const int inf = 0x3fffffff, u = 40010, w = 300010;
int head[u], now[u], ver[w], edge[w], Next[w], d[u], e[w], c[u], sta[u], ins[u], dfn[u], low[u];
int n, m, p, s, t, i, j, tot, maxflow, ans, x, y, scc, st, num;
char str[10];
vector<int> a[u];
queue<int> q;

void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, Next[tot] = head[x], head[x] = tot;
    ver[++tot] = x, edge[tot] = 0, Next[tot] = head[y], head[y] = tot;
}

bool bfs() { // 在残量网络上构造分层图
    memset(d, 0, sizeof(d));
    while (q.size()) q.pop();
    q.push(s); d[s] = 1; now[s] = head[s];
    while (q.size()) {
        int x = q.front(); q.pop();
        for (int i = head[x]; i; i = Next[i])
            if (edge[i] && !d[ver[i]]) {
                q.push(ver[i]);
                now[ver[i]] = head[ver[i]];
                d[ver[i]] = d[x] + 1;
                if (ver[i] == t) return 1;
            }
    }
    return 0;
}

int dinic(int x, int flow) { // 在当前分层图上增广
    if (x == t) return flow;
    int rest = flow, k, i;
    for (i = now[x]; i && rest; i = Next[i]) {
        now[x] = i; // 当前弧优化（避免重复遍历从x出发不可扩展的边）
        if (edge[i] && d[ver[i]] == d[x] + 1) {
            k = dinic(ver[i], min(rest, edge[i]));
            if (!k) d[ver[i]] = 0; // 剪枝，去掉增广完毕的点
            edge[i] -= k;
            edge[i ^ 1] += k;
            rest -= k;
        }
    }
    return flow - rest;
}

void add2(int x, int y)
{
    a[x].push_back(y);
}

void tarjan(int x)
{
    dfn[x] = ++num; low[x] = num;
    sta[++st] = x; ins[x] = 1;
    int y;
    for (int i = 0; i<a[x].size(); i++)
        if (!dfn[y = a[x][i]])
        {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        }
        else if (ins[y]) low[x] = min(low[x], dfn[y]);
    if (dfn[x] == low[x])
    {
        scc++;
        do { y = sta[st]; st--; ins[y] = 0; c[y] = scc; } while (x != y);
    }
}

//      k取方格数
const int N = 5010, M = 200010;
int ver[M], edge[M], cost[M], Next[M], head[N];
int d[N], incf[N], pre[N], v[N];
int n, k, tot, s, t, maxflow, ans;

void add(int x, int y, int z, int c) {
    // ����ߣ���ʼ����z����λ����c
    ver[++tot] = y, edge[tot] = z, cost[tot] = c;
    Next[tot] = head[x], head[x] = tot;
    // ����ߣ���ʼ����0����λ����-c��������ߡ��ɶԴ洢��
    ver[++tot] = x, edge[tot] = 0, cost[tot] = -c;
    Next[tot] = head[y], head[y] = tot;
}

int num(int i, int j, int k) {
    return (i - 1)*n + j + k*n*n;
}

bool spfa() {
    queue<int> q;
    memset(d, 0xcf, sizeof(d)); // -INF
    memset(v, 0, sizeof(v));
    q.push(s); d[s] = 0; v[s] = 1; // SPFA ���·
    incf[s] = 1 << 30; // ����·�ϸ��ߵ���Сʣ������
    while (q.size()) {
        int x = q.front(); v[x] = 0; q.pop();
        for (int i = head[x]; i; i = Next[i]) {
            if (!edge[i]) continue; // ʣ������Ϊ0�����ڲ��������У�������
            int y = ver[i];
            if (d[y]<d[x] + cost[i]) {
                d[y] = d[x] + cost[i];
                incf[y] = min(incf[x], edge[i]);
                pre[y] = i; // ��¼ǰ���������ҵ��·��ʵ�ʷ���
                if (!v[y]) v[y] = 1, q.push(y);
            }
        }
    }
    if (d[t] == 0xcfcfcfcf) return false; // ��㲻�ɴ����������
    return true;
}

// ���������·���䷴��ߵ�ʣ������
void update() {
    int x = t;
    while (x != s) {
        int i = pre[x];
        edge[i] -= incf[t];
        edge[i ^ 1] += incf[t]; // ���á��ɶԴ洢����xor 1����
        x = ver[i ^ 1];
    }
    maxflow += incf[t];
    ans += d[t] * incf[t];
}

//      cable TV  Network
const int N = 56, M = 20006, INF = 0x3f3f3f3f;
int n, m, s, t;
int a[N*N], b[N*N], d[N<<1];
int Head[N<<1], Edge[M], Leng[M], Next[M], tot;

inline void add(int x, int y, int z) {
    Edge[++tot] = y;
    Leng[tot] = z;
    Next[tot] = Head[x];
    Head[x] = tot;
    Edge[++tot] = x;
    Leng[tot] = 0;
    Next[tot] = Head[y];
    Head[y] = tot;
}

inline bool bfs() {
    memset(d, 0, sizeof(d));
    queue<int> q;
    q.push(s);
    d[s] = 1;
    while (q.size()) {
        int x = q.front();
        q.pop();
        for (int i = Head[x]; i; i = Next[i]) {
            int y = Edge[i], z = Leng[i];
            if (z && !d[y]) {
                q.push(y);
                d[y] = d[x] + 1;
                if (y == t) return 1;
            }
        }
    }
    return 0;
}

inline int dinic(int x, int f) {
    if (x == t) return f;
    int rest = f;
    for (int i = Head[x]; i && rest; i = Next[i]) {
        int y = Edge[i], z = Leng[i];
        if (z && d[y] == d[x] + 1) {
            int k = dinic(y, min(rest, z));
            if (!k) d[y] = 0;
            Leng[i] -= k;
            Leng[i^1] += k;
            rest -= k;
        }
    }
    return f - rest;
}

inline void Cable_TV_Network() {
    for (int i = 0; i < m; i++) {
        char str[20];
        scanf("%s", str);
        a[i] = b[i] = 0;
        int j;
        for (j = 1; str[j] != ','; j++) a[i] = a[i] * 10 + str[j] - '0';
        for (j++; str[j] != ')'; j++) b[i] = b[i] * 10 + str[j] - '0';
    }
    int ans = INF;
    for (s = 0; s < n; s++)
        for (t = 0; t < n; t++)
            if (s != t) {
                memset(Head, 0, sizeof(Head));
                tot = 1;
                int maxf = 0;
                for (int i = 0; i < n; i++)
                    if (i == s || i == t) add(i, i + n, INF);
                    else add(i, i + n, 1);
                for (int i = 0; i < m; i++) {
                    add(a[i] + n, b[i], INF);
                    add(b[i] + n, a[i], INF);
                }
                while (bfs()) {
                    int num;
                    while ((num = dinic(s, INF))) maxf += num;
                }
                ans = min(ans, maxf);
            }
    if (n <= 1 || ans == INF) ans = n;
    cout << ans << endl;
}

//


int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
        add(y, x, z == 1 ? -1 : z);
    }
    memset(d, 0x3f, sizeof(d));
    spfa(d, 1, 1); // 从1出发求前缀min（d），只有1和2的边可以用
    memset(f, 0xcf, sizeof(f));
    spfa(f, n, -1); // 从n出发倒着求后缀max（d），只有-1和2的边可以用
    int ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, f[i] - d[i]);
    cout << ans << endl;
}