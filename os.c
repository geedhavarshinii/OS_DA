#include <stdio.h>
#define MAX_PROCESSES 4
struct Process
{
    char processId[3];
    int arrivalTime;
    int cpuTime;
    int remainingTime;
    int priority;
    int waitingTime;
    int turnaroundTime;
};

// fcfs

void calculateWaitingTimeFCFS(struct Process processes[], int n)
{
    int i;
    processes[0].waitingTime = 0;
    for (i = 1; i < n; i++)
    {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].cpuTime;
    }
}
void calculateTurnaroundTimeFCFS(struct Process processes[], int n)
{
    int i;
    processes[0].turnaroundTime = processes[0].cpuTime;
    for (i = 1; i < n; i++)
    {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].cpuTime;
    }
}
void calculateAverageTimesFCFS(struct Process processes[], int n)
{
    int i;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    printf("\nProcess\tArrival Time\tCPU Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
    {
        printf("%s\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processId, processes[i].arrivalTime,
               processes[i].cpuTime, processes[i].waitingTime, processes[i].turnaroundTime);
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }
    printf("\nAverage Waiting Time: %.2f", totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f", totalTurnaroundTime / n);
}

// preemptive sjf

void calculateWaitingTimePSJF(struct Process processes[], int n)
{
    int i, smallest, time, remainingProcesses = n;
    int completed = 0;
    int currentTime = 0;
    int shortestJob = -1;
    int isCompleted[10];

    for (i = 0; i < n; i++)
    {
        processes[i].remainingTime = processes[i].cpuTime;
        isCompleted[i] = 0;
    }

    while (completed != remainingProcesses)
    {
        smallest = 9999;

        for (i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && isCompleted[i] == 0)
            {
                if (processes[i].remainingTime < smallest)
                {
                    smallest = processes[i].remainingTime;
                    shortestJob = i;
                }
            }
        }

        if (shortestJob != -1)
        {
            processes[shortestJob].remainingTime--;
            currentTime++;

            if (processes[shortestJob].remainingTime == 0)
            {
                processes[shortestJob].waitingTime = currentTime - processes[shortestJob].cpuTime - processes[shortestJob].arrivalTime;
                processes[shortestJob].turnaroundTime = currentTime - processes[shortestJob].arrivalTime;
                isCompleted[shortestJob] = 1;
                completed++;
            }
        }
        else
        {
            currentTime++;
        }
    }
}

void calculateTurnaroundTimePSJF(struct Process processes[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].cpuTime;
    }
}

void calculateAverageTimesPSJF(struct Process processes[], int n)
{
    int i;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("\nProcess\tArrival Time\tCPU Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++)
    {
        printf("%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processId, processes[i].arrivalTime,
               processes[i].cpuTime, processes[i].priority, processes[i].waitingTime, processes[i].turnaroundTime);

        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    printf("\nAverage Waiting Time: %.2f", totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f", totalTurnaroundTime / n);
}

// non preemptive sjf

void sortProcessesByArrivalTimeNPSJF(struct Process processes[], int n)
{
    struct Process temp;
    int i, j;

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (processes[i].arrivalTime > processes[j].arrivalTime)
            {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void calculateWaitingTimeNPSJF(struct Process processes[], int n)
{
    int i;

    processes[0].waitingTime = 0;

    for (i = 1; i < n; i++)
    {
        processes[i].waitingTime = processes[i - 1].cpuTime + processes[i - 1].waitingTime - processes[i].arrivalTime;
        if (processes[i].waitingTime < 0)
        {
            processes[i].waitingTime = 0;
        }
    }
}

void calculateTurnaroundTimeNPSJF(struct Process processes[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        processes[i].turnaroundTime = processes[i].cpuTime + processes[i].waitingTime;
    }
}

void calculateAverageTimesNPSJF(struct Process processes[], int n)
{
    int i;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("\nProcess\tArrival Time\tCPU Time\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++)
    {
        printf("%s\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processId, processes[i].arrivalTime,
               processes[i].cpuTime, processes[i].waitingTime, processes[i].turnaroundTime);

        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    printf("\nAverage Waiting Time: %.2f", totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f", totalTurnaroundTime / n);
}

// ps

void sortProcessesByArrivalTimePS(struct Process processes[], int n)
{
    struct Process temp;
    int i, j;

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (processes[i].arrivalTime > processes[j].arrivalTime)
            {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void calculateWaitingTimePS(struct Process processes[], int n)
{
    int i;

    processes[0].waitingTime = 0;

    for (i = 1; i < n; i++)
    {
        processes[i].waitingTime = processes[i - 1].cpuTime + processes[i - 1].waitingTime - processes[i].arrivalTime;
        if (processes[i].waitingTime < 0)
        {
            processes[i].waitingTime = 0;
        }
    }
}

void calculateTurnaroundTimePS(struct Process processes[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        processes[i].turnaroundTime = processes[i].cpuTime + processes[i].waitingTime;
    }
}

void calculateAverageTimesPS(struct Process processes[], int n)
{
    int i;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("\nProcess\tArrival Time\tCPU Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++)
    {
        printf("%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processId, processes[i].arrivalTime,
               processes[i].cpuTime, processes[i].priority, processes[i].waitingTime, processes[i].turnaroundTime);

        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    printf("\nAverage Waiting Time: %.2f", totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f", totalTurnaroundTime / n);
}

// rr

void calculateWaitingTimeRR(struct Process processes[], int n, int quantum)
{
    int i, remainingProcesses = n;
    int time = 0;

    while (remainingProcesses > 0)
    {
        for (i = 0; i < n; i++)
        {
            if (processes[i].remainingTime > 0)
            {
                if (processes[i].remainingTime > quantum)
                {
                    time += quantum;
                    processes[i].remainingTime -= quantum;
                }
                else
                {
                    time += processes[i].remainingTime;
                    processes[i].waitingTime = time - processes[i].arrivalTime - processes[i].cpuTime;
                    processes[i].remainingTime = 0;
                    remainingProcesses--;
                }
            }
        }
    }
}

void calculateTurnaroundTimeRR(struct Process processes[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].cpuTime;
    }
}

void calculateAverageTimesRR(struct Process processes[], int n)
{
    int i;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("\nProcess\tArrival Time\tCPU Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++)
    {
        printf("%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processId, processes[i].arrivalTime,
               processes[i].cpuTime, processes[i].priority, processes[i].waitingTime, processes[i].turnaroundTime);

        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    printf("\nAverage Waiting Time: %.2f", totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f", totalTurnaroundTime / n);
}

int main()
{
    int i;
    printf("Enter 1 for FCFS\nEnter 2 for Preemptive SJF\nEnter 3 for Non-Preemptive SJF\nEnter 4 for Priority Scheduling\nEnter 5 for Round Robin\nEnter 6 to exit\n");
    scanf("%d", &i);
    struct Process processes[] = {
        {"p1", 0, 20, 2},
        {"p2", 4, 10, 1},
        {"p3", 6, 15, 1},
        {"p4", 10, 5, 2}};
    struct Process processesRR[] = {
        {"p1", 0, 20, 20, 2},
        {"p2", 4, 10, 10, 1},
        {"p3", 6, 15, 15, 1},
        {"p4", 10, 5, 5, 2}};
    while (i != 6)
    {
        switch (i)
        {
        case 1:
            printf("FCFS\n");
            calculateWaitingTimeFCFS(processes, MAX_PROCESSES);
            calculateTurnaroundTimeFCFS(processes, MAX_PROCESSES);
            calculateAverageTimesFCFS(processes, MAX_PROCESSES);
            printf("\n");
            break;
        case 2:
            printf("Preemptive SJF\n");
            calculateWaitingTimePSJF(processes, MAX_PROCESSES);
            calculateTurnaroundTimePSJF(processes, MAX_PROCESSES);
            calculateAverageTimesPSJF(processes, MAX_PROCESSES);
            printf("\n");
            break;
        case 3:
            printf("Non Preemptive SJF\n");
            sortProcessesByArrivalTimeNPSJF(processes, MAX_PROCESSES);
            calculateWaitingTimeNPSJF(processes, MAX_PROCESSES);
            calculateTurnaroundTimeNPSJF(processes, MAX_PROCESSES);
            calculateAverageTimesNPSJF(processes, MAX_PROCESSES);
            printf("\n");
            break;
        case 4:
            printf("Priority Scheduling\n");
            sortProcessesByArrivalTimePS(processes, MAX_PROCESSES);
            calculateWaitingTimePS(processes, MAX_PROCESSES);
            calculateTurnaroundTimePS(processes, MAX_PROCESSES);
            calculateAverageTimesPS(processes, MAX_PROCESSES);
            printf("\n");
            break;
        case 5:
            printf("Round Robin\n");
            calculateWaitingTimeRR(processesRR, MAX_PROCESSES, 2);
            calculateTurnaroundTimeRR(processesRR, MAX_PROCESSES);
            calculateAverageTimesRR(processesRR, MAX_PROCESSES);
            printf("\n");
            break;
        default:
            break;
        }
        printf("Enter 1 for FCFS\nEnter 2 for Preemptive SJF\nEnter 3 for Non-Preemptive SJF\nEnter 4 for Priority Scheduling\nEnter 5 for Round Robin\nEnter 6 to exit\n");
        scanf("%d", &i);
        if(i == 6) printf("Program Terminated\n");
    }
    return 0;
}
