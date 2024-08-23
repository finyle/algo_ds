/*
 * 递归实现排列型枚举：把1~n这n个整数排列称一行后随机打乱顺序，输出所有可能的次序

 */
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int n;
int order[20]; // 按顺序依次记录被选择的整数
bool chosen[20]; // 标记被选择的整数
void calc(int k) {
    if (k == n + 1) { // 问题边界
        for (int i = 1; i <= n; i++)
            printf("%d ", order[i]);
        puts("");
        return;
    }
    for (int i = 1; i <= n; i++) { // 多叉树遍历
        if (chosen[i]) continue;
        order[k] = i;
        chosen[i] = 1;
        calc(k + 1);
        chosen[i] = 0;
        order[k] = 0; // 这一行可以省略
    }
}
int main() {
    cin >> n;
    calc(1);  // 主函数中的调用入口
}

/*
 * input:
3
 * output:
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
 */
