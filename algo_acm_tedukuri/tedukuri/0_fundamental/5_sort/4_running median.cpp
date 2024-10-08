/*
 * 动态维护中位数：依次读入一个整数序列，每当已经读入的整数个数为奇数时，输出已读入的整数构成的序列的中位数
 */

#include <queue>
#include <cstdio>
#include <iostream>
using namespace std;
priority_queue<int> q1, q2;

void Running_Median() {
    while (q1.size()) q1.pop();
    while (q2.size()) q2.pop();
    int num, n;
    cin >> num >> n;
    cout << num << " " << (n + 1) / 2 << endl;
    int a;
    cin >> a;
    cout << a << " ";
    q2.push(-a);
    int cnt = 1;
    for (int i = 2; i <= n; i++) {
        scanf("%d", &a);
        if (a < -q2.top()) q1.push(a); // 优先队列动态维护输入数列的中位数
        else q2.push(-a);
        int s = q1.size();
        if (s > i / 2) {
            q2.push(-q1.top());
            q1.pop();
        }
        if (s < i / 2) {
            q1.push(-q2.top());
            q2.pop();
        }
        if (i % 2) {
            cout<< -q2.top() << " ";
            if (++cnt % 10 == 0) cout << endl;
        }
    }
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) Running_Median();
    return 0;
}

/*
 * input:
9
1 9
1 2 3 4 5 6 7 8 9
2 9
9 8 7 6 5 4 3 2 1
3 23
23 41 13 22 -3 24 -31 -11 -8 -7
3 5 103 211 -311 -45 -67 -73 -81 -99
-33 24 56
4 567
 * output:
1 5
1 2 3 4 5
2 5
9 8 7 6 5
3 12
23 23 22 22 13 3 5 5 3 -3
-7 -3
 *
 */