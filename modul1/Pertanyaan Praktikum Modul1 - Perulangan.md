# Praktikum Sistem Tertanam  
## Modul 1: Perulangan 

### Pertanyaan Praktikum
1. Gambarkan rangkaian schematic 5 LED running yang digunakan pada percobaan! <br>
2. Jelaskan bagaimana program membuat efek LED berjalan dari kiri ke kanan!<br>
3. Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri!<br>
4. Buatkan program agar LED menyala tiga LED kanan dan tiga LED kiri secara bergantian
dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!

## Jawaban Pertanyaan Praktikum

### 1. Skematik LED Running
Rangkaian terdiri dari **5 LED** yang terhubung ke pin digital Arduino secara berurutan 



Setiap LED:
- Terhubung ke pin digital Arduino
- Menggunakan resistor sebagai pembatas arus
- Terhubung ke GND

### 2. LED Bergerak dari Kiri ke Kanan

Program menggunakan perulangan `for` dengan **increment (++)**:

```cpp
for (int ledPin = 2; ledPin < 9; ledPin++) {
  digitalWrite(ledPin, HIGH);
  delay(timer);
  digitalWrite(ledPin, LOW);
}
````

**Penjelasan:**

* Perulangan dimulai dari pin kecil (2)
* LED dinyalakan satu per satu
* Setelah menyala sebentar, LED dimatikan
* Nilai pin bertambah (`ledPin++`)

Karena urutan pin mengikuti posisi LED di breadboard, hasilnya terlihat seperti cahaya yang bergerak ke kanan.

### 3. LED Bergerak dari Kanan ke Kiri

Program menggunakan perulangan `for` dengan **decrement (--)**:

```cpp
for (int ledPin = 8; ledPin >= 2; ledPin--) {
  digitalWrite(ledPin, HIGH);
  delay(timer);
  digitalWrite(ledPin, LOW);
}
```

**Penjelasan:**

* Perulangan dimulai dari pin terbesar (8)
* LED menyala dari kanan ke kiri
* Nilai pin dikurangi (`ledPin--`)

Efeknya kebalikan dari sebelumnya, jadi LED terlihat balik arah.

## Program Tambahan

### Mode: 3 LED Kiri vs 3 LED Kanan (Bergantian)

Program ini membagi LED menjadi dua kelompok:

* **Kiri:** Pin 2, 3, 4
* **Kanan:** Pin 5, 6, 7

LED akan menyala secara bergantian antar grup.

### Source Code

```cpp
int timer = 500; // Delay 500 ms

void setup() {
  // Inisialisasi semua pin LED sebagai output
  for (int pin = 2; pin <= 7; pin++) {
    pinMode(pin, OUTPUT);
  }
}

void loop() {

  // --- Kondisi 1: LED kiri nyala ---
  for (int i = 2; i <= 4; i++) {
    digitalWrite(i, HIGH);
  }

  for (int i = 5; i <= 7; i++) {
    digitalWrite(i, LOW);
  }

  delay(timer);

  // --- Kondisi 2: LED kanan nyala ---
  for (int i = 2; i <= 4; i++) {
    digitalWrite(i, LOW);
  }

  for (int i = 5; i <= 7; i++) {
    digitalWrite(i, HIGH);
  }

  delay(timer);
}
```

## Penjelasan Singkat

* **Variabel `timer`**
  Mengatur kecepatan perpindahan LED.

* **Fungsi `setup()`**
  Menentukan semua pin sebagai output supaya bisa mengontrol LED.

* **Fungsi `loop()`**
  Berisi logika utama yang terus berulang.

* **Perulangan `for`**
  Digunakan untuk menyalakan/mematikan LED secara berurutan tanpa nulis kode satu-satu.

* **Konsep bergantian**
  Saat grup kiri aktif → grup kanan mati
  Saat grup kanan aktif → grup kiri mati

## Kesimpulan

1. Perulangan (`for`) sangat membantu dalam mengontrol banyak LED dengan kode yang lebih ringkas.
2. Increment dan decrement menentukan arah gerakan LED.
3. Pembagian grup LED memungkinkan variasi efek seperti nyala bergantian.
4. Delay berfungsi sebagai pengatur kecepatan visual LED.

```
