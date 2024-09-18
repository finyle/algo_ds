/*
 * IncDec Sequence(差分：前缀和和差分是一对互逆运算)： 给定长度为n的序列，每次选择一个区间，是下标在这个区间内的数都加一，减一，至少需要多少次操作，才能使区间中的数完全相同

 */
#include <cmath>
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
const int N = 100006;
ll a[N], b[N];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]); // 输入数组
    b[1] = a[1];
    for (int i = 2; i <= n; i++) b[i] = a[i] - a[i-1]; // 差分数组
    ll p = 0, q = 0;
    for (int i = 2; i <= n; i++)
        if (b[i] > 0) p += b[i];
        else if (b[i] < 0) q -= b[i];
    cout << max(p, q) << endl << abs(p - q) + 1 << endl;
    return 0;
}

/*
 * input:
4
1
1
2
2
 * output:
1
2
 */
