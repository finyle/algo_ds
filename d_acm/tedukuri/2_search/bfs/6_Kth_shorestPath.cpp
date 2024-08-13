#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1006;
int n, m, st, ed, k, f[N], cnt[N];
bool v[N];
vector<pair<int, int> > e[N], fe[N];
priority_queue<pair<int, int> > pq;

// 第k最短路， 给定n个点，m条边的有向图，求从起点s到终点t第k短路径长度, 优先队列

void dijkstra() {
    memset(f, 0x3f, sizeof(f));
    memset(v, 0, sizeof(v));
    f[ed] = 0;
    pq.push(make_pair(0, ed));
    while (pq.size()) {
        int x = pq.top().second;
        pq.pop();
        if (v[x]) continue;
        v[x] = 1;
        for (unsigned int i = 0; i < fe[x].size(); i++) {
            int y = fe[x][i].first, z = fe[x][i].second;
            if (f[y] > f[x] + z) {
                f[y] = f[x] + z;
                pq.push(make_pair(-f[y], y));
            }
        }
    }
}

void A_star() { //预处理各个节点x到终点t的最短路长度f(x),等价于在反向图上以T为起点求解单源最短路径问题
    if (st == ed) ++k;
    pq.push(make_pair(-f[st], st));
    memset(cnt, 0, sizeof(cnt));
    while (pq.size()) {
        int x = pq.top().second;
        int dist = -pq.top().first - f[x];
        pq.pop();
        ++cnt[x];
        if (cnt[ed] == k) {
            cout << dist << endl;
            return;
        }
        for (unsigned int i = 0; i < e[x].size(); i++) {
            int y = e[x][i].first, z = e[x][i].second;
            if (cnt[y] != k) pq.push(make_pair(-f[y] - dist - z, y));
        }
    }
    cout << "-1" << endl;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        e[x].push_back(make_pair(y, z));
        fe[y].push_back(make_pair(x, z));
    }
    cin >> st >> ed >> k;
    dijkstra();
    A_star();
    return 0;
}
