//给出一个表达式,其中运算符仅包含+,-,*,/,^要求求出表达式的最终值
//        数据可能会出现括号情况 还有可能出现多余括号情况
//
//        数据保证不会出现>maxlongint的数据
//
//        数据可能回出现负数情况

//表达式总长度<=30
// input: (2+2)^(1+1)
// output: 16
#include <cstring>
#include <iostream>
using namespace std;
const int N = 106;
char s[N], st[N], ans[N];
int top, t[600], cnt, stt[N], num;

int mul(int x, int k) {
	int m = 1;
	while (k--) m *= x;
	return m;
}

int main() {
	t[int('^')] = 4;
	t[int('*')] = t[int('/')] = 3;
	t[int('+')] = t[int('-')] = 1;
	cin >> (s + 1);
	int len = strlen(s + 1);
	for (int i = 1; i <= len; i++)
		if (s[i] >= '0' && s[i] <= '9') ans[++cnt] = s[i];
		else {
			if (s[i-1] >= '0' && s[i-1] <= '9') ans[++cnt] = '#';
			if (s[i] == '(') st[++top] = s[i];
			else if (s[i] == ')') {
				while (st[top] != '(') ans[++cnt] = st[top--];
				top--;
			} else {
				while (t[s[i]] <= t[st[top]] && top)
					ans[++cnt] = st[top--];
				st[++top] = s[i];
			}
		}
	if (s[len] >= '0' && s[len] <= '9') ans[++cnt] = '#';
	while (top) ans[++cnt] = st[top--];
	for (int i = 1; i <= cnt; i++) {
		if (ans[i] >= '0' && ans[i] <= '9') {
			num = num * 10 + ans[i] - '0';
			continue;
		}
		if (ans[i] == '#') {
			stt[++top] = num;
			num = 0;
		} else {
			top--;
			if (ans[i] == '+') stt[top] = stt[top] + stt[top+1];
			else if (ans[i] == '-') stt[top] = stt[top] - stt[top+1];
			else if (ans[i] == '*') stt[top] = stt[top] * stt[top+1];
			else if (ans[i] == '/') stt[top] = stt[top] / stt[top+1];
			else if (ans[i] == '^') stt[top] = mul(stt[top], stt[top+1]);
			else top++;
		}
	}
	cout << stt[top] << endl;
	return 0;
}
