//

// input: 8
//62 2 abcdefghiz
//10 16 1234567890123456789012345678901234567890
//16 35 3A0C92075C0DBF3B8ACBC5F96CE3F0AD2
//35 23 333YMHOUE8JPLT7OX6K9FYCQ8A
//23 49 946B9AA02MI37E3D3MMJ4G7BL2F05
//49 61 1VbDkSIMJL3JjRgAdlUfcaWj
//61 5 dl9MDSWqwHjDnToKcsWE1S
//5 10 42104444441001414401221302402201233340311104212022133030

// output: 62 abcdefghiz
//2 11011100000100010111110010010110011111001001100011010010001
//10 1234567890123456789012345678901234567890
//16 3A0C92075C0DBF3B8ACBC5F96CE3F0AD2
//16 3A0C92075C0DBF3B8ACBC5F96CE3F0AD2
//35 333YMHOUE8JPLT7OX6K9FYCQ8A
//35 333YMHOUE8JPLT7OX6K9FYCQ8A
//23 946B9AA02MI37E3D3MMJ4G7BL2F05
//23 946B9AA02MI37E3D3MMJ4G7BL2F05
//49 1VbDkSIMJL3JjRgAdlUfcaWj
//49 1VbDkSIMJL3JjRgAdlUfcaWj
//61 dl9MDSWqwHjDnToKcsWE1S
//61 dl9MDSWqwHjDnToKcsWE1S
//5 42104444441001414401221302402201233340311104212022133030
//5 42104444441001414401221302402201233340311104212022133030
//10 1234567890123456789012345678901234567890

#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1006;
int f[200], ff[100];
char s[N], ans[N];

void NUMBER_BASE_CONVERSION() {
	int a, b;
	cin >> a >> b;
	scanf("%s", s);
	cout << a << " " << s << endl << b << " ";
	int len = strlen(s), t = strlen(s), i;
	for (i = 0; t; i++) {
		int k = 0;
		for (int j = len - t; j < len; j++) {
			k = k * a + f[(int)s[j]];
			s[j] = ff[k/b];
			k %= b;
		}
		ans[i] = ff[k];
		while (t > 0 && s[len-t] == '0') t--;
	}
	while (--i >= 0) cout << ans[i];
	cout << endl << endl;
}

int main() {
	int t = 0;
	for (int i = '0'; i <= '9'; i++) {
		f[i] = t;
		ff[t++] = i;
	}
	for (int i = 'A'; i <= 'Z'; i++) {
		f[i] = t;
		ff[t++] = i;
	}
	for (int i = 'a'; i <= 'z'; i++) {
		f[i] = t;
		ff[t++] = i;
	}
	cin >> t;
	while (t--) NUMBER_BASE_CONVERSION();
	return 0;
}
