#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <dirent.h>



/*void logFileOperation(const char *filename, const char *action) {
    printf("File %s %s\n", action, filename);
}
*/ 
int main() {
    // Membuat shared memory yang akan digunakan untuk menyimpan nama file
    key_t key = 1234;
    int shmid = shmget(key, sizeof(char) * 10 * 256, IPC_CREAT | 0666);
    char (*shm)[10][256] = shmat(shmid, NULL, 0);

    // Membuka direktori dari new-data
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    char filename[256];
    int file_count = 0;

    dir = opendir("/home/ubuntu/SISOP/modul3/soal_1/new-data");
    if (dir == NULL) {
        printf("Cannot open directory\n");
        return 1;
    }

    // Mengirim nama file yang berakhiran _trashcan.csv dan _parkinglot.csv ke shared memory
    while ((entry = readdir(dir)) != NULL && file_count < 10) {
        sprintf(filename, "%s", entry->d_name);
        if (strlen(filename) < 256) {
            if (strstr(filename, "_trashcan.csv") || strstr(filename, "_parkinglot.csv")) {
                strcpy((*shm)[file_count], filename);
                file_count++;
                //logFileOperation(filename, "sent");
            } else {
                // Hapus file yang bukan _trashcan.csv ataupun _parkinglot.csv
                char filepath[256 + 100]; 
                sprintf(filepath, "/home/ubuntu/SISOP/modul3/soal_1/new-data/%s", filename);
                remove(filepath);
                //logFileOperation(filename, "deleted");
            }
        }
    }

    closedir(dir);
    shmdt(shm);

    return 0;
}
