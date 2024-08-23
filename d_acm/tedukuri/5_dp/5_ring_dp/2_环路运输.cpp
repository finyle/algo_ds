/*
 * 环路运输： 环形公路，n座仓库，仓库存量ai，两座仓库送货成本ai+aj+dist(i,j),求最大送货成本的两座仓库

 */

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[2000010], q[2000010], n, ans;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        a[n + i] = a[i];
    }
    int l = 1, r = 1;
    q[1] = 1;
    for (int i = 2; i <= 2 * n; i++) {
        while (l <= r && q[l] < i - n / 2) l++;
        ans = max(ans, a[i] + a[q[l]] + i - q[l]);
        while (l < r && a[i] - i >= a[q[r]] - q[r]) r--;
        q[++r] = i;
    }
    cout << ans << endl;
}

/*
 * input:
100
291 13 197 321 146 189 339 251 169 1 225 57 36 350 106 389 329 189 149 283 101 202 282 129 79 77 81 338 177 100 253 395 107 216 94 213 270 70 248 296 193 199 1 267 285 371 169 115 301 56 311 350 281 331 190 225 317 112 41 71 26 327 45 148 363 16 65 351 225 234 206 341 1 333 154 226 398 389 15 81 61 308 287 51 29 101 319 345 217 129 251 99 310 289 41 41 321 259 241 191
 * output:
838

 */