#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
#include<queue>
#include<vector>

using namespace std;

class Solution {
public:
    int n, m, deg[30010], a[30010];
    int ver[30010], Next[30010], head[30010], tot, cnt;
    bitset<30010> f[30010];
//    树与图的遍历
    void add(int x, int y) { // 在邻接表中添加一条有向边
        ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
        deg[y]++;
    }
    void topsort() { // 拓扑排序
        queue<int> q;
        for (int i = 1; i <= n; i++)
            if (deg[i] == 0) q.push(i);
        while (q.size()) {
            int x = q.front(); q.pop();
            a[++cnt] = x;
            for (int i = head[x]; i; i = Next[i]) {
                int y = ver[i];
                if (--deg[y] == 0) q.push(y);
            }
        }
    }
    void calc() {
        for (int i = cnt; i; i--) {
            int x = a[i];
            f[x][x] = 1;
            for (int i = head[x]; i; i = Next[i]) {
                int y = ver[i];
                f[x] |= f[y];
            }
        }
    }
//      小猫爬山
    int c[20], cab[20], n, w, ans;
    void dfs(int now, int cnt) {
        if (cnt >= ans) return;
        if (now == n+1) {
            ans = min(ans, cnt);
            return;
        }
        for (int i = 1; i <= cnt; i++) {  // 分配到已租用缆车
            if (cab[i] + c[now] <= w) {   // 能装下
                cab[i] += c[now];
                dfs(now+1, cnt);
                cab[i] -= c[now];         // 还原现场
            }
        }
        cab[cnt+1] = c[now];
        dfs(now+1, cnt+1);
        cab[cnt+1] = 0;
    }

//    数独
    char str[10][10];
    int row[9], col[9], grid[9], cnt[512], num[512], tot;

    inline int g(int x, int y) {
        return ((x / 3) * 3) + (y / 3);
    }

    inline void flip(int x, int y, int z) {
        row[x] ^= 1 << z;
        col[y] ^= 1 << z;
        grid[g(x, y)] ^= 1 << z;
    }

    bool dfs(int now) {
        if (now == 0) return 1;
        int temp = 10, x, y;
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++) {
                if (str[i][j] != '.') continue;
                int val = row[i] & col[j] & grid[g(i, j)];
                if (!val) return 0;
                if (cnt[val] < temp) {
                    temp = cnt[val];
                    x = i, y = j;
                }
            }
        int val = row[x] & col[y] & grid[g(x, y)];
        for (; val; val -= val&-val) {
            int z = num[val&-val];
            str[x][y] = '1' + z;
            flip(x, y, z);
            if (dfs(now - 1)) return 1;
            flip(x, y, z);
            str[x][y] = '.';
        }
        return 0;
    }

//    剪枝： sticks， sudoku， 生日蛋糕
    int a[100], v[100], n, len, cnt;

// 正在拼第stick根原始木棒（已经拼好了stick-1根）
// 第stick根木棒的当前长度为cab
// 拼接到第stick根木棒中的上一根小木棍为last
    bool dfs(int stick, int cab, int last) {
        // 所有原始木棒已经全部拼好，搜索成功
        if (stick > cnt) return true;
        // 第stick根木棒已经拼好，去拼下一根
        if (cab == len) return dfs(stick + 1, 0, 1);
        int fail = 0; // 剪枝(2)
        // 剪枝(1)：小木棍长度递减（从last开始枚举）
        for (int i = last; i <= n; i++)
            if (!v[i] && cab + a[i] <= len && fail != a[i]) {
                v[i] = 1;
                if (dfs(stick, cab + a[i], i + 1)) return true;
                fail = a[i];
                v[i] = 0; // 还原现场
                if (cab == 0 || cab + a[i] == len) return false; // 剪枝(3,4)
            }
        return false; // 所有分支均尝试过，搜索失败
    }

//
    char s[16][16];
    int cnt[1<<16], f[1<<16], num[16][16], n = 0;
    vector<int> e[1<<16];

    void work(int i, int j, int k) {
        for (int t = 0; t < 16; t++) {
            num[i][t] &= ~(1 << k);
            num[t][j] &= ~(1 << k);
        }
        int x = i / 4 * 4, y = j / 4 * 4;
        for (int ti = 0; ti < 4; ti++)
            for (int tj = 0; tj < 4; tj++)
                num[x+ti][y+tj] &= ~(1 << k);
    }

    bool dfs(int ans) {
        if (!ans) return 1;
        int pre[16][16];
        memcpy(pre, num, sizeof(pre));
        for (int i = 0; i < 16; i++)
            for (int j = 0; j < 16; j++)
                if (s[i][j] == '-') {
                    if (!num[i][j]) return 0;
                    if (cnt[num[i][j]] == 1) {
                        s[i][j] = f[num[i][j]] + 'A';
                        work(i, j, f[num[i][j]]);
                        if (dfs(ans - 1)) return 1;
                        s[i][j] = '-';
                        memcpy(num, pre, sizeof(num));
                        return 0;
                    }
                }
        for (int i = 0; i < 16; i++) {
            int w[16], o = 0;
            memset(w, 0, sizeof(w));
            for (int j = 0; j < 16; j++)
                if (s[i][j] == '-') {
                    o |= num[i][j];
                    for (unsigned int k = 0; k < e[num[i][j]].size(); k++)
                        ++w[e[num[i][j]][k]];
                } else {
                    o |= (1 << (s[i][j] - 'A'));
                    w[f[1<<(s[i][j]-'A')]] = -1;
                }
            if (o != (1 << 16) - 1) return 0;
            for (int k = 0; k < 16; k++)
                if (w[k] == 1)
                    for (int j = 0; j < 16; j++)
                        if (s[i][j] == '-' && ((num[i][j] >> k) & 1)) {
                            s[i][j] = k + 'A';
                            work(i, j, k);
                            if (dfs(ans - 1)) return 1;
                            s[i][j] = '-';
                            memcpy(num, pre, sizeof(num));
                            return 0;
                        }
        }
        for (int j = 0; j < 16; j++) {
            int w[16], o = 0;
            memset(w, 0, sizeof(w));
            for (int i = 0; i < 16; i++)
                if (s[i][j] == '-') {
                    o |= num[i][j];
                    for (unsigned int k = 0; k < e[num[i][j]].size(); k++)
                        ++w[e[num[i][j]][k]];
                } else {
                    o |= (1 << (s[i][j] - 'A'));
                    w[f[1<<(s[i][j]-'A')]] = -1;
                }
            if (o != (1 << 16) - 1) return 0;
            for (int k = 0; k < 16; k++)
                if (w[k] == 1)
                    for (int i = 0; i < 16; i++)
                        if (s[i][j] == '-' && ((num[i][j] >> k) & 1)) {
                            s[i][j] = k + 'A';
                            work(i, j, k);
                            if (dfs(ans - 1)) return 1;
                            s[i][j] = '-';
                            memcpy(num, pre, sizeof(num));
                            return 0;
                        }
        }
        for (int i = 0; i < 16; i += 4)
            for (int j = 0; j < 16; j += 4) {
                int w[16], o = 0;
                memset(w, 0, sizeof(w));
                for (int p = 0; p < 4; p++)
                    for (int q = 0; q < 4; q++)
                        if (s[i+p][j+q] == '-') {
                            o |= num[i+p][j+q];
                            for (unsigned int k = 0; k < e[num[i+p][j+q]].size(); k++)
                                ++w[e[num[i+p][j+q]][k]];
                        } else {
                            o |= (1 << (s[i+p][j+q] - 'A'));
                            w[f[1<<(s[i+p][j+q]-'A')]] = -1;
                        }
                if (o != (1 << 16) - 1) return 0;
                for (int k = 0; k < 16; k++)
                    if (w[k] == 1)
                        for (int p = 0; p < 4; p++)
                            for (int q = 0; q < 4; q++)
                                if (s[i+p][j+q] == '-' && ((num[i+p][j+q] >> k) & 1)) {
                                    s[i+p][j+q] = k + 'A';
                                    work(i + p, j + q, k);
                                    if (dfs(ans - 1)) return 1;
                                    s[i+p][j+q] = '-';
                                    memcpy(num, pre, sizeof(num));
                                    return 0;
                                }
            }
        int k = 17, tx, ty;
        for (int i = 0; i < 16; i++)
            for (int j = 0; j < 16; j++)
                if (s[i][j] == '-' && cnt[num[i][j]] < k) {
                    k = cnt[num[i][j]];
                    tx = i;
                    ty = j;
                }
        for (unsigned int i = 0; i < e[num[tx][ty]].size(); i++) {
            int tz = e[num[tx][ty]][i];
            work(tx, ty, tz);
            s[tx][ty] = tz + 'A';
            if (dfs(ans - 1)) return 1;
            s[tx][ty] = '-';
            memcpy(num, pre, sizeof(num));
        }
        return 0;
    }

    void Sudoku() {
        for (int i = 1; i < 16; i++) cin >> s[i];
        for (int i = 0; i < 16; i++)
            for (int j = 0; j < 16; j++)
                num[i][j] = (1 << 16) - 1;
        int ans = 0;
        for (int i = 0; i < 16; i++)
            for (int j = 0; j < 16; j++)
                if (s[i][j] != '-') work(i, j, s[i][j] - 'A');
                else ++ans;
        dfs(ans);
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) cout << s[i][j];
            cout << endl;
        }
        cout << endl;
    }

    int get_cnt(int i) {
        int k = i & -i;
        e[i].push_back(f[k]);
        for (unsigned int j = 0; j < e[i-k].size(); j++)
            e[i].push_back(e[i-k][j]);
        return cnt[i-k] + 1;
    }

//      生日蛋糕
    const int INF = 0x7fffffff;
    int n, m, minv[30], mins[30], ans = INF;
    int h[30], r[30], s = 0, v = 0;

    void dfs(int dep) {
        if (!dep) {
            if (v == n) ans = min(ans, s);
            return;
        }
        for (r[dep] = min((int)sqrt(n - v), r[dep + 1] - 1); r[dep] >= dep; r[dep]--)
            for (h[dep] = min((int)((double)(n-v) / r[dep] / r[dep]), h[dep+1] - 1); h[dep] >= dep; h[dep]--) {
                if (v + minv[dep-1] > n) continue;
                if (s + mins[dep-1] > ans) continue;
                if (s + (double)2 * (n - v) / r[dep] > ans) continue;
                if (dep == m) s += r[dep] * r[dep];
                s += 2 * r[dep] * h[dep];
                v += r[dep] * r[dep] * h[dep];
                dfs(dep - 1);
                if (dep == m) s -= r[dep] * r[dep];
                s -= 2 * r[dep] * h[dep];
                v -= r[dep] * r[dep] * h[dep];
            }
    }

//    迭代加深
    const int N = 106;
    int n, ans[N], dep;

    bool dfs(int now) {
        if (now == dep) return ans[now] == n;
        bool v[N];
        memset(v, 0, sizeof(v));
        for (int i = now; i; i--)
            for (int j = i; j; j--) {
                int num = ans[i] + ans[j];
                if (num <= n && num > ans[now] && !v[num]) {
                    ans[now+1] = num;
                    if (dfs(now + 1)) return 1;
                    else v[num] = 1;
                }
            }
        return 0;
    }
//      gift
    int n, half, m, g[50];
    unsigned int w, ans, a[(1 << 24) + 1];

    void dfs1(int i, unsigned int sum) {
        if (i == half) {
            a[++m] = sum;
            return;
        }
        dfs1(i + 1, sum);
        if (sum + g[i] <= w) dfs1(i + 1, sum + g[i]);
    }

    void calc(unsigned int val) {
        int rest = w - val;
        int l = 1, r = m;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (a[mid] <= rest) l = mid; else r = mid - 1;
        }
        ans = max(ans, a[l] + val);
    }

    void dfs2(int i, unsigned int sum) {
        if (i == n + 1) {
            calc(sum);
            return;
        }
        dfs2(i + 1, sum);
        if (sum + g[i] <= w) dfs2(i + 1, sum + g[i]);
    }

//    bfs
    struct rec { int x, y, lie; };  // 状态
    char s[510][510];  // 地图
    rec st, ed;  // 起始状态和目标状态
    int n, m, d[510][510][3];  // 最少步数记录数组
    queue<rec> q;  // 队列
    bool valid(int x, int y) { return x>=1 && y>=1 && x<=n && y<=m; }
// 方向数组（方向0~3依次代表左右上下）
    const int dx[4] = { 0,0,-1,1 }, dy[4] = { -1,1,0,0 };

    void parse_st_ed() {  // 处理起点和终点
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (s[i][j] == 'O') {
                    ed.x = i, ed.y = j, ed.lie = 0, s[i][j] = '.';
                }
                else if (s[i][j] == 'X') {
                    for (int k = 0; k < 4; k++) {
                        int x = i + dx[k], y = j + dy[k];
                        if (valid(x, y) && s[x][y] == 'X') {
                            st.x = min(i,x), st.y = min(j,y), st.lie = k<2?1:2;
                            s[i][j] = s[x][y] = '.';
                            break;
                        }
                    }
                    if (s[i][j] == 'X') {
                        st.x = i, st.y = j, st.lie = 0;
                    }
                }
    }

    bool valid(rec next) {  // 滚动是否合法
        if (!valid(next.x, next.y)) return 0;
        if (s[next.x][next.y] == '#') return 0;
        if (next.lie == 0 && s[next.x][next.y] != '.') return 0;
        if (next.lie == 1 && s[next.x][next.y + 1] == '#') return 0;
        if (next.lie == 2 && s[next.x + 1][next.y] == '#') return 0;
        return 1;
    }

// next_x[i][j]表示在lie=i时朝方向j滚动后x的变化情况
    const int next_x[3][4] = { { 0,0,-2,1 },{ 0,0,-1,1 },{ 0,0,-1,2 } };
// next_y[i][j]表示在lie=i时朝方向j滚动后y的变化情况
    const int next_y[3][4] = { { -2,1,0,0 },{ -1,2,0,0 },{ -1,1,0,0 } };
// next_lie[i][j]表示在lie=i时朝方向j滚动后lie的新值
    const int next_lie[3][4] = { { 1,1,2,2 },{ 0,0,1,1 },{ 2,2,0,0 } };

    int bfs() {  // 广搜
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                for (int k = 0; k < 3; k++) d[i][j][k] = -1;
        while (q.size()) q.pop();
        d[st.x][st.y][st.lie] = 0;
        q.push(st);
        while (q.size()) {
            rec now = q.front(); q.pop();  // 取出队头
            for (int i = 0; i < 4; i++) {  // 向4个方向滚动
                rec next;
                next.x = now.x + next_x[now.lie][i];
                next.y = now.y + next_y[now.lie][i];
                next.lie = next_lie[now.lie][i];
                if (!valid(next)) continue;
                if (d[next.x][next.y][next.lie] == -1) {  // 尚未访问过
                    d[next.x][next.y][next.lie] = d[now.x][now.y][now.lie]+1;
                    q.push(next);
                    if (next.x == ed.x && next.y == ed.y && next.lie == ed.lie)
                        return d[next.x][next.y][next.lie];  // 到达目标
                }
            }
        }
        return -1;  // 无解
    }

//    推箱子
    const int N = 26, INF = 0x3f3f3f3f;
    char A[4] = {'N','S','W','E'};
    char a[4] = {'n','s','w','e'};
    int r, c, num = 0;
    int d[4][2]= {{-1,0},{1,0},{0,-1},{0,1}};
    char s[N][N];
    string tmp;
    struct P {
        int x, y, px, py;
        string ans;
    };

    bool pd(int x, int y) {
        return x > 0 && x <= r && y > 0 && y <= c && s[x][y] != '#';
    }

    bool bfs2(P p1, P p2) {
        tmp = "";
        P st;
        st.x = p1.px;
        st.y = p1.py;
        st.ans = "";
        queue<P> q;
        q.push(st);
        bool v[N][N];
        memset(v, 0, sizeof(v));
        while (q.size()) {
            P now = q.front(), nxt;
            q.pop();
            if (now.x == p1.x && now.y == p1.y) {
                tmp = now.ans;
                return 1;
            }
            for (int i = 0; i < 4; i++) {
                nxt = now;
                nxt.x = now.x + d[i][0];
                nxt.y = now.y + d[i][1];
                if (!pd(nxt.x, nxt.y)) continue;
                if (nxt.x == p2.x && nxt.y == p2.y) continue;
                if (v[nxt.x][nxt.y]) continue;
                v[nxt.x][nxt.y] = 1;
                nxt.ans = now.ans + a[i];
                q.push(nxt);
            }
        }
        return 0;
    }

    string bfs1() {
        P st;
        st.x = st.y = st.px = st.py = -1;
        st.ans = "";
        for (int i = 1; i <= r && (st.x == -1 || st.px == -1); i++)
            for (int j = 1; j <= c && (st.x == -1 || st.px == -1); j++)
                if (s[i][j] == 'B') {
                    st.x = i;
                    st.y = j;
                    s[i][j] = '.';
                } else if (s[i][j] == 'S') {
                    st.px = i;
                    st.py = j;
                    s[i][j] = '.';
                }
        queue<P> q;
        q.push(st);
        bool v[N][N][4];
        memset(v, 0, sizeof(v));
        string ans = "Impossible.";
        unsigned int cntans = INF, cnt = INF;
        while (q.size()) {
            P prv, now = q.front(), nxt;
            q.pop();
            if (s[now.x][now.y] == 'T') {
                unsigned int cntnow = 0;
                for (unsigned int i = 0; i < now.ans.length(); i++)
                    if (now.ans[i] >= 'A' && now.ans[i] <= 'Z') ++cntnow;
                if (cntnow < cntans || (cntnow == cntans && now.ans.length() < cnt)) {
                    ans = now.ans;
                    cntans = cntnow;
                    cnt = now.ans.length();
                }
                continue;
            }
            for (int i = 0; i < 4; i++) {
                nxt = now;
                nxt.x = now.x + d[i][0];
                nxt.y = now.y + d[i][1];
                if (!pd(nxt.x, nxt.y)) continue;
                if (v[nxt.x][nxt.y][i]) continue;
                prv = now;
                if (i == 3) prv.y = now.y - 1;
                else if (i == 2) prv.y = now.y + 1;
                else if (i == 1) prv.x = now.x - 1;
                else prv.x = now.x + 1;
                if (!bfs2(prv, now)) continue;
                v[nxt.x][nxt.y][i] = 1;
                nxt.ans = now.ans + tmp;
                nxt.ans = nxt.ans + A[i];
                nxt.px = now.x;
                nxt.py = now.y;
                q.push(nxt);
            }
        }
        return ans;
    }

    void Pushing_Boxes() {
        for (int i = 1; i <= r; i++) cin >> (s[i] + 1);
        cout << "Maze #" << ++num << endl << bfs1() << endl << endl;
    }

//    广搜变形
    const int N = 506;
    int r, c, d[N][N];
    bool v[N][N];
    char s[N][N];
    vector<pair<pair<int, int>, int> > p[N][N];
    deque<pair<int, int> > q;

    void add(int x1, int y1, int x2, int y2, int z) {
        p[x1][y1].push_back(make_pair(make_pair(x2, y2), z));
    }

    void dlwx() {
        cin >> r >> c;
        for (int i = 1; i <= r; i++) cin >> (s[i] + 1);
        if ((r & 1) != (c & 1)) cout << "NO SOLUTION" << endl;
        for (int i = 0; i <= r; i++)
            for (int j = 0; j <= c; j++)
                p[i][j].clear();
        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
                if (s[i][j] == '/') {
                    add(i - 1, j - 1, i, j, 1);
                    add(i, j, i - 1, j - 1, 1);
                    add(i, j - 1, i - 1, j, 0);
                    add(i - 1, j, i, j - 1, 0);
                } else {
                    add(i - 1, j - 1, i, j, 0);
                    add(i, j, i - 1, j - 1, 0);
                    add(i, j - 1, i - 1, j, 1);
                    add(i - 1, j, i, j - 1, 1);
                }
        memset(d, 0x3f, sizeof(d));
        d[0][0] = 0;
        memset(v, 0, sizeof(v));
        q.clear();
        q.push_back(make_pair(0, 0));
        while (q.size()) {
            int x = q.front().first, y = q.front().second;
            q.pop_front();
            v[x][y] = 1;
            if (x == r && y == c) {
                cout << d[r][c] << endl;
                return;
            }
            for (unsigned int i = 0; i < p[x][y].size(); i++) {
                int nx = p[x][y][i].first.first;
                int ny = p[x][y][i].first.second;
                int nz = p[x][y][i].second;
                if (v[nx][ny]) continue;
                if (nz) {
                    if (d[nx][ny] > d[x][y] + 1) {
                        d[nx][ny] = d[x][y] + 1;
                        q.push_back(make_pair(nx, ny));
                    }
                } else {
                    if (d[nx][ny] > d[x][y]) {
                        q.push_front(make_pair(nx, ny));
                        d[nx][ny] = d[x][y];
                    }
                }
            }
        }
    }

//    full tank
    const int N = 1006, C = 106;
    int n, m, p[N], d[N][C];
    bool v[N][C];
    vector<pair<int, int> > e[N];
    priority_queue<pair<int, pair<int, int> > > q;

    void Full_Tank() {
        int c, st, ed;
        scanf("%d %d %d", &c, &st, &ed);
        priority_queue<pair<int, pair<int, int> > > empty;
        swap(q, empty);
        memset(d, 0x3f, sizeof(d));
        q.push(make_pair(0, make_pair(st, 0)));
        d[st][0] = 0;
        memset(v, 0, sizeof(v));
        while (q.size()) {
            int city = q.top().second.first;
            int fuel = q.top().second.second;
            q.pop();
            if (city == ed) {
                cout << d[city][fuel] << endl;
                return;
            }
            if (v[city][fuel]) continue;
            v[city][fuel] = 1;
            if (fuel < c && d[city][fuel+1] > d[city][fuel] + p[city]) {
                d[city][fuel+1] = d[city][fuel] + p[city];
                q.push(make_pair(-d[city][fuel] - p[city], make_pair(city, fuel + 1)));
            }
            for (unsigned int i = 0; i < e[city].size(); i++) {
                int y = e[city][i].first, z = e[city][i].second;
                if (z <= fuel && d[y][fuel-z] > d[city][fuel]) {
                    d[y][fuel-z] = d[city][fuel];
                    q.push(make_pair(-d[city][fuel], make_pair(y, fuel - z)));
                }
            }
        }
        cout << "impossible" << endl;
    }

//    nightmare
    const int N = 806;
    char s[N][N];
    bool v1[N][N], v2[N][N];
    int n, m, bx, by, gx, gy, px, py, qx, qy, s1, s2;
    int dx[4] = {0,0,-1,1};
    int dy[4] = {-1,1,0,0};

    bool pd(int x, int y, int k) {
        if (x <= 0 || x > n || y <= 0 || y > m) return 0;
        if (abs(x - px) + abs(y - py) <= 2 * k) return 0;
        if (abs(x - qx) + abs(y - qy) <= 2 * k) return 0;
        if (s[x][y] == 'X') return 0;
        return 1;
    }

    int bfs() {
        queue<pair<int, int> > q1, q2;
        px = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (s[i][j] == 'M') {
                    bx = i;
                    by = j;
                } else if (s[i][j] == 'G') {
                    gx = i;
                    gy = j;
                } else if (s[i][j] == 'Z') {
                    if (!px) {
                        px = i;
                        py = j;
                    } else {
                        qx = i;
                        qy = j;
                    }
                }
        int ans = 0;
        memset(v1, 0, sizeof(v1));
        memset(v2, 0, sizeof(v2));
        v1[bx][by] = 1;
        v2[gx][gy] = 1;
        q1.push(make_pair(bx, by));
        q2.push(make_pair(gx, gy));
        while (q1.size() || q2.size()) {
            ans++;
            s1 = q1.size();
            for (int i = 1; i <= s1; i++) {
                pair<int, int> now = q1.front();
                q1.pop();
                if (!pd(now.first,now.second,ans)) continue;
                for (int j = 0; j < 4; j++) {
                    int nx = now.first + dx[j];
                    int ny = now.second + dy[j];
                    if (pd(nx,ny,ans) && !v1[nx][ny]) {
                        v1[nx][ny] = 1;
                        q1.push(make_pair(nx, ny));
                    }
                }
            }
            s1 = q1.size();
            for (int i = 1; i <= s1; i++) {
                pair<int, int> now = q1.front();
                q1.pop();
                if (!pd(now.first,now.second,ans)) continue;
                for (int j = 0; j < 4; j++) {
                    int nx = now.first + dx[j];
                    int ny = now.second + dy[j];
                    if (pd(nx,ny,ans) && !v1[nx][ny]) {
                        v1[nx][ny] = 1;
                        q1.push(make_pair(nx, ny));
                    }
                }
            }
            s1 = q1.size();
            for (int i = 1; i <= s1; i++) {
                pair<int, int> now = q1.front();
                q1.pop();
                if (!pd(now.first,now.second,ans)) continue;
                for (int j = 0; j < 4; j++) {
                    int nx = now.first + dx[j];
                    int ny = now.second + dy[j];
                    if (pd(nx,ny,ans) && !v1[nx][ny]) {
                        v1[nx][ny] = 1;
                        q1.push(make_pair(nx, ny));
                    }
                }
            }
            s2 = q2.size();
            for (int i = 1; i <= s2; i++) {
                pair<int, int> now = q2.front();
                q2.pop();
                if (!pd(now.first,now.second,ans)) continue;
                for (int j = 0; j < 4; j++) {
                    int nx = now.first + dx[j];
                    int ny = now.second + dy[j];
                    if (pd(nx,ny,ans) && !v2[nx][ny]) {
                        if (v1[nx][ny]) return ans;
                        v2[nx][ny] = 1;
                        q2.push(make_pair(nx, ny));
                    }
                }
            }
        }
        return -1;
    }

//    astar
// state：八数码的状态(3*3九宫格压缩为一个整数)
// dist：当前代价 + 估价
    struct rec{int state,dist;
        rec(){}
        rec(int s,int d){state=s,dist=d;}
    };
    int a[3][3];
// map和priority_queue的用法参见0x71节C++ STL
    map<int,int> d,f,go;
    priority_queue<rec> q;
    const int dx[4]={-1,0,0,1},dy[4]={0,-1,1,0};
    char dir[4]={'u','l','r','d'};

    bool operator <(rec a,rec b) {
        return a.dist>b.dist;
    }

// 把3*3的九宫格压缩为一个整数（9进制）
    int calc(int a[3][3]) {
        int val=0;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++) {
                val=val*9+a[i][j];
            }
        return val;
    }

// 从一个9进制数复原出3*3的九宫格，以及空格位置
    pair<int,int> recover(int val,int a[3][3]) {
        int x,y;
        for(int i=2;i>=0;i--)
            for(int j=2;j>=0;j--) {
                a[i][j]=val%9;
                val/=9;
                if(a[i][j]==0) x=i,y=j;
            }
        return make_pair(x,y);
    }

// 计算估价函数
    int value(int a[3][3]) {
        int val=0;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++) {
                if(a[i][j]==0) continue;
                int x=(a[i][j]-1)/3;
                int y=(a[i][j]-1)%3;
                val+=abs(i-x)+abs(j-y);
            }
        return val;
    }

// A*算法
    int astar(int sx,int sy,int e) {
        d.clear(); f.clear(); go.clear();
        while(q.size()) q.pop();
        int start=calc(a);
        d[start]=0;
        q.push(rec(start,0+value(a)));
        while(q.size()) {
            // 取出堆顶
            int now=q.top().state; q.pop();
            // 第一次取出目标状态时，得到答案
            if(now==e) return d[now];
            int a[3][3];
            // 复原九宫格
            pair<int,int> space=recover(now,a);
            int x=space.first,y=space.second;
            // 枚举空格的移动方向（上下左右）
            for(int i=0;i<4;i++) {
                int nx=x+dx[i], ny=y+dy[i];
                if (nx<0||nx>2||ny<0||ny>2) continue;
                swap(a[x][y],a[nx][ny]);
                int next=calc(a);
                // next状态没有访问过，或者能被更新
                if(d.find(next)==d.end()||d[next]>d[now]+1) {
                    d[next]=d[now]+1;
                    // f和go记录移动的路线，以便输出方案
                    f[next]=now;
                    go[next]=i;
                    // 入堆
                    q.push(rec(next,d[next]+value(a)));
                }
                swap(a[x][y],a[nx][ny]);
            }
        }
        return -1;
    }

    void print(int e) {
        if(f.find(e)==f.end()) return;
        print(f[e]);
        putchar(dir[go[e]]);
    }

//    第k短路
    const int N = 1006;
    int n, m, st, ed, k, f[N], cnt[N];
    bool v[N];
    vector<pair<int, int> > e[N], fe[N];
    priority_queue<pair<int, int> > pq;

    void dijkstra() {
        memset(f, 0x3f, sizeof(f));
        memset(v, 0, sizeof(v));
        f[ed] = 0;
        pq.push(make_pair(0, ed));
        while (pq.size()) {
            int x = pq.top().second;
            pq.pop();
            if (v[x]) continue;
            v[x] = 1;
            for (unsigned int i = 0; i < fe[x].size(); i++) {
                int y = fe[x][i].first, z = fe[x][i].second;
                if (f[y] > f[x] + z) {
                    f[y] = f[x] + z;
                    pq.push(make_pair(-f[y], y));
                }
            }
        }
    }

    void A_star() {
        if (st == ed) ++k;
        pq.push(make_pair(-f[st], st));
        memset(cnt, 0, sizeof(cnt));
        while (pq.size()) {
            int x = pq.top().second;
            int dist = -pq.top().first - f[x];
            pq.pop();
            ++cnt[x];
            if (cnt[ed] == k) {
                cout << dist << endl;
                return;
            }
            for (unsigned int i = 0; i < e[x].size(); i++) {
                int y = e[x][i].first, z = e[x][i].second;
                if (cnt[y] != k) pq.push(make_pair(-f[y] - dist - z, y));
            }
        }
        cout << "-1" << endl;
    }

//    ida*
    const int N = 20;
    int n, a[N], dep;

    int gj() {
        int cnt = 0;
        for (int i = 1; i < n; i++)
            if (a[i] + 1 != a[i+1]) cnt++;
        if (a[n] != n) return cnt + 1;
        return cnt;
    }

    void work(int l, int r, int t) {
        int b[N], p = r;
        for (int i = l; i <= t; i++) {
            b[i] = a[++p];
            if (p == t) p = l - 1;
        }
        for (int i = l; i <= t; i++) a[i] = b[i];
    }

    bool dfs(int now) {
        int cnt = gj();
        if (!cnt) return 1;
        if (3 * now + cnt > 3 * dep) return 0;
        int c[N];
        memcpy(c, a, sizeof(c));
        for (int l = 1; l <= n; l++)
            for (int r = l; r <= n; r++)
                for (int t = r + 1; t <= n; t++) {
                    work(l, r, t);
                    if (dfs(now + 1)) return 1;
                    memcpy(a, c, sizeof(a));
                }
        return 0;
    }

    void Booksort() {
        cin >> n;
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for (dep = 0; dep <= 4; dep++)
            if (dfs(0)) {
                cout << dep << endl;
                return;
            }
        puts("5 or more");
    }
//    rotate game
    int a[9][9], dep;
    vector<char> ans;

    void work(int k) {
        if (k == 1) {
            for (int i = 1; i < 8; i++) a[i-1][3] = a[i][3];
            a[7][3] = a[0][3];
        } else if (k == 2) {
            for (int i = 1; i < 8; i++) a[i-1][5] = a[i][5];
            a[7][5] = a[0][5];
        } else if (k == 3) {
            for (int i = 7; i; i--) a[3][i+1] = a[3][i];
            a[3][1] = a[3][8];
        } else if (k == 4) {
            for (int i = 7; i; i--) a[5][i+1] = a[5][i];
            a[5][1] = a[5][8];
        } else if (k == 5) {
            for (int i = 7; i; i--) a[i+1][5] = a[i][5];
            a[1][5] = a[8][5];
        } else if (k == 6) {
            for (int i = 7; i; i--) a[i+1][3] = a[i][3];
            a[1][3] = a[8][3];
        } else if (k == 7) {
            for (int i = 1; i < 8; i++) a[5][i-1] = a[5][i];
            a[5][7] = a[5][0];
        } else {
            for (int i = 1; i < 8; i++) a[3][i-1] = a[3][i];
            a[3][7] = a[3][0];
        }
    }

    int gj() {
        int num[4];
        num[1] = num[2] = num[3] = 0;
        for (int i = 3; i < 6; i++)
            for (int j = 3; j < 6; j++) {
                if (i == 4 && j == 4) continue;
                ++num[a[i][j]];
            }
        return 8 - max(num[1], max(num[2], num[3]));
    }

    bool dfs(int now) {
        int cnt = gj();
        if (!cnt) return 1;
        if (now + cnt > dep) return 0;
        int b[9][9];
        memcpy(b, a, sizeof(b));
        for (int i = 1; i < 9; i++) {
            if (ans.size()) {
                int k = ans.back();
                if (k - 'A' + 1 == 1 && i == 6) continue;
                if (k - 'A' + 1 == 2 && i == 5) continue;
                if (k - 'A' + 1 == 3 && i == 8) continue;
                if (k - 'A' + 1 == 4 && i == 7) continue;
                if (k - 'A' + 1 == 5 && i == 2) continue;
                if (k - 'A' + 1 == 6 && i == 1) continue;
                if (k - 'A' + 1 == 7 && i == 4) continue;
                if (k - 'A' + 1 == 8 && i == 3) continue;
            }
            ans.push_back(i + 'A' - 1);
            work(i);
            if (dfs(now + 1)) return 1;
            ans.pop_back();
            memcpy(a, b, sizeof(a));
        }
        return 0;
    }

    void The_Rotation_Game() {
        cin >> a[1][5] >> a[2][3] >> a[2][5];
        for (int i = 1; i < 8; i++) cin >> a[3][i];
        cin >> a[4][3] >> a[4][5];
        for (int i = 1; i < 8; i++) cin >> a[5][i];
        cin >> a[6][3] >> a[6][5] >> a[7][3] >> a[7][5];
        ans.clear();
        dep = 0;
        while (!dfs(0)) ++dep;
        if (!dep) puts("No moves needed");
        else {
            for (unsigned int i = 0; i < ans.size(); i++)
                putchar(ans[i]);
            puts("");
        }
        cout << a[3][3] << endl;
    }
//    square destroyer
    const int N = 66;
    int n, k, s, tot, id[16][16], dep, tmp;
    vector<int> e[N], g[N];
    bool v[N];

    int gj() {
        bool w[N];
        memcpy(w, v, sizeof(w));
        int ans = 0;
        for (int i = 1; i <= tot; i++)
            if (w[i]) {
                if (!ans) tmp = i;
                ++ans;
                for (unsigned int j = 0; j < g[i].size(); j++)
                    for (unsigned int x = 0; x < e[g[i][j]].size(); x++)
                        w[e[g[i][j]][x]] = 0;
            }
        return ans;
    }

    bool dfs(int now) {
        int cnt = gj();
        if (!cnt) return 1;
        if (now + cnt > dep) return 0;
        bool w[N];
        memcpy(w, v, sizeof(w));
        int tmp0 = tmp;
        for (unsigned int i = 0; i < g[tmp0].size(); i++) {
            int st = g[tmp0][i];
            for (unsigned int j = 0; j < e[st].size(); j++)
                v[e[st][j]] = 0;
            if (dfs(now + 1)) return 1;
            memcpy(v, w, sizeof(v));
        }
        return 0;
    }

    void Square_Destroyer() {
        cin >> n >> k;
        s = 2 * n + 1;
        tot = 0;
        for (int i = 1; i <= s; i++)
            for (int j = 1; j <= s; j++)
                if ((i & 1) != (j & 1)) id[i][j] = ++tot;
        for (int i = 1; i <= tot; i++) e[i].clear();
        int z = n * (n + 1) * (2 * n + 1) / 6;
        for (int i = 1; i <= z; i++) g[i].clear();
        tot = 0;
        for (int a = 1; a < s; a += 2)
            for (int i = 2; i + a <= s; i += 2)
                for (int j = 2; j + a <= s; j += 2) {
                    ++tot;
                    for (int x = 0; x < a; x += 2) {
                        e[id[x+i][j-1]].push_back(tot);
                        e[id[x+i][j+a]].push_back(tot);
                        e[id[i-1][x+j]].push_back(tot);
                        e[id[i+a][x+j]].push_back(tot);
                        g[tot].push_back(id[x+i][j-1]);
                        g[tot].push_back(id[x+i][j+a]);
                        g[tot].push_back(id[i-1][x+j]);
                        g[tot].push_back(id[i+a][x+j]);
                    }
                }
        memset(v, 1, sizeof(v));
        for (int i = 1; i <= k; i++) {
            int a;
            cin >> a;
            for (unsigned int j = 0; j < e[a].size(); j++)
                v[e[a][j]] = 0;
        }
        dep = 0;
        while (!dfs(0)) ++dep;
        cout << dep << endl;
    }

};

int main() {
    Solution s = *new Solution;
    cin >> s.n >> s.m; // 点数、边数
    for (int i = 1; i <= s.m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        s.add(x, y);
    }
    s.topsort();
    s.calc();
    for (int i = 1; i <= s.n; i++) printf("%d\n", s.f[i].count());

//    cout << "hi";
}