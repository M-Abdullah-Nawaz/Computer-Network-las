// Muhammad Abdullah Nawaz
// i21-1393
// os-gc lab 11 



#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

#define SHM_KEY 1234
#define SHM_SIZE 1024

int main(int argc,char *argv[])
{
	int shmid;
	char *ptr_mem;
	shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
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

	int n,fd;
	char buff[50];
	fd= open(argv[1],O_RDONLY);
	n = read(fd,buff,50);
	buff[n] = '\0';
	strcpy(ptr_mem, buff);

	printf("data in the file read \n");
	if (shmdt(ptr_mem) == -1) 
	{
		printf("Errot in shmdt");
		return -1;
	}
	return 0;
}
