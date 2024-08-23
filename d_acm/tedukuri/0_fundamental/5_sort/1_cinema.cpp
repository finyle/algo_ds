/*
 * cinema(离散化： 把无穷大集合中的若干个元素映射为有限集合，以便于统计的方法)：
 * m部电影，n个人看，选择任意一部，使得高兴的人最多, 每部电影语音，字母采用不同的语言,每个人只懂一种语言，听懂语音很高兴，看懂字母，比较高兴，都不懂，不开心；让比较高兴的人最多
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200006;
int n, m, a[N], x[N], y[N], cinema[N*3], tot = 0, k, ans[N*3];

int find(int f) {
    return lower_bound(cinema + 1, cinema + k + 1, f) - cinema;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        cinema[++tot] = a[i];
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        scanf("%d", &x[i]);
        cinema[++tot] = x[i];
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", &y[i]);
        cinema[++tot] = y[i];
    }
    sort(cinema + 1, cinema + tot + 1);
    k = unique(cinema + 1, cinema + tot + 1) - (cinema + 1);
    memset(ans, 0, sizeof(ans));
    for (int i = 1; i <= n; i++) ans[find(a[i])]++;
    int ans0 = 1, ans1 = 0, ans2 = 0;
    for (int i = 1; i <= m; i++) {
        int ansx = ans[find(x[i])], ansy = ans[find(y[i])];
        if (ansx > ans1 || (ansx == ans1 && ansy > ans2)) {
            ans0 = i;
            ans1 = ansx;
            ans2 = ansy;
        }
    }
    cout << ans0 << endl;
    return 0;
}
/*
 * input:
3
2 3 2
2
3 2
2 3

 * output:
2

 */
