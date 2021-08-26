#include<stdio.h>
#include<omp.h>
#include<time.h>

int k=0;

int partition(int arr[], int low_index, int high_index)
{
    int i, j, temp, key;
    key = arr[low_index];

    i= low_index + 1;
    j= high_index;

    while(1)
    {
        while(i < high_index && key >= arr[i])
            i++;

        while(key < arr[j])
            j--;

        if(i < j)
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

        }

        else
        {
            temp= arr[low_index];
            arr[low_index] = arr[j];
            arr[j]= temp;

            return(j);
        }   
    }
}


void quicksort(int arr[], int low_index, int high_index)
{
    int j;

    if(low_index < high_index)

    {
        j = partition(arr, low_index, high_index);
        printf("Pivot element with index %d has been found out by thread %d\n",j,k);

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                k=k+1;
                quicksort(arr, low_index, j - 1);
            }

            #pragma omp section
            {
                k=k+1;
                quicksort(arr, j + 1, high_index);
            }
        }                      
    }
}

//main function

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
    printf("Burst Time:");

    scanf("%d",&bt[i]);
    printf("Priority:");
    scanf("%d",&pr[i]);
    p[i]=i+1;	//contains process number
    }

    //sorting burst time, priority and process number in ascending order using quick sort

    quicksort(pr, 0, n - 1);

    wt[0]=0;	//waiting time for first process is zero

    //calculate waiting time

    for(i=1;i<n;i++)
    {
    wt[i]=0;
    for(j=0;j<i;j++)
    wt[i]+=bt[j];
    total+=wt[i];
    }
    

    avg_wt=total/n;  //average waiting time
    total=0; 
    

    printf("\nProcess\t  Burst Time \tWaiting Time\tTurnaround Time");
    
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];  //calculate turnaround time
        total+=tat[i];
        printf("\nP[%d]\t\t %d\t\t %d\t\t\t%d",p[i],bt[i],wt[i],tat[i]);
    }

    avg_tat=total/n; //average turnaround time 
    printf("\n\nAverage Waiting Time=%d",avg_wt); 
    printf("\nAverage Turnaround Time=%d\n\n\n",avg_tat);

     clock_t end = clock();

	// calculate elapsed time by finding difference (end - begin) and
	// dividing the difference by CLOCKS_PER_SEC to convert to seconds
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Time elpased is %f seconds", time_spent);

    return 0;

}
