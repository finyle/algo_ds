/*
这头神奇的牛像其它牛一样喜欢吃草，给你一张地图，上面标注了The Knight的开始位置，树、灌木、石头以及其它障碍的位置，除此之外还有一捆草。现在你的任务是，确定The Knight要想吃到草，至少需要跳多少次。The Knight的位置用'K'来标记，障碍的位置用'*'来标记，草的位置用'H'来标记。
这里有一个地图的例子：
             11 | . . . . . . . . . .
             10 | . . . . * . . . . .
              9 | . . . . . . . . . .
              8 | . . . * . * . . . .
              7 | . . . . . . . * . .
              6 | . . * . . * . . . H
              5 | * . . . . . . . . .
              4 | . . . * . . . * . .
              3 | . K . . . . . . . .
              2 | . . . * . . . . . *
              1 | . . * . . . . * . .
              0 ----------------------
                                    1
                0 1 2 3 4 5 6 7 8 9 0

The Knight 可以按照下图中的A,B,C,D...这条路径用5次跳到草的地方（有可能其它路线的长度也是5）：
             11 | . . . . . . . . . .
             10 | . . . . * . . . . .
              9 | . . . . . . . . . .
              8 | . . . * . * . . . .
              7 | . . . . . . . * . .
              6 | . . * . . * . . . F<
              5 | * . B . . . . . . .
              4 | . . . * C . . * E .
              3 | .>A . . . . D . . .
              2 | . . . * . . . . . *
              1 | . . * . . . . * . .
              0 ----------------------
                                    1
                0 1 2 3 4 5 6 7 8 9 0
*/
#include <queue>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 156;
char s[N][N];
bool v[N][N];
int dx[8] = {-2,-1,1,2,2,1,-1,-2};
int dy[8] = {1,2,2,1,-1,-2,-2,-1};
struct P {
	int x, y, ans;
} st, ed;
queue<P> q;
int main() {
	memset(v, 0, sizeof(v));
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> (s[i] + 1);
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			if (s[i][j] == 'K') {
				st.x = i;
				st.y = j;
				st.ans = 0;
				q.push(st);
				v[i][j] = 1;
			} else if (s[i][j] == 'H') {
				ed.x = i;
				ed.y = j;
			} else if (s[i][j] == '*') v[i][j] = 1;
	while (q.size()) {
		P p = q.front();
		if (p.x == ed.x && p.y == ed.y) {
			cout << p.ans << endl;
			return 0;
		}
		q.pop();
		for (int i = 0; i < 8; i++) {
			int nx = p.x + dx[i], ny = p.y + dy[i];
			if (nx < 0 || ny < 0 || nx > m || ny > n) continue;
			if (v[nx][ny]) continue;
			P np;
			np.x = nx;
			np.y = ny;
			np.ans = p.ans + 1;
			q.push(np);
			v[nx][ny] = 1;
		}
	}
	return 0;
}
