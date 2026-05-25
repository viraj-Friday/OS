#include<stdio.h>

void show(int f[],int m)
{
    int i;
    for(i=0;i<m;i++)
        f[i]==-1 ? printf("- ") : printf("%d ",f[i]);
    printf("\n");
}

int main()
{
    int p[20],f[10],n,m,i,j,k,fault,pos;

    printf("Frames: ");
    scanf("%d",&m);

    printf("Length: ");
    scanf("%d",&n);

    printf("Pages: ");
    for(i=0;i<n;i++) scanf("%d",&p[i]);

    int fifo[10];
    for(i=0;i<m;i++) fifo[i]=-1;

    printf("\nFIFO:\n");
    fault=pos=0;

    for(i=0;i<n;i++)
    {
        for(j=0;j<m && fifo[j]!=p[i];j++);

        if(j==m)
        {
            fifo[pos]=p[i];
            pos=(pos+1)%m;
            printf("PF %d: ",++fault);
            show(fifo,m);
        }
    }
    printf("Faults=%d\n",fault);


    int lru[10],t[10]={0},c=0,min;
    for(i=0;i<m;i++) lru[i]=-1;

    printf("\nLRU:\n");
    fault=0;

    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
            if(lru[j]==p[i]) t[j]=++c;

        for(j=0;j<m && lru[j]!=p[i];j++);

        if(j==m)
        {
            min=0;
            for(j=1;j<m;j++)
                if(t[j]<t[min]) min=j;

            lru[min]=p[i];
            t[min]=++c;

            printf("PF %d: ",++fault);
            show(lru,m);
        }
    }
    printf("Faults=%d\n",fault);


    int opt[10],next[10],far;
    for(i=0;i<m;i++) opt[i]=-1;

    printf("\nOptimal:\n");
    fault=0;

    for(i=0;i<n;i++)
    {
        for(j=0;j<m && opt[j]!=p[i];j++);

        if(j==m)
        {
            far=0;

            for(j=0;j<m;j++)
            {
                next[j]=999;

                for(k=i+1;k<n;k++)
                    if(opt[j]==p[k])
                    {
                        next[j]=k;
                        break;
                    }

                if(next[j]>next[far]) far=j;
            }

            opt[far]=p[i];

            printf("PF %d: ",++fault);
            show(opt,m);
        }
    }
    printf("Faults=%d",fault);

    return 0;
}
