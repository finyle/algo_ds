
/*
将数对排序，使得数对间的权值最小

input:
4 6
1 4 2534
2 3 3512
1 2 28351
1 3 6618
2 4 1805
3 4 12884
output:
3512

*/
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 20006, M = 100006;
int n, m, fa[N<<1];
struct P {
	int a, b, c;
	bool operator < (const P x) const {
		return c > x.c;
	}
} p[M];

int get(int x) {
	if (fa[x] == x) return x;
	return fa[x] = get(fa[x]);
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> p[i].a >> p[i].b >> p[i].c;
	sort(p + 1, p + m + 1);
	for (int i = 1; i <= (n << 1); i++) fa[i] = i;
	for (int i = 1; i <= m; i++) {
		int x = get(p[i].a), y = get(p[i].b);
		int nx = get(p[i].a + n), ny = get(p[i].b + n);
		if (x == y) {
			cout << p[i].c << endl;
			return 0;
		}
		fa[x] = ny;
		fa[y] = nx;
	}
	cout << "0" << endl;
	return 0;
}
