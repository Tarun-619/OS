#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id, bt, at, priority, ct, tat, wt;
};

int comparePriority(const void *a, const void *b) {
    struct Process *p1 = (struct Process *)a;
    struct Process *p2 = (struct Process *)b;
    if (p1->at == p2->at)
        return p1->priority - p2->priority;
    return p1->at - p2->at;
}

void calculateTimes(struct Process processes[], int n) {
    int time = 0, completed = 0;

    while (completed < n) {
        int highest = -1, highestPriority = 1000000;

        for (int i = 0; i < n; i++) {
            if (processes[i].at <= time && processes[i].ct == 0) {
                if (processes[i].priority < highestPriority) {
                    highestPriority = processes[i].priority;
                    highest = i;
                }
            }
        }

        if (highest == -1) {
            time++;
        } else {
            processes[highest].ct = time + processes[highest].bt;
            processes[highest].tat = processes[highest].ct - processes[highest].at;
            processes[highest].wt = processes[highest].tat - processes[highest].bt;

            time = processes[highest].ct;
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
    printf("\nAvg WT = %.2f", (float)total_wt / n);
    printf("\nAvg TAT = %.2f", (float)total_tat / n);
}

int main() {
    int n;
    printf("No. of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("BT %d: ", i + 1);
        scanf("%d", &processes[i].bt);
        printf("AT %d: ", i + 1);
        scanf("%d", &processes[i].at);
        printf("Priority %d: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].ct = 0;
    }

    qsort(processes, n, sizeof(struct Process), comparePriority);

    calculateTimes(processes, n);
    calculateAvg(processes, n);

    return 0;
}
