#include<sys/types.h>
#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
void quicksort(int a[],int first,int last)
{
    int pivot,j,temp,i;

    if(first<last)
	{
		pivot=first;
        i=first;
        j=last;

        while(i<j){
            while(a[i]<=a[pivot]&&i<last)
                i++;
            while(a[j]>a[pivot])
                j--;
            if(i<j){
				temp=a[i];
                a[i]=a[j];
                a[j]=temp;
             }
         }

         temp=a[pivot];
         a[pivot]=a[j];
         a[j]=temp;
         quicksort(a,first,j-1);
         quicksort(a,j+1,last);
    }
}
int main()
{
    int pid;
       int n;

    char *argv[15];
    for(int i=0;i<15;i++)
    {
        argv[i]=(char*)malloc(20);
    }

    printf("\nIn Parent Process... Process Id :%d",getpid());

    printf("\nEnter size of array:");
    scanf("%d",&n);

    int arr[n];
    
    printf("\nEnter elements of array:");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
   printf("\nSort elements using quick sort !!!");
    quicksort(arr,0,n-1);

    printf("\nDisplay Sorted Elements ::");
    for(int i=0;i<n;i++)
    {
        printf("%d",arr[i]);
        printf(" ");
    }

    printf("\nParent : I am calling my child process now....");
    printf("\n----------------------------------------------");
   

   pid=fork();
   if(pid==0)
   {
       printf("\nChild : In child process\n Child Id:%d",getpid());
       printf("\nChild : My Parent Id : %d",getppid());
       printf("\nChild : I am calling child program using execv...I am overlayed !!!");

       for(int i=0;i<n;i++)
       {
         sprintf(argv[i+1],"%d",arr[i]);
       }
        argv[0]="./child";
        argv[n+2]=NULL;

        execv("./child",argv);
        printf("\nError Occurred!!");
        printf("\nI am dying now ....");
        printf("\n----------------------------------------------");
   }
   else if(pid>0)
   {
       system("wait");
		printf("\nPARENT: I am dying now\n");
		printf("-------------------------------------------------------");
		printf("\n\n.");
   }
   else{
        printf("\nError Occurred!!");
   }
}