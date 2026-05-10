#  Praktikum Sistem Tertanam  
# Modul IV : Digital to Analog Converter (DAC) / PWM

# Pertanyaan Praktikum
1. Jelaskan mengapa LED dapat diatur kecerahannya menggunakan fungsi analogWrite()! 
2. Apa hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)? 
3. Modifikasilah program berikut agar LED hanya menyala pada rentang kecerahan sedang, yaitu hanya ketika nilai PWM berada pada rentang 50 sampai 200. Jelaskan program pada file README.md.

4. # Jawaban Pertanyaan Praktikum

# 1. Jelaskan mengapa LED dapat diatur kecerahannya menggunakan fungsi `analogWrite()`!

- Fungsi `analogWrite()` menggunakan teknik PWM (*Pulse Width Modulation*).
- PWM bekerja dengan cara menghidupkan dan mematikan pin digital dengan sangat cepat sehingga menghasilkan tegangan rata-rata tertentu.
Semakin besar nilai PWM:
- Semakin lama kondisi HIGH
- Semakin besar tegangan rata-rata
- Semakin terang LED menyala
Sebaliknya, semakin kecil nilai PWM maka LED akan terlihat lebih redup.

# 2. Apa hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)?
Nilai ADC memiliki resolusi 10-bit dengan rentang:

```txt
0 - 1023
```
Sedangkan PWM menggunakan resolusi 8-bit dengan rentang:

```txt
0 - 255
```
Karena rentangnya berbeda, maka nilai ADC perlu dikonversi menggunakan fungsi `map()` agar dapat digunakan sebagai nilai PWM secara proporsional.

# 3. Program Modifikasi PWM (50 - 200)

```cpp
#include <Arduino.h> // Library dasar Arduino
// ===================== PIN SETUP =====================
// Pin analog potensiometer
const int potPin = A0;
// Pin PWM LED
const int ledPin = 9;
// ===================== VARIABEL =====================
// Variabel pembacaan ADC
int nilaiADC = 0;
// Variabel output PWM
int pwm = 0;
void setup() {
  // Mengatur pin LED sebagai output
  pinMode(ledPin, OUTPUT);
  // Memulai komunikasi serial
  Serial.begin(9600);
}
void loop() {
  // ===================== PEMBACAAN ADC =====================
  // Membaca nilai analog dari potensiometer
  nilaiADC = analogRead(potPin);
  // ===================== KONVERSI DATA =====================
  // Mengubah nilai ADC menjadi PWM
  // Rentang PWM dibatasi dari 50 sampai 200
  pwm = map(nilaiADC, 0, 1023, 50, 200);
  // ===================== OUTPUT PWM =====================
  // Mengirim sinyal PWM ke LED
  analogWrite(ledPin, pwm);
  // ===================== SERIAL MONITOR =====================
  // Menampilkan nilai ADC
  Serial.print("ADC: ");
  Serial.print(nilaiADC);
  // Menampilkan nilai PWM
  Serial.print(" | PWM: ");
  Serial.println(pwm);
  // ===================== STABILISASI =====================
  // Delay agar pembacaan stabil
  delay(50);
}
```

# Penjelasan Program
- `#include <Arduino.h>`  
  Digunakan untuk memanggil library dasar Arduino.
- `analogRead()`  
  Digunakan untuk membaca nilai analog dari potensiometer dengan rentang 0-1023.
- `map()`  
  Digunakan untuk mengubah nilai ADC menjadi nilai PWM sesuai rentang yang dibutuhkan.
- `analogWrite()`  
  Digunakan untuk menghasilkan sinyal PWM pada pin output agar kecerahan LED dapat diatur.
- `Serial.print()`  
  Digunakan untuk menampilkan nilai ADC dan PWM pada Serial Monitor.
- `delay(50)`  
  Digunakan untuk memberikan jeda agar pembacaan data lebih stabil.
  
# Penjelasan Modifikasi Program

# Modifikasi Rentang Kecerahan LED (PWM 50 - 200)
Pada program ini dilakukan modifikasi pada fungsi:

```cpp
map(nilaiADC, 0, 1023, 50, 200);
```
Pada kondisi normal, PWM biasanya menggunakan rentang:

```cpp
0 - 255
```
Namun pada program ini rentang PWM dibatasi menjadi:

```txt
50 - 200
```
Artinya:
- Saat nilai ADC minimum (`0`), LED tetap menyala redup dengan PWM `50`
- Saat nilai ADC maksimum (`1023`), LED hanya mencapai PWM `200`

# Kesimpulan 
Berdasarkan percobaan yang telah dilakukan, dapat disimpulkan bahwa:
1. Teknik PWM dapat digunakan untuk mengatur tingkat kecerahan LED menggunakan sinyal digital.
2. Fungsi `analogWrite()` berhasil menghasilkan output PWM dengan rentang nilai 0-255.
3. Nilai ADC dari potensiometer dapat dikonversi menggunakan fungsi `map()` untuk mengontrol kecerahan LED secara real-time.
