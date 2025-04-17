#include <stdio.h>
#include <limits.h>

struct Process {
    int id;
    int bt;
    int at;
    int rt;
    int ct;
    int tat;
    int wt;
};

void calculateTimes(struct Process processes[], int n) {
    int completed = 0, time = 0, shortest = -1;
    int min_burst = INT_MAX;

    while (completed < n) {
        shortest = -1;
        min_burst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].at <= time && processes[i].rt > 0) {
                if (processes[i].rt < min_burst) {
                    min_burst = processes[i].rt;
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        processes[shortest].rt--;
        time++;

        if (processes[shortest].rt == 0) {
            completed++;
            processes[shortest].ct = time;
            processes[shortest].tat = processes[shortest].ct - processes[shortest].at;
            processes[shortest].wt = processes[shortest].tat - processes[shortest].bt;
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
    
    printf("Enter BT and AT: \n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("BT %d: ", i + 1);
        scanf("%d", &processes[i].bt);
        printf("AT %d: ", i + 1);
        scanf("%d", &processes[i].at);
        processes[i].rt = processes[i].bt;
    }
    
    calculateTimes(processes, n);
    
    calculateAvg(processes, n);
    
    return 0;
}
