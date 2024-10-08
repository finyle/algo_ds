/*
设计一个计算器，完成：Y^Z MOD P 的值：
input：
8 3
729747280 945350145 692576509
1003782582 1052995490 874047913
830933225 1064553781 799657219
838858074 226936475 794398013
81849408 363441763 937530961
537548626 762299815 268774313
434803981 112377358 720989147
535017411 188743780 959592839
output：
Orz, I cannot find x!
660548660
Orz, I cannot find x!
101265586
61062441
Orz, I cannot find x!
439374774
721409727
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;

int ksm(int a, int b, int p) {
	int ans = 1 % p;
	a %= p;
	b %= p - 1;
	while (b) {
		if (b & 1) ans = (ll)ans * a % p;
		a = (ll)a * a % p;
		b >>= 1;
	}
	return ans;
}

int exgcd(int a, int b, int &x, int &y) {
	if (!b) {
		x = 1;
		y = 0;
		return a;
	}
	int d = exgcd(b, a % b, x, y);
	int z = x;
	x = y;
	y = z - y * (a / b);
	return d;
}

int bsgs(int a, int b, int p) {
	map<int, int> H;
	H.clear();
	b %= p;
	int t = (int)sqrt(p) + 1;
	for (int i = 0; i < t; i++) {
		int val = (ll)b * ksm(a, i, p) % p;
		H[val] = i;
	}
	a = ksm(a, t, p);
	if (!a) return b ? -1 : 1;
	for (int i = 0; i <= t; i++) {
		int val = ksm(a, i, p);
		int j = H.find(val) == H.end() ? -1 : H[val];
		if (j >= 0 && i * t >= j) return i * t - j;
	}
	return -1;
}

int main() {
	int t, k;
	cin >> t >> k;
	while (t--) {
		int y, z, p;
		cin >> y >> z >> p;
		if (k == 1)  {
			cout << ksm(y, z, p) << endl;
			continue;
		}
		if (k == 2) {
			int x, t;
			int d = exgcd(y, p, x, t);
			if (z % d) puts("Orz, I cannot find x!");
			else cout << ((ll)x * z / d % p + p) % p << endl;
			continue;
		}
		if (k == 3) {
			int ans = bsgs(y, z, p);
			if (ans == -1) puts("Orz, I cannot find x!");
			else cout << ans << endl;
		}
	}
	return 0;
}
