// 解法一：分层图+堆优化Dijkstra
#include<bits/stdc++.h>
using namespace std;
const int MAX_N = 1005, MAX_M = 20005;
int head[MAX_N], ver[MAX_M], edge[MAX_M], nxt[MAX_M], tot;
int n, m, k, d[MAX_N][MAX_N];
bool v[MAX_N][MAX_N];
// pair<-dist[x], pair<x, j>>
priority_queue<pair<int, pair<int, int>>> q;

// 插入一条从x到y长度z的有向边
void add(int x, int y, int z) {
    tot++;
    ver[tot] = y;
    edge[tot] = z;
    nxt[tot] = head[x]; // 在head[x]这条链的开头插入新点
    head[x] = tot;
}

int main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
        add(y, x, z);
    }
    memset(d, 0x7f, sizeof(d));
    d[1][0] = 0;
    q.push(make_pair(0, make_pair(1, 0)));
    while (!q.empty()) {
        int i = q.top().second.first, j = q.top().second.second;
        q.pop();
        if (v[i][j]) continue;
        v[i][j] = true;
        for (int _ = head[i]; _; _ = nxt[_]) {
            int y = ver[_], z = edge[_];
            if (d[y][j] > max(d[i][j], z)) {
                d[y][j] = max(d[i][j], z);
                q.push(make_pair(-d[y][j], make_pair(y, j)));
            }
            if (j < k && d[y][j+1] > d[i][j]) {
                d[y][j+1] = d[i][j];
                q.push(make_pair(-d[y][j+1], make_pair(y, j+1)));
            }
        }
    }
    int ans = 0x7f7f7f7f;
    for (int j = 0; j <= k; j++) ans = min(ans, d[n][j]);
    if (ans == 0x7f7f7f7f) puts("-1");
    else cout << ans << endl;
}

/*
 * input:
5 7 1
1 2 5
3 1 4
2 4 8
3 2 3
5 2 9
3 4 7
4 5 6

 * output:
4

 */

// 二分答案, 双端队列bfs
// 解法二：二分答案+双端队列BFS
//#include<bits/stdc++.h>
//using namespace std;
//const int MAX_N = 1005, MAX_M = 20005;
//int head[MAX_N], ver[MAX_M], edge[MAX_M], nxt[MAX_M], tot;
//int n, m, k, d[MAX_N];
//deque<int> q;
//
//// 插入一条从x到y长度z的有向边
//void add(int x, int y, int z) {
//    tot++;
//    ver[tot] = y;
//    edge[tot] = z;
//    nxt[tot] = head[x]; // 在head[x]这条链的开头插入新点
//    head[x] = tot;
//}
//
//bool solve(int t) {
//    memset(d, 0x7f, sizeof(d));
//    d[1] = 0;
//    q.push_back(1);
//    while (!q.empty()) {
//        int x = q.front();
//        q.pop_front();
//        for (int i = head[x]; i; i = nxt[i]) {
//            int y = ver[i], z = edge[i] > t ? 1 : 0;
//            if (d[y] > d[x] + z) {
//                d[y] = d[x] + z;
//                if (z == 0) q.push_front(y); else q.push_back(y);
//            }
//        }
//    }
//    return d[n] <= k;
//}
//
//int main() {
//    cin >> n >> m >> k;
//    for (int i = 1; i <= m; i++) {
//        int x, y, z;
//        scanf("%d%d%d", &x, &y, &z);
//        add(x, y, z);
//        add(y, x, z);
//    }
//    int L = 0, R = 1000001;
//    while (L < R) {
//        int mid = (L + R) >> 1;
//        if (solve(mid)) R = mid; else L = mid + 1;
//    }
//    if (L == 1000001) puts("-1"); else cout << L << endl;
//}