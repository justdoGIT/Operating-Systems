#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void bubble_sort(int burst_time[], int processes[], int n)
{
    bool swapped;
    do
    {
      swapped = false;
      for (int i=0; i < n; i++)
      {
        if (burst_time[i] > burst_time[i+1])
        {
          int temp = burst_time[i];
          burst_time[i] = burst_time[i+1];
          burst_time[i+1] = temp;

          temp = processes[i];
          processes[i] = processes[i+1];
          processes[i+1]= temp;
          swapped = true;
        }
      }
    }
    while (swapped);
}

void find_waiting_time(int processes[], int n, int burst_time[], int wait_time[])
{
  wait_time[0] = 0;
  for (int i = 1; i < n; i++)
  {
    wait_time[i] = wait_time[i-1] + burst_time[i-1];
  }
}

void find_turn_around_time(int processes[], int n, int burst_time[],
                           int wait_time[], int turn_around_time[])
{
  for(int i = 0; i < n; i++)
  {
    turn_around_time[i] = burst_time[i] + wait_time[i];
  }
}

void find_avg_time(int processes[], int burst_time[], int n)
{
  int wait_time[n], turn_around_time[n];
  int total_wait_time = 0, total_turn_around_time = 0;

  find_waiting_time(processes, n, burst_time, wait_time);
  find_turn_around_time(processes, n, burst_time, wait_time, turn_around_time);

  printf("Processes   Burst Time   Waiting Time   "
         "Turn Around Time\n");

  for(int i = 0; i < n; i++)
  {
    total_wait_time += wait_time[i];
    total_turn_around_time += turn_around_time[i];
    printf(" %d", processes[i]);
    printf("            %d", burst_time[i]);
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
  int processes[] = {1, 2, 3, 4};
  int n = sizeof(processes)/sizeof(processes[0]);
  int burst_time[] = {6, 8, 7, 3};

  bubble_sort(burst_time, processes, n);
  printf("Order in which processes get executed: ");
  for (int i = 0; i < n; i++)
  {
    printf("%d ", processes[i]);
  }
  printf("\n");
  find_avg_time(processes, burst_time, n);
  return 0;
}
