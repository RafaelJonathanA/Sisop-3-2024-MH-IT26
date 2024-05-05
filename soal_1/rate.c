#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// Struktur untuk menyimpan informasi tentang tempat sampah atau tempat parkir
typedef struct {
    char type[20];      
    char filename[256]; 
    char name[100];     
    float rating;       
} PlaceInfo;

int main() {
// masuk ke shared memory yang sudah dibuat
    key_t key = 1234;
    int shmid = shmget(key, sizeof(char) * 10 * 256, IPC_CREAT | 0666);
    char (*shm)[10][256] = shmat(shmid, NULL, 0);

    PlaceInfo places[10];
    int place_count = 0;

    // Membaca informasi dari shared memory yang sudah dibuat di auth
    for (int i = 0; i < 10; i++) {
        if ((*shm)[i][0] == '\0') 
            break;

        char *filename = (*shm)[i];

        char filepath[512];
        sprintf(filepath, "/home/ubuntu/SISOP/modul3/soal_1/new-data/%s", filename);

        FILE *file = fopen(filepath, "r");
        if (file == NULL) {
            printf("Cannot open file: %s\n", filepath);
            continue;
        }

        // Menskip header dari file
    char header[1024];
    fgets(header, sizeof(header), file); 

    char name[100];
    float rating;
    while (fscanf(file, "%[^,],%f", name, &rating) == 2) {
        // Membaca file mulai dari tipenya namanya dan ratingnya
        strcpy(places[place_count].type, strstr(filename, "trashcan.csv") ? "Trash Can" : "Parking Lot");
        strcpy(places[place_count].filename, filename);
        strcpy(places[place_count].name, name);  
        places[place_count].rating = rating;
        place_count++;
    }

    fclose(file);
}
    // Cari rating tertinggi dari kedua  tipe trashcan dan parkinglot
    float max_rating_trashcan = 0.0;
    float max_rating_parkinglot = 0.0;
    int max_index_trashcan = -1;
    int max_index_parkinglot = -1;

    for (int i = 0; i < place_count; i++) {
        if (strcmp(places[i].type, "Trash Can") == 0) {
            if (places[i].rating > max_rating_trashcan) {
                max_rating_trashcan = places[i].rating;
                max_index_trashcan = i;
            }
        } else if (strcmp(places[i].type, "Parking Lot") == 0) {
            if (places[i].rating > max_rating_parkinglot) {
                max_rating_parkinglot = places[i].rating;
                max_index_parkinglot = i;
            }
        }
    }


    // Menampilkan hasil yang tertinggi ratingnya 
    printf("\nHighest rated places:\n\n");

    if (max_index_trashcan != -1) {
        printf("Type: Trash Can\n");
        printf("Filename: %s\n", places[max_index_trashcan].filename);
        printf("----------------------------------------\n");
        printf("Name: %s\n", places[max_index_trashcan].name);
        printf("Rating: %.1f\n\n", places[max_index_trashcan].rating);
    } else {
        printf("No highest rated Trash Can found.\n\n");
    }

    if (max_index_parkinglot != -1) {
        printf("Type: Parking Lot\n");
        printf("Filename: %s\n", places[max_index_parkinglot].filename);
        printf("----------------------------------------\n");
        printf("Name: %s\n", places[max_index_parkinglot].name);
        printf("Rating: %.1f\n\n", places[max_index_parkinglot].rating);
    } else {
        printf("No highest rated Parking Lot found.\n\n");
    }

 // menghapus shared memory
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
