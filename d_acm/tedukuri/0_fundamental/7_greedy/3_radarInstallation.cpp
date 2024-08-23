// 安装监控： 覆盖学校内的n座建筑，每座建筑视为一个质点，在笛卡尔坐标系种给出它们的坐标(x, y),监控只能安装在x轴上
// 每台监控设备的范围为一个半径为R的圆形，圆心即为这台设备，给出n座建筑的坐标，最少需要几台设备监控所有建筑

#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#define ld long double
using namespace std;

const int N = 1006;
const double INF = -0X3f3f3f3f, eps = 0.000001;
int n, d, num = 0;
struct P { //
    int x, y;
    double l, r;
    bool operator<(const P x) const {
        return l < x.l;
    }
}p[N];

void Radar_Installation() {
    for (int i = 1; i <= n; i++) scanf("%d %d", &p[i], &p[i].y);
    bool b = 1;
    for (int i = 1; i <= n; i++)
        if (p[i].y > d) {
            b = 0;
            break;
        }
    if (!b) {
        cout << "Case" << ++num << ": -1" << endl;
        return;
    }
    for (int i = 1; i <= n; i++) {
        ld k = sqrt((ld)d * d - (ld)p[i].y * p[i].y); // 计算平面欧几里得距离
        p[i].l = p[i].x - k, p[i].r = p[i].x + k;
    }
    sort(p + 1, p + n + 1);
    int ans = 1;
    double pos = -INF;
    for (int i = 1; i <= n; i++) {
        if (pos + eps < p[i].l) {
            ans++;
            pos = p[i].r;
        } else pos = min(p[i].r, pos);
    }
    cout << "Case" << ++num << ": " << ans << endl;
}
int main() {
    while (cin >> n >> d && n && d) Radar_Installation();
    return 0;
}

/*
 * input:
10 10
592 7
602 9
847 4
645 4
-297 9
-963 2
-477 8
528 5
392 10
71 3

 * output:
9

 */