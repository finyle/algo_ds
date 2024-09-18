// fractal: 画出n级分形box

#include <cstdio>
#include <iostream>
using namespace std;
const int N = 730;
int n, p[7];
bool a[N][N];

void Fractal(int k, int x, int y) {
	if (!k) {
		a[x][y] = 1;
		return;
	}
	Fractal(k - 1, x, y);
	Fractal(k - 1, x, y + 2 * p[k-1]);
	Fractal(k - 1, x + p[k-1], y + p[k-1]);
	Fractal(k - 1, x + 2 * p[k-1], y);
	Fractal(k - 1, x + 2 * p[k-1], y + 2 * p[k-1]);
}

void Fractal() {
	n--;
	Fractal(n, 1, 1);
	for (int i = 1; i <= p[n]; i++) {
		for (int j = 1; j <= p[n]; j++)
			putchar(a[i][j] ? 'X' : ' ');
		printf("\n");
	}
	printf("-\n");
	for (int i = 1; i <= p[n]; i++)
		for (int j = 1; j <= p[n]; j++)
			a[i][j] = 0;
}

int main() {
	p[0] = 1;
	for (int i = 1; i < 7; i++) p[i] = p[i-1] * 3;
	while (scanf("%d", &n) == 1 && n != -1) Fractal();
	return 0;
}

/*
 * input:
7
2
7
6
4
3
6
1
6
7
1
6
7
7
1
2
7
1
5
5
3
3
4
7
6
7
6
6
7
2
2
6
2
3
1
5
6
1
5
4
4
5
5
3
6
3
1
5
2
2
5
2
1
5
4
1
2
5
6
2
4
5
1
2
2
7
4
4
1
4
7
6
1
3
4
7
6
1
6
7
2
3
5
5
4
4
4
6
2
3
5
2
1
5
1
7
5
4
5
1
-1
 * output:

 */
