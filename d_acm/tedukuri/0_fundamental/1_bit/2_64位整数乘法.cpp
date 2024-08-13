/*
 * 64位整数乘法: 求a乘b对p取模的值：数学推导无需遍历

 */

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long a, b, p;

long long mul(long long a, long long b, long long p) {
    long long ans = 0;
    for (; b; b >>= 1) {
        if (b & 1) ans = (ans + a) % p;
        a = a * 2 % p;
    }
    return ans;
}

int main() {
    cin >> a >> b >> p;
    cout << mul(a, b, p) << endl;
}

/*
 * input: 3 4 5
 * output: 2
 */