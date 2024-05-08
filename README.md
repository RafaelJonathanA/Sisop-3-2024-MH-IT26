# Sisop-3-2024-MH-IT26

## ***KELOMPOK IT 26***
  | Nama      | NRP         |
  |-----------|-------------|
  | Rafael Jonathan Arnoldus   | 5027231006  |
  | Muhammad Abhinaya Al-Faruqi  | 5027231011  |  
  | Danendra Fidel Khansa  | 5027231063  |

## Bagian Pengerjaan Soal 
+ Soal 1 = Rafael Jonathan Arnoldus
+ Soal 2 = Danendra Fidel Khansa
+ Soal 3 = Danendra Fidel Khansa
+ Soal 4 = Muhammad Abhinaya Al-Faruqi

## ***MODUL 3***
  Berikut untuk struktur repository pengumpulan dari hasil praktikum sistem operasi modul 3 :
  ```
—soal_1:
   -auth.c
   - rate.c
   - db.c

—soal_2:
   - dudududu.c
				
—soal_3:
   - actions.c
   - driver.c
   - paddock.c
				
—soal_4:
   - client/
     - client.c 
   - server/
     -  server.c
```
## ***SOAL 1 (Rafael)***
## ***PENGERJAAN***
## ***PENJELASAN PENGERJAAN***
## ***Dokumentasi***

## ***SOAL 2 (Fidel)***

Max Verstappen 🏎️ seorang pembalap F1 dan programer memiliki seorang adik bernama Min Verstappen (masih SD) sedang menghadapi tahap paling kelam dalam kehidupan yaitu perkalian matematika, Min meminta bantuan Max untuk membuat kalkulator perkalian sederhana **(satu sampai sembilan)**. Sembari Max nguli dia menyuruh Min untuk belajar perkalian dari web (referensi) agar tidak bergantung pada kalkulator.

**(Wajib menerapkan konsep pipes dan fork seperti yang dijelaskan di modul Sisop. Gunakan 2 pipes dengan diagram seperti di modul 3).**

a. Sesuai request dari adiknya Max ingin nama programnya dudududu.c. Sebelum program parent process dan child process, ada input dari user berupa 2 string. Contoh input: tiga tujuh. 

b. Pada parent process, program akan mengubah input menjadi angka dan melakukan perkalian dari angka yang telah diubah. Contoh: tiga tujuh menjadi 21. 

c. Pada child process, program akan mengubah hasil angka yang telah diperoleh dari parent process menjadi kalimat. Contoh: `21` menjadi “dua puluh satu”.

d. Max ingin membuat program kalkulator dapat melakukan penjumlahan, pengurangan, dan pembagian, maka pada program buatlah argumen untuk menjalankan program : 
```
   i. perkalian	: ./kalkulator -kali
   ii. penjumlahan	: ./kalkulator -tambah
   iii. pengurangan	: ./kalkulator -kurang
   iv. pembagian	: ./kalkulator -bagi
```
Beberapa hari kemudian karena Max terpaksa keluar dari Australian Grand Prix 2024 membuat Max tidak bersemangat untuk melanjutkan programnya sehingga kalkulator yang dibuatnya cuma menampilkan hasil positif jika bernilai negatif maka program akan print “ERROR” serta cuma menampilkan bilangan bulat jika ada bilangan desimal maka dibulatkan ke bawah.

e. Setelah diberi semangat, Max pun melanjutkan programnya dia ingin (pada child process) kalimat akan di print dengan contoh format : 
```
i. perkalian	: “hasil perkalian tiga dan tujuh adalah dua puluh satu.”
ii. penjumlahan	: “hasil penjumlahan tiga dan tujuh adalah sepuluh.”
iii. pengurangan	: “hasil pengurangan tujuh dan tiga adalah empat.”
iv. pembagian	: “hasil pembagian tujuh dan tiga adalah dua.”
```
f. Max ingin hasil dari setiap perhitungan dicatat dalam sebuah log yang diberi nama **histori.log**. Pada parent process, lakukan pembuatan file log berdasarkan data yang dikirim dari child process. 
```
Format: [date] [type] [message]
Type: KALI, TAMBAH, KURANG, BAGI
Ex:
1. [10/03/24 00:29:47] [KALI] tujuh kali enam sama dengan empat puluh dua.
2. [10/03/24 00:30:00] [TAMBAH] sembilan tambah sepuluh sama dengan sembilan belas.
3. [10/03/24 00:30:12] [KURANG] ERROR pada pengurangan.
```

## ***PENGERJAAN***
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>
#include <math.h>

// Fungsi mengubah angka menjadi string
char *intToWords(int num) {
// Array huruf yang digunakan untuk konversi angka ke kata
const char *satuan[] = {"", "satu", "dua", "tiga", "empat", "lima", "enam", "tujuh", "delapan", "sembilan"};
    const char *belasan[] = {"", "sebelas", "dua belas", "tiga belas", "empat belas", "lima belas", "enam belas", "tujuh belas", "delapan belas", "sembilan belas"};
       const char *puluh[] = {"", "sepuluh", "dua puluh", "tiga puluh", "empat puluh", "lima puluh", "enam puluh", "tujuh puluh", "delapan puluh", "sembilan puluh"};

  char *result = (char *)malloc(100 * sizeof(char));
    strcpy(result, "");
// Konversi ratusan
if (num >= 100) {
        strcat(result, satuan[num / 100]);
        strcat(result, " ratus ");
        num %= 100;
    }
// Konversi puluhan
if (num >= 20) {
        strcat(result, puluh[num / 10]);
        strcat(result, " ");
        num %= 10;
    }
// Konversi belasan
if (num >= 11 && num <= 19) {
        strcat(result, belasan[num - 10]);
    } else if (num >= 1 && num <= 9) { // Konversi satuan
        strcat(result, satuan[num]);
    }
return result;
}
// Fungsi menulis ke file log dan kapital
void writeToLog(const char *operation, int num1, int num2, int result) {
FILE *logFile = fopen("histori.log", "a");
    if (logFile != NULL) {
        time_t rawtime;
        struct tm *info;
        char buffer[80];

        time(&rawtime);
        info = localtime(&rawtime);
        strftime(buffer, 80, "%d/%m/%y %H:%M:%S", info);
        
// Ngerubah tulisan operasi biar CAPSLOCK
        char upperOperation[10];
        int i;
        for (i = 0; operation[i]; i++) {
            upperOperation[i] = toupper(operation[i]);
        }
        upperOperation[i] = '\0';
// Tulis ke file log sesuai format soal
if (result < 0) {
    fprintf(logFile, "[%s] [%s] ERROR pada %s.\n", buffer, upperOperation, upperOperation);
} else {
    fprintf(logFile, "[%s] [%s] %s %s %s sama dengan %s.\n", buffer, upperOperation, intToWords(num1), operation, intToWords(num2), intToWords(result));
        }
fclose(logFile);
    }
}

//Konversi string nama angka ke angka int
int stringToNumber(char *str) {
    const char *words[] = {"", "satu", "dua", "tiga", "empat", "lima", "enam", "tujuh", "delapan", "sembilan"};
    for (int i = 1; i <= 9; i++) {
    if (strcmp(str, words[i]) == 0) {
return i;
        }
    }
return 0;
}

//Fungsi main untuk input dan manggil void
int main(int argc, char *argv[]) {
    // Masukkin operasi perhitungan (tambah,kurang,kali,bagi)
    if (argc != 2) {
        printf("Usage: %s <operation>\n", argv[0]);
        return 1;
    }
    char *operation = argv[1];
    char operand1[20], operand2[20];
// Masukkin input angka di terminal
printf("Masukkan angka pertama: ");
scanf("%s", operand1);
printf("Masukkan angka kedua: ");
scanf("%s", operand2);

    int num1 = stringToNumber(operand1);
    int num2 = stringToNumber(operand2);

    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == -1) {  
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {  // Child process
        close(pipefd[1]);  // Akhiri pipe
        int result;
        read(pipefd[0], &result, sizeof(result));

        if (result < 0) {
            printf("ERROR: Hasil operasi negatif.\n");
    } else {
            // Merubah output pada terminal sesuai format soal
            if (strcmp(operation, "-tambah") == 0) {
                printf("Hasil penjumlahan %s dan %s adalah %s.\n", operand1, operand2, intToWords(result));
            } else if (strcmp(operation, "-kali") == 0) {
                printf("Hasil perkalian %s dan %s adalah %s.\n", operand1, operand2, intToWords(result));
            } else if (strcmp(operation, "-kurang") == 0) {
                printf("Hasil pengurangan %s dan %s adalah %s.\n", operand1, operand2, intToWords(result));
            } else if (strcmp(operation, "-bagi") == 0) {
                printf("Hasil pembagian %s dan %s adalah %s.\n", operand1, operand2, intToWords(result));
            }
        }
        // Tulis ke file log
        writeToLog(operation + 1, num1, num2, result);
        close(pipefd[0]);
        exit(EXIT_SUCCESS);
    } else {  // Parent process
close(pipefd[0]);  // AKhiri pipe

        int result = 0;
        // Operasi perhitungan
        if (strcmp(operation, "-kali") == 0) {
            result = num1 * num2;
        } else if (strcmp(operation, "-tambah") == 0) {
            result = num1 + num2;
        } else if (strcmp(operation, "-kurang") == 0) {
            result = num1 - num2;
            if (result < 0) {
                printf("ERROR: Hasil negatif.\n");
                close(pipefd[1]);
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(operation, "-bagi") == 0) {
            if (num2 == 0) {
                printf("ERROR: Pembagian gabisa.\n");
                close(pipefd[1]);
                exit(EXIT_FAILURE);
            }
            result = num1 / num2;
        } else {
            printf("Operasi tidak valid.\n");
            close(pipefd[1]);
            exit(EXIT_FAILURE);
        }
        // Nulis hasil operasi
        write(pipefd[1], &result, sizeof(result));
        close(pipefd[1]);
        wait(NULL);
    }
return 0;
}
```
## ***PENJELASAN PENGERJAAN***

## ***Dokumentasi***

## ***SOAL 3 (Fidel)***
Shall Leglerg🥶 dan Carloss Signs 😎 adalah seorang pembalap F1 untuk tim Ferrari 🥵. Mobil F1 memiliki banyak pengaturan, seperti penghematan ERS, Fuel, Tire Wear dan lainnya. Pada minggu ini ada race di sirkuit Silverstone. Malangnya, seluruh tim Ferrari diracun oleh Super Max Max pada hari sabtu sehingga seluruh kru tim Ferrari tidak bisa membantu Shall Leglerg🥶 dan Carloss Signs 😎 dalam race. Namun, kru Ferrari telah menyiapkan program yang bisa membantu mereka dalam menyelesaikan race secara optimal. Program yang dibuat bisa mengatur pengaturan - pengaturan dalam mobil F1 yang digunakan dalam balapan. Programnya ber ketentuan sebagai berikut:

a. Pada program **actions.c**, program akan berisi function function yang bisa di call oleh **paddock.c**

b. Action berisikan sebagai berikut:
```
- Gap [Jarak dengan driver di depan (float)]: Jika Jarak antara Driver dengan Musuh di depan adalah < 3.5s maka return Gogogo, jika jarak > 3.5s dan 10s return Push, dan jika jarak > 10s maka return Stay out of trouble.
- Fuel [Sisa Bensin% (string/int/float)]: Jika bensin lebih dari 80% maka return Push Push Push, jika bensin di antara 50% dan 80% maka return You can go, dan jika bensin kurang dari 50% return Conserve Fuel.
- Tire [Sisa Ban (int)]: Jika pemakaian ban lebih dari 80 maka return Go Push Go Push, jika pemakaian ban diantara 50 dan 80 return Good Tire Wear, jika pemakaian di antara 30 dan 50 return Conserve Your Tire, dan jika pemakaian ban kurang dari 30 maka return Box Box Box.
- Tire Change [Tipe ban saat ini (string)]: Jika tipe ban adalah Soft return Mediums Ready, dan jika tipe ban Medium return Box for Softs.
```
```
Contoh:
[Driver] : [Fuel] [55%]
[Paddock]: [You can go]
```
c. Pada **paddock.c** program berjalan secara daemon di background, bisa terhubung dengan **driver.c** melalui socket RPC.

d. Program **paddock.c** dapat call function yang berada di dalam actions.c.

e. Program **paddock.c** tidak keluar/terminate saat terjadi error dan akan log semua percakapan antara **paddock.c** dan **driver.c** di dalam file **race.log**
```
Format log:
[Source] [DD/MM/YY hh:mm:ss]: [Command] [Additional-info]
```
```
ex :
[Driver] [07/04/2024 08:34:50]: [Fuel] [55%]
[Paddock] [07/04/2024 08:34:51]: [Fuel] [You can go]
```
f. Program **driver.c** bisa terhubung dengan **paddock.c** dan bisa mengirimkan pesan dan menerima pesan serta menampilan pesan tersebut dari **paddock.c** sesuai dengan perintah atau function call yang diberikan.

**g. Jika bisa digunakan antar device/os (non local) akan diberi nilai tambahan.**

h. untuk mengaktifkan RPC call dari **driver.c**, bisa digunakan in-program CLI atau Argv (bebas) yang penting bisa send command seperti poin **B** dan menampilkan balasan dari **paddock.c**
```		
ex:
Argv: 
     ./driver -c Fuel -i 55% 
in-program CLI:
     Command: Fuel
     Info: 55%
```
Contoh direktori 😶‍🌫️:
```
.		.
├── client
│   └── driver.c
└── server
    ├── actions.c
    ├── paddock.c
    └── race.log
```
## ***PENGERJAAN***
### a. actions.c
```
//Fungsi actions.c yang nanti akan dipanggil Paddock.c
#include <stdio.h>
#include <string.h>

char* gap(float distance) {
    if (distance < 3.5)
        return "Gogogo";
    else if (distance >= 3.5 && distance <= 10)
        return "Push";
    else
        return "Stay out of trouble";
}

char* fuel(int fuel_percent) {
    if (fuel_percent > 80)
        return "Push Push Push";
    else if (fuel_percent >= 50 && fuel_percent <= 80)
        return "You can go";
    else
        return "Conserve Fuel";
}

char* tire(int tire_usage) {
    if (tire_usage > 80)
        return "Go Push Go Push";
    else if (tire_usage >= 50 && tire_usage <= 80)
        return "Good Tire Wear";
    else if (tire_usage >= 30 && tire_usage < 50)
        return "Conserve Your Tire";
    else
        return "Box Box Box";
}

char* tire_change(char* current_tire) {
    if (strcmp(current_tire, "Soft") == 0)
        return "Mediums Ready";
    else if (strcmp(current_tire, "Medium") == 0)
        return "Box for Softs";
    else
        return "Invalid tire type";
}
```
### b. driver.c 
```
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
```
### c. paddock.c 
```
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
```
## ***PENJELASAN PENGERJAAN***
## ***Dokumentasi***

## ***SOAL 4 (Abhinaya)***
## ***PENGERJAAN***
## ***PENJELASAN PENGERJAAN***
## ***Dokumentasi***


