
/*
 * // 游戏：n个人：左右手分别写下一个正整数，国王也写，n个人拍成一排，国王站最前面；
// 每个人获得金币：排在该大臣前的所有人左手数字的乘积除以该大臣右手数字,向下取整；国王不希望某个大臣获得特别多的奖赏
// 重新排队使得获得金币最多的大臣得到的金币尽可能的少
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;



const int N = 1006;
int n, k[N * 4], lk = 1, ans[N * 4], la = 1, ans0[N * 4], la0 = 1;
struct P {  // 左右手的数字
    int a, b;
    bool operator < (const P x) const {
        return a * b < x.a * x.b;
    }
} p[N];

void gj1(int x) {
    for (int i = 1; i <= lk; i++) k[i] *= x;
    lk += 4;
    for (int i = 1; i <= lk; i++) {
        k[i + 1] += k[i] / 10;
        k[i] %= 10;
    }
    while (!k[lk]) lk--;
}
void gj2(int x) {
    int w = 0;
    bool flag = 1;
    for (int i = lk; i; i--) {
        w = w * 10 + k[i];
        ans0[i] = w / x;
        w %= x;
        if (ans0[i] && flag) {
            la0 = i;
            flag = 0;
        }
    }
}
bool pd() {
    if (la != la0) return la < la0;
    for (int i = la; i; i--)
        if (ans[i] != ans0[i]) return ans[i] < ans0[i];
    return 0;
}

int main() {
    cin >> n;
    for (int i = 0; i <= n; i++) scanf("%d %d", &p[i].a, &p[i].b); //
    sort(p + 1, p + n + 1);
    memset(k, 0, sizeof(k));
    memset(ans, 0, sizeof(ans));
    memset(ans0, 0, sizeof(ans0));
    k[1] = 1;
    gj1(p[0].a); // 微扰邻项交换
    for (int i = 1; i <= n; i++) {
        gj2(p[i].b);
        if (pd()) {
            memcpy(ans, ans0, sizeof(ans));
            la = la0;
        }
        gj1(p[i].a);
    }
    for (int i = la; i; i--) cout << ans[i];
    cout << endl;
    return 0;
}

/*
 * input:
3
1 7
6 1
2 3
2 3

 * output:
4
 */