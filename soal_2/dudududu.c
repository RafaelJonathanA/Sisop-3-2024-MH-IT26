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
