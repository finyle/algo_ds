/*
 * 邻值查找：带有索引数组的多个数据链表构成的结构集合(平衡树， 链表)

 */

#include <set>
#include <cstdio>
#include <iostream>
using namespace std;
const int INF = 0x7f7f7f7f;
set<pair<int, int> > s;

int main() {
    int n, a;
    cin >> n >> a;
    s.insert(make_pair(a, 1));
    for (int i = 2; i <= n; i++) {
        scanf("%d", &a);
        s.insert(make_pair(a, i));
        set<pair<int, int> >::iterator it = s.find(make_pair(a, i));
        pair<int, int> ans;
        ans.first = INF;
        if (++it != s.end())
            ans = make_pair((*it).first - a, (*it).second);
        it = s.find(make_pair(a, i));
        if (it-- != s.begin() && ans.first >= a - (*it).first)
            ans = make_pair(a - (*it).first, (*it).second);
        cout << ans.first << " " << ans.second << endl;
    }
    return 0;
}

/*
 * input:
10
4 5 6 1 2 3 7 8 9 10
 * output:
1 1
1 2
3 1
1 4
1 5
1 3
1 7
1 8
1 9

 *
 */