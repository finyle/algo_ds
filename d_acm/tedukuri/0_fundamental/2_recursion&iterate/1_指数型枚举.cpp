/*
 * 递归实现指数型枚举：从1~n这n个整数中随机选取任意多个，输出所有可能的选择方案
 */

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int n;
vector<int> chosen; // 被选择的数
void calc(int x) {
    if (x == n + 1) { // 问题边界
        for (int i = 0; i < chosen.size(); i++)
            printf("%d ", chosen[i]);
        puts("");
        return;
    }
    //"不选x"分支
    calc(x + 1); // 求解子问题
    //"选x"分支
    chosen.push_back(x); // 记录x已被选择
    calc(x + 1); // 求解子问题
    chosen.pop_back(); // 准备回溯到上一问题之前，还原现场
}
int main() {
    cin >> n;
    calc(1);  // 主函数中的调用入口
}

/*
 * input:
5
 * output:
5
4
4 5
3
3 5
3 4
3 4 5
2
2 5
2 4
2 4 5
2 3
2 3 5
2 3 4
2 3 4 5
1
1 5
1 4
1 4 5
1 3
1 3 5
1 3 4
1 3 4 5
1 2
1 2 5
1 2 4
1 2 4 5
1 2 3
1 2 3 5
1 2 3 4
1 2 3 4 5
 */