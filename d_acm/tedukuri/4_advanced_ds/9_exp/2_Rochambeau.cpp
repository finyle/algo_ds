
/*
rochambeau game: n个人，1人做裁判，n-1人分为3组，通过组件的判断，推测出谁是裁判？
input：
3 3
0<1
1<2
2<0
3 5
0<1
0>1
1<2
1>2
0<2
4 4
0<1
0>1
2<3
2>3
1 0

output:
Can not determine
Player 1 can be determined to be the judge after 4 lines
Impossible
Player 0 can be determined to be the judge after 0 lines
*/
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 2006;
int n, m, a[N], b[N], fa[N], d[N], p[N];
char c[N];

int get(int x) {
	if (fa[x] == x) return x;
	int root = get(fa[x]);
	d[x] = (d[x] + d[fa[x]]) % 3;
	return fa[x] = root;
}

bool work(int x, int y, int k) {
	int fx = get(x), fy = get(y);
	if (fx == fy) {
		if (k == 0 && d[x] != d[y]) return 0;
		if (k == 1 && (d[x] + 1) % 3 != d[y]) return 0;
		return 1;
	}
	fa[fy] = fx;
	d[fy] = (d[x] - d[y] + 3 + k) % 3;
	return 1;
}

bool pd(int x) {
	if (c[x] == '=' && !work(a[x], b[x], 0)) return 1;
	if (c[x] == '<' && !work(a[x], b[x], 1)) return 1;
	if (c[x] == '>' && !work(b[x], a[x], 1)) return 1;
	return 0;
}

void Rochambeau() {
	for (int i = 0; i < m; i++)
		scanf("%d%c%d", &a[i], &c[i], &b[i]);
	memset(p, 0, sizeof(p));
	int cnt = 0, num = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) fa[j] = j;
		memset(d, 0, sizeof(d));
		bool flag = 0;
		for (int j = 0; j < m; j++)
			if (a[j] != i && b[j] != i && pd(j)) {
				flag = 1;
				if (j > p[i]) p[i] = j + 1;
				break;
			}
		if (!flag) {
			num = i;
			++cnt;
		}
	}
	if (!cnt) puts("Impossible");
	else if (cnt == 1) {
		int ans = 0;
		for (int i = 0; i < n; i++)
			if (i != num && p[i] > ans)
				ans = p[i];
		printf("Player %d can be determined to be the judge after %d lines\n", num, ans);
	} else puts("Can not determine");
}

int main() {
	while (cin >> n >> m) Rochambeau();
	return 0;
}
