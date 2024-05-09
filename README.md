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
## Library
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

```
- <stdio.h>: fungsi-fungsi input-output c.

- <stdlib.h>: fungsi-fungsi dasar seperti alokasi memori, konversi angka, dan fungsi pengaturan lingkungan.

- <unistd.h>: fungsi-fungsi untuk berinteraksi dengan sistem operasi, termasuk fungsi fork() dan pipe().

- <sys/wait.h>: fungsi-fungsi untuk menangani proses anak.

- <string.h>: fungsi-fungsi untuk manipulasi string, seperti strcmp() dan strcpy().

- <ctype.h>: fungsi-fungsi untuk operasi karakter seperti toupper().

- <errno.h>: definisi variabel errno yang menyimpan kode kesalahan terakhir.

- <time.h>: fungsi-fungsi untuk manipulasi waktu.

- <math.h>: fungsi-fungsi matematika

## char *intToWords(int num)
```
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
```
1. Deklarasi Array:

- Fungsi intToWords dimulai dengan mendeklarasikan tiga array konstan: satuan, belasan, dan puluh. Array ini digunakan untuk menyimpan kata-kata yang mewakili angka dalam bahasa Indonesia.

2. Pengalokasian Memori:

- Fungsi malloc digunakan untuk mengalokasikan memori untuk string result, yang akan menampung hasil konversi angka ke kata-kata.

- Ukuran memori yang dialokasikan adalah 100 * ukuran char, yang cukup untuk menampung hasil konversi maksimum.

3. Inisialisasi String Kosong:

- String result diinisialisasi dengan string kosong menggunakan strcpy(result, ""). Hal ini dilakukan untuk memastikan bahwa result kosong sebelum dimulainya konversi.

4. Konversi Ratusan:

- Jika angka lebih besar dari atau sama dengan 100, maka bagian ratusannya akan dikonversi terlebih dahulu.

- Kata yang mewakili bagian ratusan diambil dari array satuan, kemudian ditambahkan dengan kata "ratus".

- Nilai num kemudian di-modulus dengan 100 untuk mendapatkan sisa angka setelah bagian ratusan dihilangkan.

5. Konversi Puluhan:

- Jika angka yang tersisa masih lebih besar dari atau sama dengan 20, maka bagian puluhannya akan dikonversi.

- Kata yang mewakili bagian puluhan diambil dari array puluh.

- Sama seperti sebelumnya, nilai num kemudian di-modulus dengan 10 untuk mendapatkan sisa angka setelah bagian puluhan dihilangkan.

6. Konversi Belasan:

- Jika angka yang tersisa berada dalam rentang 11-19, maka angka tersebut akan dikonversi menjadi bentuk "belasan".

- Kata yang mewakili bagian belasan diambil dari array belasan.

7. Konversi Satuan:

- Jika angka yang tersisa berada dalam rentang 1-9 (setelah bagian ratusan dan puluhan dihilangkan), maka angka tersebut akan dikonversi menjadi bentuk "satuan".

- Kata yang mewakili bagian satuan diambil dari array satuan.

8. Pengembalian Hasil:

- Hasil konversi disimpan dalam string result.

- String result kemudian dikembalikan sebagai hasil fungsi.

## void writeToLog(const char *operation, int num1, int num2, int result)
```
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
```
1. Membuka File Log:

- Fungsi fopen digunakan untuk membuka file "histori.log" dalam mode append ("a"), yang berarti data baru akan ditambahkan ke akhir file tanpa menghapus yang sudah ada.

2. Pengecekan Ketersediaan File:

- Dilakukan pengecekan apakah file log berhasil dibuka atau tidak. Jika file log berhasil dibuka (logFile != NULL), maka operasi akan dilanjutkan.

3. Mengambil Waktu Sekarang:

- Fungsi time digunakan untuk mengambil waktu sistem saat ini dalam bentuk waktu mentah (rawtime).

- Waktu mentah kemudian diubah menjadi struktur waktu (struct tm) menggunakan fungsi localtime.

- Informasi waktu kemudian diformat sesuai dengan format yang ditentukan ("[%d/%m/%y %H:%M:%S]") menggunakan fungsi strftime.

4. Konversi Operasi menjadi Uppercase:

- Setiap karakter dalam string operation diubah menjadi huruf kapital menggunakan fungsi toupper, dan hasilnya disimpan dalam array upperOperation. Hal ini dilakukan agar operasi yang dicatat dalam log berada dalam format huruf kapital.

5. Penulisan Pesan Log:

- Jika result kurang dari 0 (negatif), maka pesan log akan mencatat pesan error dengan format yang sesuai.

- Jika result tidak negatif, maka pesan log akan mencatat operasi matematika beserta hasilnya dalam format yang sesuai.

- Untuk merepresentasikan angka dalam kata-kata, fungsi intToWords digunakan untuk mengonversi num1, num2, dan result menjadi bentuk kata-kata yang sesuai.

- Pesan log yang terbentuk akan ditulis ke file log menggunakan fungsi fprintf.

6. Menutup File Log:

- Setelah selesai menulis pesan log, file log ditutup menggunakan fungsi fclose

## int stringToNumber(char *str) 
```
int stringToNumber(char *str) {
    const char *words[] = {"", "satu", "dua", "tiga", "empat", "lima", "enam", "tujuh", "delapan", "sembilan"};
    for (int i = 1; i <= 9; i++) {
    if (strcmp(str, words[i]) == 0) {
return i;
        }
    }
return 0;
}
```
1. Deklarasi Variabel:

- Variabel words merupakan array konstan yang berisi representasi string dari angka 1 hingga 9 dalam bahasa Indonesia.

2. Iterasi Melalui Array:
   
- Fungsi ini melakukan iterasi melalui array words untuk mencocokkan string input str dengan setiap elemen array.

4. Pengecekan Kesamaan:

- Setiap elemen array words dibandingkan dengan string input str menggunakan fungsi strcmp.

- Jika terdapat kecocokan antara string input str dengan salah satu elemen array, maka fungsi akan mengembalikan nilai integer yang sesuai dengan indeks elemen tersebut (nilai dari 1 hingga 9).

4. Penanganan String Tidak Valid:

- Jika tidak ada kecocokan yang ditemukan, maka fungsi akan mengembalikan nilai 0, menandakan bahwa string input tidak valid atau tidak cocok dengan representasi angka dalam bahasa Indonesia.

## int main(int argc, char *argv[]) 
```
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
1. Input Operasi dan Operand:

- Program memeriksa apakah jumlah argumen command-line sesuai. Jika tidak, program mencetak pesan penggunaan yang benar.

- Operasi matematika (tambah, kurang, kali, bagi) disediakan sebagai argumen command-line.

2. Input Angka:

- Pengguna diminta untuk memasukkan dua angka secara berurutan.

3. Konversi Angka ke Integer:

- Angka yang dimasukkan oleh pengguna dikonversi menjadi integer menggunakan fungsi stringToNumber.

4. Pembuatan Pipe dan Fork:

- Pipe dibuat untuk komunikasi antara proses induk dan anak.

- Proses anak dibuat menggunakan fork().

5. Child Process:

- Proses anak menutup ujung penulisan pipe, membaca hasil operasi dari pipe, dan menampilkan hasilnya di terminal.

- Hasil operasi ditulis ke file log menggunakan fungsi writeToLog.

6. Parent Process:

- Proses induk menutup ujung pembacaan pipe, melakukan operasi aritmatika, menulis hasilnya ke pipe, dan menunggu proses anak selesai.

## ***Dokumentasi***
![Cuplikan layar 2024-05-08 215449](https://github.com/Rafjonath/Sisop-3-2024-MH-IT26/assets/150430084/0b6678a2-de3f-4fa9-8f86-a6375c4a9a92)
![Cuplikan layar 2024-05-08 215511](https://github.com/Rafjonath/Sisop-3-2024-MH-IT26/assets/150430084/a985d66e-b588-45b1-b785-dcc48d79afec)


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
## Actions.c
```
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
1. gap(float distance): Fungsi ini mengambil jarak sebagai argumen dan memberikan rekomendasi berdasarkan jarak tersebut. Jika jarak kurang dari 3,5, pengemudi disarankan untuk 'Gogogo'. Jika jarak antara 3,5 dan 10, pengemudi disarankan untuk 'Push'. Jika jarak lebih dari 10, pengemudi disarankan untuk 'Stay out of trouble'.

2. fuel(int fuel_percent): Fungsi ini mengambil persentase bahan bakar sebagai argumen dan memberikan rekomendasi berdasarkan tingkat bahan bakar tersebut. Jika bahan bakar lebih dari 80%, pengemudi disarankan untuk 'Push Push Push'. Jika bahan bakar antara 50% dan 80%, pengemudi disarankan untuk 'You can go'. Jika bahan bakar kurang dari 50%, pengemudi disarankan untuk 'Conserve Fuel'.

3. tire(int tire_usage): Fungsi ini mengambil persentase penggunaan ban sebagai argumen dan memberikan rekomendasi berdasarkan kondisi ban tersebut. Jika penggunaan ban lebih dari 80%, pengemudi disarankan untuk 'Go Push Go Push'. Jika penggunaan ban antara 50% dan 80%, pengemudi disarankan untuk 'Good Tire Wear'. Jika penggunaan ban antara 30% dan 50%, pengemudi disarankan untuk 'Conserve Your Tire'. Jika penggunaan ban kurang dari 30%, pengemudi disarankan untuk 'Box Box Box'.

4. tire_change(char* current_tire): Fungsi ini mengambil jenis ban saat ini sebagai argumen dan memberikan rekomendasi tentang pergantian ban. Jika jenis ban saat ini adalah 'Soft', pengemudi disarankan untuk 'Mediums Ready'. Jika jenis ban saat ini adalah 'Medium', pengemudi disarankan untuk 'Box for Softs'. Jika jenis ban saat ini tidak valid, fungsi akan mengembalikan 'Invalid tire type'.

Fungsi diatas akan dipanggil oleh paddock.c untuk melengkapi proses pada paddock.c

## Paddock.c
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
1. Library

- #include <stdio.h> = fungsi-fungsi input-output c.

- #include <stdlib.h> = fungsi-fungsi dasar seperti alokasi memori

- #include <unistd.h> = fungsi-fungsi untuk berinteraksi dengan sistem operasi, termasuk fungsi fork() dan pipe().

- #include <string.h> = fungsi-fungsi untuk manipulasi string, seperti strcmp() dan strcpy().

- #include <time.h> = fungsi-fungsi untuk manipulasi waktu.

- #include <sys/types.h> = definisi tipe data dasar yang digunakan dalam pemrograman sistem.

- #include <sys/socket.h> = deklarasi fungsi, struktur data, dan konstanta yang digunakan untuk membuat dan mengelola socket.

- #include <netinet/in.h> = deklarasi struktur data dan konstanta yang digunakan untuk menangani alamat Internet (IPv4 dan IPv6).

- #include "actions.c" = Panggil Fungsi Actions.c lewat library

2.Define
#define PORT 8080:

- Ini mendefinisikan konstanta PORT dengan nilai 8080 dan konstanta ini digunakan untuk menentukan nomor port yang akan digunakan oleh server untuk menerima koneksi dari klien.

#define MAX_COMMAND_SIZE 100:

- Ini mendefinisikan konstanta MAX_COMMAND_SIZE dengan nilai 100.

- Konstanta ini digunakan untuk menentukan ukuran maksimum pesan yang dapat diterima oleh server dari klien.

- Penggunaan konstanta ini memungkinkan program untuk mengalokasikan memori dengan benar saat menerima atau memproses pesan dari klien.**

3. void log_message(char *source, char *command, char *info)

Fungsi ini digunakan untuk menulis pesan log ke file "race.log". Pesan log ini berisi informasi tentang sumber pesan (source), waktu pesan (timestamp), jenis perintah (command), dan informasi tambahan (info). Fungsi ini menggunakan fungsi time() dan localtime() dari library time.h untuk mendapatkan waktu lokal dan fprintf() untuk menulis pesan ke file.

4. void handle_rpc_call(int new_socket)

Fungsi ini merupakan inti dari server. Ini menerima permintaan dari klien melalui socket, memproses permintaan tersebut, dan mengirimkan respons kembali ke klien. Beberapa langkah yang dilakukan adalah:

- Membaca pesan dari socket klien ke dalam buffer.

- Mem-parse pesan menjadi jenis perintah (command) dan informasi tambahan (info).

- Berdasarkan jenis perintah, fungsi memanggil fungsi yang sesuai dari file "actions.c" (yang diimpor melalui preprocessor directive) untuk memproses informasi tambahan.

- Menyiapkan respons berdasarkan hasil pemrosesan dan menulisnya kembali ke socket klien.

- Mencatat pesan log untuk kedua sumber pesan (driver dan paddock).

- Mencetak respons ke konsol untuk melacak aktivitas server.

5. int main ()

Fungsi main adalah titik masuk utama program. Pada fungsi ini:

- Socket server dibuat menggunakan socket() dan dikonfigurasi untuk mendengarkan koneksi di PORT yang ditentukan.

- Loop tak terbatas dimulai, dimana server terus menerima koneksi baru dari klien menggunakan accept().

- Setiap koneksi baru dihandle menggunakan fungsi handle_rpc_call.

- Setelah selesai menangani koneksi, socket baru ditutup dengan close().

## Driver.c
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
1.Library dan  Define

Untuk library dan define sama seperti pada **paddock.c**

2.void send_rpc_command(char* command, char* info)

Fungsi ini digunakan untuk mengirimkan permintaan RPC ke server. Beberapa langkah yang dilakukan adalah:

- Membuat socket menggunakan socket() untuk menghubungkan klien ke server.

- Mengatur alamat server dan port yang dituju menggunakan struct sockaddr_in.

- Menghubungkan klien ke server menggunakan connect().

- Membuat pesan RPC berdasarkan perintah dan informasi yang diberikan oleh pengguna.

- Mengirimkan pesan ke server menggunakan send().

- Menerima respons dari server menggunakan read().

- Mencetak pesan respons ke konsol untuk memantau aktivitas klien.

3. int main()

Fungsi main adalah titik masuk utama program. Pada fungsi ini:

- Dilakukan pemeriksaan terhadap argumen yang diberikan saat menjalankan program.

- Jika argumen tidak sesuai, program mencetak pesan penggunaan dan keluar dengan kode kesalahan.

- Jika argumen sesuai, perintah dan informasi dari argumen digunakan untuk memanggil fungsi send_rpc_command.

## ***Dokumentasi***
![Cuplikan layar 2024-05-08 221153](https://github.com/Rafjonath/Sisop-3-2024-MH-IT26/assets/150430084/f37a053a-9033-4286-a8d7-87a77ed8ea11)
![Cuplikan layar 2024-05-08 221252](https://github.com/Rafjonath/Sisop-3-2024-MH-IT26/assets/150430084/40c6c69f-dd14-4394-adb8-d59128a79611)
![Cuplikan layar 2024-05-08 221343](https://github.com/Rafjonath/Sisop-3-2024-MH-IT26/assets/150430084/395754b5-09b1-4c80-a868-48839c34b505)
![Cuplikan layar 2024-05-08 221402](https://github.com/Rafjonath/Sisop-3-2024-MH-IT26/assets/150430084/0e9bf9eb-09ee-4c05-80f0-6b018dc00db7)



## ***SOAL 4 (Abhinaya)***
## ***PENGERJAAN***
## ***PENJELASAN PENGERJAAN***
## ***Dokumentasi***


