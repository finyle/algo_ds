/*
 * team queue： n 个小组排队，每个小组中若干人。给定入队和出队指令，输出出队顺序

 */

#include <queue>
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 1000000, T = 1006;
int t, f[N], id = 0;
char s[10];
queue<int> q[T];

void Team_Queue() {
    q[0] = queue<int>();
    for (int i = 1; i <= t; i++) {
        int n;
        scanf("%d", &n);
        while (n--) {
            int x;
            scanf("%d", &x);
            f[x] = i;
        }
        q[i] = queue<int>();
    }
    cout << "Scenario #" << ++id << endl;
    while (scanf("%s", s) && s[0] != 'S') {
        if (s[0] == 'E') {
            int x;
            scanf("%d", &x);
            if (q[f[x]].empty()) q[0].push(f[x]);
            q[f[x]].push(x);
        } else {
            int x = q[0].front();
            printf("%d\n", q[x].front());
            q[x].pop();
            if (q[x].empty()) q[0].pop();
        }
    }
    cout << endl;
}

int main() {
    while (cin >> t && t) Team_Queue();
    return 0;
}

/*
 * input:
2
3 101 102 103
3 201 202 203
ENQUEUE 101
ENQUEUE 201
ENQUEUE 102
ENQUEUE 202
ENQUEUE 103
ENQUEUE 203
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
STOP
 * output:
Scenario #1
101
102
103
201
202
203
 */