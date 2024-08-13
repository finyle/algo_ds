/*
 * 费解的开关： 5*5的01矩阵中，点击任意位置，该位置的上下左右四个相邻的位置中的数字都会变化，最少多少次点击把给定的01矩阵完全变成0矩阵

 */
#include <cstring>
#include <iostream>
using namespace std;
const int N = 6;
int a[N], ans, aa[N];
char s[N];

void dj(int x, int y) { // 位运算模拟点击01变化
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

void abc() { // 递推求解
    memset(a, 0, sizeof(a)); // 输入棋盘状态
    for (int i = 1; i <= 5; i++) {
        cin >> (s + 1);
        for (int j = 1; j <= 5; j++) a[i] = a[i] * 2 + (s[j] - '0');
    }
    ans = 7;
    for (int p = 0; p < (1 << 5); p++) pd(p); // pd模拟棋盘点击
    if (ans == 7) cout << "-1" << endl;
    else cout << ans << endl;
}

int main() {
    int n;
    cin >> n;
    while (n--) abc();
    return 0;
}

/*
 * input:
3
00111
01011
10001
11010
11100

11101
11101
11110
11111
11111

01111
11111
11111
11111
11111
 * output:
3
2
-1
 */