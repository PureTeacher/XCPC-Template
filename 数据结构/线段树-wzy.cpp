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