// 银河英雄传说：n列战场，n艘战舰，m条指令：指令格式：Mij表示让第i号战舰所在列的全部战舰保持原有顺序
// Cij 表示询问i号战舰与j号战舰是否处于同一列中，如果在同一列中，它们之间隔了多少战舰；

#include <cmath>
#include <iostream>
using namespace std;
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
