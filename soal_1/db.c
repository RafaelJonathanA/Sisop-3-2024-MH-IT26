#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>

// Fungsi untuk menuliskan ke dalam log 
void log_to_file(const char *type, const char *filename) {
    FILE *log_file = fopen("/home/ubuntu/SISOP/modul3/soal_1/microservices/database/db.log", "a");
    if (log_file != NULL) {
        time_t current_time = time(NULL);
        struct tm *tm_info;
        tm_info = localtime(&current_time);
        fprintf(log_file, "[%02d/%02d/%04d %02d:%02d:%02d] [%s] [%s]\n", tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900, tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, type, filename);
        fclose(log_file);
    } else {
        printf("Failed to open log file.\n");
    }
}

int main() {
    // Masuk  ke shared memory
    key_t key = 1234;
    int shmid = shmget(key, sizeof(char) * 10 * 256, 0666);
    char (*shm)[10][256] = shmat(shmid, NULL, 0);

    //Mengecek apakah ada shared memory
    if (shm == (char (*)[10][256]) -1) {
        printf("Shared memory kosong\n");
        return 1;
    }

    // Membuka directory new-data
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("/home/ubuntu/SISOP/modul3/soal_1/new-data")) != NULL) {

        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {  
                char filepath[256];
                snprintf(filepath, sizeof(filepath), "/home/ubuntu/SISOP/modul3/soal_1/new-data/%s", ent->d_name);

                char newpath[256];
                snprintf(newpath, sizeof(newpath), "/home/ubuntu/SISOP/modul3/soal_1/microservices/database/%s", ent->d_name);

                // Menentukan tipe file 
                char *type;
                if (strstr(ent->d_name, "_trashcan.csv") != NULL) {
                    type = "Trash Can";
                } else if (strstr(ent->d_name, "_parkinglot.csv") != NULL) {
                    type = "Parking Lot";
                } else {
                    type = "Tidak ada";
                }

                if (rename(filepath, newpath) == 0) {
                    log_to_file(type, ent->d_name);
                   
                } else {
                    perror("rename");
                }
            }
        }
        closedir(dir);
    } else {
        perror("opendir");
        return 1;
    }

    // Menghapus shared memory
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
      
    return 0;
}
