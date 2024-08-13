
// n个城市，m条道路构成一张无向图。在每个城市里有一个加油站，prices[],计算容量为c的车，从起点到终点至少花多少油费

void Full_Tank() {
    int c, st, ed;
    scanf("%d %d %d", &c, &st, &ed);
    priority_queue<pair<int, pair<int, int>>> empty;
    swap(q, empty);
    memset(d, 0x3f, sizeof(d));
    q.push(make_peir(0, make_pair(st, 0)));
    d[st][0] = 0;
    memset(v, 0, sizeof(v));
    while (q.size) {
        int city = q.top().second.first;
        int fuel = q.top().second.second;
        q.pop();
        if (city == ed) {
            cout << d[city][fuel] << endl;
            return;
        }
        if (v[city][fuel]) continue;
        v[city][fuel] = 1;
        if (fuel < c && d[city][fuel + 1] > d[city][fuel] + p[city]) {
            d[city][fuel + 1] = d[city][fuel] + p[city];
            q.push(make_pair(-d[city][fuel] - p[city], make_pair(city, fuel + 1)));
        }
        for (unsigned int i = 0; i < e[city].size(); i++) {
            int y = e[city][i].first, z = e[city][i].second;
            if (z <= fuel && d[y][fuel - z] > d[city][fuel]) {
                d[y][fuel - z] = d[city][fuel];
                q.push(make_pair(-d[city][fune]], make_pair(y, fuel - 2);)
            }
        }
    }
}