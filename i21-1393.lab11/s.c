// Muhammad Abdullah Nawaz
// i21-1393
// os-gc lab 11 




#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

#define SHM_KEY 1234
#define SHM_SIZE 1024

int main(int argc,char *argv[])
{
	int shmid;
	char *ptr_mem;
	shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
	if (shmid < 0) 
	{
		printf("Error");
		return -1;
	}
	ptr_mem = (char *)shmat(shmid, NULL, 0);
	if (ptr_mem == (char *)(-1)) 
	{
		printf("Error");
		return -1;
	}
	printf("Message that is  send from shared memory : %s\n", ptr_mem);
	int n,i,j,num;
	float average,sum=0;
	for(i=0,n=0;ptr_mem[i]!='\0';i=i+2,n++)
	{
		printf("%c",ptr_mem[i]);
	}
	printf("\n");
	for(i=0,j=0;j<=n;i=i+2,j++)
	{
		num=atoi(&ptr_mem[i]);
		sum=sum+num;
	}
	average=sum/n;
	printf("Sum: %f",sum);
	printf("\n");
	printf("Average: %f",average);
	printf("\n");
	if (shmdt(ptr_mem) == -1) 
	{
		printf("Error");
		return -1;
	}
	if (shmctl(shmid, IPC_RMID, NULL) == -1)
	{
		printf("Error");
		return -1;
	}
	return 0;
}
