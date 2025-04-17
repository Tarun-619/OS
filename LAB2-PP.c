#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id, bt, at, priority, ct, tat, wt, rt;
};

int compareArrival(const void *a, const void *b) {
    struct Process *p1 = (struct Process *)a;
    struct Process *p2 = (struct Process *)b;
    return p1->at - p2->at;
}

void calculateTimes(struct Process processes[], int n) {
    int time = 0, completed = 0, min_priority, shortest;
    for (int i = 0; i < n; i++) processes[i].rt = processes[i].bt;
    
    while (completed < n) {
        shortest = -1;
        min_priority = 1000000;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= time && processes[i].rt > 0 && processes[i].priority < min_priority) {
                min_priority = processes[i].priority;
                shortest = i;
            }
        }
        
        if (shortest == -1) {
            time++;
        } else {
            processes[shortest].rt--;
            time++;
            if (processes[shortest].rt == 0) {
                processes[shortest].ct = time;
                processes[shortest].tat = processes[shortest].ct - processes[shortest].at;
                processes[shortest].wt = processes[shortest].tat - processes[shortest].bt;
                completed++;
            }
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
    }

    qsort(processes, n, sizeof(struct Process), compareArrival);
    calculateTimes(processes, n);
    calculateAvg(processes, n);
    return 0;
}
