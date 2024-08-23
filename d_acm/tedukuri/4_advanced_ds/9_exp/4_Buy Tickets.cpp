/*


input:
5
0 30894
0 26816
0 30933
3 29536
4 5530
4
0 77
1 51
1 33
2 69
4
0 20523
1 19243
1 3890
0 31492

output:
30933 26816 30894 29536 5530
77 33 69 51
31492 20523 3890 19243

*/
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 200006;
int n, ans[N], p[N], v[N], c[N];

int ask(int x) {
	int ans = 0;
	while (x) {
		ans += c[x];
		x -= x & -x;
	}
	return ans;
}

void add(int x, int y) {
	while (x <= n) {
		c[x] += y;
		x += x & -x;
	}
}

int get(int x) {
	int l = 1, r = n;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (ask(mid) < x) l = mid + 1;
		else r = mid -1;
	}
	return l;
}

void Buy_Tickets() {
	memset(c, 0, sizeof(c));
	for (int i = 1; i <= n; i++) add(i, 1);
	for (int i = 0; i < n; i++) scanf("%d %d", &p[i], &v[i]);
	for (int i = n - 1; i >= 0; i--) {
		int t = get(p[i] + 1);
		ans[t] = v[i];
		add(t, -1);
	}
	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
	puts("");
}

int main() {
	while (cin >> n) Buy_Tickets();
	return 0;
}
