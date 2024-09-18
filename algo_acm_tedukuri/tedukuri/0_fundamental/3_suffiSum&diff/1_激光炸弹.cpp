/*
 * 激光炸弹(前缀和：对于给定的数列A，它的前缀和数列是通过递推能求出的基本信息之一)：
 * 二维矩阵元素记录权重值，炸弹可炸毁长度为r的正方形，求一颗炸弹最大炸毁权重；最大子矩阵和

 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 5006;
int n, r, s[N][N];

int main() {
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
                if (i == r - 1 && j == r - 1) ans = max(ans, s[i][j]); // 前缀和
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

/*
 * input:
50 20
43 36 35
12 25 23
7 49 59
24 27 62
17 14 89
49 39 77
5 6 38
32 14 84
4 25 29
22 1 87
32 21 1
23 38 34
4 15 92
45 2 89
19 42 13
46 25 69
15 39 54
40 24 63
1 30 5
43 22 21
19 2 61
10 47 97
19 33 46
7 9 94
22 44 48
5 23 11
32 25 40
5 20 20
28 47 63
17 7 81
3 11 59
35 10 3
45 27 83
36 40 9
23 39 28
25 34 34
6 35 77
7 15 29
15 31 26
0 45 54
37 12 77
6 24 57
1 3 64
22 6 23
34 3 42
10 7 15
46 13 62
40 0 79
42 37 31
36 22 84
 * output:
688
 *
 */