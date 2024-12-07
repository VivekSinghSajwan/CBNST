#include <stdio.h>
#include <stdbool.h>

int n, m;

bool applySafetyAlgo(int max[n][m], int allocated[n][m], int need[n][m], int available[m], int safeSequence[n]) 
{
    bool finish[n];  // Array to track whether a process has finished
    int work[m];  // Work array to simulate resource availability during the algorithm
    for(int i=0; i<m; i++)
        work[i] = available[i];
    for(int i=0; i<n; i++) 
        finish[i] = false;

    int k = 0;
    bool proceed = true;
    while(proceed) 
    {
        proceed = false;
        for(int i=0; i<n; i++) 
        {
            bool flag = true;
            if(finish[i] == false)
            {
                for(int j=0; j<m; j++) 
                {
                    if(need[i][j] > work[j]) 
                    {
                        flag = false;
                        break;
                    }
                }
                if(flag) 
                {
                    // Update work (release the resources)
                    for (int j = 0; j < m; j++)
                        work[j] += allocated[i][j];
                    finish[i] = true;
                    safeSequence[k++] = i;
                    proceed = true;
                }
            }
        }
    }

    for(int i=0; i<n; i++) 
    {
        if (!finish[i]) 
            return false;
    }
    return true;
}
int main() 
{
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);
    int max[n][m], allocated[n][m], need[n][m], available[m], total[m], safeSequence[n];
    printf("Enter maximum requirement for %d processes:\n", n);
    for(int i=0; i<n; i++) 
    {
        for(int j=0; j<m; j++) 
            scanf("%d", &max[i][j]);
    }
    printf("Enter allocated resources for %d processes:\n",n);
    for(int i=0; i<n; i++) 
    {
        for (int j=0; j<m; j++) 
        {
            scanf("%d",&allocated[i][j]);
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }
    printf("Enter total resources: ");
    for(int i=0; i<m; i++) 
        scanf("%d", &total[i]);

    //calculating sum of allocated resource
    int allocatedSum[m];
    for(int i=0; i<m; i++) 
    {
        allocatedSum[i] = 0;
        for (int j=0; j<n; j++) 
            allocatedSum[i] += allocated[j][i];
        available[i] = total[i]-allocatedSum[i];
    }
    //-----
    if(applySafetyAlgo(max, allocated, need, available, safeSequence)) 
    {
        printf("\nSystem is in a SAFE state.\n");
        printf("Safe sequence is: ");
        for(int i=0; i<n; i++)
            printf("P[%d] ", safeSequence[i]);
    } 
    else 
        printf("\nSystem is NOT in a safe state.\n");
    return 0;
}
