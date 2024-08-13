#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
const int INF = 0x7fffffff;
int n, m, minv[30], mins[30], ans = INF;
int h[30], r[30], s = 0, v = 0;

// (剪枝) 制作体积为nΠ的m层生日蛋糕，每层都是个圆柱体，蛋糕的设计：r，h，使得蛋糕表面积最小

void dfs(int dep) {
    if (!dep) {
        if (v == n) ans = min(ans, s);
        return;
    }
    for (r[dep] = min((int)sqrt(n - v), r[dep + 1] - 1); r[dep] >= dep; r[dep]--)
        for (h[dep] = min((int)((double)(n - v)/ r[dep]), h[dep + 1] - 1); h[dep] >= dep; h[dep]--) {
            // 剪枝
            if (v + minv[dep - 1] > n) continue;
            if (s + mins[dep - 1] > ans) continue;
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

int main() {
    cin >> n >> m;
    minv[0] = mins[0] = 0;
    for (int i = 1; i <= m; i++) {
        minv[i] = minv[i - 1] + i * i * i;
        mins[i] = mins[i - 1] + i * i;
    }
    h[m + 1] = r[m + 1] = INF;
    dfs(m);
    cout << ans << endl;
    return 0;
}