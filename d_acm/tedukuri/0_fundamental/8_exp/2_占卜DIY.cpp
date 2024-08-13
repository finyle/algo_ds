// 模拟： 13行， 代表13堆牌，每堆4张， 计算一共开了几对
// 规则：最后一堆为生命牌，从中抽一张翻过来放至对应数字牌堆，再从对应牌堆底部抽一张重复，抽到k就扔掉，从生命牌中抽取，直至生命牌用完，统计多少对

// intput:
//8 5 A A
//K 5 3 2
//9 6 0 6
//3 4 3 4
//3 4 4 5
//5 6 7 6
//8 7 7 7
//9 9 8 8
//9 0 0 0
//K J J J
//Q A Q K
//J Q 2 2
//A K Q 2

// output:
// 9

#include <cstring>
#include <iostream>
using namespace std;
char s[14][5];
int f[100], ans[13];

int main() {
	for (int i = 1; i <= 13; i++) {
		for (int j = 1; j <= 4; j++)
			cin >> s[i][j];
	}
	f['A'] = 1;
	for (int i = '2'; i <= '9'; i++) f[i] = i - '0';
	f['0'] = 10;
	f['J'] = 11;
	f['Q'] = 12;
	f['K'] = 13;
	memset(ans, 0, sizeof(ans));
	for (int i = 1; i <= 4; i++) {
		int t = s[13][i];
		while (f[t] != 13 && ans[f[t]] < 4) {
			ans[f[t]]++;
			int temp = s[f[t]][4];
			for (int j = 4; j > 1; j--) s[f[t]][j] = s[f[t]][j-1];
			t = s[f[t]][1] = temp;
		}
	}
	for (int i = 1; i <= 12; i++)
		if (ans[i] == 4) ans[0]++;
	cout << ans[0] << endl;
	return 0;
}

/*
 * input:
 * output:
 *
 */