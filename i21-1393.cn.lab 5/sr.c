
// M Abdullah Nawaz
// i21-1393
// cn lab -05



#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 

int main(void)
{
        char array[10][1000]; 
        int arrPointer = 9;
        int sCapacity = 10;
        int socket_desc;
        struct sockaddr_in server_addr, client_addr;
        char server_message[2000], client_message[2000]; 
        int client_struct_length = sizeof(client_addr);
        
        
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
       
        
        socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        
        if(socket_desc < 0)
        {
                printf("could not Create socket.\n");
                return -1;
        }
        
        printf("Socket Created\n");
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(2000);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  
        
        if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)
        {
                printf("Bind Failed. Error!!!!!\n");
                return -1;
        }        
        
        printf("Bind Done\n");
        
        while(1)
        {
        printf("Listening for messages.\n\n");
        
        if (recvfrom(socket_desc, client_message, sizeof(client_message), 0, (struct sockaddr*)&client_addr,&client_struct_length) < 0)
        {
                printf("receive Failed.\n");
                return -1;
        }
  	
  	 if(client_message[strlen(client_message) - 1] == 'I') //Check in request;
  	 {
  	 	int i = arrPointer;
  	 	int exists = 0;
  	 	if(arrPointer == 0)
  	 	{
  	 		strcpy(server_message, "Attendance sheet bFull.");
  	 	}
  	 	for(; i <= sCapacity; i++)
  	 	{
  	 		if(strcmp(array[i], client_message) == 0)
  	 		{
  	 			strcpy(server_message, "you are already here");
  	 			exists = 1;
  	 		}
  	 	}
  	 	if(exists == 0)
  	 	{
  	 		strcpy(array[arrPointer], client_message);
  	 		char RollNo[9];
  	 		int i;
  	 		for(i=0;i<7;++i)
  	 		RollNo[i]=client_message[i];
  	 		RollNo[i]='\0';
  	 		
  	 		strcpy(server_message, "welcome student");
  	 		strcat(server_message,RollNo);
  	 		arrPointer--;
  	 	}
  	 }
  	 else if(client_message[strlen(client_message) - 1] == 'O')
  	 {
  	 	int i = arrPointer;
  	 	int notExists = 1;
  	 	for(; i < sCapacity; i++)
  	 	{
  	 		char pseudo[100];
  	 		strcpy(pseudo, client_message);
  	 		pseudo[strlen(pseudo) - 1] = 'I';
  	 		if(strcmp(array[i], pseudo) == 0)
  	 		{
  	 		char RollNo[9];
  	 		int j;
  	 		for(j=0;j<7;++j)
  	 		RollNo[j]=client_message[j];
  	 		RollNo[j]='\0';
  	 			strcpy(server_message, "goodBye student ");
  	 			strcat(server_message,RollNo);
  	 			strcat(server_message,"have a nice day.");
  	 			strcpy(array[i], "no");
  	 			notExists = 0;
  	 			arrPointer++;
  	 			break;
  	 		}
  	 	}
  	 	if(notExists == 0 && i != 0)
  	 	{
	  	 	int j = i;
	  	 	for(; j > arrPointer; j--)
	  	 	{
	  	 		bzero(array[j], 0);
	  	 		strcpy(array[j], array[j - 1]);
	  	 	}
	  	}
  	 	if(notExists == 1)
  	 	{
  	 		strcpy(server_message, "You did not check in today Contact administrator");
  	 	}
  	 }
  	 else
  	 {
  	 	strcpy(server_message, "wrong input format");
  	 }
        printf("received Message from IP: %s and Port No: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

        printf("Client Message: %s\n",client_message);
        
   
        
        if (sendto(socket_desc, server_message, strlen(server_message), 0, (struct sockaddr*)&client_addr,client_struct_length)<0)
        {
                printf("Send Failed. Error!!!!!\n");
                return -1;
        }
    memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        }
        close(socket_desc);
        return 0;       
}
