/*
 * Best cow fence：给定整数数列n，求一个平均数最大的，长度不小于l的最长子段(子段必须连续)
 * 判定是否存在一个长度不小于l的子段，平均数不小于二分的值；如果把数列中的每个数都减去二分的值，就转化为判定”是否存在一个长度不小于l的子段，子段和非负“
 */
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
double a[100001], b[100001], sum[100001];
int main() {
    int N, L;
    cin >> N >> L;
    for (int i = 1; i <= N; i++) scanf("%lf", &a[i]);
    double eps = 1e-5;
    double l = -1e6, r = 1e6;
    while (r - l > eps) {
        double mid = (l + r) / 2;
        for (int i = 1; i <= N; i++) b[i] = a[i] - mid;
        for (int i = 1; i <= N; i++)
            sum[i] = (sum[i - 1] + b[i]);
        double ans = -1e10;
        double min_val = 1e10;
        for (int i = L; i <= N; i++) {
            min_val = min(min_val, sum[i - L]);
            ans = max(ans, sum[i] - min_val);
        }
        if (ans >= 0) l = mid; else r = mid;
    }
    cout << int(r * 1000) << endl;
}

/*
 * input:
10 6
6
4
2
10
3
8
5
9
4
1
 * output:
6500

 *
 */