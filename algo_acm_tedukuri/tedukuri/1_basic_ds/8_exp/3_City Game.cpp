// 这片土地被分成N*M个格子，每个格子里写着'R'或者'F'，R代表这块土地被赐予了rainbow，F代表这块土地被赐予了freda。
//现在freda要在这里卖萌。。。它要找一块矩形土地，要求这片土地都标着'F'并且面积最大。

// 对于50%的数据，1<=N,M<=200
//对于100%的数据，1<=N,M<=1000

// input: 5 6
//R F F F F F
//F F F F F F
//R R R F F F
//F F F F F F
//F F F F F F
// output: 45
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1006;
bool a[N][N];
int t, n, m, h[N], st[N], width[N];

int ddz(int k) {
	int ans = 0, top = 0;
	for (int i = 1; i <= m; i++)
		if (a[k][i]) h[i]++;
		else h[i] = 0;
	for (int i = 1; i <= m + 1; i++) {
		if (st[top] < h[i]) {
			st[++top] = h[i];
			width[top] = 1;
			ans = max(ans, h[i]);
		} else {
			int num = 0;
			while (top && st[top] >= h[i]) {
				num += width[top];
				ans = max(ans, st[top--] * num);
			}
			st[++top] = h[i];
			width[top] = ++num;
			ans = max(ans, st[top] * width[top]);
		}
	}
	return ans;
}

void City_Game() {
	memset(h, 0, sizeof(h));
	memset(st, 0, sizeof(st));
	memset(width, 0, sizeof(width));
	memset(a, 0, sizeof(a));
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			char c;
			cin >> c;
			a[i][j] = (c == 'F' ? 1 : 0);
		}
	int ans = 0;
	for (int i = 1; i <= n; i++) ans = max(ans, ddz(i));
	cout << 3 * ans << endl;
}

int main() {
	cin >> t;
	while (t--) City_Game();
	return 0;
}
