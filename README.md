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
## ***PENGERJAAN***
## ***PENJELASAN PENGERJAAN***
## ***Dokumentasi***

## ***SOAL 4 (Abhinaya)***
## ***PENGERJAAN***
## ***PENJELASAN PENGERJAAN***
## ***Dokumentasi***


