
// (双向bfs) nightmareII

int bfs() {
    queue<pair<int, int>> q1, q2;
    px = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j ++) {

        }
    }
    int ans = 0;
    memset(v1, 0, sizeof(v1));
    memset(v2, 0, sizeof(v2));
    v1[bx][by] = 1; v2[gx][gy] = 1;
    q1.push(make_pair(bx, by)); q2.push(make_pair(gx, gy));
    while (q1.size() || q2.size()) {
        ans++;
        s1 = q1.size();
        for (int i = 1; i <= s1; i++) {
            pair<int, int> now = q1.front();
            q1.pop();
            if (!pd(now.first, now.second, ans)) continue;
            for (int j = 0; j < 4; j++) {
                int nx = now.first + dx[j];
                int ny = now.second + dy[j];
                if pd(nx, ny, ans) && ! v1[nx][ny] {
                    v1[nx][ny] = 1;
                    q1.push(make_pair(nx, ny));
                }
            }
        }
        s2 = q2.size();
        for (int i = 1; i <= s2; i++) {
            pair<int, int> now = q2.front();
            q2.pop();
            if (!pd(now.first, now.second, ans)) continue;
            for (int j = 0; j < 4; j++) {
                int nx = now.first + dx[j];
                int ny = now.second + dy[j];
                if pd(nx, ny, ans) && ! v2[nx][ny] {
                    if (v1[nx][ny]) return ans;
                    v2[nx][ny] = 1;
                    q2.push(make_pair(nx, ny));
                }
            }
        }
    }
}
