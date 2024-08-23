
/*
 * 最大子序和(单调队列)： 给定长度为n的整数序列，找出长度不超过m的连续子序列，使得子序列中所有数的和最大
*/


#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 300006, INF = 0x3f3f3f3f;
int n, m, s[N], q[N];

int main() {
    cin >> n >> m;
    s[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &s[i]);
        s[i] += s[i-1];
    }
    int l = 1, r = 1, ans = -INF;
    q[1] = 0;
    for (int i = 1; i <= n; i++) {
        while (l <= r && q[l] < i - m) l++;
        ans = max(ans, s[i] - s[q[l]]);
        while (l <= r && s[q[r]] >= s[i]) r--;
        q[++r] = i;
    }
    cout << ans << endl;
    return 0;
}

/*
 * input:
6 4
1 -3 5 1 -2 3
 * output:
7

 */
