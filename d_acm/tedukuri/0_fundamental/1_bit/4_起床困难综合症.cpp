/*
 * 起床困难综合症：选择区间[0,m]之间的一个整数x0，经过给定的n次位运算，使结果ans最大(位运算的主要特点是在二进制表示下不进位)

 */

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
using namespace std;
int n, m;
pair<string, int> a[100005];

int calc(int bit, int now) { // 用参数的第bit位进行n次运算
    for (int i = 1; i <= n; i++) { // 进行三种位运算
        int x = a[i].second >> bit & 1; // 数组中存放键值对，k：操作符，v：操作数
        if (a[i].first == "AND") now &= x;
        else if (a[i].first == "OR") now |= x;
        else now ^= x;
    }
    return now;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        char str[5];
        int x;
        scanf("%s%d", str, &x);
        a[i] = make_pair(str, x);
    }
    int val = 0, ans = 0;
    for (int bit = 29; bit >= 0; bit--) {
        int res0 = calc(bit, 0);
        int res1 = calc(bit, 1);
        if (val + (1 << bit) <= m && res0 < res1)
            val += 1 << bit, ans += res1 << bit;
        else
            ans += res0 << bit;
    }
    cout << ans << endl;
}

/*
 * input:
95 0
AND 767
XOR 72
XOR 376
AND 1015
OR 32
XOR 992
AND 1019
XOR 648
OR 264
AND 735
OR 36
AND 1023
XOR 987
OR 268
AND 723
OR 256
OR 296
OR 40
OR 288
XOR 201
AND 1015
AND 979
XOR 38
AND 1019
AND 1015
OR 12
XOR 918
OR 268
OR 292
AND 991
OR 8
XOR 255
AND 755
XOR 134
AND 735
AND 759
XOR 458
OR 300
AND 755
AND 1015
XOR 100
AND 1023
AND 735
OR 12
OR 40
AND 979
AND 723
XOR 53
XOR 623
AND 1011
OR 44
XOR 860
OR 0
XOR 420
OR 264
XOR 81
OR 44
AND 735
AND 731
AND 991
XOR 323
XOR 214
XOR 453
XOR 172
XOR 475
OR 268
AND 1023
XOR 699
XOR 850
OR 0
OR 40
AND 731
OR 256
XOR 3
OR 36
AND 991
AND 731
OR 0
AND 1015
XOR 18
OR 260
AND 759
AND 731
OR 44
XOR 522
OR 296
XOR 426
XOR 261
AND 1015
AND 755
OR 260
OR 32
OR 260
OR 8
OR 36

 * output:
940

 */