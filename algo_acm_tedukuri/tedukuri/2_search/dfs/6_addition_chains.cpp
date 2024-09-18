#include <cstring>
#include <iostream>
using namespace std;
const int N = 106;
int n, ans[N], dep;
// (迭代加深) 给定整数n，找出符合条件的长度m最小的”加成序列“如果有多个满足要求的答案，找出任意一个可行解 n<=100
// x[1] = 1; x[m]=n; x[i] < x[i + 1];

bool dfs(int now) {
    if (now == dep) return ans[now] == n;
    bool v[N];
    memset(v, 0, sizeof(v));
    for (int i = now; i; i--) {
        for (int j = i; j; j--) {
            int num = ans[i] + ans[j];
            if (num <= n && num > ans[now] && !v[num]) {
                ans[now + 1] = num;
                if (dfs(now + 1)) return 1; // 迭代加深，
                else v[num] = 1;
            }
        }
    }
    return 0;
}

int main() {
    ans[1] = 1;
    while (cin >> n && n) {
        dep = 1;
        while (!dfs(1)) ++dep;
        for (int i = 1; i <= dep; i++) cout << ans[i] << " ";
        cout << endl;
    }
    return 0;
}