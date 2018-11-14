#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Process
{
  int pid;
  int burst_time;
};

bool compare(struct Process a[], struct Process b[])
{
  return (a->burst_time > b->burst_time);
}

void find_waiting_time(struct Process proc[], int n, int wait_time[])
{
  wait_time[0] = 0;
  for (int i = 1; i < n; i++)
  {
    wait_time[i] = wait_time[i-1] + proc[i-1].burst_time;
  }
}

void find_turn_around_time(struct Process proc[], int n,
                           int wait_time[], int turn_around_time[])
{
  for(int i = 0; i < n; i++)
  {
    turn_around_time[i] = proc[i].burst_time + wait_time[i];
  }
}

void find_avg_time(struct Process proc[], int n)
{
  int wait_time[n], turn_around_time[n];
  int total_wait_time = 0, total_turn_around_time = 0;

  find_waiting_time(proc, n, wait_time);
  find_turn_around_time(proc, n, wait_time, turn_around_time);

  printf("Processes   Burst Time   Waiting Time   "
         "Turn Around Time\n");

  for(int i = 0; i < n; i++)
  {
    total_wait_time += wait_time[i];
    total_turn_around_time += turn_around_time[i];
    printf(" %d", proc[i].pid);
    printf("            %d", proc[i].burst_time);
    printf("            %d", wait_time[i]);
    printf("            %d", turn_around_time[i]);
    printf("\n");
  }
  float s = (float)total_wait_time/(float)n;
  float t = (float)total_turn_around_time/(float)n;
  printf("Average waiting time = %f\n", s);
  printf("Average turn around time = %f\n", t);
}
int main()
{
  struct Process proc[] = {{1, 6}, {2, 8}, {3, 7}, {4, 3}};
  int n = sizeof(proc) / sizeof(proc[0]);
  qsort(proc, n, sizeof(proc[0]), (void *)compare);
  printf("Order in which processes get executed: ");
  for (int i = 0; i < n; i++)
  {
    printf("%d ", proc[i].pid);
  }
  printf("\n");
  find_avg_time(proc , n);
  return 0;
}
