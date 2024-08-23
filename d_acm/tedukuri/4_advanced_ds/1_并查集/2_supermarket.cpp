

#include <iostream>
#include <algorithm>
using namespace std;

//supermarket: 给定n个商品，每个商品有利润pi和过期时间di，每天只能卖一个商品，过期商品不能卖，如何安排每天卖的商品，可以使收益最大？


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

int main() {
    while (cin >> n) Supermarket();
    return 0;
}
