/*
 * 合并果子(Huffman树：构造包含n个叶子节点的k叉树，其中第i个叶子节点带有权值Wi，最小化sum(wi*li),li表示第i个叶子节点到根节点的距离： 构造一个包含n个叶子节点的k叉树，其中第i个叶子节点带有权值wi，最小化sum(wi * li) li表示第i个叶子节点到根节点的距离：k叉huffman树(哈夫曼树)

 */
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
priority_queue<int> q;
int n,a[100010],ans;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        q.push(-a[i]);
    }
    for(int i=1;i<n;i++)
    {
        int x=-q.top(); q.pop();
        int y=-q.top(); q.pop();
        ans+=x+y;
        q.push(-x-y);
    }
    cout<<ans<<endl;
}