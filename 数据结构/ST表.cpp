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