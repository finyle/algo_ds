/*
 * 阶乘分解：给定整数n，试把阶乘n！分解质因数，按照算术基本定理的形式输出结果中的pi和ci

 */

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
vector<int> prime;
bool v[1000010];
int n;
void primes(int n) {
    memset(v, 0, sizeof(v));
    for (int i = 2; i <= n; i++) {
        if (v[i]) continue;
        prime.push_back(i);
        for (int j = i; j <= n/i; j++) v[i*j] = 1;
    }
}
int main() {
	cin >> n;
	primes(n);
	for (int i = 0; i < prime.size(); i++) {
		int p = prime[i], c = 0;
		for (int j = n; j; j /= p) c += j / p;
		printf("%d %d\n", p, c);
	}
}

/*
 * input:
9
 * output:
2 7
3 4
5 1
7 1

 *
 */