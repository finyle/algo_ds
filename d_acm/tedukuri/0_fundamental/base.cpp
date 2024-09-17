//
// Created by linsh on 2024/9/12.
//

#include "base.h"
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <map>

#define ll long long

using namespace std;

class Solution {

public:
//    位运算：
    ll mul(ll a, ll b, ll p) {
        ll ans = 0;
        while (b) {
            if (b & 1) ans = (ans + a) % p;
            a = a * 2 % p;
            b >>= 1;
        }
        return ans;
    }
    int power(int a, int b, int p) {
        int ans = 1 % p;
        for(; b; b >>= 1) {
            if (b & 1) ans = (long long)ans * a % p;
            a = (long long)a * a % p;
        }
        return ans;
    }

//    int f[1 << 20][20], weight[20][20], n;
//    int hamilton(int n, int weight[20][20]) {
//        memset(f, 0x3f, sizeof(f));
//        f[1][0] = 0;
//        for (int i = 1; i < 1 << n; i++)
//            for (int j = 0; j < n; j++) if (i >> j & 1)
//                    for (int k = 0; k < n; k++)
//                        if ((i^1<<j) >> k & 1)
//                            f[i][j] = min(f[i][j], f[i^1<<j][k]+weight[k][j]);
//        return f[(1 << n) - 1][n - 1];
//    }

//    pair<string, int> a[100005];
//    int calc(int bit, int now) {
//        for (int i = 1; i <= n; i++) {
//            int x = a[i].second >> bit & 1;
//            if (a[i].first == "AND") now &= x;
//            else if (a[i].first == "OR") now |= x;
//            else now ^= x;
//        }
//        return now;
//    }

    void Raising_Modulo_Numbers() {
        int p, n;
        cin >> p >> n;
        int ans = 0;
        while (n--) {
            int a, b;
            cin >> a >> b;
            ans = (ll)(ans + power(a, b, p)) % p;
        }
        cout << ans << endl;
    }

    int n, m;
    vector<int> chosen;
    void calc_(int x) {
        if (chosen.size() > m || chosen.size() + (n - x + 1) < m) return;
        if (x == n + 1) {
            for (int i = 0; i < chosen.size(); i++)
                printf("%d ", chosen[i]);
            puts("");
            return;
        }
        chosen.push_back(x);
        calc_(x + 1);
        chosen.pop_back();
        calc_(x + 1);
    }

//    递归与递推
//    int n;
//    vector<int> chosen; // 被选择的数
    void calc_2(int x) {
        if (x == n + 1) { // 问题边界
            for (int i = 0; i < chosen.size(); i++)
                printf("%d ", chosen[i]);
            puts("");
            return;
        }
        //"不选x"分支
        calc_2(x + 1); // 求解子问题
        //"选x"分支
        chosen.push_back(x); // 记录x已被选择
        calc_2(x + 1); // 求解子问题
        chosen.pop_back(); // 准备回溯到上一问题之前，还原现场
    }

    int order[20]; // 按顺序依次记录被选择的整数
//    bool chosen[20]; // 标记被选择的整数
    void calc(int k) {
        if (k == n + 1) { // 问题边界
            for (int i = 1; i <= n; i++)
                printf("%d ", order[i]);
            puts("");
            return;
        }
        for (int i = 1; i <= n; i++) {
            if (chosen[i]) continue;
            order[k] = i;
            chosen[i] = 1;
            calc(k + 1);
            chosen[i] = 0;
            order[k] = 0; // 这一行可以省略
        }
    }

//    开关问题
    static const int N = 6;
    int a[N], ans, aa[N];
    char s[N];
    void dj(int x, int y) {
        aa[x] ^= (1 << y);
        if (x != 1) aa[x-1] ^= (1 << y);
        if (x != 5) aa[x+1] ^= (1 << y);
        if (y != 0) aa[x] ^= (1 << (y - 1));
        if (y != 4) aa[x] ^= (1 << (y + 1));
    }
    void pd(int p) {
        int k = 0;
        memcpy(aa, a, sizeof(a));
        for (int i = 0; i < 5; i++)
            if (!((p >> i) & 1)) {
                dj(1, i);
                if (++k >= ans) return;
            }
        for (int x = 1; x < 5; x++)
            for (int y = 0; y < 5; y++)
                if (!((aa[x] >> y) & 1)) {
                    dj(x + 1, y);
                    if (++k >= ans) return;
                }
        if (aa[5] == 31) ans = k;
    }
    void abc() {
        memset(a, 0, sizeof(a));
        for (int i = 1; i <= 5; i++) {
            cin >> (s + 1);
            for (int j = 1; j <= 5; j++) a[i] = a[i] * 2 + (s[j] - '0');
        }
        ans = 7;
        for (int p = 0; p < (1 << 5); p++) pd(p);
        if (ans == 7) cout << "-1" << endl;
        else cout << ans << endl;
    }

//    汉诺塔问题
//    const int N = 15;
    ll d[N], f[N];
    int hanoi() {
        int n = 12;
        memset(f, 0x3f, sizeof(f));
        d[1] = f[1] = 1;
        for (int i = 2; i <= n; i++) d[i] = 2 * d[i-1] + 1;
        for (int i = 2; i <= n; i++)
            for (int j = 1; j < i; j++)
                f[i] = min(f[i], 2 * f[j] + d[i-j]);
        for (int i = 1; i <= n; i++) cout << f[i] << endl;
        return 0;
    }

//    a的b次幂的的约数之和
    const ll P = 9901;
    vector<pair<ll, ll> > w;
    ll ksm(ll a, ll b) {
        ll ans = 1;
        a %= P;
        while (b) {
            if (b & 1) (ans *= a) %= P;
            (a *= a) %= P;
            b >>= 1;
        }
        return ans;
    }
    ll get_sum(ll p, ll c) {
        if (!p) return 0;
        if (!c) return 1;
        if (c & 1) return (ksm(p, (c + 1) / 2) + 1) * get_sum(p, c / 2) % P;
        return ((ksm(p, c / 2) + 1) * get_sum(p, c / 2 - 1) + ksm(p, c)) % P;
    }
    void fj(ll a) {
        for (ll i = 2; i * i <= a; i++)
            if (!(a % i)) {
                ll num = 0;
                while (!(a % i)) {
                    num++;
                    a /= i;
                }
                w.push_back(make_pair(i, num));
            }
        if (a != 1) w.push_back(make_pair(a, 1));
    }

//    分形街道
    pair<long long, long long> calc(int n, long long m) {
        if (n == 0) return make_pair(0, 0);
        long long len = 1ll << (n - 1), cnt = 1ll << (2 * n - 2);
        pair<long long, long long> pos = calc(n - 1, m % cnt); // 递归
        long long x = pos.first, y = pos.second;
        long long z = m / cnt;
        if (z == 0) return make_pair(y, x);
        if (z == 1) return make_pair(x, y + len);
        if (z == 2) return make_pair(x + len, y + len);
        if (z == 3) return make_pair(2 * len - y - 1, len - x - 1);
    }

//    前缀与差分
//    incdec sequence
//    const int N = 100006;
    ll a[N], b[N];
    int incDec() {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
        b[1] = a[1];
        for (int i = 2; i <= n; i++) b[i] = a[i] - a[i-1];
        ll p = 0, q = 0;
        for (int i = 2; i <= n; i++)
            if (b[i] > 0) p += b[i];
            else if (b[i] < 0) q -= b[i];
        cout << max(p, q) << endl << abs(p - q) + 1 << endl;
        return 0;
    }

    map<pair<int, int>, bool> v;
//    int s[N];
    int tallsetCow() {
        int n, p, h, t;
        cin >> n >> p >> h >> t;
        memset(s, 0, sizeof(s));
        while (t--) {
            int a, b;
            scanf("%d %d", &a, &b);
            if (a > b) swap(a, b);
            if (v[make_pair(a, b)]) continue;
            s[a+1]--;
            s[b]++;
            v[make_pair(a, b)] = 1;
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += s[i];
            printf("%d\n", h + ans);
        }
        return 0;
    }

    const int N = 5006;
    int n, r, s[N][N];
    int bomb() {
        memset(s, 0, sizeof(s));
        cin >> n >> r;
        while (n--) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            s[x][y] += z;
        }
        for (int i = 0; i <= 5000; i++)
            for (int j = 0; j <= 5000; j++)
                if (!i && !j) continue;
                else if (!i) s[i][j] += s[i][j-1];
                else if (!j) s[i][j] += s[i-1][j];
                else s[i][j] += s[i-1][j] + s[i][j-1] - s[i-1][j-1];
        int ans = 0;
        if(r<5001){
            for (int i = r - 1; i <= 5000; i++)
                for (int j = r - 1; j <= 5000; j++)
                    if (i == r - 1 && j == r - 1) ans = max(ans, s[i][j]);
                    else if (i == r - 1) ans = max(ans, s[i][j] - s[i][j-r]);
                    else if (j == r - 1) ans = max(ans, s[i][j] - s[i-r][j]);
                    else ans = max(ans, s[i][j] - s[i-r][j] - s[i][j-r] + s[i-r][j-r]);
        }
        else{	//r>=5001，可以覆盖所有区域
            ans=s[5000][5000];
        }
        cout << ans << endl;
        return 0;
    }

//    二分
    double a[100001], b[100001], sum[100001];
    int bestCowFence() {
        int N, L;
        cin >> N >> L;
        for (int i = 1; i <= N; i++) scanf("%lf", &a[i]);
        double eps = 1e-5;
        double l = -1e6, r = 1e6;
        while (r - l > eps) {
            double mid = (l + r) / 2;
            for (int i = 1; i <= N; i++) b[i] = a[i] - mid;
            for (int i = 1; i <= N; i++)
                sum[i] = (sum[i - 1] + b[i]);
            double ans = -1e10;
            double min_val = 1e10;
            for (int i = L; i <= N; i++) {
                min_val = min(min_val, sum[i - L]);
                ans = max(ans, sum[i] - min_val);
            }
            if (ans >= 0) l = mid; else r = mid;
        }
        cout << int(r * 1000) << endl;
    }

//    innovation business
    vector<int> specialSort(int N) {
        vector<int> a;
        for(int i=0;i<N;i++){
            a.push_back(i+1);
        }
        for (int i=1;i<N;i++){
            int temp = a[i];
            int left = 0;
            int right = i - 1;
            int mid = 0;
            while (left <= right) {
                mid = (left + right) / 2;
                if (compare(temp,a[mid])) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            for (int j = i - 1; j >= left; j--) {
                a[j + 1] = a[j];
            }
            if (left != i) {
                a[left] = temp;
            }
        }
        return a;
    }

//    倍增
//    genius acm 倍增
    const int N = 500006;
    int n, m, w;
    ll k, a[N], b[N], c[N];
    void gb(int l, int mid, int r) {
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
        gb(l, w, r);
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
                ll num = f(l, r + p);
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

//    贪心
//    color a tree
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

//    exp
//
};

int main() {
    Solution s = *new Solution();
//    927364012 847372916 237840192
//    int a, b, p;
//    cin >> a >> b >> p;
//    cout << s.power(a, b, p) << endl;

//    int a, b, p;
//    250182048980811753 413715569939057660 133223633696258584
//    cin >> a >> b >> p;
//    cout << s.mul(a, b, p) << endl;

//5
//0 2 4 5 1
//2 0 6 5 3
//4 6 0 8 3
//5 5 8 0 5
//1 3 3 5 0
//    int f[1 << 20][20], weight[20][20], n;
//    cin >> n;
//    for(int i = 0; i < n; i++)
//        for(int j = 0; j < n; j++)
//            scanf("%d", &weight[i][j]);
//    cout << s.hamilton(n, weight) << endl;

//95 0
//AND 767
//XOR 72
//XOR 376
//AND 1015
//OR 32
//XOR 992
//AND 1019
//XOR 648
//OR 264
//AND 735
//OR 36
//AND 1023
//XOR 987
//OR 268
//AND 723
//OR 256
//OR 296
//OR 40
//OR 288
//XOR 201
//AND 1015
//AND 979
//XOR 38
//AND 1019
//AND 1015
//OR 12
//XOR 918
//OR 268
//OR 292
//AND 991
//OR 8
//XOR 255
//AND 755
//XOR 134
//AND 735
//AND 759
//XOR 458
//OR 300
//AND 755
//AND 1015
//XOR 100
//AND 1023
//AND 735
//OR 12
//OR 40
//AND 979
//AND 723
//XOR 53
//XOR 623
//AND 1011
//OR 44
//XOR 860
//OR 0
//XOR 420
//OR 264
//XOR 81
//OR 44
//AND 735
//AND 731
//AND 991
//XOR 323
//XOR 214
//XOR 453
//XOR 172
//XOR 475
//OR 268
//AND 1023
//XOR 699
//XOR 850
//OR 0
//OR 40
//AND 731
//OR 256
//XOR 3
//OR 36
//AND 991
//AND 731
//OR 0
//AND 1015
//XOR 18
//OR 260
//AND 759
//AND 731
//OR 44
//XOR 522
//OR 296
//XOR 426
//XOR 261
//AND 1015
//AND 755
//OR 260
//OR 32
//OR 260
//OR 8
//OR 36
//    int n, m;
//    pair<string, int> a[100005];
//    cin >> n >> m;
//    for (int i = 1; i <= n; i++) {
//        char str[5];
//        int x;
//        scanf("%s%d", str, &x);
//        a[i] = make_pair(str, x);
//    }
//    int val = 0, ans = 0;
//    for (int bit = 29; bit >= 0; bit--) {
//        int res0 = s.calc(bit, 0);
//        int res1 = s.calc(bit, 1);
//        if (val + (1 << bit) <= m && res0 < res1)
//            val += 1 << bit, ans += res1 << bit;
//        else
//            ans += res0 << bit;
//    }
//    cout << ans << endl;

//    int t;
//    cin >> t;
//    while (t--) s.Raising_Modulo_Numbers();
//    return 0;

//    int n, m;
//    cin >> n >> m;
//    s.calc_(1);
}

