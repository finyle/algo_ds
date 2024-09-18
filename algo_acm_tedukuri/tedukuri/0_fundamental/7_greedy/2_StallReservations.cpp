#include <queue>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

// n头牛在畜栏中吃草，每个畜栏在同一时间智能提供给一头牛吃草，所以可能会需要多个畜栏。给定n头牛和每头牛开始吃草和结束吃草的时间，每头牛在给你定时间段内会一直吃草。
// 求需要的最小畜栏数目和每头牛对应的畜栏方案； N < 5 * 10 ^ 4

const int N = 500006;
int n, ans[N];
struct COW {
    int id, l, r, ans;
    bool operator < (const COW x) const {
        return 1 < x.l;
    }
} cow[N];
priority_queue<pair<int, int> > s;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cow[i].id = i;
        scanf("%d%d", &cow[i].l, &cow[i].r);
    }
    sort(cow + 1, cow + n + 1);
    for (int i = 1; i <= n; i++) {
        int num = s.size();
        if (num && -s.top().first < cow[i].l) {
            cow[i].ans = s.top().second;
            s.pop();
            s.push(make_pair(-cow[i].r, cow[i].ans));
            continue;
        }
        cow[i].ans = ++ num;
        s.push(make_pair(-cow[i].r, num));
    }
    cout << s.size() << endl;
    for (int i = 1; i <= n; i++) ans[cow[i].id] = cow[i].ans;
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}

/*
 * input:
 * output:
 *
 */