/*
 * 后缀数组：通常使用倍增或DC3算法事项； 使用快排 快排，hash，二分实现一个简单的O(nlog^2n);

 */
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int SIZE = 300010, INF = 1 << 30;
int a[SIZE], sa[SIZE], rk[SIZE], fir[SIZE], sec[SIZE], c[SIZE], h[SIZE];
char str[SIZE];
int n, p;

bool comp(int i, int j, int k)
{
    return sec[i] == sec[j] && sec[i + k] == sec[j + k];
}

void sufarr(int n)
{
    int i, p, l, m = 200;
    for (i = 0;i < m;i++) c[i] = 0;
    for (i = 0;i < n;i++) c[rk[i] = a[i]]++;
    for (i = 1;i < m;i++) c[i] += c[i - 1];
    for (i = n - 1;i >= 0;i--) sa[--c[a[i]]] = i;
    for (l = p = 1;p < n;l *= 2, m = p)
    {
        for (p = 0, i = n - l;i < n;i++) sec[p++] = i;
        for (i = 0;i < n;i++)
            if (sa[i] >= l) sec[p++] = sa[i] - l;
        for (i = 0;i < n;i++) fir[i] = rk[sec[i]];
        for (i = 0;i < m;i++) c[i] = 0;
        for (i = 0;i < n;i++) c[fir[i]]++;
        for (i = 1;i < m;i++) c[i] += c[i - 1];
        for (i = n - 1;i >= 0;i--) sa[--c[fir[i]]] = sec[i];
        memcpy(sec, rk, sizeof(rk));
        rk[sa[0]] = 0;
        for (i = p = 1;i < n;i++)
            rk[sa[i]] = comp(sa[i], sa[i - 1], l) ? p - 1 : p++;
    }
}

void calh()
{
    int i, j, k = 0;
    for (i = 1;i <= n;i++) rk[sa[i]] = i;
    for (i = 0;i < n;h[rk[i++]] = k)
        for (k ? k-- : 0, j = sa[rk[i] - 1];a[i + k] == a[j + k];k++);
}

int main()
{
    //freopen("savour.in", "r", stdin);
    //freopen("savour.out", "w", stdout);
    scanf("%s", str);
    n = strlen(str);
    for (int i = 0;i < n;i++) a[i] = str[i];
    a[n] = 0;
    sufarr(n + 1);
    calh();
    for(int i = 1; i <= n; i++) printf("%d ", sa[i]); puts("");
    for(int i = 1; i <= n; i++) printf("%d ", h[i]); puts("");
    //fclose(stdin);
    //fclose(stdout);
}

/*
 * input:
ycobizcoyizcobiyyobiycobiycoyiycybyyyobiycobizyoyiycybyzcoyiycoyizcoyizcybiyyoyiycobyzcoyizcybizcobi

 * output:
98 18 38 23 13 73 93 3 43 33 53 83 96 21 11 1 41 81 56 26 6 61 66 86 71 91 31 51 99 19 39 79 24 59 29 49 14 74 94 9 4 64 69 89 44 97 17 37 22 12 2 42 82 77 57 27 47 7 62 67 87 72 92 32 52 20 0 40 80 25 60 30 50 78 58 28 48 8 63 68 88 16 36 76 46 15 35 75 34 54 84 95 10 55 5 65 85 70 90 45
0 2 7 5 3 5 2 5 3 1 2 7 0 4 5 4 5 3 2 6 4 7 6 9 1 4 3 4 0 1 6 5 4 6 3 6 2 4 1 6 4 8 3 6 2 0 3 8 6 4 3 4 2 1 6 5 8 3 6 5 8 0 3 2 3 1 5 6 4 3 5 2 5 1 5 4 7 2 5 4 7 1 9 2 6 1 10 3 2 1 6 0 5 3 5 7 10 2 5 1

 */