#  Praktikum Sistem Tertanam  
# Modul III: Protokol Komunikasi

# Pertanyaan Praktikum

1. Jelaskan bagaimana cara kerja komunikasi I2C antara Arduino dan LCD pada rangkaian  tersebut! 
2. Apakah pin potensiometer harus seperti itu? Jelaskan yang terjadi apabila pin kiri dan pin kanan tertukar! 
3) Modifikasi program dengan menggabungkan antara UART dan I2C (keduanya sebagai output) sehingga: 
Data tidak hanya ditampilkan di LCD tetapi juga di Serial Monitor 
| ADC:0 | Volt: 0.00 V | Persen: 0%|
|ADC: 0  0% | setCursor(0, 0) dan Bar (level) | setCursor(0, 1)
Berikan penjelasan disetiap baris kode nya dalam bentuk README.md! 
4. Lengkapi table berikut berdasarkan pengamatan pada Serial Monitor
| ADC     | Volt(V) | Persen (%)|
|---------|---------|-----------|
| 1       | Isi B   | Isi C     |
| 21      | Isi E   | Isi F     |
| 49      | Isi E   | Isi F     |
| 74      | Isi E   | Isi F     |
| 96      | Isi E   | Isi       |

# Jawaban Pertanyaan Praktikum

# 1. Cara Kerja Komunikasi I2C antara Arduino dan LCD
Komunikasi ini bekerja menggunakan prinsip Master-Slave melalui dua jalur kabel utama: SDA (Serial Data) untuk pengiriman data dan SCL (Serial Clock) untuk sinkronisasi waktu.
- Peran Perangkat: Arduino Uno bertindak sebagai Master yang mengendalikan bus, sementara LCD bertindak sebagai Slave yang menerima instruksi.
- Proses: Arduino mengirimkan sinyal "Start" diikuti dengan I2C Address unik (misalnya 0x27) milik LCD agar perangkat lain di jalur yang sama tidak ikut merespons.
- Wiring: Data bit dikirimkan secara serial melalui pin A4 (SDA) dan A5 (SCL) pada Arduino Uno ke modul backpack I2C pada LCD.

# 2. Konfigurasi Pin Potensiometer
- Pin potensiometer tidak harus selalu seperti itu, namun urutan standarnya adalah kaki pinggir ke VCC/GND dan kaki tengah ke input analog (A0) .
- Jika pin kiri dan kanan tertukar: Potensiometer tetap akan bekerja sebagai pembagi tegangan (voltage divider), namun logika pembacaannya akan terbalik.
Dampaknya: Jika sebelumnya memutar ke kanan (searah jarum jam) meningkatkan nilai ADC, setelah ditukar, memutar ke kanan justru akan memperkecl nilai ADC karena tegangan yang masuk ke kaki tengah bergeser ke arah GND, bukan 5V.

# 3. Modifikasi Program (UART + I2C)
```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int pinPot = A0;

void setup() {
  Serial.begin(9600); // Inisialisasi UART
  lcd.init();         // Inisialisasi I2C
  lcd.backlight();
}

void loop() {
  int adcVal = analogRead(pinPot);
  
  // Kalkulasi data
  float volt = (adcVal / 1023.0) * 5.0;
  int persen = map(adcVal, 0, 1023, 0, 100);
  int panjangBar = map(adcVal, 0, 1023, 0, 16);

  // OUTPUT 1: Serial Monitor (UART)
  Serial.print("ADC: "); Serial.print(adcVal);
  Serial.print(" | Volt: "); Serial.print(volt); Serial.print(" V");
  Serial.print(" | Persen: "); Serial.print(persen); Serial.println("%");

  // OUTPUT 2: LCD (I2C)
  // Baris 1: Nilai ADC dan Persentase
  lcd.setCursor(0, 0);
  lcd.print("ADC:"); lcd.print(adcVal);
  lcd.setCursor(8, 0); // Pindah posisi agar rapi
  lcd.print(persen); lcd.print("%   "); // Clear sisa karakter

  // Baris 2: Visualisasi Bar (Level)
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    if (i < panjangBar) lcd.print((char)255); // Karakter blok penuh
    else lcd.print(" ");
  }

  delay(250); // Jeda pembacaan
}
```
Penjelasan Program (README.md):
- float volt: Menghitung tegangan dengan membagi nilai ADC terhadap resolusi 10-bit (1023) dikali tegangan referensi 5V.
- map(..., 0, 100): Mengonversi rentang pembacaan analog menjadi skala persentase.
- Serial.print: Mengirimkan data gabungan ke komputer melalui protokol UART.
- lcd.setCursor: Mengatur posisi teks pada baris pertama (0) dan baris kedua (1) melalui protokol I2C.

# 4. Tabel Hasil Pengamatan
Berdasarkan rumus kalkulasi Volt = (ADC / 1023) \times x 5 dan Persen = (ADC / 1023) x 100,
berikut adalah datanya:
| ADC     | Volt(V) | Persen (%)|
|---------|---------|-----------|
| 1       |0.00 V   |0.10 %     |
| 21      |0.10 V   |2.05 %     |
| 49      |0.24 V   |4.79 %     |
| 74      |0.36 V   |7.23 %     |
| 96      |0.47 V   |9.38 %     |

Kesimpulan
- Komunikasi I2C mempermudah pengelolaan banyak perangkat output dengan meminimalisir penggunaan kabel melalui sistem pengalamatan (addressing).
- Penggabungan UART dan I2C dalam satu sistem sangat efektif untuk melakukan monitoring data secara real-time baik lewat terminal komputer maupun display fisik secara bersamaan.
- Ketepatan rumus konversi data analog ke besaran fisis (Volt/Persen) sangat menentukan akurasi informasi yang ditampilkan pada sistem tertanam.
