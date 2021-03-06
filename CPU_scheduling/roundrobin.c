#include <stdio.h>
#define max 50
struct process
{
    int burst_t, comp_t, arr_t, wait_t, remain_t;
} p[max], temp;
int quanta; // sort of constant
void main()
{
    printf("Enter the quanta of the RoundRobin :");
    scanf("%d", &quanta);
    int n, i, j, finish, process = 0, total_bt = 0, run = 0;
    float avgt_t = 0.0, avgw_t = 0.0;
    printf("Enter no of processes:");
    scanf("%d", &n);
    printf("Enter the Burst time and arrival time\n");
    while (process++ < n)
    {
        printf("p%d\t", process);
        scanf("%d%d", &p[process].burst_t, &p[process].arr_t);
        p[process].remain_t = p[process].burst_t;
        total_bt += p[process].burst_t;
    }
    //sort according to arrival time
    for (i = 2; i <= n; i++)
    {
        temp = p[i];
        j = i - 1;
        while (j >= 1 && p[j].arr_t > temp.arr_t)
        {
            p[j + 1] = p[j];
            j = j - 1;
        }
        p[j + 1] = temp;
    }
    while (run <= total_bt)
    {
        finish = 1;
        for (i = 1; i <= n; i++)
        {
            if (p[i].remain_t > 0)
            {
                finish = 0;
                if (p[i].remain_t > quanta)
                {
                    run += quanta;
                    p[i].remain_t -= quanta;
                }
                else
                {
                    p[i].wait_t = run - (p[i].burst_t - p[i].remain_t) - p[i].arr_t;
                    run += p[i].remain_t;
                    p[i].comp_t = run;
                    p[i].remain_t = 0;
                }
            }
        }
        if (finish == 1)
            break;
    }
    for (i = 1; i <= n; i++)
    {
        avgt_t += p[i].comp_t - p[i].arr_t;
        avgw_t += p[i].wait_t;
    }
    avgt_t /= n;
    avgw_t /= n;
    printf("Avg Waiting time = %.2f\nAvg Turnaround time =%.2f\n", avgw_t, avgt_t);
}