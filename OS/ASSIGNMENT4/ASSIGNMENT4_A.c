#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

#define buffer_size 10
int buffer[buffer_size];

sem_t empty,full;
pthread_mutex_t mutex;
int prod,cons;
int count=0;

void *producer(void*no)
{
    int *prod_id=(int*)no;
    int item;
    while(1)
    {
        item=rand()%100;
        if(count==buffer_size)
        {
            printf("\n\t\t\tBUFFER IS FULL !!! CAN'T INSERT ITEMS");
            break;
        }
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[count++]=item;
        printf("\n\t\t\tProducer[%d] produced item number : I0%d\n",*prod_id,item);
        printf("\n\t\t\tBUFFER SIZE : %d",count);

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *consumer (void *no)
{
    int *cons_id=(int*) no;
    int item;
    while(1)
    {
        if(count==0)
        
            printf("\n\t\t\tBUFFER IS EMPTY !! CAN'T CONSUME");
            break;
        }
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item=buffer[count--];
        printf("\n\t\t\tConsumer[%d] consumed item Number : I0%d",*cons_id[i],item);
        printf("\n\t\t\tBuffer Size :%d",count);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main()
{
    printf("-----------------PRODUCER-CONSUMER PROBLEM-----------------------");
    printf("\nEnter number of producers:");
    scanf("%d",&prod);
     printf("\nEnter number of consumers:");
    scanf("%d",&cons);

    pthread_t producer_thread[prod];
    pthread_t consumer_thread[cons];

    sem_init(&empty,0,buffer_size);
    sem_init(&full,0,0);

    pthread_mutex_init(&mutex,NULL);

    int prod_id[prod];
    int cons_id[cons];

    for(int i=0;i<prod;i++)
    {
        prod_id[i]=i+1;
        pthread_create(&producer_thread[i],NULL,producer,prod_id[i]);
    }

    for(int i=0;i<cons;i++)
    {
        cons_id[i]=i+1;
        pthread_create(&consumer_thread[i],NULL,consumer,cons_id[i]);
    }

    for(int i=0;i<prod;i++)
    {
        pthread_join(producer_thread[i],NULL);

    }
    for(int i=0;i<cons;i++)
    {
        pthread_join(consumer_thread[i],NULL);

    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}