
/*
 * a^b(移位运算：二进制补码表示下，把数字同时向左或向右移)：求a的b次方对p取模的值
 * cpp 位运算符： 按位与& 按位或| 异或^ 取反~ <<二进制左移 >>二进制右移
 * 与：满足两个为1； 或至少一个为1； 异或：不同为1； 同或：相同为1
 * 左移n位相当于10进制乘2的n次幂；右移对应除
 */

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lowbit(x) (x&-x)
using namespace std;
int a, b, p;

int power(int a, int b, int p) { // calculate (a ^ b) mod p
    int ans = 1 % p; // 取余
    for (; b; b >>= 1) { // b循环除以2，计算a的b次幂
        if (b & 1) ans = (long long)ans * a % p; // 直到b被除到1，终止循环
        a = (long long)a * a % p;
    }
    return ans;
}

int main() {
    cin >> a >> b >> p;
    cout << power(a, b, p) << endl;
    cout << lowbit(10) << endl;
}


/*
 * input:
126348976 982638476 938420413
 * output:
701649771
 */