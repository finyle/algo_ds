
/*
 * 火车进出栈问题(进出栈序列问题: 搜索(递归), 递推， dp， 数学：求卡特兰数)：给定n个整数和一个无限大的栈，每个数都进栈出栈一次，进栈顺序为1，2，...,N,可能的出栈顺序有多少种？

 */
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 26;
int n, num = 0, st[N], top = 0, ans[N], t = 0;

void z(int x) {
    if (x == n + 1) {
        if (++num > 20) exit(0);
        for (int i = 1; i <= t; i++) printf("%d", ans[i]);
        for (int i = top; i; i--) printf("%d", st[i]);
        cout << endl;
        return;
    }
    if (top) {
        ans[++t] = st[top--];
        z(x);
        st[++top] = ans[t--];
    }
    st[++top] = x;
    z(x + 1);
    --top;
}

int main() {
    cin >> n;
    z(1);
    return 0;
}

/*
 * input:
3

 * output:
123
132
213
231
321
 *
 */
