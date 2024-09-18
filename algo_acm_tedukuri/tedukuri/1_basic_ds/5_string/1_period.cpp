/*
 * period： 如果一个字符从S是由一个字符串T 重复K西形成的，则称T是S的循环元，使K最大的字符串T称为S的最小循环元，求出最小循环元长度和最大循环次数

 */

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
using namespace std;
char a[1000010];
int next1[1000010], n, T;
void calc_next() {
    next1[1] = 0;
    for (int i = 2, j = 0; i <= n; i++) {
        while (j > 0 && a[i] != a[j+1]) j = next1[j];
        if (a[i] == a[j+1]) j++;
        next1[i] = j;
    }
}
int main() {
    while (cin >> n && n) {
        scanf("%s", a + 1);
        calc_next();
        printf("Test case #%d\n", ++T);
        for (int i = 2; i <= n; i++) {
            if (i % (i - next1[i]) == 0 && i / (i - next1[i]) > 1)
                printf("%d %d\n", i, i / (i - next1[i]));
        }
        puts("");
    }
}

/*
 * input:
5
abcde
610
abaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabacabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabacabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabacabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabacabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabacabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabacabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabacabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabacabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabacabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabaabac
 * output:
 */