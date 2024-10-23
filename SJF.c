#include<stdio.h>
#include<stdbool.h>
#include<limits.h>

struct process_struct
{
  int pid;
  int at;
  int bt;
  int ct,wt,tat,rt,start_time;
}ps[100];

int findmax(int a, int b)
{
    return a>b?a:b;
}

int findmin(int a, int b)
{
    return a<b?a:b;
}

int main()
{
    
    int n;
    bool is_completed[100]={false},is_first_process=true;
    int current_time = 0;
    int completed = 0;;
    printf("Enter total number of processes: ");
    scanf("%d",&n);    
    int sum_tat=0,sum_wt=0,sum_rt=0,total_idle_time=0,length_cycle;
    int prev = 0;//stores the ct of the just last process
    float cpu_utilization;
    int max_completion_time,min_arrival_time;
    int gantt_chart[100];  // To store the order of process execution
    int gantt_index = 0;   // To track the number of processes executed in Gantt chart

    printf("\nEnter Processes Arrival Time: ");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&ps[i].at);
        ps[i].pid = i ;
    }
    
    printf("\nEnter Processes Burst Time: ");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&ps[i].bt);
    }
    
    while(completed!=n)
    {
        //find process with min. burst time in ready queue at current time
        int min_index = -1;
        int minimum = INT_MAX;
        for(int i = 0; i < n; i++) 
        {
            if(ps[i].at <= current_time && is_completed[i] == false) 
            {
                if(ps[i].bt < minimum) 
                {
                    minimum = ps[i].bt;
                    min_index = i;
                }
                if(ps[i].bt == minimum) //if processes have same burst time
                {
                    if(ps[i].at < ps[min_index].at) 
                    {
                        minimum= ps[i].bt;
                        min_index = i;
                    }
                }
            }
        }

        if(min_index == -1)
            current_time++;
        else
        {
            ps[min_index].start_time = current_time;
            ps[min_index].ct = ps[min_index].start_time + ps[min_index].bt;
            ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
            ps[min_index].wt = ps[min_index].tat - ps[min_index].bt;
            ps[min_index].rt = ps[min_index].wt;
            
            sum_tat +=ps[min_index].tat;
            sum_wt += ps[min_index].wt;
            sum_rt += ps[min_index].rt;
            total_idle_time += (is_first_process==true) ? 0 : (ps[min_index].start_time -  prev);
            
            completed++;
            is_completed[min_index]=true;
            current_time = ps[min_index].ct;
            prev= current_time; //for calculating idle time
            is_first_process = false;  
            gantt_chart[gantt_index++] = ps[min_index].pid;
        }
    }
    
    //Calculate Length of Process completion cycle
    max_completion_time = INT_MIN;
    min_arrival_time = INT_MAX;
    for(int i=0;i<n;i++)
    {
        max_completion_time = findmax(max_completion_time,ps[i].ct);
        min_arrival_time = findmin(min_arrival_time,ps[i].at);
    }
    length_cycle = max_completion_time - min_arrival_time;

    // Output the Gantt Chart
    printf("\nGantt Chart: ");
    for (int i = 0; i < gantt_index; i++) {
        printf("P%d ", gantt_chart[i]);
    }
    printf("\n");

    //Output
    printf("\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++)
     printf("%d\t\t%d\t%d\t\t%d\t%d\t%d\t%d\n",ps[i].pid,ps[i].at,ps[i].bt,ps[i].ct,ps[i].tat,ps[i].wt,ps[i].rt);

    printf("\n");    
    
    cpu_utilization = (float)(length_cycle - total_idle_time)/ length_cycle;

    printf("\nAvg. Turn Around time= %.2f ",(float)sum_tat/n);
    printf("\nAvg. Waiting Time= %.2f ",(float)sum_wt/n);
    printf("\nAvg. Response Time= %.2f ",(float)sum_rt/n);
    printf("\nThroughput= %.2f",n/(float)length_cycle);    
    printf("\nCPU Utilization(percent)= %.2f",cpu_utilization*100);
    return 0;
}
