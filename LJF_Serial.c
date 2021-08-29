#include <stdio.h>
#include <sys/time.h>
int main()
{
	struct timeval start, endd;

	gettimeofday(&start, NULL);
	int arrival_time[10], burst_time[10], temp[10];
	int i, biggest, count = 0, time, limit, Limit;
	double wait_time = 0, turnaround_time = 0, end;
	float average_waiting_time = 0, average_turnaround_time = 0;
	printf("\nEnter the Total Number of Processes:\t");
	scanf("%d", &limit);
	printf("\nEnter Details of %d Processes\n", limit);
	for (i = 0; i < limit; i++)
	{
		printf("\nEnter Arrival Time:\t");
		scanf("%d", &arrival_time[i]);
		printf("Enter Burst Time:\t");
		scanf("%d", &burst_time[i]);
		temp[i] = burst_time[i];
	}
	burst_time[9] = -1;
	for (time = 0; count != limit; time++)
	{
		biggest = 9;
		for (i = 0; i < limit; i++)
		{
			if (arrival_time[i] <= time && burst_time[i] > burst_time[biggest] && burst_time[i] > 0)
			{
				biggest = i;
			}
		}
		burst_time[biggest]--;
		if (burst_time[biggest] == 0)
		{
			count++;
			end = time + 1;
			wait_time = wait_time + end - arrival_time[biggest] - temp[biggest];
			turnaround_time = turnaround_time + end - arrival_time[biggest];
		}
	}
	average_waiting_time = wait_time / limit;
	average_turnaround_time = turnaround_time / limit;
	printf("\n\nAverage Waiting Time:\t%lf\n", average_waiting_time);
	printf("Average Turnaround Time:\t%lf\n", average_turnaround_time);
	
	gettimeofday(&endd, NULL);
	long seconds = (endd.tv_sec - start.tv_sec);

	printf("Time elpased is %d seconds\n", seconds);
	return 0;
}


/*

5

1
7
2
5
3
1
4
2
5
8

*/
