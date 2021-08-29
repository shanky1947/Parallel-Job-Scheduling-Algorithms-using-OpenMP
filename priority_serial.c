#include<stdio.h>
#include<time.h>

#define BILLION  1000000000.0


int main()
{

    double time_spent = 0.0;

	clock_t begin = clock();


    int bt[20],p[20],wt[20],tat[20],pr[20],i,j,n,total=0,pos,temp,avg_wt,avg_tat;

    printf("Enter Total Number of Process:");
    scanf("%d",&n);

    printf("\nEnter Burst Time and Priority\n");

    for(i=0;i<n;i++)
    {
        printf("\nP[%d]\n",i+1);
        printf("Burst Time: ");

        scanf("%d",&bt[i]);

        printf("Priority: ");
        scanf("%d",&pr[i]);
        p[i]=i+1; //contains process number

    }

    
    for(i=0;i<n;i++)
    {
        pos=i;

        for(j=i+1;j<n;j++)
        {
            if(pr[j]<pr[pos])
                pos=j;
        }

        temp=pr[i];
        pr[i]=pr[pos];
        pr[pos]=temp;
        temp=bt[i];
        bt[i]=bt[pos];
        bt[pos]=temp;
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;

    }

    wt[0]=0;   //waiting time for first process is zero

    for(i=1;i<n;i++)
    {
        wt[i]=0;

        for(j=0;j<i;j++)
            wt[i]+=bt[j];

        total+=wt[i];
    }

    avg_wt=total/n; //average waiting time
    total=0;


    printf("\nProcess\t  Burst Time\tWaiting Time\tTurnaround Time");

    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i]; //calculate turnaround time
        total+=tat[i];
        printf("\nP[%d]\t      %d\t\t    %d\t\t    %d",p[i],bt[i],wt[i],tat[i]);
    }

    avg_tat=total/n; //average turnaround time

    printf("\n\n\nAverage Waiting Time = %d\n",avg_wt); 
    printf("\nAverage Turnaround Time = %d\n\n\n",avg_tat); 

    clock_t end = clock();

	// calculate elapsed time by finding difference (end - begin) and
	// dividing the difference by CLOCKS_PER_SEC to convert to seconds
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Time elpased is %f seconds", time_spent);

 

    return 0;

}