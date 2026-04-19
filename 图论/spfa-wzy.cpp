#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define MAXN 10010
#define MAXM 500010
using namespace std;
struct Edge
{
	int to;
	int dis;
	int nxt;
}
edge[MAXM];
int head[MAXN],siz;
void add(int from,int to,int dis)
{
	edge[++siz].nxt=head[from];
	edge[siz].to=to;
	edge[siz].dis=dis;
	head[from]=siz;
}
void init()
{
	memset(head,-1,sizeof(head));
	memset(edge,-1,sizeof(edge));
}
int n,m,s;
int u,v,w;
int dis[MAXN];
bool vis[MAXN];
void spfa(int s)
{
	queue<int> q;
	for(int i=1;i<=n;i++)
		dis[i]=(1ll<<31)-1ll;
	dis[s]=0;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=head[u];~i;i=edge[i].nxt)
		{
			int v=edge[i].to;
			int w=edge[i].dis;
			if(dis[u]+w<dis[v])
			{
				dis[v]=dis[u]+w;
				if(!vis[v])
				{
					q.push(v);
					vis[v]=1;
				}
			}
		}
	}
}
int main()
{
	init();
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
	}
	spfa(s);
	for(int i=1;i<=n;i++)
		printf("%d ",dis[i]);
	return 0;
}