#include<stdio.h>

void CT(int processes[], int n, int bt[], int at[], int ct[]) {
    ct[0] = at[0] + bt[0]; 
    for (int i = 1; i < n; i++) {
        ct[i] = (ct[i - 1] > at[i] ? ct[i - 1] : at[i]) + bt[i];
    }
}

void TAT(int processes[], int n, int bt[], int at[], int ct[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];  
    }
}

void WT(int processes[], int n, int bt[], int at[], int tat[], int wt[]) {
    for (int i = 0; i < n; i++) {
        wt[i] = tat[i] - bt[i];  
    }
}

void AVG(int processes[], int n, int bt[], int at[]) {
    int wt[n], tat[n], ct[n];
    CT(processes, n, bt, at, ct);
    TAT(processes, n, bt, at, ct, tat);
    WT(processes, n, bt, at, tat, wt);

    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\navg bt= %.2f", (float)total_wt / n);
    printf("\navg tat = %.2f", (float)total_tat / n);
}

int main() {
    int n;

    printf("no. of processes: ");
    scanf("%d", &n);

    int processes[n], bt[n], at[n];

    printf("enter bt and tat: \n");
    for (int i = 0; i < n; i++) {
        printf("bt %d: ", i + 1);
        scanf("%d", &bt[i]);
        printf("tat %d: ", i + 1);
        scanf("%d", &at[i]);
        processes[i] = i + 1;  
    }

    AVG(processes, n, bt, at);

    return 0;
}
