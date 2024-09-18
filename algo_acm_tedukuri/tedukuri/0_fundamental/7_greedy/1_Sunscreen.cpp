#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

// c头奶牛日光浴，第i头需要minSPF[i]-maxSPF[i]单位强度之间的阳光。每头牛在日光浴前必须涂防晒
// l中防晒，接收阳光强度 spf[i]; 第i种防晒有cover[i]瓶，最多可以满足几头牛日光浴 C,L < 2500;

const int N = 2506;
int n, m;
struct COW { // i种防晒
    int l, r;
    bool operator < (const COW x) const {
        return l > x.l;
    }
} cow[N];
struct SPF { // 涂防晒后，身体接收到的阳光强度稳定位spf
    int s, c;
    bool operator < (const SPF x) const {
        return s > x.s;
    }
} spf[N];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) scanf("%d %d", &cow[i].l, &cow[i].r);
    for (int i = 1; i <= m; i++) scanf("%d %d", &spf[i].s, &spf[i].c);
    sort(cow + 1, cow + n + 1);
    sort(spf + 1, spf + m + 1);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (spf[j].c && spf[j].s >= cow[i].l && spf[j].s <= cow[i].r) {
                ans++;
                spf[j].c--;
                break;
            }
    cout << ans << endl;
    return 0;
}

/*
 * input:
3 2
3 10
2 5
1 5
6 2
4 1

 * output:
2

 *
 */