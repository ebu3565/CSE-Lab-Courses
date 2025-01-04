#include <stdio.h>
#define MAX_PROCESSES 100

typedef struct {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int remaining;  // Remaining burst time (for RR)
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
    int completed;  // Completion flag
} Process;

// Function to sort processes by arrival time
void sort_by_arrival(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival > processes[j + 1].arrival) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Function for FCFS Scheduling
void fcfs(Process processes[], int n) {
    printf("\n--- FCFS Scheduling ---\n");
    sort_by_arrival(processes, n);

    int time = 0;
    float total_waiting = 0, total_turnaround = 0;

    for (int i = 0; i < n; i++) {
        if (time < processes[i].arrival) {
            time = processes[i].arrival; // CPU idle time
        }

        processes[i].waiting = time - processes[i].arrival;
        time += processes[i].burst;
        processes[i].turnaround = processes[i].waiting + processes[i].burst;

        total_waiting += processes[i].waiting;
        total_turnaround += processes[i].turnaround;

        printf("Process %d: Waiting = %d, Turnaround = %d\n",
               processes[i].pid, processes[i].waiting, processes[i].turnaround);
    }

    printf("Average Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);
}

// Function for Round Robin Scheduling
void round_robin(Process processes[], int n, int quantum) {
    printf("\n--- Round Robin Scheduling ---\n");
    int time = 0, completed = 0;
    float total_waiting = 0, total_turnaround = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining > 0) {
                if (processes[i].remaining > quantum) {
                    time += quantum;
                    processes[i].remaining -= quantum;
                } else {
                    time += processes[i].remaining;
                    processes[i].waiting = time - processes[i].arrival - processes[i].burst;
                    processes[i].turnaround = time - processes[i].arrival;
                    processes[i].remaining = 0;
                    completed++;
                    total_waiting += processes[i].waiting;
                    total_turnaround += processes[i].turnaround;

                    printf("Process %d: Waiting = %d, Turnaround = %d\n",
                           processes[i].pid, processes[i].waiting, processes[i].turnaround);
                }
            }
        }
    }

    printf("Average Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);
}

// Function for Shortest Job First Scheduling
void sjf(Process processes[], int n) {
    printf("\n--- Shortest Job First (Non-Preemptive) Scheduling ---\n");
    int time = 0, completed = 0;
    float total_waiting = 0, total_turnaround = 0;

    while (completed < n) {
        int min_burst = 9999, shortest = -1;

        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrival <= time && processes[i].burst < min_burst) {
                min_burst = processes[i].burst;
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
        } else {
            processes[shortest].waiting = time - processes[shortest].arrival;
            time += processes[shortest].burst;
            processes[shortest].turnaround = processes[shortest].waiting + processes[shortest].burst;
            processes[shortest].completed = 1;

            completed++;
            total_waiting += processes[shortest].waiting;
            total_turnaround += processes[shortest].turnaround;

            printf("Process %d: Waiting = %d, Turnaround = %d\n",
                   processes[shortest].pid, processes[shortest].waiting, processes[shortest].turnaround);
        }
    }

    printf("Average Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);
}

int main() {
    int n, quantum;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival, &processes[i].burst);
        processes[i].remaining = processes[i].burst; // Initialize remaining burst time
        processes[i].completed = 0; // Initialize as not completed
    }

    printf("Enter time quantum for Round Robin: ");
    scanf("%d", &quantum);

    fcfs(processes, n);
    sjf(processes, n);

    // Reset remaining time and completed flag for Round Robin
    for (int i = 0; i < n; i++) {
        processes[i].remaining = processes[i].burst;
        processes[i].completed = 0;
    }

    round_robin(processes, n, quantum);

    return 0;
}
