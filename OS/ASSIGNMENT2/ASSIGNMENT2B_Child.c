#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char*argv)
{
    printf("Child Process is running!!");
    printf("Array elements are received..");
     for(int i=1;i<argc;i++)
     {
        printf("%s",argv[i]);
     }
    printf("\nArray elements in reverse order: ");
	for (int i = argc - 1; i >= 1; i--)
	{
		printf("%s ", argv[i]);
	}
	printf("\n");
	return 0;
}