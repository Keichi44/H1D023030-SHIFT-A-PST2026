#  Praktikum Sistem Tertanam  
# Modul IV:   Analog to Digital Converter (ADC)

# Pertanyaan Praktikum 

1. Apa fungsi perintah analogRead() pada rangkaian praktikum ini? 
2. Mengapa diperlukan fungsi map() dalam program tersebut? 
3. Modifikasi program berikut agar servo hanya bergerak dalam rentang 30° hingga 150°, meskipun potensiometer tetap memiliki rentang ADC 0–1023. Jelaskan program pada file README.md

# Jawaban Pertanyaan Praktikum

# 1. Apa fungsi perintah `analogRead()` pada rangkaian praktikum ini?
- Fungsi `analogRead()` digunakan untuk membaca nilai tegangan analog dari potensiometer.
- Arduino Uno memiliki ADC (Analog to Digital Converter) 10-bit yang akan mengubah tegangan analog menjadi data digital dengan rentang:
  
```txt
0 - 1023
```
- Nilai tersebut nantinya digunakan untuk mengontrol sudut pergerakan motor servo.

# 2. Mengapa diperlukan fungsi `map()` dalam program tersebut?
- Fungsi `map()` digunakan untuk melakukan konversi rentang nilai.
- Nilai hasil ADC memiliki rentang:
  
```txt
0 - 1023
```
Sedangkan motor servo bergerak berdasarkan sudut:
```txt
0° - 180°
```
- Karena rentangnya berbeda, maka diperlukan fungsi `map()` agar nilai ADC dapat diterjemahkan menjadi sudut servo secara proporsional.
Contoh:

```cpp
map(val, 0, 1023, 0, 180);
```
Artinya:
- ADC `0` menjadi sudut `0°`
- ADC `1023` menjadi sudut `180°`

# 3. Modifikasi Program Servo (30° - 150°)
# File Program: `modul4_adc.ino`

```cpp
#include <Servo.h> // Library untuk servo motor
Servo myservo; // Membuat objek servo
// ===================== PIN SETUP =====================
// Pin input analog dari potensiometer
const int potensioPin = A0;
// Pin PWM untuk servo
const int servoPin = 9;
// ===================== VARIABEL =====================
// Variabel sudut servo
int pos = 0;
// Variabel nilai ADC
int val = 0;
void setup() {
 // Menghubungkan servo ke pin PWM
  myservo.attach(servoPin);
  // Memulai komunikasi serial
  Serial.begin(9600);
}
void loop() {
  // ===================== PEMBACAAN ADC =====================
  // Membaca nilai analog dari potensiometer
  val = analogRead(potensioPin);
  // ===================== KONVERSI DATA =====================
  // Mengubah nilai ADC menjadi sudut servo
  // Rentang dimodifikasi dari 30° sampai 150°
  pos = map(val, 0, 1023, 30, 150);
  // ===================== OUTPUT SERVO =====================
  // Menggerakkan servo sesuai hasil mapping
  myservo.write(pos);
  // ===================== SERIAL MONITOR =====================
  // Menampilkan nilai ADC
  Serial.print("ADC Potensio: ");
  Serial.print(val);
  // Menampilkan sudut servo
  Serial.print(" | Sudut Servo: ");
  Serial.println(pos);
  // ===================== STABILISASI =====================
  // Delay agar pergerakan servo stabil
  delay(15);
}
```

# Penjelasan Program
- `#include <Servo.h>`  
  Digunakan untuk memanggil library servo agar Arduino dapat mengontrol motor servo.
- `Servo myservo`  
  Digunakan untuk membuat objek servo yang nantinya dipakai untuk mengendalikan motor servo.
- `analogRead()`  
  Digunakan untuk membaca nilai analog dari potensiometer dengan rentang nilai 0 sampai 1023.
- `map()`  
  Digunakan untuk mengubah nilai ADC menjadi sudut servo agar sesuai dengan rentang pergerakan yang diinginkan.
- `myservo.write()`  
  Digunakan untuk menggerakkan servo ke sudut tertentu sesuai hasil konversi data.
- `Serial.print()`  
  Digunakan untuk menampilkan data ADC dan sudut servo pada Serial Monitor.
- `delay(15)`  
  Digunakan untuk memberikan jeda singkat agar pergerakan servo lebih stabil dan tidak terlalu cepat.

# Penjelasan Modifikasi Program

## Modifikasi Rentang Sudut Servo
Pada program ini dilakukan modifikasi pada fungsi:

```cpp
map(val, 0, 1023, 30, 150);
```
Pada program normal:
```cpp
map(val, 0, 1023, 0, 180);
```
servo dapat bergerak penuh dari:
```txt
0° hingga 180°
```

Sedangkan pada program modifikasi:
- Nilai minimum ADC (`0`) menjadi sudut `30°`
- Nilai maksimum ADC (`1023`) menjadi sudut `150°`
Dengan demikian servo hanya bergerak pada rentang:

```txt
30° - 150°
```

# Kesimpulan 

Berdasarkan percobaan yang telah dilakukan, dapat disimpulkan bahwa:

1. Arduino Uno berhasil membaca nilai analog dari potensiometer menggunakan fitur ADC dengan rentang nilai 0-1023.

2. Fungsi `map()` digunakan untuk mengubah nilai ADC menjadi sudut pergerakan servo agar sesuai dengan kebutuhan sistem.

3. Motor servo dapat bergerak secara real-time mengikuti perubahan nilai dari potensiometer dengan baik.
