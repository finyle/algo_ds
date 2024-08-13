/*
 * prime distance: 给定两个整数l r， 求闭区间[l,r]中相邻两个质数的差最大是多少？输出这两个质数

 */
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 100006, L = 1000006, M = 46340, INF = 0x7fffffff;
bool v[L];
vector<int> p, ans;

int main() {
	memset(v, 1, sizeof(v));
	for (int i = 2; i <= M; i++)
		if (v[i]) {
			p.push_back(i);
			for (int j = 2; j <= M / i; j++) v[i*j] = 0;
		}
	unsigned int l, r;
	while (cin >> l >> r) {
		memset(v, 1, sizeof(v));
		ans.clear();
		if (l == 1) v[0] = 0;
		for (unsigned int i = 0; i < p.size(); i++)
			for (unsigned int j = (l - 1) / p[i] + 1; j <= r / p[i]; j++)
				if (j > 1) v[p[i]*j-l] = 0;
		for (unsigned int i = l; i <= r; i++)
			if (v[i-l]) ans.push_back(i);
		int minn = INF, maxx = 0, x1, y1, x2, y2;
		for (unsigned int i = 0; i + 1 < ans.size(); i++) {
			int num = ans[i+1] - ans[i];
			if (num < minn) {
				minn = num;
				x1 = ans[i];
				y1 = ans[i+1];
			}
			if (num > maxx) {
				maxx = num;
				x2 = ans[i];
				y2 = ans[i+1];
			}
		}
		if (!maxx) puts("There are no adjacent primes.");
		else printf("%d,%d are closest, %d,%d are most distant.\n", x1, y1, x2, y2);
	}
	return 0;
}

/*
 * input:
1 100
1000000000 1001000000
1000000000 1000000008
2147483587 2147483647
2147481000 2147483646
1 2
2 3

 * output:
2,3 are closest, 89,97 are most distant.
1000000007,1000000009 are closest, 1000097621,1000097797 are most distant.
There are no adjacent primes.
2147483629,2147483647 are closest, 2147483587,2147483629 are most distant.
2147481899,2147481901 are closest, 2147481673,2147481793 are most distant.
There are no adjacent primes.
2,3 are closest, 2,3 are most distant.
 */