#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#define PORT 8080
  
int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char hello[1024];
    char text[1024];
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    char line[512];
    while(1){
        memset(text,0,sizeof(text));
        printf("You: ");
        scanf("%s", hello);
        scanf("%[^\n]%*c", text);
        
        FILE* filePtr;
        FILE* flog;

        if ((strcmp(hello, "tampilkan") == 0) || (strcmp(hello, "hari") == 0) || (strcmp(hello, "genre") == 0) || (strcmp(hello, "status") == 0)){
            filePtr = fopen("myanimelist.csv", "r");
        } else if (strcmp(hello, "add") == 0){
            filePtr = fopen("myanimelist.csv", "a");
            flog = fopen("change.log", "a");
        }
        int count = 1;


        if (strcmp(hello, "tampilkan") == 0){
            while (fgets(line, 512, filePtr) != NULL){
                char *strPtr = strtok(line, ",");
                for (int i=0; i<2; i++){
                    strPtr = strtok(NULL, ",");
                }
                printf("%d. %s\n", count, strPtr);
                count++;
            }
            fclose(filePtr);

        } else if (strcmp(hello, "hari") == 0){
            while (fgets(line, 512, filePtr) != NULL){
                char *strHari = strtok(line, ",");
                if (strcmp(text+1, strHari) == 0){
                   for (int i=0; i<2; i++){
                        strHari = strtok(NULL, ",");
                   }
                   printf("%d. %s\n", count, strHari);
                   count++; 
                }
            }
            fclose(filePtr);

        } else if (strcmp(hello, "status") == 0){
            while (fgets(line, 512, filePtr) != NULL){
                char *strName = strtok(line, ",");
                for (int i=0; i<2; i++){
                    strName = strtok(NULL, ",");
                }
                if (strcmp(text+1, strName) == 0){
                    strName = strtok(NULL, ",");
                    printf("%s\n", strName);
                    break;
                }
            }
            fclose(filePtr);

        } else if (strcmp(hello, "genre") == 0){
            while (fgets(line, 512, filePtr) != NULL){
                char *strGenre = strtok(line, ",");
                strGenre = strtok(NULL, ",");
                if (strcmp(text+1, strGenre) == 0){
                    strGenre = strtok(NULL, ",");
                    printf("%d. %s\n", count, strGenre);
                    count++;
                }
            }
            fclose(filePtr);
        } else if (strcmp(hello, "add") == 0){
            
            char buff[20];
            struct tm *sTm;

            time_t now = time (0);
            sTm = gmtime (&now);

            strftime (buff, sizeof(buff), "%d/%m/%y", sTm);

            char *str = strtok(text, ",");
            str = strtok(NULL, ",");
            str = strtok(NULL, ",");

            fprintf(filePtr, "\n");
            fprintf(filePtr, "%s\n", text+1);
            fprintf(flog, "[ADD] [%s] %s ditambahkan", buff, str);
            fclose(filePtr);
            fclose(flog);
        } else if (strcmp(hello, "exit") != 0){
            printf("invalid command\n");
        }

        strcat(hello, text);
        send(sock , hello , strlen(hello) , 0 );
        if (strcmp(hello, "exit") == 0) break;
        
    }
    
    return 0;
}