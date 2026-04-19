# 我的青春算竞物语果然有问题 XCPC 模板

## 完整目录
- [图论](#图论)
  - [spfa-wzy](#spfa-wzy)
- [数据结构](#数据结构)
  - [ST表-wzy](#ST表-wzy)
  - [线段树-wzy](#线段树-wzy)

---

# 图论

## spfa-wzy
```cpp
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
```

---


# 数据结构

## ST表-wzy
```cpp
#include<iostream>
#include<cstdio>
#define MAXN 100010
using namespace std;
int n,m;
int a[MAXN];
int f[MAXN][30];
int lg[MAXN];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		f[i][0]=a[i];
	}
	for(int i=2;i<=n;i++)
		lg[i]=lg[i>>1]+1;
	for(int j=1;j<=lg[n];j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
	for(int i=1;i<=m;i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		int len=lg[r-l+1];
		printf("%d\n",max(f[l][len],f[r-(1<<len)+1][len]));
	}
	return 0;
}
```

---

## 线段树-wzy
```cpp
#include<iostream>
#include<cstdio>
#define LL long long
#define MAXN 100010
using namespace std;
struct sgt
{
	LL val;
	LL tag;
}
t[MAXN<<2];
LL n,m;
LL op,x,y,k;
LL a[MAXN];
void push_up(LL p)
{
	t[p].val=t[p<<1].val+t[p<<1|1].val;
}
void build(LL p,LL l,LL r)
{
	if(l==r)
	{
		t[p].val=a[l];
		return;
	}
	LL mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	push_up(p);
}
void push_tag(LL p,LL l,LL r,LL k)
{
	t[p].tag+=k;
	t[p].val+=k*(r-l+1);
}
void push_down(LL p,LL l,LL r)
{
	if(t[p].tag==0)
		return;
	LL mid=(l+r)>>1;
	push_tag(p<<1,l,mid,t[p].tag);
	push_tag(p<<1|1,mid+1,r,t[p].tag);
	t[p].tag=0;
}
void update(LL p,LL l,LL r,LL L,LL R,LL k)
{
	if(L<=l&&R>=r)
	{
		push_tag(p,l,r,k);
		return;
	}
	push_down(p,l,r);
	LL mid=(l+r)>>1;
	if(L<=mid)
		update(p<<1,l,mid,L,R,k);
	if(R>=mid+1)
		update(p<<1|1,mid+1,r,L,R,k);
	push_up(p);
}
LL query(LL p,LL l,LL r,LL L,LL R)
{
	if(L<=l&&R>=r)
		return t[p].val;
	push_down(p,l,r);
	LL mid=(l+r)>>1;
	LL res=0;
	if(L<=mid)
		res+=query(p<<1,l,mid,L,R);
	if(R>=mid+1)
		res+=query(p<<1|1,mid+1,r,L,R);
	return res;
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(LL i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	build(1,1,n);
	for(LL i=1;i<=m;i++)
	{
		scanf("%lld%lld%lld",&op,&x,&y);
		if(op==1)
		{
			scanf("%lld",&k);
			update(1,1,n,x,y,k);
		}
		else
			printf("%lld\n",query(1,1,n,x,y));
	}
	return 0;
}
```

---
