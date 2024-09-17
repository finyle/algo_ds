#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
#include <set>

#define ll long long
using namespace std;

const int N = 1000006, INF = 0x3f3f3f3f;
int q, st1[N], st2[N], s[N], f[N];

class Solution {
public:
//    栈
    void Editor() {
//        const int N = 1000006, INF = 0x3f3f3f3f;
//        int q, st1[N], st2[N], s[N], f[N];
        int t1 = 0, t2 = 0;
        while (q--) {
            char c[2];
            scanf("%s", c);
            switch (c[0]) {
                case 'I':
                    scanf("%d", &st1[++t1]);
                    s[t1] = s[t1-1] + st1[t1];
                    f[t1] = max(f[t1-1], s[t1]);
                    continue;
                case 'D':
                    if (t1) t1--;
                    continue;
                case 'L':
                    if (t1) st2[++t2] = st1[t1--];
                    continue;
                case 'R':
                    if (!t2) continue;
                    st1[++t1] = st2[t2--];
                    s[t1] = s[t1-1] + st1[t1];
                    f[t1] = max(f[t1-1], s[t1]);
                    continue;
                case 'Q':
                    int k;
                    scanf("%d", &k);
                    printf("%d\n", f[k]);
            }
        }
    }


    void Largest(int n) {
        const int N = 100006;
        int n, a[N], s[N], w[N];
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
    void train(int x) {
        const int N = 26;
        int n, num = 0, st[N], top = 0, ans[N], t = 0;
        if (x == n + 1) {
            if (++num > 20) exit(0);
            for (int i = 1; i <= t; i++) printf("%d", ans[i]);
            for (int i = top; i; i--) printf("%d", st[i]);
            cout << endl;
            return;
        }
        if (top) {
            ans[++t] = st[top--];
            train(x);
            st[++top] = ans[t--];
        }
        st[++top] = x;
        train(x + 1);
        --top;
    }

//    队列
    void Team_Queue() {
        const int N = 1000000, T = 1006;
        int t, f[N], id = 0;
        char s[10];
        queue<int> q[T];

        q[0] = queue<int>();
        for (int i = 1; i <= t; i++) {
            int n;
            scanf("%d", &n);
            while (n--) {
                int x;
                scanf("%d", &x);
                f[x] = i;
            }
            q[i] = queue<int>();
        }
        cout << "Scenario #" << ++id << endl;
        while (scanf("%s", s) && s[0] != 'S') {
            if (s[0] == 'E') {
                int x;
                scanf("%d", &x);
                if (q[f[x]].empty()) q[0].push(f[x]);
                q[f[x]].push(x);
            } else {
                int x = q[0].front();
                printf("%d\n", q[x].front());
                q[x].pop();
                if (q[x].empty()) q[0].pop();
            }
        }
        cout << endl;
}
    int earthworm() {
        const ll INF = 0x3f3f3f3f3f3f3f3f;
        int n, m, q, u, v, t, delta = 0;
        priority_queue<ll> pq;
        queue<ll> q1, q2;

        cin >> n >> m >> q >> u >> v >> t;
        for (int i = 1; i <= n; i++) {
            ll a;
            scanf("%lld", &a);
            pq.push(a);
        }
        for (int i = 1; i <= m; i++) {
            ll maxx = -INF;
            int w;
            if (pq.size() && maxx < pq.top()) {
                maxx = pq.top();
                w = 0;
            }
            if (q1.size() && maxx < q1.front()) {
                maxx = q1.front();
                w = 1;
            }
            if (q2.size() && maxx < q2.front()) {
                maxx = q2.front();
                w = 2;
            }
            if (w == 1) q1.pop();
            else if (w == 2) q2.pop();
            else pq.pop();
            maxx += delta;
            q1.push(maxx * u / v - delta - q);
            q2.push(maxx - maxx * u / v - delta - q);
            delta += q;
            if (i % t == 0) printf("%lld ", maxx);
        }
        cout << endl;
        for (int i = 1; i <= n + m; i++) {
            ll maxx = -INF;
            int w;
            if (pq.size() && maxx < pq.top()) {
                maxx = pq.top();
                w = 0;
            }
            if (q1.size() && maxx < q1.front()) {
                maxx = q1.front();
                w = 1;
            }
            if (q2.size() && maxx < q2.front()) {
                maxx = q2.front();
                w = 2;
            }
            if (w == 1) q1.pop();
            else if (w == 2) q2.pop();
            else pq.pop();
            if (i % t == 0) printf("%lld ", maxx + delta);
        }
        cout << endl;
        return 0;
}
    int deque() {
        const int N = 200006, INF = 0x3f3f3f3f;
        pair<int, int> a[N];
        int n;
        vector<int> p[N];

        cin >> n;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i].first);
            a[i].second = i;
        }
        sort(a + 1, a + n + 1);
        int t = 0;
        for (int i = 1; i <= n; i++) {
            p[++t].push_back(a[i].second);
            while (a[i].first == a[i+1].first)
                p[t].push_back(a[++i].second);
        }
        for (int i = 1; i <= t; i++) sort(p[i].begin(), p[i].end());
        bool flag = 0;
        int num = INF, ans = 1;
        for (int i = 1; i <= t; i++) {
            int s = p[i].size();
            if (flag) {
                if (num < p[i][0]) num = p[i][s-1];
                else {
                    ++ans;
                    flag = 0;
                    num = p[i][0];
                }
            }
            else {
                if (num > p[i][s-1]) num = p[i][0];
                else {
                    flag = 1;
                    num = p[i][s-1];
                }
            }
        }
        cout << ans << endl;
        return 0;
}
    int maxSubSeq() {
        const int N = 300006, INF = 0x3f3f3f3f;
        int n, m, s[N], q[N];
        cin >> n >> m;
        s[0] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &s[i]);
            s[i] += s[i-1];
        }
        int l = 1, r = 1, ans = -INF;
        q[1] = 0;
        for (int i = 1; i <= n; i++) {
            while (l <= r && q[l] < i - m) l++;
            ans = max(ans, s[i] - s[q[l]]);
            while (l <= r && s[q[r]] >= s[i]) r--;
            q[++r] = i;
        }
        cout << ans << endl;
        return 0;
}

//  链表
    int listNode() {
        const int INF = 0x7f7f7f7f;
        set<pair<int, int> > s;
        int n, a;
        cin >> n >> a;
        s.insert(make_pair(a, 1));
        for (int i = 2; i <= n; i++) {
            scanf("%d", &a);
            s.insert(make_pair(a, i));
            set<pair<int, int> >::iterator it = s.find(make_pair(a, i));
            pair<int, int> ans;
            ans.first = INF;
            if (++it != s.end())
                ans = make_pair((*it).first - a, (*it).second);
            it = s.find(make_pair(a, i));
            if (it-- != s.begin() && ans.first >= a - (*it).first)
                ans = make_pair(a - (*it).first, (*it).second);
            cout << ans.first << " " << ans.second << endl;
        }
        return 0;
}

// hash
    const int N = 100006, P = 99991;
    int n, a[6], b[6];
    struct S {
        int s[6];
    };
    vector<S> snow[N];

    int H() {
        int s = 0, k = 1;
        for (int i = 0; i < 6; i++) {
            (s += a[i]) %= P;
            k = (ll)k * a[i] % P;
        }
        return (s + k) % P;
    }

    bool pd() {
        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 6; j++) {
                bool v = 1;
                for (int k = 0; k < 6; k++)
                    if (a[(i+k)%6] != b[(j+k%6)]) {
                        v = 0;
                        break;
                    }
                if (v) return 1;
                v = 1;
                for (int k = 0; k < 6; k++)
                    if (a[(i+k)%6] != b[(j-k+6)%6]) {
                        v = 0;
                        break;
                    }
                if (v) return 1;

            }
        return 0;
    }

    bool insert() {
        int h = H();
        for (unsigned int i = 0; i < snow[h].size(); i++) {
            memcpy(b, snow[h][i].s, sizeof(b));
            if (pd()) return 1;
        }
        S s;
        memcpy(s.s, a, sizeof(s.s));
        snow[h].push_back(s);
        return 0;
    }

   int rabbit() {
       using namespace std;
       char s[1000010];
       unsigned long long f[1000010], p[1000010];
       scanf("%s", s + 1);
       int n, q;
       n = strlen(s + 1);
       cin >> q;
       p[0] = 1; // 131^0
       for (int i = 1; i <= n; i++) {
           f[i] = f[i-1] * 131 + (s[i]-'a'+1); // hash of 1~i
           p[i] = p[i-1] * 131; // 131^i
       }
       for (int i = 1; i <= q; i++) {
           int l1, r1, l2, r2;
           scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
           if (f[r1] - f[l1-1] * p[r1-l1+1] == // hash of l1~r1
               f[r2] - f[l2-1] * p[r2-l2+1]) { // hash of l2~r2
               puts("Yes");
           } else {
               puts("No");
           }
       }
    }

//    字符串
    void calc_next() {
        char a[1000010];
        int next[1000010], n, T;
        next[1] = 0;
        for (int i = 2, j = 0; i <= n; i++) {
            while (j > 0 && a[i] != a[j+1]) j = next[j];
            if (a[i] == a[j+1]) j++;
            next[i] = j;
        }
    }

//    Trie
//    xor largest pair
    static const int SIZE=100010;
    int trie[SIZE*32+5][2], tot = 1; // 初始化，假设字符串由小写字母构成
    int a[SIZE], n, ans;

    void insert(int val) { // 插入一个二进制数
        int p = 1;
        for (int k = 30; k >= 0; k--) {
            int ch = val >> k & 1;
            if (trie[p][ch] == 0) trie[p][ch] = ++tot;
            p = trie[p][ch];
        }
    }

    int search(int val) {
        int p = 1;
        int ans = 0;
        for (int k = 30; k >= 0; k--) {
            int ch = val >> k & 1;
            if (trie[p][ch ^ 1]) { // 走相反的位
                p = trie[p][ch ^ 1];
                ans |= 1 << k;
            } else { // 只能走相同的位
                p = trie[p][ch];
            }
        }
        return ans;
    }

//    xor-longest path
    const int N = 100006;
    int n, d[N], trie[N*33][2], tot;
    vector<pair<int, int> > e[N];
    int Head[N], Edge[N*2], Leng[N*2], Next[N*2], num;
    bool v[N];

    void dfs(int x) {
        for (int i = Head[x]; i; i = Next[i]) {
            int y = Edge[i], z = Leng[i];
            if (v[y]) continue;
            v[y] = 1;
            d[y] = d[x] ^ z;
            dfs(y);
        }
    }

    void add(int x, int y, int z) {
        Edge[++tot] = y;
        Leng[tot] = z;
        Next[tot] = Head[x];
        Head[x] = tot;
    }

    void The_xor_longest_Path() {
        memset(d, 0, sizeof(d));
        memset(trie, 0, sizeof(trie));
        memset(v, 0, sizeof(v));
        memset(Head, 0, sizeof(Head));
        num = 0;
        v[0] = 1;
        tot = 1;
        for (int i = 1; i < n; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            add(u, v, w);
            add(v, u, w);
        }
        dfs(0);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int p = 1;
            for (int j = 31; j >= 0; j--) {
                int k = (d[i] >> j) & 1;
                if (!trie[p][k]) trie[p][k] = ++tot;
                p = trie[p][k];
            }
            p = 1;
            if (i) {
                int w = 0;
                for (int j = 31; j >= 0; j--) {
                    int k = (d[i] >> j) & 1;
                    if (trie[p][k^1]) {
                        w = (w << 1) + (k ^ 1);
                        p = trie[p][k^1];
                    } else {
                        w = (w << 1) + k;
                        p = trie[p][k];
                    }
                }
                ans = max(ans, w ^ d[i]);
            }
        }
        cout << ans << endl;
    }
//    前缀统计
    const int SIZE=1000010;
    int trie[SIZE][26], tot = 1; // 初始化，假设字符串由小写字母构成
    int ed[SIZE];
    int n, m;
    char str[SIZE];

    void insert(char* str) { // 插入一个字符串
        int len = strlen(str), p = 1;
        for (int k = 0; k < len; k++) {
            int ch = str[k]-'a';
            if (trie[p][ch] == 0) trie[p][ch] = ++tot;
            p = trie[p][ch];
        }
        ed[p]++;
    }

    int search(char* str) {
        int len = strlen(str), p = 1;
        int ans = 0;
        for (int k = 0; k < len; k++) {
            p = trie[p][str[k]-'a'];
            if (p == 0) return ans;
            ans += ed[p];
        }
        return ans;
    }
//    heap
    const int N = 2006;
    int m, n, f[N], a[N], b[N];
    priority_queue<pair<int, pair<int, int> > > q;

    void work() {
        priority_queue<pair<int, pair<int, int> > > w;
        swap(w, q);
        q.push(make_pair(- a[1] - b[1], make_pair(1, 1)));
        for (int i = 1; i <= n; i++) {
            f[i] = -q.top().first;
            int x = q.top().second.first, y = q.top().second.second;
            q.pop();
            if (y == 1) q.push(make_pair(- a[x+1] - b[y], make_pair(x + 1, y)));
            q.push(make_pair(- a[x] - b[y+1], make_pair(x, y + 1)));
        }
    }

    void Sequence() {
        cin >> m >> n;
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        sort(a + 1, a + n + 1);
        --m;
        while (m--) {
            for (int j = 1; j <= n; j++) scanf("%d", &b[j]);
            sort(b + 1, b + n + 1);
            work();
            memcpy(a, f, sizeof(a));
        }
        for (int i = 1; i <= n; i++) printf("%d ", a[i]);
        cout << endl;
    }

    const int N = 10006;
    int n;
    pair<int, int> a[N];
    priority_queue<int> q;

    void Supermarket() {
        for (int i = 1; i <= n; i++)
            scanf("%d %d", &a[i].second, &a[i].first);
        sort(a + 1, a + n + 1);
        for (int i = 1; i <= n; i++) {
            if (a[i].first == q.size() && -q.top() < a[i].second) {
                q.pop();
                q.push(-a[i].second);
                continue;
            }
            if (a[i].first > q.size()) q.push(-a[i].second);
        }
        int ans = 0;
        while (q.size()) {
            ans += q.top();
            q.pop();
        }
        cout << -ans << endl;
    }

    int mergeApple() {
        priority_queue<int> q;
        int n, a;
        cin >> n;
        while (n--) {
            scanf("%d", &a);
            q.push(-a);
        }
        int ans = 0;
        while (q.size() != 1) {
            int x = -q.top();
            q.pop();
            int y = -q.top();
            q.pop();
            ans += x + y;
            q.push(- x - y);
        }
        cout << ans << endl;
        return 0;
    }
//    数据备份
    const int N = 100006;
    struct L {
        int d, prv, nxt, th;
    } p[N];
    struct H {
        int D, tp;
    } h[N];
    int tot = 0;

    void up(int i) {
        while (i > 1) {
            if (h[i].D < h[i>>1].D) {
                swap(h[i], h[i>>1]);
                swap(p[h[i].tp].th, p[h[i>>1].tp].th);
                i >>= 1;
            } else return;
        }
    }

    void down(int i) {
        int ii = i << 1;
        while (ii <= tot) {
            if (ii < tot && h[ii].D > h[ii+1].D) ++ii;
            if (h[ii].D < h[i].D) {
                swap(h[ii], h[i]);
                swap(p[h[ii].tp].th, p[h[i].tp].th);
                i = ii;
                ii = i << 1;
            } else return;
        }
    }

    void DeL(int i) {
        p[p[i].prv].nxt = p[i].nxt;
        p[p[i].nxt].prv = p[i].prv;
    }

    void DeH(int i) {
        if (i == --tot + 1) return;
        swap(h[i], h[tot+1]);
        swap(p[h[i].tp].th, p[h[tot+1].tp].th);
        up(i);
        down(i);
    }

//    荷马史诗
    int epic() {
        priority_queue<pair<ll, ll> > q;
        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; i++) {
            ll a;
            scanf("%lld", &a);
            q.push(make_pair(-a, 0));
        }
        while ((n - 1) % (k - 1)) {
            ++n;
            q.push(make_pair(0, 0));
        }
        ll ans = 0;
        while (q.size() != 1) {
            ll num = 0, w = 0;
            for (int i = 1; i <= k; i++) {
                num += q.top().first;
                w = min(w, q.top().second);
                q.pop();
            }
            ans += -num;
            q.push(make_pair(num, w - 1));
        }
        cout << ans << endl << -q.top().second << endl;
        return 0;
    }
//    exp
};

int main() {
    Solution s1 = *new Solution;
    s[0] = 0;
    f[0] = -INF;
    while (cin >> q) s1.Editor();
    return 0;
}