 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>

 #define MAX_PROCESS 10
 #define MAX_ARRIVAL 20
 #define MAX_BURST 10
 #define QUANTUM 3

 typedef struct {
       int pid;                // Process ID
       int arrival_time;       // Arrival Time
       int burst_time;         // Burst Time
       int remaining_time;     // Remaining Time
       int waiting_time;       // Waiting Time
       int turnaround_time;    // Turnaround Time
 } Process;

 void generate_processes(Process processes[], int n);
 void run_round_robin(Process processes[], int n, int quantum);
 void print_results(Process processes[], int n);

 int main() {
       Process processes[MAX_PROCESS];
       int n = 0;

srand(time(NULL));

// Generate random processes
generate_processes(processes, MAX_PROCESS);
n = MAX_PROCESS;

// Run Round Robin scheduling algorithm
run_round_robin(processes, n, QUANTUM);

// Print results
print_results(processes, n);

return 0;
 }

   void generate_processes(Process processes[], int n) {
       int i;
          for (i = 0; i < n; i++) {
               processes[i].pid = i + 1;
               processes[i].arrival_time = rand() % MAX_ARRIVAL;
               processes[i].burst_time = rand() % MAX_BURST + 1;
               processes[i].remaining_time = processes[i].burst_time;
               processes[i].waiting_time = 0;
               processes[i].turnaround_time = 0;
          }
   }

    void run_round_robin(Process processes[], int n, int quantum) {
               int time = 0;
               int i;
               int done = 0;

while (!done) {
    done = 1;
    
    for (i = 0; i < n; i++) {
        if (processes[i].remaining_time > 0) {
            done = 0;
            
            if (processes[i].remaining_time > quantum) {
                time += quantum;
                processes[i].remaining_time -= quantum;
            } else {
                time += processes[i].remaining_time;
                processes[i].waiting_time = time - processes[i].burst_time - processes[i].arrival_time;
                processes[i].remaining_time = 0;
                processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
            }
        }
      }
    }
  }

     void print_results(Process processes[], int n) {
        int i;
          float avg_waiting_time = 0;
          float avg_turnaround_time = 0;

printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

for (i = 0; i < n; i++) {
    printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    avg_waiting_time += processes[i].waiting_time;
    avg_turnaround_time += processes[i].turnaround_time;
  }

  printf("Average Waiting Time = %.2f\n", avg_waiting_time / n);
  printf("Average Turnaround Time = %.2f\n", avg_turnaround_time / n);
}
