#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id;  
    int bt;  
    int at;  
    int ct;  
    int tat;
    int wt;  
};

int compareArrivalTime(const void *a, const void *b) {
    return ((struct Process*)a)->at - ((struct Process*)b)->at;
}

void calculateTimes(struct Process processes[], int n) {
    int time = 0;
    int completed = 0;

    while (completed < n) {
        int shortest = -1;
        int min_burst = 1000000;

        for (int i = 0; i < n; i++) {
            if (processes[i].at <= time && processes[i].ct == 0) {
                if (processes[i].bt < min_burst) {
                    min_burst = processes[i].bt;
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            time++;
        } else {
            processes[shortest].ct = time + processes[shortest].bt;
            processes[shortest].tat = processes[shortest].ct - processes[shortest].at;
            processes[shortest].wt = processes[shortest].tat - processes[shortest].bt;

            time = processes[shortest].ct;
            completed++;
        }
    }
}

void calculateAvg(struct Process processes[], int n) {
    int total_wt = 0, total_tat = 0;
   
    for (int i = 0; i < n; i++) {
        total_wt += processes[i].wt;
        total_tat += processes[i].tat;
    }

    printf("\navg wt = %.2f", (float)total_wt / n);
    printf("\navg tat = %.2f", (float)total_tat / n);
}

int main() {
    int n;

    printf("no. of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("enter bt and at: \n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("bt %d: ", i + 1);
        scanf("%d", &processes[i].bt);
        printf("at %d: ", i + 1);
        scanf("%d", &processes[i].at);
        processes[i].ct = 0;
    }

    qsort(processes, n, sizeof(struct Process), compareArrivalTime);

    calculateTimes(processes, n);

    calculateAvg(processes, n);

    return 0;
}
