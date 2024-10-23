#include <stdio.h>
#include <stdbool.h>

int n, m;

// Apply safety algorithm to check if a safe sequence exists
bool applySafetyAlgo(int max[n][m], int allocated[n][m], int need[n][m], int available[m], int safeSequence[n]) 
{
    bool finish[n];  // Array to track whether a process has finished
    int work[m];  // Work array to simulate resource availability during the algorithm

    // Initialize work array as a copy of available resources
    for (int i = 0; i < m; i++)
        work[i] = available[i];

    // Initialize all processes as unfinished
    for (int i = 0; i < n; i++) 
        finish[i] = false;

    int k = 0;  // Index for the safe sequence
    bool proceed = true;

    // Main loop to find safe sequence
    while (proceed) 
    {
        proceed = false;
        for (int i = 0; i < n; i++) 
        {
            bool flag = true;
            if (!finish[i])  // Only check unfinished processes
            {
                // Check if the process can be executed (Need <= Available)
                for (int j = 0; j < m; j++) 
                {
                    if (need[i][j] > work[j]) 
                    {
                        flag = false;  // If need is greater, the process cannot proceed
                        break;
                    }
                }

                // If the process can proceed
                if (flag) 
                {
                    // Update work (release the resources)
                    for (int j = 0; j < m; j++)
                        work[j] += allocated[i][j];

                    finish[i] = true;  // Mark the process as finished
                    safeSequence[k++] = i;  // Add the process to the safe sequence
                    proceed = true;  // At least one process has been executed, so continue
                }
            }
        }
    }

    // Check if all processes have finished
    for (int i = 0; i < n; i++) 
    {
        if (!finish[i]) 
            return false;  // If any process is unfinished, the state is unsafe
    }

    return true;  // All processes finished, safe state
}

// Checks if the state is safe
bool isSafeState(int max[n][m], int allocated[n][m], int need[n][m], int available[m], int safeSequence[n]) 
{
    return applySafetyAlgo(max, allocated, need, available, safeSequence);
}

int main() 
{
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int max[n][m], allocated[n][m], need[n][m], available[m], safeSequence[n];

    printf("Enter maximum requirement for %d processes:\n", n);
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
            scanf("%d", &max[i][j]);
    }

    printf("Enter allocated resources for %d processes:\n", n);
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            scanf("%d", &allocated[i][j]);
            need[i][j] = max[i][j] - allocated[i][j];  // Need = Max - Allocated
        }
    }

    printf("Enter available resources: ");
    for (int i = 0; i < m; i++) 
        scanf("%d", &available[i]);

    // Check if the system is in a safe state
    if (isSafeState(max, allocated, need, available, safeSequence)) 
    {
        printf("\nSystem is in a SAFE state.\n");
        printf("Safe sequence is: ");
        for (int i = 0; i < n; i++)
            printf("P[%d] ", safeSequence[i]);
    } 
    else 
    {
        printf("\nSystem is NOT in a safe state.\n");
    }

    return 0;
}
