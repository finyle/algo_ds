/*
 * 双端队列: 对n个数进行排序，只能使用若干个双端队列，必须依次处理这些书，对每个数只能：创建一个新双队列，并将Ai作为队列中唯一的数；把Ai从已有队列的队头或队尾入队，最少需要多少个队列

 */
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200006, INF = 0x3f3f3f3f;
pair<int, int> a[N];
int n;
vector<int> p[N];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i].first);
        a[i].second = i;
    }
    sort(a + 1, a + n + 1);
    int t = 0;
    for (int i = 1; i <= n; i++) {
        p[++t].push_back(a[i].second);
        while (a[i].first == a[i+1].first)
            p[t].push_back(a[++i].second);
    }
    for (int i = 1; i <= t; i++) sort(p[i].begin(), p[i].end());
    bool flag = 0;
    int num = INF, ans = 1;
    for (int i = 1; i <= t; i++) {
        int s = p[i].size();
        if (flag) {
            if (num < p[i][0]) num = p[i][s-1];
            else {
                ++ans;
                flag = 0;
                num = p[i][0];
            }
        }
        else {
            if (num > p[i][s-1]) num = p[i][0];
            else {
                flag = 1;
                num = p[i][s-1];
            }
        }
    }
    cout << ans << endl;
    return 0;
}
/*
 * input:
19
1
2
3
4
5
6
7
8
9
10
9
8
7
6
5
4
3
2
1

 * output:
5

 */