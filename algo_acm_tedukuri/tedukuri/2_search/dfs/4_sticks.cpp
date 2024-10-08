#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[100], v[100], n, len, cnt;
// (剪枝) 一组等长木棍，随机砍断每节长度不超过50；复原时初始的最小长度
// 正在拼第stick根原始木棒
// 第stick根木棒的当前长度为cab
// 拼接到第stick根木棒中的上一根小木棒为last
bool dfs(int stick, int cab, int last) {
    if (stick > cnt) return true;  // 所有木棒已经全部拼接好，搜索成功
    if (cab == len) return dfs(stick + 1, 0, 1); // 第stick根木棒已经拼接好，去拼下一根
    int fail = 0; // 剪枝
    for (int i = last; i <= n; i++) { // 剪枝
        if (!v[i] && cab + a[i] <= len && fail != a[i]) {
            v[i] = 1;
            if (dfs(stick, cab + a[i], i + 1)) return true;
            fail = a[i];
            v[i] = 0; // 还原现场
            if (cab == 0 || cab + a[i] == len) return false; // 剪枝(3, 4)
        }
    }
    return false; // 所有分支均尝试过，搜索失败
}
int main() {
    while (cin >> n && n) {
        int sum = 0, val = 0, m = 0;
        for (int i = 1; i <= n; i++) {
            int x;
            scanf("%d", &x);
            if (x <= 50) {
                a[++m] = x;
                sum += a[m];
                val = max(val, a[m]);
            }
        }
        n = m;
        sort(a + 1, a + n + 1);
        reverse(a + 1, a + n + 1);
        for (len = val; len <= sum; len++) {
            if (sum % len) continue;
            cnt = sum / len; //原始木棒长度为len，共cnt根
            memset(v, 0, sizeof(v));
            if (dfs(1, 0, 1)) break;
        }
        cout << len << endl;
    }
}