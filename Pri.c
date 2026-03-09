#include <stdio.h>

int main()
{
    int choice, n;
    int at[10], bt[10], pr[10], rt[10];
    int ct[10], tat[10], wt[10];
    int done[10] = {0};

    int time = 0, completed = 0, i;
    float avg_tat = 0, avg_wt = 0;

    printf("Select Priority Scheduling Mode\n");
    printf("1. Preemptive\n");
    printf("2. Non-Preemptive\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter Arrival Time Burst Time Priority\n");
    printf("(Lower number = Higher priority)\n\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d: ", i+1);
        scanf("%d %d %d", &at[i], &bt[i], &pr[i]);
        rt[i] = bt[i]; // remaining time for preemptive
    }

    if(choice == 2)   // Non-Preemptive
    {
        while(completed < n)
        {
            int idx = -1;
            int highest = 9999;

            for(i = 0; i < n; i++)
            {
                if(at[i] <= time && done[i] == 0 && pr[i] < highest)
                {
                    highest = pr[i];
                    idx = i;
                }
            }

            if(idx != -1)
            {
                time += bt[idx];
                ct[idx] = time;

                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];

                done[idx] = 1;
                completed++;
            }
            else
                time++;
        }
    }

    else if(choice == 1)   // Preemptive
    {
        while(completed < n)
        {
            int idx = -1;
            int highest = 9999;

            for(i = 0; i < n; i++)
            {
                if(at[i] <= time && rt[i] > 0 && pr[i] < highest)
                {
                    highest = pr[i];
                    idx = i;
                }
            }

            if(idx != -1)
            {
                rt[idx]--;
                time++;

                if(rt[idx] == 0)
                {
                    ct[idx] = time;
                    tat[idx] = ct[idx] - at[idx];
                    wt[idx] = tat[idx] - bt[idx];
                    completed++;
                }
            }
            else
                time++;
        }
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("\nAverage Turnaround Time = %.2f", avg_tat);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt);

    return 0;
}
