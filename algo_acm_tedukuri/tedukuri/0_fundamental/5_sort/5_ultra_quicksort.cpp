/*
 * ltra-quicksort(逆序对)： 长度为n的序列a，只允许相邻元素两两交换，至少需要多少次将a从小到大排列

 */
#include <cstdio>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 500006;
int n, a[N], b[N];
ll ans;

void merge(int l, int mid, int r) {
    if (l == r) return;
    if (l + 1 == r) {
        if (a[l] > a[r]) {
            ans++;
            swap(a[l], a[r]);
        }
        return;
    }
    merge(l, (l + mid) >> 1, mid); // 归并排序，模拟两两元素比较交换
    merge(mid + 1, (mid + 1 + r) >> 1, r);
    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++)
        if (j > r || (i <= mid && a[i] <= a[j])) b[k] = a[i++];
        else {
            b[k] = a[j++];
            ans += mid - i + 1;
        }
    for (int k = l; k <= r; k++) a[k] = b[k];
}

void Ultra_QuickSort() {
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    ans = 0;
    merge(1, (1 + n) >> 1, n);
    cout << ans << endl;
}

int main() {
    while (cin >> n && n) Ultra_QuickSort();
    return 0;
}

/*
 * input:
5
9
1
0
5
4
 * output:
6

 *
 */