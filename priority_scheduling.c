#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct process_struct{
    int id, priority, arrival, burst, rem_burst, start, completion, waiting, tat, responce;
};
typedef struct process_struct process;

void printProcesses(int n, process ps[]){
    printf("\nID\tPR\tAT\tBT\tRBT\tST\tCT\tWT\tTAT\tRT\n");
    printf("-----------------------------------------------------------------\n");
    for(int i = 0; i < n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", ps[i].id, ps[i].priority, ps[i].arrival, ps[i].burst, ps[i].rem_burst, ps[i].start, ps[i].completion, ps[i].waiting, ps[i].tat, ps[i].responce);
    }
    printf("\n");
}

int main(){
    printf("Name\t: AYUSH GARG\nSection\t: A1\nRoll no.: 20\n\n");
    
    int n;
    printf("Enter the number of processess : ");
    scanf("%d", &n);
    printf("Enter the arrival and burst time along with thier priority for every process\n");
    process ps[n];
    for(int i = 0; i < n; i++){
        ps[i].id = i+1;
        scanf("%d %d %d", &ps[i].priority, &ps[i].arrival, &ps[i].burst);
        ps[i].rem_burst = ps[i].burst;
        ps[i].start = -1;
        ps[i].completion = 0;
        ps[i].responce = 0;
        ps[i].tat = 0;
        ps[i].waiting = 0;
    }

    int completed = 0, time = 0, idle_time = 0, tat = 0, response = 0, wait = 0;
    int completed_[n];
    memset(completed_, 0, sizeof(completed_));
    printf("Gantt's Chart : ");

    while(completed != n){
        int pid = -1;
        int mini = 1e8;
        for(int i = 0; i < n; i++){
            if(ps[i].arrival <= time && completed_[i] == 0){
                if(ps[i].priority < mini){
                    mini = ps[i].priority;
                    pid = i;
                }else if(ps[i].priority == mini){
                    if(ps[i].arrival < ps[pid].arrival){
                        pid = i;
                    }
                }
            }
        }
        if(pid == -1){
            printf("## ");
            idle_time++;
            time++;
        }else{
            printf("P%d ", ps[pid].id);
            if(ps[pid].start == -1) ps[pid].start = time;
            time += 1;
            ps[pid].rem_burst -= 1;
            if(ps[pid].rem_burst <= 0){
                completed++;
                completed_[pid] = 1;
                ps[pid].completion = time;
                ps[pid].responce = (ps[pid].start - ps[pid].arrival);
                ps[pid].tat = (ps[pid].completion - ps[pid].arrival);
                ps[pid].waiting = (ps[pid].tat - ps[pid].burst);
                tat += ps[pid].tat;
                wait += ps[pid].waiting;
                response += ps[pid].responce;
            }

        }

    }
    printProcesses(n, ps);
    printf("AVG TAT\t\t: %.2f\t\t AVG WAITING\t: %.2f\n", (float)tat/n, (float)wait/n);
    printf("AVG RESPONSE\t: %.2f\t\t IDLE TIME\t: %.2f\n", (float)response/n, (float)idle_time);
    printf("THROUGHPUT\t: %.2f\t\t CPU UTILIZATION: %.2f%%\n", (float)n/time, (float)(time-idle_time)*100/time);


    return 0;
}