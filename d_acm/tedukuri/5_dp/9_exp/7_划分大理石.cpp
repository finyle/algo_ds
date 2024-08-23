
/*
 * Folding(给定字符串，将连续字符计数后压缩) 区间dp
 */

#include <bits/stdc++.h>
using namespace std;

const int p = 10005;

int a[7], used[p << 1];
bool f[p];

int main()
{
    while (true)
    {
        a[0] = 0;
        for (int i = 1; i < 7; ++i)
            cin >> a[i], a[0] += a[i] * i;

        if (a[0] == 0) break;
        if (a[0] & 1) { cout << "Can't\n"; continue; }
        memset(f, 0, sizeof f);
        a[0] >>= 1; f[0] = 1;

        for (int i = 1; i < 7; ++i)
        {
            for (int j = 0; j <= a[0]; ++j) used[j] = 0;

            for (int j = i; j <= a[0]; ++j)
                if (!f[j] && f[j - i] && used[j - i] < a[i])
                    f[j] = 1, used[j] = used[j - i] + 1;
        }

        if (f[a[0]]) cout << "Can\n";
        else cout << "Can't\n";
    }
    return 0;
}

/*
 * input:
2 6 7 3 0 9
0 9 2 2 5 7
2 5 5 1 3 2
5 2 9 0 4 0
2 2 3 3 2 2
5 4 8 8 2 0
5 1 0 8 6 8
0 2 6 6 0 0
5 9 7 9 2 8
6 0 0 4 4 3
0 0 0 0 0 0

 * output:
Can't
Can't
Can
Can
Can't
Can't
Can't
Can
Can
Can
 */