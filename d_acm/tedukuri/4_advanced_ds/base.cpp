#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
//    并查集：
//    程序自动分析
    static const int N = 100006;
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
        Solution s = *new Solution();
        int t;
        cin >> t;
        while (t--) s.cxzdfx();
        return 0;
    }

//    supermarket
    const int N = 10006;
    int n, fa[N];
    pair<int, int> p[N];

    int get(int x) {
        if (x == fa[x]) return x;
        return fa[x] = get(fa[x]);
    }

    void Supermarket() {
        int d = 0, ans = 0;
        for (int i = 1; i <= n; i++) {
            cin >> p[i].first >> p[i].second;
            d = max(d, p[i].second);
        }
        for (int i = 0; i <= d; i++) fa[i] = i;
        sort(p + 1, p + n + 1);
        for (int i = n; i; i--) {
            int x = get(p[i].second);
            if (x) {
                ans += p[i].first;
                fa[x] = x - 1;
            }
        }
        cout << ans << endl;
    }

//    银河英雄传
    const int N = 30001;
    int fa[N], d[N], s[N];

    int get(int x) {
        if (x == fa[x]) return x;
        int root = get(fa[x]);
        d[x] += d[fa[x]];
        return fa[x] = root;
    }

    int main() {
        int t;
        cin >> t;
        for (int i = 1; i < N; i++) {
            fa[i] = i;
            s[i] = 1;
            d[i] = 0;
        }
        while (t--) {
            char c;
            cin >> c;
            int x, y;
            cin >> x >> y;
            int m = get(x), n = get(y);
            if (c == 'M') {
                fa[m] = n;
                d[m] = s[n];
                s[n] += s[m];
            } else {
                if (m == n) cout << abs(d[x] - d[y]) - 1 << endl;
                else cout << "-1" << endl;
            }
        }
        return 0;
    }

//      parity game
    struct { int l, r, ans; } query[10010];
    int a[20010], fa[40010], n, m, t;
    void read_discrete() { // 读入、离散化
        cin >> n >> m;
        for (int i = 1; i <= m; i++) {
            char str[5];
            scanf("%d%d%s", &query[i].l, &query[i].r, str);
            query[i].ans = (str[0] == 'o' ? 1 : 0);
            a[++t] = query[i].l - 1;
            a[++t] = query[i].r;
        }
        sort(a + 1, a + t + 1);
        n = unique(a + 1, a + t + 1) - a - 1;
    }
    int get(int x) {
        if (x == fa[x]) return x;
        return fa[x] = get(fa[x]);
    }
    int main() {
        read_discrete();
        for (int i = 1; i <= 2 * n; i++) fa[i] = i;
        for (int i = 1; i <= m; i++) {
            // 求出l-1和r离散化之后的值
            int x = lower_bound(a + 1, a + n + 1, query[i].l - 1) - a;
            int y = lower_bound(a + 1, a + n + 1, query[i].r) - a;
            int x_odd = x, x_even = x + n;
            int y_odd = y, y_even = y + n;
            if (query[i].ans == 0) { // 回答奇偶性相同
                if (get(x_odd) == get(y_even)) { // 与已知情况矛盾
                    cout << i - 1 << endl;
                    return 0;
                }
                fa[get(x_odd)] = get(y_odd); // 合并
                fa[get(x_even)] = get(y_even);
            }
            else { // 回答奇偶性不同
                if (get(x_odd) == get(y_odd)) { // 与已知情况矛盾
                    cout << i - 1 << endl;
                    return 0;
                }
                fa[get(x_odd)] = get(y_even); // 合并
                fa[get(x_even)] = get(y_odd);
            }
        }
        cout << m << endl; // 没有矛盾
    }

//    食物链
    const int N = 50006;
    int fa[3*N];

    int get(int x) {
        if (x == fa[x]) return x;
        return fa[x] = get(fa[x]);
    }

    int main() {
        int n, k, ans = 0;
        cin >> n >> k;
        for (int i = 1; i <= 3 * n; i++) fa[i] = i;
        while (k--) {
            int num, x, y;
            scanf("%d %d %d", &num, &x, &y);
            if (x > n || y > n || (num == 2 && x == y)) {
                ++ans;
                continue;
            }
            if (num == 1 && (get(x) == get(y + n) || get(x + n) == get(y))) {
                ++ans;
                continue;
            }
            if (num == 2 && (get(x) == get(y) || get(x) == get(y + n))) {
                ++ans;
                continue;
            }
            if (num == 1) {
                fa[get(x)] = get(y);
                fa[get(x+n)] = get(y + n);
                fa[get(x+2*n)] = get(y + 2 * n);
            } else {
                fa[get(x+n)] = get(y);
                fa[get(x+2*n)] = get(y + n);
                fa[get(x)] = get(y + 2 * n);
            }
        }
        cout << ans << endl;
        return 0;
    }

//    树状数组
//      楼兰图腾
    const int N = 200006;
    int n, a[N], c[N], l[N], r[N];

    int ask(int x) {
        int ans = 0;
        while (x) {
            ans += c[x];
            x -= x & -x;
        }
        return ans;
    }

    void add(int x, int y) {
        while (x <= n) {
            c[x] += y;
            x += x & -x;
        }
    }

    int main() {
        cin >> n;
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        memset(c, 0, sizeof(c));
        for (int i = n; i; i--) {
            r[i] = ask(a[i] - 1);
            add(a[i], 1);
        }
        memset(c, 0, sizeof(c));
        for (int i = 1; i <= n; i++) {
            l[i] = ask(a[i] - 1);
            add(a[i], 1);
        }
        ll ans = 0;
        for (int i = 1; i <= n; i++)
            ans += (ll)(n - i - r[i]) * (i - 1 - l[i]);
        cout << ans << " ";
        ans = 0;
        for (int i = 1; i <= n; i++) ans += (ll)r[i] * l[i];
        cout << ans << endl;
        return 0;
    }

//    a simple problem with integers
    const int SIZE=100010;
    int a[SIZE],n,m;
    long long c[2][SIZE],sum[SIZE];

    long long ask(int k,int x)
    {
        long long ans=0;
        for(;x;x-=x&-x) ans+=c[k][x];
        return ans;
    }

    void add(int k,int x,int y)
    {
        for(;x<=n;x+=x&-x) c[k][x]+=y;
    }

    int main()
    {
        cin>>n>>m;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            sum[i]=sum[i-1]+a[i];
        }
        while(m--)
        {
            char op[2]; int l,r,d;
            scanf("%s%d%d",op,&l,&r);
            if(op[0]=='C')
            {
                scanf("%d",&d);
                add(0,l,d);
                add(0,r+1,-d);
                add(1,l,l*d);
                add(1,r+1,-(r+1)*d);
            }
            else{
                long long ans=sum[r]+(r+1)*ask(0,r)-ask(1,r);
                ans-=sum[l-1]+l*ask(0,l-1)-ask(1,l-1);
                printf("%lld\n",ans);
            }
        }
    }

//    lost cows
    const int N = 8006;
    int n, a[N], c[N], h[N];

    void add(int x) {
        while (x <= n) {
            --c[x];
            x += x & -x;
        }
    }

    int ask(int x) {
        int ans = 0;
        while (x) {
            ans += c[x];
            x -= x & -x;
        }
        return ans;
    }

    int main() {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            ++c[i];
            if (i + (i & -i) <= n) c[i+(i&-i)] += c[i];
        }
        a[1] = 1;
        for (int i = 2; i <= n; i++) {
            scanf("%d", &a[i]);
            ++a[i];
        }
        for (int i = n; i; i--) {
            int l = 1, r = n;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (ask(mid) < a[i]) l = mid + 1;
                else r = mid;
            }
            add(h[i] = l);
        }
        for (int i = 1; i <= n; i++) printf("%d\n", h[i]);
        return 0;
    }

//    线段树
//      can you answer on these queries
    const int N = 500006, INF = 0x3f3f3f3f;
    int n, m, a[N];
    struct T {
        int l, r, s, lx, rx, ans;
    } t[N*4];

    void build(int p, int l, int r) {
        t[p].l = l;
        t[p].r = r;
        if (l == r) {
            t[p].s = t[p].lx = t[p].rx = t[p].ans = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        t[p].s = t[p<<1].s + t[p<<1|1].s;
        t[p].lx = max(t[p<<1].lx, t[p<<1].s + t[p<<1|1].lx);
        t[p].rx = max(t[p<<1|1].rx, t[p<<1].rx + t[p<<1|1].s);
        t[p].ans = max(max(t[p<<1].ans, t[p<<1|1].ans), t[p<<1].rx + t[p<<1|1].lx);
    }

    void change(int p, int x, int y) {
        if (t[p].l == t[p].r) {
            t[p].s = t[p].lx = t[p].rx = t[p].ans = y;
            return;
        }
        int mid = (t[p].l + t[p].r) >> 1;
        if (x <= mid) change(p << 1, x, y);
        else change(p << 1 | 1, x, y);
        t[p].s = t[p<<1].s + t[p<<1|1].s;
        t[p].lx = max(t[p<<1].lx, t[p<<1].s + t[p<<1|1].lx);
        t[p].rx = max(t[p<<1|1].rx, t[p<<1].rx + t[p<<1|1].s);
        t[p].ans = max(max(t[p<<1].ans, t[p<<1|1].ans), t[p<<1].rx + t[p<<1|1].lx);
    }

    T ask(int p, int l, int r) {
        if (l <= t[p].l && r >= t[p].r) return t[p];
        T a, b, ans;
        a.s = a.lx = a.rx = a.ans = b.s = b.lx = b.rx = b.ans = -INF;
        ans.s = 0;
        int mid = (t[p].l + t[p].r) >> 1;
        if (l <= mid) {
            a = ask(p << 1, l, r);
            ans.s += a.s;
        }
        if (r > mid) {
            b = ask(p << 1 | 1, l, r);
            ans.s += b.s;
        }
        ans.ans = max(max(a.ans, b.ans), a.rx + b.lx);
        ans.lx = max(a.lx, a.s + b.lx);
        ans.rx = max(b.rx, b.s + a.rx);
        if (l > mid) ans.lx = max(ans.lx, b.lx);
        if (r <= mid) ans.rx = max(ans.rx, a.rx);
        return ans;
    }

//    intervel GCD
    const int N = 500006;
    int n, m;
    ll a[N], b[N], c[N];
    struct T {
        int l, r;
        ll ans;
    } t[N*4];

    ll gcd(ll x, ll y) {
        return y ? gcd(y, x % y) : x;
    }

    void build(int p, int l, int r) {
        t[p].l = l;
        t[p].r = r;
        if (l == r) {
            t[p].ans = b[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        t[p].ans = gcd(t[p<<1].ans, t[p<<1|1].ans);
    }

    void change_add(int p, int x, ll v) {
        if (t[p].l == t[p].r) {
            t[p].ans += v;
            return;
        }
        int mid = (t[p].l + t[p].r) >> 1;
        if (x <= mid) change_add(p << 1, x, v);
        else change_add(p << 1 | 1, x, v);
        t[p].ans = gcd(t[p<<1].ans, t[p<<1|1].ans);
    }

    ll ask_t(int p, int l, int r) {
        if (l <= t[p].l && r >= t[p].r) return t[p].ans;
        int mid = (t[p].l + t[p].r) >> 1;
        ll ans = 0;
        if (l <= mid) ans = gcd(ans, ask_t(p << 1, l, r));
        if (r > mid) ans = gcd(ans, ask_t(p << 1 | 1, l, r));
        return abs(ans);
    }

    void add(int x, ll y) {
        while (x <= n) {
            c[x] += y;
            x += x & -x;
        }
    }

    ll ask_c(int x) {
        ll ans = 0;
        while (x) {
            ans += c[x];
            x -= x & -x;
        }
        return ans;
    }

//      atlantis
#define ls (p << 1)
#define rs (ls | 1)
#define mid ((t[p].l + t[p].r) >> 1)
    using namespace std;
    const int N = 1e5 + 6;
    int n, m, num;
    struct P {
        double x, y, z;
        int k;
        inline bool operator < (const P &o) const {
            return x < o.x;
        }
    } a[N<<1];
    double raw[N<<1];
    map<double, int> val;
    struct T {
        int l, r, cnt;
        double len;
    } t[N<<3];

    void build(int p, int l, int r) {
        t[p].l = l, t[p].r = r, t[p].cnt = 0, t[p].len = 0;
        if (l == r) return;
        build(ls, l, mid), build(rs, mid + 1, r);
    }

    void change(int p, int l, int r, double k) {
        if (l <= t[p].l && r >= t[p].r) return t[p].len = ((t[p].cnt += k) ? raw[t[p].r+1] - raw[t[p].l] : (t[p].l == t[p].r ? 0 : t[ls].len + t[rs].len)), void();
        if (l <= mid) change(ls, l, r, k);
        if (r > mid) change(rs, l, r, k);
        t[p].len = (t[p].cnt ? raw[t[p].r+1] - raw[t[p].l] : t[ls].len + t[rs].len);
    }

    inline void Atlantis() {
        for (int i = 1; i <= n; i++) {
            int k = i << 1;
            double y, z;
            scanf("%lf %lf %lf %lf", &a[k-1].x, &y, &a[k].x, &z);
            raw[k-1] = a[k-1].y = a[k].y = y;
            raw[k] = a[k-1].z = a[k].z = z;
            a[k-1].k = 1, a[k].k = -1;
        }
        n <<= 1;
        sort(raw + 1, raw + n + 1);
        int m = unique(raw + 1, raw + n + 1) - (raw + 1);
        for (int i = 1; i <= m; i++) val[raw[i]] = i;
        sort(a + 1, a + n + 1);
        build(1, 1, m - 1);
        double ans = 0;
        for (int i = 1; i < n; i++) {
            int y = val[a[i].y], z = val[a[i].z] - 1;
            change(1, y, z, a[i].k);
            ans += t[1].len * (a[i+1].x - a[i].x);
        }
        printf("Test case #%d\nTotal explored area: %.2f\n\n", ++num, ans);
    }

//    starts in windows
    const int N = 10006;
    int n;
    struct P {
        unsigned int x, y, z;
        int c;
        bool operator < (const P w) const {
            return x < w.x || (x == w.x && c < w.c);
        }
    } a[N<<1];
    unsigned int w, h, b[N<<1];
    struct T {
        int l, r, ans, add;
    } t[N<<3];

    void build(int p, int l, int r) {
        t[p].l = l;
        t[p].r = r;
        t[p].ans = t[p].add = 0;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
    }

    void spread(int p) {
        t[p<<1].add += t[p].add;
        t[p<<1].ans += t[p].add;
        t[p<<1|1].add += t[p].add;
        t[p<<1|1].ans += t[p].add;
        t[p].add = 0;
    }

    void change(int p, int l, int r, int c) {
        if (l <= t[p].l && r >= t[p].r) {
            t[p].add += c;
            t[p].ans += c;
            return;
        }
        if (t[p].add) spread(p);
        int mid = (t[p].l + t[p].r) >> 1;
        if (l <= mid) change(p<<1, l, r, c);
        if (r > mid) change(p<<1|1, l, r, c);
        t[p].ans = max(t[p<<1].ans, t[p<<1|1].ans);
    }

    void Stars_in_Your_Window() {
        for (int i = 1; i <= n; i++) {
            int k = i << 1;
            scanf("%u %u %d", &a[k-1].x, &a[k-1].y, &a[k-1].c);
            a[k].x = a[k-1].x + w;
            b[k-1] = a[k].y = a[k-1].y;
            b[k] = a[k].z = a[k-1].z = a[k].y + h - 1;
            a[k].c = -a[k-1].c;
        }
        n <<= 1;
        sort(b + 1, b + n + 1);
        int m = unique(b + 1, b + n + 1) - (b + 1);
        for (int i = 1; i <= n; i++) {
            a[i].y = lower_bound(b + 1, b + m + 1, a[i].y) - b;
            a[i].z = lower_bound(b + 1, b + m + 1, a[i].z) - b;
        }
        sort(a + 1, a + n + 1);
        build(1, 1, m);
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            change(1, a[i].y, a[i].z, a[i].c);
            ans = max(ans, t[1].ans);
        }
        cout << ans << endl;
    }

//    分块
//      a simple problem with integers
    long long a[100010], sum[100010], add[100010];
    int L[100010], R[100010]; // 每段左右端点
    int pos[100010]; // 每个位置属于哪一段
    int n, m, t;

    void change(int l, int r, long long d) {
        int p = pos[l], q = pos[r];
        if (p == q) {
            for (int i = l; i <= r; i++) a[i] += d;
            sum[p] += d*(r - l + 1);
        }
        else {
            for (int i = p + 1; i <= q - 1; i++) add[i] += d;
            for (int i = l; i <= R[p]; i++) a[i] += d;
            sum[p] += d*(R[p] - l + 1);
            for (int i = L[q]; i <= r; i++) a[i] += d;
            sum[q] += d*(r - L[q] + 1);
        }
    }

    long long ask(int l, int r) {
        int p = pos[l], q = pos[r];
        long long ans = 0;
        if (p == q) {
            for (int i = l; i <= r; i++) ans += a[i];
            ans += add[p] * (r - l + 1);
        }
        else {
            for (int i = p + 1; i <= q - 1; i++)
                ans += sum[i] + add[i] * (R[i] - L[i] + 1);
            for (int i = l; i <= R[p]; i++) ans += a[i];
            ans += add[p] * (R[p] - l + 1);
            for (int i = L[q]; i <= r; i++) ans += a[i];
            ans += add[q] * (r - L[q] + 1);
        }
        return ans;
    }

//    蒲公英
    const int u=40010;
    int c[40][40][u],f[40][40],d[40][40],a[u],b[u],fa[u],fb[u],st[40],ed[40];
    int n,m,t,l,tot,i,j,k,x,y,ans,L,R,cnt,num;

    void prework()
    {
        t=(int)pow(n*1.0,1.0/3);
        if(t) l=n/t;
        for(i=1;i<=t;i++) st[i]=(i-1)*l+1,ed[i]=i*l;
        if(ed[t]<n) st[t+1]=ed[t]+1,ed[++t]=n;
        memcpy(fa,a,sizeof(a));
        sort(fa+1,fa+n+1);
        for(i=1;i<=n;i++)
            if(i==1||fa[i]!=fa[i-1]) fb[++tot]=fa[i];
        for(i=1;i<=n;i++) b[i]=lower_bound(fb+1,fb+tot+1,a[i])-fb;
        for(i=1;i<=t;i++)
            for(j=i;j<=t;j++)
            {
                for(k=st[i];k<=ed[j];k++) c[i][j][b[k]]++;
                for(k=1;k<=tot;k++)
                    if(c[i][j][k]>f[i][j]||c[i][j][k]==f[i][j]&&k<d[i][j])
                        f[i][j]=c[i][j][k],d[i][j]=k;
            }
    }

    inline void update(int i)
    {
        c[L][R][b[i]]++;
        if(c[L][R][b[i]]>cnt||c[L][R][b[i]]==cnt&&b[i]<num) cnt=c[L][R][b[i]],num=b[i];
    }

    int solve(int x,int y)
    {
        int i,l,r;
        if(x>y) swap(x,y);
        for(i=1;i<=t;i++) if(x<=ed[i]) {l=i; break;}
        for(i=t;i;i--) if(y>=st[i]) {r=i; break;}
        if(l+1<=r-1) L=l+1,R=r-1; else L=R=0;
        cnt=f[L][R],num=d[L][R];
        if(l==r)
        {
            for(i=x;i<=y;i++) update(i);
            for(i=x;i<=y;i++) c[L][R][b[i]]--;
        }
        else{
            for(i=x;i<=ed[l];i++) update(i);
            for(i=st[r];i<=y;i++) update(i);
            for(i=x;i<=ed[l];i++) c[L][R][b[i]]--;
            for(i=st[r];i<=y;i++) c[L][R][b[i]]--;
        }
        return fb[num];
    }

//    磁力快
#define ll long long
    using namespace std;
    const int N = 250006;
    struct P {
        int x, y, m, p, r;
    } p[N], q[N];
    bool b[N];
    int n, L[N], R[N], M[N];

    bool cmp(P a, P b) {
        return a.m < b.m;
    }

    bool cmp0(P a, P b) {
        return (ll)(a.x - q[0].x) * (a.x - q[0].x) + (ll)(a.y - q[0].y) * (a.y - q[0].y) < (ll)(b.x - q[0].x) * (b.x - q[0].x) + (ll)(b.y - q[0].y) * (b.y - q[0].y);
    }

    bool pd(P a, P b) {
        return (ll)(q[0].x - b.x) * (q[0].x - b.x) + (ll)(q[0].y - b.y) * (q[0].y - b.y) <= (ll)a.r * a.r;
    }

    int main() {
        cin >> q[0].x >> q[0].y >> q[0].p >> q[0].r >> n;
        for (int i = 1; i <= n; i++)
            scanf("%d %d %d %d %d", &p[i].x, &p[i].y, &p[i].m, &p[i].p, &p[i].r);
        sort(p + 1, p + n + 1, cmp);
        int t = sqrt(n);
        for (int i = 1; i <= t; i++) {
            L[i] = (i - 1) * t + 1;;
            R[i] = i * t;
            M[i] = p[R[i]].m;
            sort(p + L[i], p + R[i] + 1, cmp0);
        }
        if (R[t] < n) {
            L[t+1] = R[t] + 1;
            R[++t] = n;
            M[t] = p[R[t]].m;
            sort(p + L[t], p + R[t] + 1, cmp0);
        }
        int l = 0, r = 1;
        memset(b, 0, sizeof(b));
        while (l < r) {
            int k = 0;
            for (int i = 1; i <= t; i++)
                if (M[i] <= q[l].p) k = i;
                else break;
            for (int i = 1; i <= k; i++)
                while (L[i] <= R[i] && pd(q[l], p[L[i]])) {
                    if (!b[L[i]]) {
                        b[L[i]] = 1;
                        q[r++] = p[L[i]];
                    }
                    ++L[i];
                }
            if (t != k++)
                for (int i = L[k]; i <= R[k]; i++)
                    if (!b[i] && p[i].m <= q[l].p && pd(q[l], p[i])) {
                        b[i] = 1;
                        q[r++] = p[i];
                    }
            ++l;
        }
        cout << r - 1 << endl;
        return 0;
    }

//    小z的袜子
    const int N = 50006;
    int n, m, c[N], L[N], R[N], num[N];
    struct P {
        int id, l, r;
    } p[N];
    ll ans, Ans[N][2], g;

    bool cmp(P a, P b) {
        return a.l < b.l || (a.l == b.l && a.r < b.r);
    }

    bool cmp0(P a, P b) {
        return a.r < b.r;
    }

    void work(int x, int w) {
        ans -= (ll)num[x] * (num[x] - 1);
        num[x] += w;
        ans += (ll)num[x] * (num[x] - 1);
    }

    ll gcd(ll a, ll b) {
        return b ? gcd(b, a % b) : a;
    }

    int main() {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
        for (int i = 1; i <= m; i++) {
            scanf("%d %d", &p[i].l, &p[i].r);
            p[i].id = i;
        }
        sort(p + 1, p + m + 1, cmp);
        int t = sqrt(m);
        for (int i = 1; i <= t; i++) {
            L[i] = (i - 1) * t + 1;
            R[i] = i * t;
        }
        if (R[t] < m) {
            L[t+1] = R[t] + 1;
            R[++t] = m;
        }
        for (int i = 1; i <= t; i++) {
            sort(p + L[i], p + R[i] + 1, cmp0);
            memset(num, 0, sizeof(num));
            ans = 0;
            int l = p[L[i]].l, r = p[L[i]].r;
            for (int j = l; j <= r; j++) work(c[j], 1);
            Ans[p[L[i]].id][0] = ans;
            Ans[p[L[i]].id][1] = (ll)(r - l) * (r - l + 1);
            g = gcd(Ans[p[L[i]].id][0], Ans[p[L[i]].id][1]);
            if (!g) Ans[p[L[i]].id][1] = 1;
            else {
                Ans[p[L[i]].id][0] /= g;
                Ans[p[L[i]].id][1] /= g;
            }
            for (int j = L[i] + 1; j <= R[i]; j++) {
                while (r < p[j].r) work(c[++r], 1);
                while (r > p[j].r) work(c[r--], -1);
                while (l < p[j].l) work(c[l++], -1);
                while (l > p[j].l) work(c[--l], 1);
                if (p[j].l == p[j].r) {
                    Ans[p[j].id][0] = 0;
                    Ans[p[j].id][1] = 1;
                } else {
                    Ans[p[j].id][0] = ans;
                    Ans[p[j].id][1] = (ll)(r - l) * (r - l + 1);
                    g = gcd(Ans[p[j].id][0], Ans[p[j].id][1]);
                    if (!g) Ans[p[j].id][1] = 1;
                    else {
                        Ans[p[j].id][0] /= g;
                        Ans[p[j].id][1] /= g;
                    }
                }
            }
        }
        for (int i = 1; i <= m; i++)
            printf("%lld/%lld\n", Ans[i][0], Ans[i][1]);
        return 0;
    }

//    点分治
    const int N = 10006;
    int n, k, s[N], Ans;
    bool v[N], w[N];
    int Head[N], Edge[N<<1], Leng[N<<1], Next[N<<1], t;
    int ans, pos;
    int d[N], b[N], a[N], tot, cnt[N];

    void dfs_find(int S, int x) {
        v[x] = 1;
        s[x] = 1;
        int max_part = 0;
        for (int i = Head[x]; i; i = Next[i]) {
            int y = Edge[i];
            if (v[y] || w[y]) continue;
            dfs_find(S, y);
            s[x] += s[y];
            max_part = max(max_part, s[y]);
        }
        max_part = max(max_part, S - s[x]);
        if (max_part < ans) {
            ans = max_part;
            pos = x;
        }
    }

    void dfs(int x) {
        v[x] = 1;
        for (int i = Head[x]; i; i = Next[i]) {
            int y = Edge[i], z = Leng[i];
            if (v[y] || w[y]) continue;
            ++cnt[b[a[++tot]=y]=b[x]];
            d[y] = d[x] + z;
            dfs(y);
        }
    }

    bool cmp(int i, int j) {
        return d[i] < d[j];
    }

    void work(int S, int x) {
        memset(v, 0, sizeof(v));
        ans = S;
        dfs_find(S, x);
        memset(d, 0, sizeof(d));
        memset(cnt, 0, sizeof(cnt));
        memset(v, 0, sizeof(v));
        w[a[tot=1]=b[pos]=pos] = 1;
        ++cnt[pos];
        for (int i = Head[pos]; i; i = Next[i]) {
            int y = Edge[i], z = Leng[i];
            if (v[y] || w[y]) continue;
            ++cnt[a[++tot]=b[y]=y];
            d[y] = z;
            dfs(y);
        }
        sort(a + 1, a + tot + 1, cmp);
        int l = 1, r = tot;
        --cnt[b[a[1]]];
        while (l < r) {
            while (d[a[l]] + d[a[r]] > k) --cnt[b[a[r--]]];
            Ans += r - l - cnt[b[a[l]]];
            --cnt[b[a[++l]]];
        }
        int now = pos;
        for (int i = Head[now]; i; i = Next[i]) {
            int y = Edge[i];
            if (w[y]) continue;
            work(s[y], y);
        }
    }

    void add(int x, int y, int z) {
        Edge[++t] = y;
        Leng[t] = z;
        Next[t] = Head[x];
        Head[x] = t;
    }

    void Tree() {
        t = 0;
        memset(Head, 0, sizeof(Head));
        for (int i = 1; i < n; i++) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            add(x, y, z);
            add(y, x, z);
        }
        memset(w, 0, sizeof(w));
        Ans = 0;
        work(n, 1);
        cout << Ans << endl;
    }


//    二叉查找树
    const int SIZE = 100010;
    struct Treap {
        int l, r; // 左右子节点在数组中的下标
        int val, dat; // 节点关键码、权值
        int cnt, size; // 副本数、子树大小
    } a[SIZE]; // 数组模拟链表
    int tot, root, n, INF = 0x7fffffff;

    int New(int val) {
        a[++tot].val = val;
        a[tot].dat = rand();
        a[tot].cnt = a[tot].size = 1;
        return tot;
    }

    void Update(int p) {
        a[p].size = a[a[p].l].size + a[a[p].r].size + a[p].cnt;
    }

    void Build() {
        New(-INF), New(INF);
        root = 1, a[1].r = 2;
        Update(root);
    }

    int GetRankByVal(int p, int val) {
        if (p == 0) return 0;
        if (val == a[p].val) return a[a[p].l].size + 1;
        if (val < a[p].val) return GetRankByVal(a[p].l, val);
        return GetRankByVal(a[p].r, val) + a[a[p].l].size + a[p].cnt;
    }

    int GetValByRank(int p, int rank) {
        if (p == 0) return INF;
        if (a[a[p].l].size >= rank) return GetValByRank(a[p].l, rank);
        if (a[a[p].l].size + a[p].cnt >= rank) return a[p].val;
        return GetValByRank(a[p].r, rank - a[a[p].l].size - a[p].cnt);
    }

    void zig(int &p) {
        int q = a[p].l;
        a[p].l = a[q].r, a[q].r = p, p = q;
        Update(a[p].r), Update(p);
    }

    void zag(int &p) {
        int q = a[p].r;
        a[p].r = a[q].l, a[q].l = p, p = q;
        Update(a[p].l), Update(p);
    }

    void Insert(int &p, int val) {
        if (p == 0) {
            p = New(val);
            return;
        }
        if (val == a[p].val) {
            a[p].cnt++, Update(p);
            return;
        }
        if (val < a[p].val) {
            Insert(a[p].l, val);
            if (a[p].dat < a[a[p].l].dat) zig(p); // 不满足堆性质，右旋
        }
        else {
            Insert(a[p].r, val);
            if (a[p].dat < a[a[p].r].dat) zag(p); // 不满足堆性质，左旋
        }
        Update(p);
    }

    int GetPre(int val) {
        int ans = 1; // a[1].val==-INF
        int p = root;
        while (p) {
            if (val == a[p].val) {
                if (a[p].l > 0) {
                    p = a[p].l;
                    while (a[p].r > 0) p = a[p].r; // 左子树上一直向右走
                    ans = p;
                }
                break;
            }
            if (a[p].val < val && a[p].val > a[ans].val) ans = p;
            p = val < a[p].val ? a[p].l : a[p].r;
        }
        return a[ans].val;
    }

    int GetNext(int val) {
        int ans = 2; // a[2].val==INF
        int p = root;
        while (p) {
            if (val == a[p].val) {
                if (a[p].r > 0) {
                    p = a[p].r;
                    while (a[p].l > 0) p = a[p].l; // 右子树上一直向左走
                    ans = p;
                }
                break;
            }
            if (a[p].val > val && a[p].val < a[ans].val) ans = p;
            p = val < a[p].val ? a[p].l : a[p].r;
        }
        return a[ans].val;
    }

    void Remove(int &p, int val) {
        if (p == 0) return;
        if (val == a[p].val) { // 检索到了val
            if (a[p].cnt > 1) { // 有重复，减少副本数即可
                a[p].cnt--, Update(p);
                return;
            }
            if (a[p].l || a[p].r) { // 不是叶子节点，向下旋转
                if (a[p].r == 0 || a[a[p].l].dat > a[a[p].r].dat)
                    zig(p), Remove(a[p].r, val);
                else
                    zag(p), Remove(a[p].l, val);
                Update(p);
            }
            else p = 0; // 叶子节点，删除
            return;
        }
        val < a[p].val ? Remove(a[p].l, val) : Remove(a[p].r, val);
        Update(p);
    }

    int main() {
        Build();
        cin >> n;
        while (n--) {
            int opt, x;
            scanf("%d%d", &opt, &x);
            switch (opt) {
                case 1:
                    Insert(root, x);
                    break;
                case 2:
                    Remove(root, x);
                    break;
                case 3:
                    printf("%d\n", GetRankByVal(root, x) - 1);
                    break;
                case 4:
                    printf("%d\n", GetValByRank(root, x + 1));
                    break;
                case 5:
                    printf("%d\n", GetPre(x));
                    break;
                case 6:
                    printf("%d\n", GetNext(x));
                    break;
            }
        }
    }

//    离线分治算法
//      天使玩偶
    const int u = 1000010;
    struct rec { int x, y, z; };
    rec a[u]; // 原始问题的操作序列（长度为n+m）
    rec b[u]; // 静态问题的坐标（按横坐标排序）及其在a中的下标
    int c[u], tot; // 树状数组、坐标的最大范围
    int ans[u], n, m, t;

    bool operator <(const rec &a, const rec &b) {
        return a.x < b.x || a.x == b.x && a.y < b.y;
    }

    int ask(int x) {
        int y = -(1 << 30);
        for (; x; x -= x & -x) y = max(y, c[x]);
        return y;
    }

    void insert(int x, int y) {
        for (; x < tot; x += x & -x) c[x] = max(c[x], y);
    }

// 求解简化版问题，需要考虑b[st~ed]的坐标，根据4个方向的不同，
// 横坐标顺序为de(±1)，树状数组维护的信息用系数dx,dy(±1)指定
    void calc(int st, int ed, int de, int dx, int dy) {
        for (int i = st; i != ed; i += de) {
            int y = dy == 1 ? b[i].y : tot - b[i].y;
            int temp = dx*b[i].x + dy*b[i].y;
            if (a[b[i].z].z == 1) insert(y, temp);
            else ans[b[i].z] = min(ans[b[i].z], abs(temp - ask(y)));
        }
        for (int i = st; i != ed; i += de) { // 还原树状数组
            int y = dy == 1 ? b[i].y : tot - b[i].y;
            if (a[b[i].z].z == 1) // 撤销修改
                for (int j = y; j < tot; j += j & -j) c[j] = -(1 << 30);
        }
    }

    void cdqdiv(int l, int r) {
        int mid = (l + r) >> 1;
        if (l < mid) cdqdiv(l, mid);
        if (mid + 1 < r) cdqdiv(mid + 1, r);
        t = 0;
        for (int i = l; i <= r; i++)
            if (i <= mid && a[i].z == 1 || i > mid && a[i].z == 2)
                b[++t] = a[i], b[t].z = i;
        // 此处排序可以优化掉（放在外边并适当修改写法）
        sort(b + 1, b + t + 1);
        calc(1, t + 1, 1, 1, 1), calc(t, 0, -1, -1, -1);
        calc(1, t + 1, 1, 1, -1), calc(t, 0, -1, -1, 1);
    }

//      k-th number
    const int N = 100010, INF = 1e9;
    struct rec {int op, x, y, z;} q[2 * N], lq[2 * N], rq[2 * N];
    int n, m, t, c[N], ans[N];

    int ask(int x) {
        int y = 0;
        for (; x; x -= x & -x) y += c[x];
        return y;
    }

    void change(int x, int y) {
        for (; x <= n; x += x & -x) c[x] += y;
    }

    void solve(int lval, int rval, int st, int ed) {
        if (st > ed) return;
        if (lval == rval) {
            for (int i = st; i <= ed; i++)
                if (q[i].op > 0) ans[q[i].op] = lval;
            return;
        }
        int mid = (lval + rval) >> 1;
        int lt = 0, rt = 0;
        for (int i = st; i <= ed; i++) {
            if (q[i].op == 0) { // 是一次赋值操作
                if (q[i].y <= mid) change(q[i].x, 1), lq[++lt] = q[i];
                else rq[++rt] = q[i];
            } else { // 是一次询问
                int cnt = ask(q[i].y) - ask(q[i].x - 1);
                if (cnt >= q[i].z) lq[++lt] = q[i];
                else q[i].z -= cnt, rq[++rt] = q[i];
            }
        }
        for (int i = ed; i >= st; i--) { // 还原树状数组
            if (q[i].op == 0 && q[i].y <= mid) change(q[i].x, -1);
        }
        for (int i = 1; i <= lt; i++) q[st + i - 1] = lq[i];
        for (int i = 1; i <= rt; i++) q[st + lt + i - 1] = rq[i];
        solve(lval, mid, st, st + lt - 1);
        solve(mid + 1, rval, st + lt, ed);
    }

//    dynamic ranking
    const int N = 100010, INF = 1e9;
    struct rec {int op, x, y, z;} q[3 * N], lq[3 * N], rq[3 * N];
    int T, n, m, t, p, a[N], c[N], ans[N];

    int ask(int x) {
        int y = 0;
        for (; x; x -= x & -x) y += c[x];
        return y;
    }

    void change(int x, int y) {
        for (; x <= n; x += x & -x) c[x] += y;
    }

    void solve(int lval, int rval, int st, int ed) {
        if (st > ed) return;
        if (lval == rval) {
            for (int i = st; i <= ed; i++)
                if (q[i].op > 0) ans[q[i].op] = lval;
            return;
        }
        int mid = (lval + rval) >> 1;
        int lt = 0, rt = 0;
        for (int i = st; i <= ed; i++) {
            if (q[i].op <= 0) { // 是一次修改
                if (q[i].y <= mid) change(q[i].x, q[i].z), lq[++lt] = q[i];
                else rq[++rt] = q[i];
            } else { // 是一次询问
                int cnt = ask(q[i].y) - ask(q[i].x - 1);
                if (cnt >= q[i].z) lq[++lt] = q[i];
                else q[i].z -= cnt, rq[++rt] = q[i];
            }
        }
        for (int i = ed; i >= st; i--) { // 还原树状数组
            if (q[i].op <= 0 && q[i].y <= mid) change(q[i].x, -q[i].z);
        }
        for (int i = 1; i <= lt; i++) q[st + i - 1] = lq[i];
        for (int i = 1; i <= rt; i++) q[st + lt + i - 1] = rq[i];
        solve(lval, mid, st, st + lt - 1);
        solve(mid + 1, rval, st + lt, ed);
    }

    int main() {
        cin >> T;
        while (T--) {
            cin >> n >> m;
            t = p = 0;
            for (int i = 1; i <= n; i++) {
                int val; scanf("%d", &val);
                // 等价于在第i个位置上加入一个数val
                q[++t].op = 0, q[t].x = i, q[t].y = val, q[i].z = 1;
                a[i] = val;
            }
            for (int i = 1; i <= m; i++) {
                char op[2]; scanf("%s", op);
                if (op[0] == 'Q') {
                    int l, r, k; scanf("%d%d%d", &l, &r, &k);
                    // 记录一次询问
                    q[++t].op = ++p, q[t].x = l, q[t].y = r, q[t].z = k;
                } else {
                    int x, y; scanf("%d%d", &x, &y);
                    // 去掉原来的数a[x]
                    q[++t].op = -1, q[t].x = x, q[t].y = a[x], q[t].z = -1;
                    // 在第x个位置上加入一个新的数y
                    q[++t].op = 0, q[t].x = x, q[t].y = y, q[t].z = 1;
                    a[x] = y;
                }
            }
            // 基于值域对t=n+m个操作进行整体分治
            solve(0, INF, 1, t);
            for (int i = 1; i <= p; i++)
                printf("%d\n", ans[i]);
        }
    }

//    可持久化数据结构
//      最大异或和
    const int N = 600010;
    int trie[N * 24][2], latest[N * 24]; // latest和end可合并为一个数组
    int s[N], root[N], n, m, tot;

// 本题需要统计子树latest，故使用递归插入
// 插入s[i]，当前为s[i]的第k位
    void insert(int i, int k, int p, int q) {
        if (k < 0) {
            latest[q] = i;
            return;
        }
        int c = s[i] >> k & 1;
        if (p) trie[q][c ^ 1] = trie[p][c ^ 1];
        trie[q][c] = ++tot;
        insert(i, k - 1, trie[p][c], trie[q][c]);
        latest[q] = max(latest[trie[q][0]], latest[trie[q][1]]);
    }

    int ask(int now, int val, int k, int limit) {
        if (k < 0) return s[latest[now]] ^ val;
        int c = val >> k & 1;
        if (latest[trie[now][c ^ 1]] >= limit)
            return ask(trie[now][c ^ 1], val, k - 1, limit);
        else
            return ask(trie[now][c], val, k - 1, limit);
    }

    int main() {
        cin >> n >> m;
        latest[0] = -1;
        root[0] = ++tot;
        insert(0, 23, 0, root[0]);
        for (int i = 1; i <= n; i++) {
            int x; scanf("%d", &x);
            s[i] = s[i - 1] ^ x;
            root[i] = ++tot;
            insert(i, 23, root[i - 1], root[i]);
        }
        for (int i = 1; i <= m; i++) {
            char op[2]; scanf("%s", op);
            if (op[0] == 'A') {
                int x; scanf("%d", &x);
                root[++n] = ++tot;
                s[n] = s[n - 1] ^ x;
                insert(n, 23, root[n - 1], root[n]);
            }
            else {
                int l, r, x; scanf("%d%d%d", &l, &r, &x);
                printf("%d\n", ask(root[r - 1], x ^ s[n], 23, l - 1));
            }
        }
    }

//    k-th number
    const int N = 100010, INF = 1e9;
    struct SegmentTree {
        int lc, rc; // 左右子节点编号
        int sum;
    } tree[N * 20];
    int n, m, t, tot, a[N], b[N], root[N];

    int build(int l, int r) {
        int p = ++tot; // 新建一个节点，编号为p，代表当前区间[l,r]
        tree[p].sum = 0;
        if (l == r) return p;
        int mid = (l + r) >> 1;
        tree[p].lc = build(l, mid);
        tree[p].rc = build(mid + 1, r);
        return p;
    }

    int insert(int now, int l, int r, int x, int delta) {
        int p = ++tot;
        tree[p] = tree[now]; // 新建一个副本
        if (l == r) {
            tree[p].sum += delta; // 在副本上修改
            return p;
        }
        int mid = (l + r) >> 1;
        if (x <= mid) tree[p].lc = insert(tree[now].lc, l, mid, x, delta);
        else tree[p].rc = insert(tree[now].rc, mid + 1, r, x, delta);
        tree[p].sum = tree[tree[p].lc].sum + tree[tree[p].rc].sum;
        return p;
    }

    int ask(int p, int q, int l, int r, int k) {
        if (l == r) return l; // 找到答案
        int mid = (l + r) >> 1;
        int lcnt = tree[tree[p].lc].sum - tree[tree[q].lc].sum; // 值在[l,mid]中的数有多少个
        if (k <= lcnt) return ask(tree[p].lc, tree[q].lc, l, mid, k);
        else return ask(tree[p].rc, tree[q].rc, mid + 1, r, k - lcnt);
    }

    int main() {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            b[++t] = a[i];
        }
        sort(b + 1, b + t + 1); // 离散化
        t = unique(b + 1, b + t + 1) - (b + 1);
        root[0] = build(1, t); // 关于离散化后的值域建树
        for (int i = 1; i <= n; i++) {
            int x = lower_bound(b + 1, b + t + 1, a[i]) - b; // 离散化后的值
            root[i] = insert(root[i - 1], 1, t, x, 1); // 值为x的数增加1个
        }
        for (int i = 1; i <= m; i++) {
            int l, r, k; scanf("%d%d%d", &l, &r, &k);
            int ans = ask(root[r], root[l - 1], 1, t, k);
            printf("%d\n", b[ans]); // 从离散化后的值变回原值
        }
    }

//    dynamic ranking
    const int inf=1000000000;
    struct tree{int l,r,dat,size;}t[40010],a[1000010];
    int L[10010],R[10010],p[40010],b[10010],n,m,tot,i,l,r,k,x,y,z;
    char str[2];

    inline void update(int x)
    {
        a[x].size=a[a[x].l].size+a[a[x].r].size+1;
    }

    void zag(int &x)
    {
        int y=a[x].r; a[x].r=a[y].l; a[y].l=x;
        update(x); update(y); x=y;
    }

    void zig(int &x)
    {
        int y=a[x].l; a[x].l=a[y].r; a[y].r=x;
        update(x); update(y); x=y;
    }

    void comb(int &x)
    {
        L[L[0]+1]=a[x].l; R[R[0]+1]=a[x].r;
        for(int i=L[0];i>0;i--) {a[L[i]].r=L[i+1]; update(L[i]);}
        for(int i=R[0];i>0;i--) {a[R[i]].l=R[i+1]; update(R[i]);}
        a[x].l=L[1]; a[x].r=R[1]; update(x);
    }

    void get(int &x,int y)
    {
        if(!x) return;
        L[0]=R[0]=0;
        while(1)
        {
            if(y==a[x].dat||(y<a[x].dat&&!a[x].l)||(y>a[x].dat&&!a[x].r)) break;
            if(y<a[x].dat)
            {
                if(y<a[a[x].l].dat) {zig(x); if(!a[x].l) break;}
                R[++R[0]]=x; x=a[x].l;
            }
            else{
                if(y>a[a[x].r].dat) {zag(x); if(!a[x].r) break;}
                L[++L[0]]=x; x=a[x].r;
            }
        }
        comb(x);
    }

    void splay(int &x,int y)
    {
        if(!x) return;
        L[0]=R[0]=0;
        while(1)
        {
            int temp=a[a[x].l].size+1;
            if(y==temp||(y<temp&&!a[x].l)||(y>temp&&!a[x].r)) break;
            if(y<temp)
            {
                if(a[a[x].l].l&&y<=a[a[a[x].l].l].size) {zig(x); if(!a[x].l) break;}
                R[++R[0]]=x; x=a[x].l;
            }
            else{
                y-=temp;
                temp=a[a[a[x].r].l].size+1;
                if(a[a[x].r].r&&y>temp) {y-=temp; zag(x); if(!a[x].r) break;}
                L[++L[0]]=x; x=a[x].r;
            }
        }
        comb(x);
    }

    void ins(int &x,int y)
    {
        a[++tot].dat=y; a[tot].size=1;
        get(x,y);
        if(a[x].dat<=y)
        {
            splay(a[x].r,1);
            a[a[x].r].l=tot;
            update(a[x].r); update(x);
        }
        else{
            splay(a[x].l,a[a[x].l].size);
            a[a[x].l].r=tot;
            update(a[x].l); update(x);
        }
    }

    void del(int &x,int y)
    {
        get(x,y);
        splay(a[x].r,1);
        a[a[x].r].l=a[x].l;
        x=a[x].r;
        update(x);
    }

    void buildsplay(int num)
    {
        p[num]=++tot; a[tot].r=tot+1;
        a[tot].dat=-inf; a[tot].size=2;
        a[++tot].dat=inf; a[tot].size=1;
        for(int i=t[num].l;i<=t[num].r;i++) ins(p[num],b[i]);
    }

    void build(int num,int l,int r)
    {
        t[num].l=l; t[num].r=r; t[num].dat=b[l];
        buildsplay(num);
        if(l==r) return;
        int mid=(l+r)>>1;
        build(num*2,l,mid);
        build(num*2+1,mid+1,r);
    }

    void change(int num)
    {
        if(t[num].l==t[num].r)
        {
            z=t[num].dat; t[num].dat=y;
            del(p[num],z);
            ins(p[num],y);
            return;
        }
        int mid=(t[num].l+t[num].r)>>1;
        if(x<=mid) change(num*2); else change(num*2+1);
        del(p[num],z);
        ins(p[num],y);
    }

    int ask(int num)
    {
        if(x<=t[num].l&&y>=t[num].r)
        {
            get(p[num],k);
            splay(a[p[num]].r,1);
            while(a[p[num]].dat==k&&a[a[p[num]].r].dat==k)
            {
                zag(p[num]);
                splay(a[p[num]].r,1);
            }
            if(a[p[num]].dat<=k) return a[a[p[num]].l].size;
            else return a[a[p[num]].l].size-1;
        }
        int mid=(t[num].l+t[num].r)>>1,temp=0;
        if(x<=mid) temp+=ask(num*2);
        if(y>mid) temp+=ask(num*2+1);
        return temp;
    }

    int main()
    {
        cin>>n>>m;
        for(i=1;i<=n;i++) scanf("%d",&b[i]);
        build(1,1,n);
        for(i=1;i<=m;i++)
        {
            scanf("%s%d%d",str,&x,&y);
            if(str[0]=='Q')
            {
                scanf("%d",&z);
                l=0; r=inf;
                while(l<r)
                {
                    k=(l+r)>>1;
                    if(ask(1)<z) l=k+1;else r=k;
                }
                printf("%d\n",l);
            }
            else change(1);
        }
        return 0;
    }
    

};

int main() {
    Solution s = *new Solution();
    int t;
    cin >> t;
    while (t--) s.cxzdfx();
    return 0;
}
