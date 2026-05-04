#include <stdio.h>

int main() {
    int n, tq, i, time = 0, remain, flag = 0;
    int at[10], bt[10], rt[10], wt[10], tat[10], ct[10];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for P%d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    remain = n;

    for(i = 0; remain != 0; ) {
        if(rt[i] <= tq && rt[i] > 0) {
            time += rt[i];
            rt[i] = 0;
            flag = 1;
        }
        else if(rt[i] > 0) {
            rt[i] -= tq;
            time += tq;
        }

        if(rt[i] == 0 && flag == 1) {
            remain--;
            ct[i] = time;
            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];

            avg_wt += wt[i];
            avg_tat += tat[i];

            flag = 0;
        }

        if(i == n-1)
            i = 0;
        else
            i++;
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat/n);

    return 0;
}
