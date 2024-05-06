#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define MAX_COMMAND_SIZE 100

//Fungsi untuk ngirim input command pake RPC ke paddock.c
void send_rpc_command(char* command, char* info) {
    struct sockaddr_in serv_addr;
    int sock = 0, valread;
    char buffer[MAX_COMMAND_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
return;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Konversi IP
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
return;
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
return;
    }
    snprintf(buffer, MAX_COMMAND_SIZE, "Command: %s\nInfo: %s\n", command, info);
    send(sock , buffer , strlen(buffer) , 0 );
    printf("[Driver] : [%s] [%s]\n", command, info);
    valread = read( sock , buffer, MAX_COMMAND_SIZE);
    printf("[Paddock]: [%s]\n",buffer );
}
//Fungsi main untuk input command di soal
int main(int argc, char *argv[]) {
    if (argc != 5 || strcmp(argv[1], "-c") != 0) {
        printf("Usage: %s -c <Command> -i <Info>\n", argv[0]);
        return 1;
    }
    char* command = argv[2];
    char* info = argv[4];
    send_rpc_command(command, info);
return 0;
}
