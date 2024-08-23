// 有n个小朋友坐成一圈，每人有ai个糖果。每人只能给左右两人传递糖果。每人每次传递一个糖果代价为1。求所有人获得均等糖果的最小代价

// input:4
//1
//2
//5
//4
// output:4

#include <cstdio>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 1000006;
int n;
ll a[N], k = 0;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
    	scanf("%lld", &a[i]);
        k += a[i];
    }
    k /= n;
    a[0] = 0;
    for (int i = 1; i <= n; i++) a[i] = a[i] - k + a[i-1];
    sort(a + 1, a + n + 1);
    ll ans = 0;
    for (int i = 1; i <= n / 2; i++) ans += a[n+1-i] - a[i];
    cout << ans << endl;
    return 0;
}
