#include <stdio.h>

struct Process {
    int id, bt, at, rt, ct, tat, wt;
};

void roundRobin(struct Process processes[], int n, int quantum) {
    int time = 0, completed = 0;
    while (completed < n) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (processes[i].rt > 0 && processes[i].at <= time) {
                done = 0;
                if (processes[i].rt > quantum) {
                    time += quantum;
                    processes[i].rt -= quantum;
                } else {
                    time += processes[i].rt;
                    processes[i].ct = time;
                    processes[i].tat = processes[i].ct - processes[i].at;
                    processes[i].wt = processes[i].tat - processes[i].bt;
                    processes[i].rt = 0;
                    completed++;
                }
            }
        }
        if (done) time++;
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
    int n, quantum;
    printf("No. of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("BT %d: ", i + 1);
        scanf("%d", &processes[i].bt);
        printf("AT %d: ", i + 1);
        scanf("%d", &processes[i].at);
        processes[i].rt = processes[i].bt;
    }

    printf("Time Quantum: ");
    scanf("%d", &quantum);

    roundRobin(processes, n, quantum);
    calculateAvg(processes, n);

    return 0;
}

