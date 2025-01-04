#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int pid;        
    int burstTime;  
    int arrivalTime;
    int waitingTime;
    int turnAroundTime;
    int remainingTime;  
} Process;


void displayGanttChart(Process processes[], int n, int ganttChart[], int gcSize) {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < gcSize; i++) {
        printf("P%d ", ganttChart[i]);
    }
    printf("\n");
}


void fcfsScheduling(Process processes[], int n) {
    printf("\nFirst Come First Serve Scheduling\n");
    int ganttChart[n], gcIndex = 0;

  
    int totalWaitingTime = 0, totalTurnAroundTime = 0;
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        processes[i].waitingTime = (currentTime - processes[i].arrivalTime);
        processes[i].waitingTime = (processes[i].waitingTime < 0) ? 0 : processes[i].waitingTime;
        processes[i].turnAroundTime = processes[i].waitingTime + processes[i].burstTime;

        ganttChart[gcIndex++] = processes[i].pid;
        currentTime += processes[i].burstTime;

        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;
    }

 
    printf("Process\tBT\tAT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].burstTime, processes[i].arrivalTime,
               processes[i].waitingTime, processes[i].turnAroundTime);
    }
    printf("Average Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnAroundTime / n);

  
    displayGanttChart(processes, n, ganttChart, gcIndex);
}


void sjfScheduling(Process processes[], int n) {
    printf("\nShortest Job First Scheduling\n");
    int ganttChart[n], gcIndex = 0;

    int totalWaitingTime = 0, totalTurnAroundTime = 0;
    int currentTime = 0, completed = 0;

    int visited[n];
    memset(visited, 0, sizeof(visited));

    while (completed != n) {
        int minIndex = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && processes[i].arrivalTime <= currentTime) {
                if (minIndex == -1 || processes[i].burstTime < processes[minIndex].burstTime) {
                    minIndex = i;
                }
            }
        }

        if (minIndex != -1) {
            ganttChart[gcIndex++] = processes[minIndex].pid;
            currentTime += processes[minIndex].burstTime;

            processes[minIndex].waitingTime = currentTime - processes[minIndex].arrivalTime - processes[minIndex].burstTime;
            processes[minIndex].turnAroundTime = currentTime - processes[minIndex].arrivalTime;

            totalWaitingTime += processes[minIndex].waitingTime;
            totalTurnAroundTime += processes[minIndex].turnAroundTime;

            visited[minIndex] = 1;
            completed++;
        } else {
            currentTime++;
        }
    }

   
    printf("Process\tBT\tAT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].burstTime, processes[i].arrivalTime,
               processes[i].waitingTime, processes[i].turnAroundTime);
    }
    printf("Average Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnAroundTime / n);

  
    displayGanttChart(processes, n, ganttChart, gcIndex);
}

void roundRobinScheduling(Process processes[], int n, int timeQuantum) {
    printf("\nRound Robin Scheduling\n");
    int ganttChart[100], gcIndex = 0; 

    int totalWaitingTime = 0, totalTurnAroundTime = 0;
    int completed = 0, currentTime = 0;

    for (int i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
    }

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0) {
                ganttChart[gcIndex++] = processes[i].pid;

                if (processes[i].remainingTime > timeQuantum) {
                    currentTime += timeQuantum;
                    processes[i].remainingTime -= timeQuantum;
                } else {
                    currentTime += processes[i].remainingTime;
                    processes[i].remainingTime = 0;

                    processes[i].turnAroundTime = currentTime - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;

                    totalWaitingTime += processes[i].waitingTime;
                    totalTurnAroundTime += processes[i].turnAroundTime;

                    completed++;
                }
            }
        }
    }

    
    printf("Process\tBT\tAT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].burstTime, processes[i].arrivalTime,
               processes[i].waitingTime, processes[i].turnAroundTime);
    }
    printf("Average Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnAroundTime / n);

   
    displayGanttChart(processes, n, ganttChart, gcIndex);
}


int main() {
    int n, timeQuantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter Burst Time and Arrival Time for Process %d: ", i + 1);
        scanf("%d %d", &processes[i].burstTime, &processes[i].arrivalTime);
    }

    printf("Enter Time Quantum for Round Robin: ");
    scanf("%d", &timeQuantum);


    fcfsScheduling(processes, n);


    sjfScheduling(processes, n);

  
    roundRobinScheduling(processes, n, timeQuantum);

    return 0;
}
