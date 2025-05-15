#include <stdio.h>
#include <stdbool.h>
int main() {
    int n, m;
    printf("enter num of processes and number of resources:\n");
    scanf("%d %d", &n, &m);
    int alloc[n][m], request[n][m], avail[m];
    printf("enter alloc matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
    printf("enter req matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("enter avail resource (%d values):\n", m);
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);
    int work[m];
    for (int i = 0; i < m; i++)
        work[i] = avail[i];
    bool finish[n];
    for (int i = 0; i < n; i++) {
        bool hasAllocation = false;
        for (int j = 0; j < m; j++) {
            if (alloc[i][j] != 0) {
                hasAllocation = true;
                break;
            }
        }
        finish[i] = hasAllocation ? false : true;
    }
    while (true) {
        bool progress = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canGrant = true;

                for (int j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        canGrant = false;
                        break;
                    }
                }

                if (canGrant) {
                    for (int j = 0; j < m; j++)
                        work[j] += alloc[i][j];
                    finish[i] = true;
                    progress = true;
                }
            }
        }

        if (!progress)
            break;
    }
    printf("\nDLD result:\n");
    bool deadlock = false;

    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            printf("process P%d is deadlocked\n", i);
            deadlock = true;
        } else {
            printf("process P%d is not deadlocked\n", i);
        }
    }
    if (!deadlock)
        printf("\nno deadlock detected in the system.\n");

    return 0;
}