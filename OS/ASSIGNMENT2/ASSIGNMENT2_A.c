#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
void swap_elements()
int partition(int* arr,int l,int h)
{
    int pivot=arr[h];
    int i=l-1;
    for(int j=l;j<=h;j++)
    {
        if(arr[j]<pivot)
        {
            i++;
            int temp=arr[j];
            arr[j]=arr[i];
            arr[i]=temp;
        }
    }
    // swap_elements(arr[i+1],arr[h]);
    int temp=arr[i+1];
    arr[i+1]=arr[h];
    arr[h]=temp;
    return (i+1);
}
void quicksort(int *arr,int l,int h)
{
    if(l<h)
    {
        int p=partition(arr,l,h);
        quicksort(arr,0,p-1);
        quicksort(arr,p+1,h);
    }
}

void display(int *arr,int n){
	int i;
	printf("\n");
	printf("Sorted array:- ");
	for(i=0;i<n;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
}

int main()
{
    pid_t PID;
    int n;
  

    printf("Enter Size of Array:");
    scanf("%d",&n);
    int arr[n];
    printf("\nEnter elements of array:");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    
    int choice;
    printf("\n=====MENU=====");
    printf("\n1.Orphan\n2.Zombie");
    printf("\nEnter your choice:");
    scanf("%d",&choice);
   //Demonstrating orphan process
    if(choice==1)
    {
    
        printf("\n=============Forking==================");
        PID=fork();
        if(PID>0)
        {
            //It will be parent process
            printf("\nIn parent process......Running quick Sort !!");
            quicksort(arr,0,n-1);
            display(arr,n);
            //parent Info
            printf("\nIDs of Processes:");
            printf("\nParent Id: %d",getpid());
            printf("\nPPID: %d",getppid());
            printf("\nChild Id: %d",PID);
            printf("\n");
            system("ps -elf | grep a.out");
            printf("\nParent process exited!!");
        }
        else if(PID==0)
        {
            //It will be child process
            sleep(10);
            printf("\nIn Child process......Running quick Sort !!");
            quicksort(arr,0,n-1);
            display(arr,n);

            printf("Child Process in sleep\n");						
			printf("Child process is awake\n");
            //Child Info
            printf("\nIDs of Processes:");
            printf("\nChild Id: %d",getpid());
            printf("\nParent Id: %d",getppid());
           
            
            printf("\n");
            system("ps -elf | grep a.out");
            printf("\n Child process exited!!");
        }

    }
    if(choice==2)
    {
        printf("\n=============Forking==================");
        PID=fork();
        if(PID>0)
        {
            sleep(10);
            //It will be parent process
            printf("\nIn parent process......Running quick Sort !!");
            quicksort(arr,n);
            display(arr,n);
            //parent Info
            printf("\nIDs of Processes:");
            printf("\nParent Id: %d",getpid());
            printf("\nPPID: %d",getppid());
            printf("\nChild Id: %d",PID);
            printf("\n");
            system("ps -elf | grep a.out");
            printf("\nParent process exited!!");
        }
        else if(PID==0)
        {
            //It will be child process
           
            printf("\nIn Child process......Running quick Sort !!");
            quicksort(arr,n);
            display(arr,n);

            printf("Child Process in sleep\n");						
			printf("Child process is awake\n");
            //Child Info
            printf("\nIDs of Processes:");
            printf("\nChild Id: %d",getpid());
            printf("\nParent Id: %d",getppid());
       
            
            printf("\n");
            system("ps -elf | grep a.out");
            printf("\n Child process exited!!");
        }


    }
    exit(0);
}