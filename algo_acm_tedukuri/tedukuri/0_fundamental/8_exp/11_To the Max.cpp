/*
 * To the Max: 最大子矩阵和 (贪心)
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 106;
int n, a[N][N], x[N], ans = 0;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &a[i][j]);
	for (int i = 1; i <= n; i++) {
		memset(x, 0, sizeof(x));
		for (int j = i; j <= n; j++) {
			int num = 0;
			for (int k = 1; k <= n; k++) {
				num += x[k] += a[j][k];
				ans = max(ans, num);
				if (num < 0) num = 0;
			}
		}
	}
	cout << ans << endl;
	return 0;
}

/*
 * input:
4
0 -2 -7 0
 9 2 -6 2
-4 1 -4 1
-1 8 0 -2

 * output:
15
 */