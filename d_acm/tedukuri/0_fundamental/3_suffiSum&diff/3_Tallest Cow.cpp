/*
 * Tallest Cow： n头牛站成一行，两头牛能相互看到，求每头牛的最大身高为多少？已知最高的牛是第p头，身高位h；
 * 直到m对关系，每对关系的牛可以相互看到，求每头牛的最大身高

 */
#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
map<pair<int, int>, bool> v;
const int N = 10006;
int s[N];

int main() {
    int n, p, h, t;
    cin >> n >> p >> h >> t;
    memset(s, 0, sizeof(s));
    while (t--) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a > b) swap(a, b);
        if (v[make_pair(a, b)]) continue;
        s[a+1]--;
        s[b]++; // 差分数组
        v[make_pair(a, b)] = 1;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += s[i];
        printf("%d\n", h + ans);
    }
    return 0;
}

/*
 * input:
9 3 5 5
1 3
5 3
4 3
3 7
9 8
 * output:
5
4
5
3
4
4
5
5
5
 *
 */