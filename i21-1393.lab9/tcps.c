/*
        TCP_Server. This Program will will create the Server side for TCP_Socket Programming.
        It will receive the data from the client and then send the same data back to client.
*/



#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <stdbool.h>

    bool check(char *name, char *cnic) {
        FILE *file = fopen("Voters_List.txt", "r");
        char buffer[100];
        char name2[10];
        char cnic2[15];
        bool found = false;

 while (fgets(buffer, sizeof(buffer), file)) {
      sscanf(buffer, "%[^/]/%s", name2, cnic2);
            if (strcmp(name2, name) == 0 && strcmp(cnic2, cnic) == 0) {
                found = true;
                break;
    }
  }
       
     fclose(file);
   file=fopen("output.txt","r");
    memset(buffer, '\0', sizeof(buffer));
        char vote[15];
    memset(cnic2, '\0', sizeof(cnic2));
 while (fgets(buffer, sizeof(buffer), file)) {
      sscanf(buffer, "%[^/]/%s", vote, cnic2);
           if (strcmp(cnic2, cnic) == 0) {
                found = false;
                break;
     }
  }
        fclose(file);
        return found;
    }
    void showcandidate(){
        char buffer[100];
        FILE  *file2=fopen("Candidates_List.txt","r");
        printf("candidate name       and his/her     voting  symbol \n");
 while(fgets(buffer,sizeof(buffer),file2)){
            printf("%s",buffer);
        }
    }
    
    
    void output(char*vote,char*cnic){
        FILE *file3=fopen("output.txt","a");
        fprintf(file3, "%s/%s\n", vote, cnic);
        fclose(file3);
    }


int main(void){
        int socket_desc, client_sock, client_size; 
        struct sockaddr_in server_addr, client_addr;         //SERVER ADDR will have all the server address
        char server_message[2000], client_message[2000];                 // Sending values from the server and receive from the server we need this

        //Cleaning the Buffers
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));     // Set all bits of the padding field//
        
        //Creating Socket
        
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(socket_desc < 0)
        {
                printf("Could Not Create Socket. Error!!!!!\n");
                return -1;
        }
        
        printf("Socket Created\n");
        
        //Binding IP and Port to socket
        
        server_addr.sin_family = AF_INET;               /* Address family = Internet */
        server_addr.sin_port = htons(2000);               // Set port number, using htons function to use proper byte order */
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");    /* Set IP address to localhost */
		
		
		
		// BINDING FUNCTION
        
        if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)    // Bind the address struct to the socket.  /
	                            	//bind() passes file descriptor, the address structure,and the length of the address structure
        {
                printf("Bind Failed. Error!!!!!\n");
                return -1;
        }        
        
        printf("Bind Done\n");

        while(1){  
            //Put the socket into Listening State
            
            if(listen(socket_desc, 1) < 0)
            {
                    printf("Listening Failed. Error!!!!!\n");
                    return -1;
            }
            
            printf("Listening for Incoming Connections.....\n");
            
            //Accept the incoming Connections
            
      client_size = sizeof(client_addr);
            
  client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);     
            
            if (client_sock < 0){
                    printf("Accept Failed. Error!!!!!!\n");
                    return -1;
            }
            
            printf("Client Connected with IP: %s and Port No: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
                //inet_ntoa() function converts the Internet host address in, given in network byte order, to a string in IPv4 dotted-decimal notation
            
            //Receive the message from the client
            
            if (recv(client_sock, client_message, sizeof(client_message),0) < 0)
            {
                    printf("Receive Failed. Error!!!!!\n");
                    return -1;
            }
           
      printf("client Message: %s\n",client_message);
            char name[10];
            char cnic[20];
            sscanf(client_message, "%[^/]/%s",name,cnic);
            printf("\n%s\n%s\n",name,cnic);
            bool check2=check(name,cnic);
            if(check2){
           printf("\nWelcome Voter\n");
           showcandidate();
          memset(client_message,'\0',sizeof(client_message));
        if (recv(client_sock, client_message, sizeof(client_message),0) < 0){
           printf("Receive Failed. Error!!!\n");
           return -1;
        }
          printf("\nvote = %s\n",client_message);
        output(client_message,cnic);
     }
        
        else{
   printf("\nVoter already voted or Invalid Voter\n");
            }
           
            //Closing the Socket
            memset(server_message,'\0',sizeof(server_message));
            memset(client_message,'\0',sizeof(client_message));

            
        }
        close(client_sock);
        close(socket_desc);
        return 0;       
}
