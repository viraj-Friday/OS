#include <stdio.h>

#define MAX 100

int main() {
    int n;

    int PID[MAX], AT[MAX], BT[MAX], TYPE[MAX];
    int CT[MAX], TAT[MAX], WT[MAX], Start[MAX];

    int systemQueue[MAX], userQueue[MAX];
    int sysCount = 0, userCount = 0;

    int time = 0;

    float totalTAT = 0, totalWT = 0;


    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter details in one line: PID AT BT TYPE(0=System,1=User)\n");

    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d %d", &PID[i], &AT[i], &BT[i], &TYPE[i]);
    }

    for (int i = 0; i < n; i++) {
        if (TYPE[i] == 0)
            systemQueue[sysCount++] = i;
        else
            userQueue[userCount++] = i;
    }

    for (int i = 0; i < sysCount - 1; i++) {
        for (int j = i + 1; j < sysCount; j++) {
            if (AT[systemQueue[i]] > AT[systemQueue[j]]) {
                int temp = systemQueue[i];
                systemQueue[i] = systemQueue[j];
                systemQueue[j] = temp;
            }
        }
    }

    for (int i = 0; i < userCount - 1; i++) {
        for (int j = i + 1; j < userCount; j++) {
            if (AT[userQueue[i]] > AT[userQueue[j]]) {
                int temp = userQueue[i];
                userQueue[i] = userQueue[j];
                userQueue[j] = temp;
            }
        }
    }

    for (int i = 0; i < sysCount; i++) {
        int p = systemQueue[i];

        if (time < AT[p])
            time = AT[p];

        Start[p] = time;
        time += BT[p];

        CT[p] = time;
        TAT[p] = CT[p] - AT[p];
        WT[p] = TAT[p] - BT[p];
    }

    for (int i = 0; i < userCount; i++) {
        int p = userQueue[i];

        if (time < AT[p])
            time = AT[p];

        Start[p] = time;
        time += BT[p];

        CT[p] = time;
        TAT[p] = CT[p] - AT[p];
        WT[p] = TAT[p] - BT[p];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (PID[i] > PID[j]) {
                int temp;

                temp = PID[i]; PID[i] = PID[j]; PID[j] = temp;
                temp = AT[i]; AT[i] = AT[j]; AT[j] = temp;
                temp = BT[i]; BT[i] = BT[j]; BT[j] = temp;
                temp = TYPE[i]; TYPE[i] = TYPE[j]; TYPE[j] = temp;
                temp = CT[i]; CT[i] = CT[j]; CT[j] = temp;
                temp = TAT[i]; TAT[i] = TAT[j]; TAT[j] = temp;
                temp = WT[i]; WT[i] = WT[j]; WT[j] = temp;
            }
        }
    }

    printf("\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               PID[i], AT[i], BT[i], TYPE[i],
               CT[i], TAT[i], WT[i]);

        totalTAT += TAT[i];
        totalWT += WT[i];
    }

    printf("\nAverage Turnaround Time = %.2f", totalTAT / n);
    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);

    return 0;
}
