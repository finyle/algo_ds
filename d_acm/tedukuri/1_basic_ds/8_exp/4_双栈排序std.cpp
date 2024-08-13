//Tom最近在研究一个有趣的排序问题。如图所示，通过2个栈S1和S2，Tom希望借助以下4种操作实现将输入序列升序排序。
//
//[IMG]http://www.tyvj.cn:8080/ProblemImg/1121-1.gif[/IMG]
//
//操作a
//        如果输入序列不为空，将第一个元素压入栈S1
//        操作b
//如果栈S1不为空，将S1栈顶元素弹出至输出序列
//        操作c
//如果输入序列不为空，将第一个元素压入栈S2
//        操作d
//如果栈S2不为空，将S2栈顶元素弹出至输出序列
//
//[IMG]http://www.tyvj.cn:8080/ProblemImg/1121-2.gif[/IMG]
//
//如果一个1~n的排列P可以通过一系列操作使得输出序列为1, 2,…,(n-1), n，Tom就称P是一个"可双栈排序排列"。例如(1, 3, 2, 4)就是一个"可双栈排序序列"，而(2, 3, 4, 1)不是。下图描述了一个将(1, 3, 2, 4)排序的操作序列：<a, c, c, b, a, d, d, b>
//
//
//        当然，这样的操作序列有可能有几个，对于上例(1, 3, 2, 4)，<a, c, c, b, a, d, d, b>是另外一个可行的操作序列。Tom希望知道其中字典序最小的操作序列是什么。
//

// 100%的数据满足： n<=10^5

//1
//3
//2 3 1

// a c a b b d

#include <iostream>
#include <algorithm>
#include <stack>
#include <cstring>

using namespace std;

const int N = 1010;

int n;
int a[N], f[N];
int color[N];
bool g[N][N];

bool dfs(int u, int c)
{
	color[u] = c;
	for (int i = 1; i <= n; i++)
		if (g[u][i])
		{
			if (color[i] == c) return false;
			if (color[i] == -1 && !dfs(i, !c)) return false;
		}

	return true;
}

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i];
		f[n + 1] = n + 1;
		memset(g, false, sizeof g);
		for (int i = n; i; i--) f[i] = min(f[i + 1], a[i]);

		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++)
				if (a[i] < a[j] && f[j + 1] < a[i])
					g[i][j] = g[j][i] = true;

		memset(color, -1, sizeof color);

		bool flag = true;
		for (int i = 1; i <= n; i++)
			if (color[i] == -1 && !dfs(i, 0))
			{
				flag = false;
				break;
			}

		if (!flag)
		{
			cout << 0 << endl;
			continue;
		}

		stack<int> stk1, stk2;

		int now = 1;
		for (int i = 1; i <= n; i++)
		{
			if (color[i] == 0)
			{
				// 要入第一个栈了，第一个栈该出的现在必须要出掉
				// 为了使字典序最小，第二个栈可以再等等
				while (stk1.size() && stk1.top() == now)
				{
					stk1.pop();
					cout << "b ";
					now++;
				}
				stk1.push(a[i]);
				cout << "a ";
			}
			else
			{
				// 要入第二个栈了，第二个栈该出的现在必须要出掉
				// 然而由于b比c字典序小，第一个栈可以出的也应该出掉
				while (true)
					if (stk1.size() && stk1.top() == now)
					{
						stk1.pop();
						cout << "b ";
						now++;
					}
					else if (stk2.size() && stk2.top() == now)
					{
						stk2.pop();
						cout << "d ";
						now++;
					}
					else break;
                stk2.push(a[i]);
                cout << "c ";
			}

		}
		// 最后出栈剩余的
		while (true)
			if (stk1.size() && stk1.top() == now)
			{
				stk1.pop();
				cout << "b ";
				now++;
			}
			else if (stk2.size() && stk2.top() == now)
			{
				stk2.pop();
				cout << "d ";
				now++;
			}
			else break;
		cout << endl;
	}
	return 0;
}