/*
 * 递归实现组合型枚举：从1~n这n个整数中随机选出m个，输出所有可能的选择方案

 */
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int n, m;
vector<int> chosen;
void calc(int x) {
    if (chosen.size() > m || chosen.size() + (n - x + 1) < m) return;
    if (x == n + 1) { // 问题边界
        for (int i = 0; i < chosen.size(); i++)
            printf("%d ", chosen[i]);
        puts("");
        return;
    }
    chosen.push_back(x);
    calc(x + 1);
    chosen.pop_back(); // 回溯 还原现场
    calc(x + 1);
}
int main() {
    cin >> n >> m;
    calc(1);
}

/*
 * input:
5 3
 * output：
1 2 3
1 2 4
1 2 5
1 3 4
1 3 5
1 4 5
2 3 4
2 3 5
2 4 5
3 4 5

 */