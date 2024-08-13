/*
给定数组，统计数组元素的累计波动值

input:
10
26
86
25
37
56
70
71
81
70
4
output：
158


*/
#include <set>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
const int INF = 0x3f3f3f3f;
int n, x, ans;
multiset<int> s;
multiset<int>::iterator it, l, r;

int main() {
	s.insert(INF);
	s.insert(-INF);
	cin >> n >> x;
	s.insert(x);
	ans = x;
	while (--n) {
		scanf("%d", &x);
		it = s.insert(x);
		l = --it;
		r = ++(++it);
		if (*l == -INF) ans += abs((double)x - *r);
		if (*r == INF) ans += abs((double)x - *l);
		if (*l != -INF && *r != INF)
			ans += min(abs((double)x - *r), abs((double)x - *l));
	}
	cout << ans << endl;
	return 0;
}
