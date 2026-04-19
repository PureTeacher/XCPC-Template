struct tree
{
	int vis;
	int tag;
}
t[MAXN*4];
int n,m;
int op,x,y,k;
int a[MAXN];
void push_up(int p)
{
	t[p].vis=t[p<<1].vis+t[p<<1|1].vis;
}
void build(int p,int l,int r)
{
	t[p].tag=0;
	if(l==r)
	{
		t[p].vis=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	push_up(p);
}
void push_tag(int p,int l,int r,int k)
{
	t[p].tag+=k;
	t[p].vis+=k*(r-l+1);
}
void push_down(int p,int l,int r)
{
	if(t[p].tag==0)
		return;
	int mid=(l+r)>>1;
	push_tag(p<<1,l,mid,t[p].tag);
	push_tag(p<<1|1,mid+1,r,t[p].tag);
	t[p].tag=0;
}
void update(int p,int l,int r,int L,int R,int k)
{
	if(L<=l&&R>=r)
	{
		push_tag(p,l,r,k);
		return;
	}
	push_down(p,l,r);
	int mid=(l+r)>>1;
	if(L<=mid)
		update(p<<1,l,mid,L,R,k);
	if(R>=mid+1)
		update(p<<1|1,mid+1,r,L,R,k);
	push_up(p);
}
int query(int p,int l,int r,int L,int R)
{
	if(L<=l&&R>=r)
		return t[p].vis;
	push_down(p,l,r);
	int mid=(l+r)>>1;
	int res=0;
	if(L<=mid)
		res+=query(p<<1,l,mid,L,R);
	if(R>=mid+1)
		res+=query(p<<1|1,mid+1,r,L,R);
	return res;
}