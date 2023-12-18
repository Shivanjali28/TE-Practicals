#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


struct process
{
	int *allocation;
	int *need;
	int *max;
};

int *available, *sequence;
int NUM,SIZE;			//SIZE=NO. OF PROCESSES & NUM=NO. OF RESOURCES

int safety(struct process *p);
int resource_allocation(struct process *p);
int less(int a[], int b[]);
void snapshot(struct process *p);


int main()
{
	int i,err,j,choice,ans,counter=1;
	struct process *p;
	
	printf("\nEnter no. of resources: ");
	scanf("%d",&NUM);
	printf("\nEnter no. of processes: ");
	scanf("%d",&SIZE);
	
	//MEMORY ALLOCATION
	p = (struct process*) malloc(SIZE * sizeof(struct process));
	available = (int*) malloc(NUM * sizeof(int));
	sequence = (int*) malloc(SIZE * sizeof(int));
	for(i=0;i<SIZE;i++)
	{
		p[i].allocation = (int*) malloc(sizeof(int) * NUM);
		p[i].need = (int*) malloc(sizeof(int) * NUM);
		p[i].max = (int*) malloc(sizeof(int) * NUM);
	}
	
	//INITIALIZATION
	for(i=0;i<SIZE;i++)
	{
		printf("\n\n\t::P%d::\n",i);
		printf("\nMax :");
		for(j=0;j<NUM;j++)
			scanf("%d",&p[i].max[j]);
		printf("\nAllocation :");
		for(j=0;j<NUM;j++)
			scanf("%d",&p[i].allocation[j]);
		for(j=0;j<NUM;j++)
			p[i].need[j] = p[i].max[j]-p[i].allocation[j];
	}
	
	//PRINTING SNAPSHOT
	snapshot(p);
	
	printf("\n\nAvailable :");
	for(j=0;j<NUM;j++)
		scanf("%d",&available[j]);
	
	while(choice!=3)
	{
		snapshot(p);
		printf("\n\t:::MENU:::\n1.Safety Check\n2.Grant request\n3.Exit\n");
		scanf("%d",&choice);
	
		if(choice == 1)
		{
			ans=safety(p);
			if(ans==-1)
			{
				printf("\n-------------------------------------------\n");
				printf("\n\t:::::System is not safe!!!:::::::\n");
			}
			else if(ans==1)
			{
				printf("\n-------------------------------------------\n");
				printf("\n\t:::::System is safe!!!:::::\n");
				printf("\n\tThe safe sequence is: ");
				for(i=0;i<SIZE;i++)
					printf("P[%d] ,",sequence[i]);
			}
		}
		else if(choice==2)
		{
			ans=resource_allocation(p);
			if(ans==-1)
				printf("\nSorry request cannot be granted now!!!\nPlease wait!!!\n");
			else if(ans==1)
			{
				printf("\nRequest is granted! System is safe!!!\n");
				snapshot(p);
				printf("\nThe safe sequence is: ");
				for(i=0;i<SIZE;i++)
					printf("P%d ,",sequence[i]);
			}
		}
	}
	
return 0;
}

int safety(struct process *p)	//FUNC FOR CHECKING SAFETY OF SYSTEM
{
	int check[SIZE],work[SIZE]; 
	int i,count=0,j,counter=0,k=0,m,ch;
	
	for(i=0;i<SIZE;i++)
		check[i]=0;
	for(i=0;i<SIZE;i++)
		work[i]=available[i];
	ch=0;
	
	printf("\n\tWork : ");
	for(m=0;m<NUM;m++)
		printf("%d ",work[m]);
	while(count!=SIZE)
	{
		printf("\n------------------------------------\n");
		printf("\nChecking for Process P[%d]\n",ch);
		if(less(p[ch].need,work)==1 && check[ch]==0)
		{
			for(j=0;j<NUM;j++)
				work[j]+=p[ch].allocation[j];
			printf("\n\tWork : ");
			for(m=0;m<NUM;m++)
				printf("%d ",work[m]);
			check[ch]=1;
			count++;		//COUNT KEEPS TRACK OF NO. OF PROCCESSES ADDED TO SEQUENCE
			counter=0;		//COUNTER IS FOR AVOIDING INFINITE LOOP IN CASE RESOURCE CANNOT BE ALLOCATED
			sequence[k++]=ch;
			printf("\n\nProcess P[%d] added to sequence\n",ch);
		}
		else
		{
			printf("\nProcess P[%d] needs to wait\n",ch);
			counter++;
		}
		if(counter>SIZE)	//IF IT HAS CHECKED FOR ALL PROCESSES BUT RESOURCE CANNOT BE GRANTED
			break;
				
		ch=(ch+1)%SIZE;
	}
	for(i=0;i<SIZE;i++)
	{
		if(check[i]==0)
			return -1;
	}
	return 1;
}

int resource_allocation(struct process *p)
{
	int req, request[NUM],i,ch;
	
	printf("\nEnter process no. which is requesting:");
	scanf("%d",&req);
	printf("\nEnter request:");
	for(i=0;i<NUM;i++)
		scanf("%d",&request[i]);
	if(less(request,p[req].need)==1 && less(request,available)==1)
	{
		for(i=0;i<NUM;i++)
		{
			p[req].allocation[i] += request[i];
			p[req].need[i] -= request[i];
			available[i] -= request[i];
		}
		
		printf("\n------------------------------------\n");
		printf("\nPretending to allocate resources\n");
		snapshot(p);
		printf("\n------------------------------------\n");
		printf("\nChecking the safety of this snapshot\n");
		ch=safety(p);
		if(ch==1)
			return 1;
		else
		{
			for(i=0;i<NUM;i++)
			{
				p[req].allocation[i] -= request[i];
				p[req].need[i] += request[i];
				available[i] += request[i];
			}
			return -1;
		}
	}
	return -1;
}

int less(int a[], int b[])
{
	int i;
	for(i=0;i<NUM;i++)
	{
		if(a[i]>b[i])
			return(-1);
	}
	return(1);
}

void snapshot(struct process *p)
{
	int i,j;
	printf("\n\t\t:::SNAPSHOT:::\n");
	printf("\n\nPROCESS\tMAX\t\tALLOCATION\tNEED\n");
	for(i=0;i<SIZE;i++)
	{
		printf("P%d\t",i);
		for(j=0;j<NUM;j++)
			printf("%d ",p[i].max[j]);
		printf("\t");
		for(j=0;j<NUM;j++)
			printf("%d ",p[i].allocation[j]);
		printf("\t");
		for(j=0;j<NUM;j++)
			printf("%d ",p[i].need[j]);
		printf("\t\n");
	}
	
}

