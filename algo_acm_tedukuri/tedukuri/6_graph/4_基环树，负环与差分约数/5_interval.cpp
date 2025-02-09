
/*
 *
 */

#include<bits/stdc++.h>
using namespace std;
const int MAX_N = 50005;
int head[MAX_N], ver[3 * MAX_N], edge[3 * MAX_N], nxt[3 * MAX_N], tot;
int n, d[MAX_N], cnt[MAX_N];
bool v[MAX_N];
queue<int> q;

void add(int x, int y, int z) {
    tot++;
    ver[tot] = y;
    edge[tot] = z;
    nxt[tot] = head[x];
    head[x] = tot;
}

inline int num(int x) {
    return x == -1 ? 50001 : x;
}

bool spfa() {
    memset(d, 0xcc, sizeof(d));
    d[num(-1)] = 0;
    q.push(num(-1)); v[num(-1)] = true;
    while (!q.empty()) {
        int x = q.front();
        q.pop(); v[x] = false;
        for (int i = head[x]; i; i = nxt[i]) {
            int y = ver[i], z = edge[i];
            if (d[y] < d[x] + z) {
                d[y] = d[x] + z;
                cnt[y] = cnt[x] + 1;
                if (cnt[y] >= 50002) return true;
                if (!v[y]) { q.push(y); v[y] = true; }
            }
        }
    }
    return false;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(num(x - 1), num(y), z);
    }
    for (int i = 0; i <= 50000; i++) {
        add(num(i - 1), num(i), 0);
        add(num(i), num(i - 1), -1);
    }
    spfa();
    cout << d[50000] << endl;
}

/*
 * input:
248 245
127 241 56
29 48 12
84 242 139
30 42 10
174 248 75
9 20 12
41 93 36
16 44 24
22 93 52
196 196 1
89 209 83
17 21 2
151 163 10
10 102 83
121 122 1
45 174 51
46 69 6
103 192 9
2 28 22
112 200 65
1 4 0
149 177 21
175 221 46
22 83 58
22 41 8
31 44 9
78 128 37
55 67 0
53 59 4
46 128 27
151 247 48
11 168 21
17 45 15
107 148 38
49 65 7
98 114 14
6 103 52
4 4 0
9 21 11
24 36 0
53 77 25
45 229 27
6 31 26
164 209 29
1 45 11
167 209 38
104 198 51
4 22 17
87 127 7
62 183 54
103 163 35
77 144 64
14 121 7
18 38 21
44 77 8
1 2 0
114 165 19
20 70 11
62 200 46
49 114 50
7 34 14
28 39 8
108 113 2
8 25 9
17 23 7
20 28 2
55 155 35
30 58 29
4 19 9
14 20 4
18 54 2
23 24 1
122 164 31
38 42 5
7 100 51
71 235 165
213 220 5
48 89 10
31 106 59
52 131 75
85 118 6
77 147 29
66 212 20
139 244 69
10 32 14
19 154 43
139 244 34
38 41 0
28 63 33
82 82 0
3 233 202
75 82 2
169 183 14
60 113 10
98 142 9
59 163 67
57 91 26
15 181 15
124 238 72
57 198 75
122 143 13
13 59 5
13 198 46
34 88 17
190 206 6
67 114 33
10 37 25
65 198 68
3 85 50
23 38 13
34 81 9
63 123 13
112 205 80
42 53 5
11 64 42
70 171 52
166 219 37
160 185 3
99 174 55
92 148 38
18 69 22
185 188 3
114 124 0
4 4 1
83 99 16
4 4 1
77 193 16
26 37 1
86 93 3
130 201 22
95 135 8
122 145 2
3 44 28
44 111 29
14 95 9
86 203 46
33 72 3
1 94 91
16 49 21
30 107 25
31 49 5
221 238 12
135 139 3
120 174 1
129 179 22
26 92 31
1 214 42
166 166 0
109 196 56
132 171 23
57 88 27
54 152 46
162 177 7
31 66 36
70 128 22
40 45 5
169 248 54
75 107 22
117 187 41
102 202 11
201 207 5
2 3 2
117 160 21
41 81 37
62 62 1
67 72 1
56 100 31
65 197 17
79 128 48
91 205 109
198 208 3
61 221 32
3 3 1
134 143 10
29 147 101
60 93 20
59 197 78
136 214 4
161 212 8
22 198 166
130 205 61
4 44 33
85 96 1
51 55 5
14 89 27
95 183 14
152 219 1
34 37 2
87 115 22
6 230 179
151 213 27
22 128 69
150 171 20
61 72 5
27 54 14
129 168 25
182 225 39
142 226 26
21 174 63
113 232 82
42 145 17
14 59 3
189 245 38
10 124 34
172 181 6
115 198 45
3 120 46
176 235 53
3 4 2
87 161 58
5 14 5
213 216 0
21 39 7
32 34 3
24 34 8
7 59 32
178 241 37
53 111 1
1 7 3
7 225 153
22 213 76
6 190 9
19 44 17
97 116 14
217 225 4
87 186 53
48 64 4
94 114 3
153 220 61
44 85 29
46 79 25
13 29 0
13 15 3
45 80 3
87 161 40
113 187 57
47 180 15
17 131 59
184 247 40
28 239 199
22 102 58
23 53 10
3 12 7
116 117 2
90 97 4

 * output:
246
 */