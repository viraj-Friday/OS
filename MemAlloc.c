#include<stdio.h>

int main()
{
    int b[10],p[10],a[10],m,n,i,j,choice;

    printf("1.First Fit\n2.Best Fit\n3.Worst Fit\n");
    printf("Enter choice: ");
    scanf("%d",&choice);

    printf("Enter number of blocks: ");
    scanf("%d",&m);

    printf("Enter block sizes:\n");
    for(i=0;i<m;i++)
        scanf("%d",&b[i]);

    printf("Enter number of processes: ");
    scanf("%d",&n);

    printf("Enter process sizes:\n");
    for(i=0;i<n;i++)
        scanf("%d",&p[i]);

    for(i=0;i<n;i++)
        a[i]=-1;

    for(i=0;i<n;i++)
    {
        int index=-1;

        for(j=0;j<m;j++)
        {
            if(b[j]>=p[i])
            {
                if(choice==1)
                {
                    index=j;
                    break;
                }

                if(choice==2)
                {
                    if(index==-1 || b[j]<b[index])
                        index=j;
                }

                if(choice==3)
                {
                    if(index==-1 || b[j]>b[index])
                        index=j;
                }
            }
        }

        if(index!=-1)
        {
            a[i]=index;
            b[index]-=p[i];
        }
    }

    printf("Process\tBlock\n");

    for(i=0;i<n;i++)
    {
        printf("%d\t",i+1);

        if(a[i]!=-1)
            printf("%d\n",a[i]+1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}

