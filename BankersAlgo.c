#include<stdio.h>
#include<stdbool.h>

int n,m;
bool bankersAlgo(int need[n][m], int allocated[n][m], int available[m], int safeSeq[n])
{
    bool finish[n];
    for(int i=0; i<n; i++)
        finish[i] = false;
    int k=0;
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
                    if(need[i][j] > available[j])
                    {
                        flag = false;
                        break;
                    }
                }
                if(flag == true)
                {
                    for(int j=0; j<m; j++)
                        available[j] += allocated[i][j];
                    proceed = true;
                    safeSeq[k++] = i;
                    finish[i] = true;
                }
            }
        }
    }
    for(int i=0; i<n; i++)
    {
        if(finish[i] == false)
            return false;
    }
    return true;
}
int main()
{
    printf("Enter no. of processes: ");
    scanf("%d",&n);
    printf("Enter no. of resources: ");
    scanf("%d",&m);
    int max[n][m],allocated[n][m],need[n][m],total[m],available[m],safeSeq[n];
    printf("Enter max. requirement for each process: ");
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
            scanf("%d",&max[i][j]);
    }
    printf("Enter allocated resources for each process: ");
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            scanf("%d",&allocated[i][j]);
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }
    printf("Enter total resources: ");
    for(int i=0; i<m; i++) 
        scanf("%d", &total[i]);

    //calculating available
    for(int i=0; i<m; i++)
    {
        int sum = 0;
        for(int j=0; j<n; j++)
            sum += allocated[j][i];
        available[i] = total[i]-sum;
    }
    if(bankersAlgo(need,allocated,available,safeSeq))
    {
        printf("No Deadlock\n");
        for(int i=0; i<n; i++)
            printf("P[%d] ",safeSeq[i]);
    }else
        printf("Deadlock Detected");
    return 0;
}
