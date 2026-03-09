#include <stdio.h>

int main() {
    int n, choice;
    int at[10], bt[10], rt[10], ct[10], tat[10], wt[10];
    int completed = 0, time = 0;
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input Arrival Time and Burst Time
    for(int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i]; // remaining time for preemptive
    }

    printf("\n1. Non-Preemptive SJF");
    printf("\n2. Preemptive SJF (SRTF)");
    printf("\nEnter choice: ");
    scanf("%d", &choice);

    if(choice == 1) // Non-Preemptive SJF
    {
        int done[10] = {0};

        while(completed < n) {
            int min = 9999, idx = -1;

            for(int i = 0; i < n; i++) {
                if(at[i] <= time && done[i] == 0 && bt[i] < min) {
                    min = bt[i];
                    idx = i;
                }
            }

            if(idx != -1) {
                time += bt[idx];
                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];

                done[idx] = 1;
                completed++;
            }
            else {
                time++;
            }
        }
    }
    else if(choice == 2) // Preemptive SJF (SRTF)
    {
        while(completed < n) {
            int min = 9999, idx = -1;

            for(int i = 0; i < n; i++) {
                if(at[i] <= time && rt[i] > 0 && rt[i] < min) {
                    min = rt[i];
                    idx = i;
                }
            }

            if(idx != -1) {
                rt[idx]--;
                time++;

                if(rt[idx] == 0) {
                    completed++;
                    ct[idx] = time;
                    tat[idx] = ct[idx] - at[idx];
                    wt[idx] = tat[idx] - bt[idx];
                }
            }
            else {
                time++;
            }
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    avg_tat = avg_tat / n;
    avg_wt = avg_wt / n;

    printf("\nAverage Turnaround Time = %.2f", avg_tat);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt);

    return 0;
}
