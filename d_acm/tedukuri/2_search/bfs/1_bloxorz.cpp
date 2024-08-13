// bloxorz: 二维矩阵四方向移动，带限制条件

int bfs() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < 3; k ++)
                d[i][j][k] = -1;
        }
    }
    while (q.size()) q.pop();
    d[st.x][st.y][st.lie] = 0;
    q.push(st);
    while (q.size()) {
        rec now = q.front(); q.pop(); //取出队头
        for (int i = 0; i < 4; i++) { //向4个方向滚动
            rec next;
            next.x = now.x + next_x[now.lie][i];
            next.y = now.y + next_y[now.lie][i];
            next.lie = next_lie[now.lie][i];
            if (!valid(next)) continue;
            if (d[next.x][next.y][next.lie] == -1) { // 还未访问
                d[next.x][next.y][next.lie] = d[now.x][now.y][now.lie] + 1;
                q.push(next);
                if (next.x = ed.x && next.y == ed.y && next.lie == ed.lie)
                    return d[next.x][next.y][next.lie];  // 到达目标
            }
        }
    }
}