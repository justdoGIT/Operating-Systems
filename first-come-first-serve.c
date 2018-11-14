#include <stdio.h>

void find_waiting_time(int processes[], int n, int burst_time[],
                       int wait_time[], int arrival_time[])
{
  int service_time[n];
  service_time[0] = 0;
  wait_time[0] = 0;

  for (int i = 1; i < n; i++)
  {
    service_time[i] = service_time[i-1] + burst_time[i-1];
    wait_time[i] =  service_time[i] - arrival_time[i];

    if (wait_time[i] < 0)
      wait_time[i] = 0;
  }
}

void find_turn_around_time(int processes[], int n, int burst_time[],
                           int wait_time[], int turn_around_time[])
{
  for(int i = 0; i < n; i++)
  {
    turn_around_time[i] = wait_time[i] + burst_time[i];
  }
}

void find_avg_time(int processes[], int n, int burst_time[], int arrival_time[])
{
  int wait_time[n], turn_around_time[n], completion_time[n];
  int total_wait_time = 0, total_turn_around_time = 0;

  find_waiting_time(processes, n, burst_time, wait_time, arrival_time);
  find_turn_around_time(processes, n, burst_time, wait_time, turn_around_time);

  printf("Processes   Burst Time   Arrival Time   Waiting Time   "
         "Turn Around Time   Completion Time\n");

  for(int i = 0; i < n; i++)
  {
    total_wait_time += wait_time[i];
    total_turn_around_time += turn_around_time[i];
    completion_time[i] = turn_around_time[i] + arrival_time[i];
    printf(" %d ", i+1);
    printf("            %d ", burst_time[i]);
    printf("            %d ", arrival_time[i]);
    printf("            %d ", wait_time[i]);
    printf("            %d ", turn_around_time[i]);
    printf("                 %d\n", completion_time[i]);
  }
  float s = (float)total_wait_time/(float)n;
  float t = (float)total_turn_around_time/(float)n;
  printf("Average waiting time = %f\n", s);
  printf("Average turn around time = %f\n", t);
}

int main()
{
  // process ID's
  int processes[] = {1, 2, 3};
  int n = sizeof(processes)/ sizeof(processes[0]);
  int burst_time[] = {5, 9, 6};
  int arrival_time[] = {0, 3, 6};
  find_avg_time(processes, n, burst_time, arrival_time);
  return 0;
}
