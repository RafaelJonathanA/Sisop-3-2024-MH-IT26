#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "actions.c" // Panggil Fungsi Actions.c lewat library

#define PORT 8080
#define MAX_COMMAND_SIZE 100

// Fungsi nulis ke log yang isinya driver dan paddock
void log_message(char *source, char *command, char *info) {
    time_t now;
    struct tm *local_time;
    char timestamp[30];

    time(&now);
    local_time = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%d/%m/%Y %H:%M:%S", local_time);

    FILE *log_file = fopen("race.log", "a");
    fprintf(log_file, "[%s] [%s]: [%s] [%s]\n", source, timestamp, command, info);
    fclose(log_file);
}

// Fungsi RPC buat manggil actions.c ke program paddock.c
void handle_rpc_call(int new_socket) {
    char buffer[MAX_COMMAND_SIZE] = {0};
    char response[MAX_COMMAND_SIZE] = {0};
    char command[MAX_COMMAND_SIZE];
    char info[MAX_COMMAND_SIZE];
    char source[] = "Driver"; //nambahin driver ke log sesuai soal
    char paddock_source[] = "Paddock"; //nambahin paddock ke log sesuai soal

    read(new_socket, buffer, MAX_COMMAND_SIZE);
    sscanf(buffer, "Command: %s\nInfo: %[^\n]", command, info);

//if else command input soal (Gap,Fuel,Tire<Tire Change)
    if (strcmp(command, "Gap") == 0) {
        float distance;
        sscanf(info, "%f", &distance);
        snprintf(response, MAX_COMMAND_SIZE, "%s", gap(distance));
    } else if (strcmp(command, "Fuel") == 0) {
        int fuel_percent;
        sscanf(info, "%d", &fuel_percent);
        snprintf(response, MAX_COMMAND_SIZE, "%s", fuel(fuel_percent));
    } else if (strcmp(command, "Tire") == 0) {
        int tire_usage;
        sscanf(info, "%d", &tire_usage);
        snprintf(response, MAX_COMMAND_SIZE, "%s", tire(tire_usage));
    } else if (strcmp(command, "TireChange") == 0) {
        snprintf(response, MAX_COMMAND_SIZE, "%s", tire_change(info));
    } else {
        snprintf(response, MAX_COMMAND_SIZE, "Invalid command");
    }
    write(new_socket, response, strlen(response));
    log_message(source, command, info); // Log untuk driver
    log_message(paddock_source, command, response); // Log untuk paddock
   // Print response 
    printf("[Paddock]: [%s]\n", response);
}

//Fungsi Main
int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    //Bikin socket file
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

   //Nyambungin ke port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        handle_rpc_call(new_socket);
        close(new_socket);
    }
return 0;
}
