// Description
//内存是计算机重要的资源之一，程序运行的过程中必须对内存进行分配。
//经典的内存分配过程是这样进行的：
//1. 内存以内存单元为基本单位，每个内存单元用一个固定的整数作为标识，称为地址。地址从0开始连续排列，地址相邻的内存单元被认为是逻辑上连续的。我们把
//从地址i开始的s个连续的内存单元称为首地址为i长度为s的地址片。
//2. 运行过程中有若干进程需要占用内存，对于每个进程有一个申请时刻T，需要内存单元数M及运行时间P。在运行时间P内（即T时刻开始，T+P时刻结束），这M
//个被占用的内存单元不能再被其他进程使用。
//3、假设在T时刻有一个进程申请M个单元，且运行时间为P，则：
//1. 若T时刻内存中存在长度为M的空闲地址片，则系统将这M个空闲单元分配给该进程。若存在多个长度为M个空闲地址片，则系统将首地址最小的那个空闲地址片
//分配给该进程。
//2. 如果T时刻不存在长度为M的空闲地址片，则该进程被放入一个等待队列。对于处于等待队列队头的进程，只要在任一时刻，存在长度为M的空闲地址片，系统马
//上将该进程取出队列，并为它分配内存单元。注意，在进行内存分配处理过程中，处于等待队列队头的进程的处理优先级最高，队列中的其它进程不能先于队头进
//程被处理。
//现在给出一系列描述进程的数据，请编写一程序模拟系统分配内存的过程。
//Input
//第一行是一个数N，表示总内存单元数（即地址范围从0到N-1）。从第二行开始每行描述一个进程的三个整数T、M、P（M <= N）。最后一行用三个0表示结束。
//数据已按T从小到大排序。
//输入文件最多10000行，且所有数据都小于109。
//输入文件中同一行相邻两项之间用一个或多个空格隔开。
//Language: Default 
//Output
//包括2行。
//第一行是全部进程都运行完毕的时刻。
//第二行是被放入过等待队列的进程总数。
//Sample Input
//10
//1 3 10
//2 4 3
//3 4 4
//4 1 4
//5 3 4
//0 0 0
//Sample Output
//12
//2

#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
int n, w = INF, cnt = 0;
struct P {
	int t, m, p, s;
	bool operator < (const P x) const {
		return s < x.s;
	}
} x;
vector<P> p;
queue<P> q;

bool work_in(int t) {
	if (p.empty() || p[0].s >= x.m) {
		x.s = 0;
		x.t = t;
		p.push_back(x);
		sort(p.begin(), p.end());
		return 1;
	}
	for (unsigned int i = 1; i < p.size(); i++)
		if (p[i].s - (p[i-1].s + p[i-1].m) >= x.m) {
			x.s = p[i-1].s + p[i-1].m;
			x.t = t;
			p.push_back(x);
			sort(p.begin(), p.end());
			return 1;
		}
	int sz = p.size();
	if (n - (p[sz-1].s + p[sz-1].m) >= x.m) {
		x.s = p[sz-1].s + p[sz-1].m;
		x.t = t;
		p.push_back(x);
		sort(p.begin(), p.end());
		return 1;
	}
	return 0;
}

void work_out() {
	int nw = INF;
	for (unsigned int i = 0; i < p.size(); i++)
		if (p[i].t + p[i].p == w) p.erase(p.begin() + i--);
		else nw = min(nw, p[i].t + p[i].p);
	while (q.size()) {
		x = q.front();
		if (work_in(w)) {
			nw = min(nw, q.front().t + q.front().p);
			q.pop();
			cnt++;
		} else break;
	}
	w = nw;
}

void work(int t, int m, int p) {
	while (t >= w) work_out();
	x.t = t;
	x.m = m;
	x.p = p;
	if (work_in(t)) w = min(w, t + p);
	else q.push(x);
}

int main() {
	ios::sync_with_stdio(0);
	cin >> n;
	int t0, m0, p0;
	while (cin >> t0 >> m0 >> p0 && !(!t0 && !m0 && !p0))
		work(t0, m0, p0);
	while (q.size())
		work_out();
	int ans = w;
	for (unsigned int i = 0; i < p.size(); i++)
		ans = max(ans, p[i].t + p[i].p);
	cout << ans << endl << cnt << endl;
	return 0;
}
