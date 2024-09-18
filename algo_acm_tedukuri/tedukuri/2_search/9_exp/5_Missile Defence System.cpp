/*

防御系统，给定数组，返回
input:
40
15 30 40 34 12 23 24 1 31 35 22 37 29 21 3 13 33 5 25 32 8 2 4 36 7 38 10 27 18 6 28 26 17 16 9 20 11 39 19 14
40
21 35 2 15 13 14 33 11 22 19 12 9 31 18 5 20 25 28 10 23 1 27 6 24 16 26 29 34 39 7 40 8 17 36 30 3 37 32 38 4
50
42 20 17 25 8 2 34 27 39 29 11 1 4 16 24 21 10 37 22 12 18 28 9 50 19 5 36 13 33 15 7 47 32 31 26 14 49 6 44 41 40 23 35 45 43 46 30 48 3 38
10
1 10 2 9 3 8 4 7 5 6
10
1 2 3 4 5 6 7 8 9 10
10
10 9 8 7 6 5 4 3 2 1
25
1 21 14 11 12 6 13 5 19 17 9 23 16 18 7 22 8 20 15 10 25 3 24 2 4
25
6 11 8 18 12 23 16 3 4 20 7 21 5 24 22 15 25 13 2 19 14 10 9 1 17
0


output:
6
6
8
2
1
1
5
5

*/

#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;
const int N = 56;
int n, a[N];
unsigned int dep;
vector<int> up, down;

bool dfs(int x) {
	if (up.size() + down.size() > dep) return 0;
	if (x == n + 1) return 1;
	int num = 0, t;
	for (unsigned int i = 0; i < up.size(); i++)
		if (up[i] < a[x] && up[i] > num) {
			num = up[i];
			t = i;
		}
	if (num) {
		up[t] = a[x];
		if (dfs(x + 1)) return 1;
		up[t] = num;
	} else {
		up.push_back(a[x]);
		if (dfs(x + 1)) return 1;
		up.pop_back();
	}
	num = 0x3f3f3f3f;
	for (unsigned int i = 0; i < down.size(); i++)
		if (down[i] > a[x] && down[i] < num) {
			num = down[i];
			t = i;
		}
	if (num != 0x3f3f3f3f) {
		down[t] = a[x];
		if (dfs(x + 1)) return 1;
		down[t] = num;
	} else {
		down.push_back(a[x]);
		if (dfs(x + 1)) return 1;
		down.pop_back();
	}
	return 0;
}

void Missile_Defence_System() {
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	up.clear();
	down.clear();
	dep = 0;
	while (!dfs(1)) ++dep;
	cout << dep << endl;
}

int main() {
	while (cin >> n && n) Missile_Defence_System();
	return 0;
}
