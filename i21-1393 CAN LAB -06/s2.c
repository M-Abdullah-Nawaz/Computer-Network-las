// M Abdullah Nawaz
// i21-1393
// cs- CN lab 6


#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>


// checking for the vowels function

int checkvowels(char *w) {
    char vowels[] = "AEIOUaeiou";
    int i,j;
    for ( i = 0; w[i] != '\0'; i++) {

        for (j = 0; vowels[j] != '\0'; j++) {

            if (w[i] == vowels[j]) {
                return 1;
            }
        }
    }
    return 0;
}

// function to reverse the string

void reverseword(char *w) {
    int length = strlen(w);
    int i;
    for ( i = 0; i < length / 2; i++) {

        char temp = w[i];
        w[i] = w[length - i - 1];
        
        w[length - i - 1] = temp;
    }
}

int main(void) {
    int socket_desc, client_sock, client_size;
    struct sockaddr_in server_addr, client_addr;
    char server_message[2000], client_message[2000];

    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc < 0) {
        printf("Could Not Create Socket. Error!!!!!\n");
        return -1;
    }

    printf("Socket Created\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Bind Failed. Error!!!!!\n");
        return -1;
    }

    printf("Bind Done\n");
    while (1)
    {
    
    if (listen(socket_desc, 5) < 0) {
        printf("Listening Failed. Error!!!!!\n");
        return -1;
    }

    printf("Listening for Incoming Connections.....\n");


        client_size = sizeof(client_addr);
        client_sock = accept(socket_desc, (struct sockaddr *)&client_addr, &client_size);

        if (client_sock < 0) {
            printf("Accept Failed. Error!!!!!!\n");
            return -1;
        }

        printf("Client Connected with IP: %s and Port No: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        if (recv(client_sock, client_message, sizeof(client_message), 0) < 0) {
            printf("Receive Failed. Error!!!!!\n");
            return -1;
        }

        printf("Client Message: %s\n", client_message);

        // Tokenize the string into words
        char *token = strtok(client_message, " ");
        while (token != NULL) {
            if (checkvowels(token)) {
                reverseword(token);
            }
            strcat(server_message, token);
            strcat(server_message, " ");
            token = strtok(NULL, " ");
        }
        printf("inverted message = %s\n",server_message);
        if (send(client_sock, server_message, strlen(server_message), 0) < 0) {
            printf("Send Failed. Error!!!!!\n");
            return -1;
        }


        memset(server_message, '\0', sizeof(server_message));
        memset(client_message, '\0', sizeof(client_message));

        close(client_sock);
    }

    close(socket_desc);
    return 0;
}
