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
## ***PENJELASAN PENGERJAAN***
## ***Dokumentasi***

## ***SOAL 4 (Abhinaya)***
## ***PENGERJAAN***
## ***PENJELASAN PENGERJAAN***
## ***Dokumentasi***


