#  Praktikum Sistem Tertanam  
# Modul V : Multitasking

# Pertanyaan Praktikum

1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya! 
2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya! 
3. Modifikasilah program dengan menambah sensor (misalnya potensiometer), lalu gunakan nilainya untuk mengontrol kecepatan LED! Bagaimana hasilnya? Jelaskan program pada file README.md.

# Jawaban Pertanyaan Praktikum

# 1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

- Ketiga task berjalan secara bergantian (*concurrent*), bukan benar-benar paralel.
- Arduino Uno menggunakan prosesor *single-core*, sehingga hanya dapat menjalankan satu instruksi pada satu waktu. FreeRTOS menggunakan *scheduler* untuk mengatur pergantian eksekusi setiap task menggunakan teknik *time slicing* atau *context switching*. Perpindahan antar task terjadi sangat cepat sehingga task terlihat berjalan secara bersamaan.

# 2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!
- Langkah-langkah menambahkan task keempat:
### a. Membuat deklarasi fungsi task

```cpp
void TaskKeempat(void *pvParameters);
```
### b. Menambahkan `xTaskCreate()` pada `setup()`

```cpp
xTaskCreate(
  TaskKeempat,
  "task4",
  128,
  NULL,
  1,
  NULL
);
```
### c. Membuat isi task

```cpp
void TaskKeempat(void *pvParameters) {

  while(1) {

    // Instruksi task

    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
```
- Task baru akan dijalankan oleh scheduler bersama task lainnya.

# 3. Modifikasi Program dengan Sensor Potensiometer
## File Program: `modul5_freertos.ino`

```cpp
#include <Arduino_FreeRTOS.h>
// ===================== DEKLARASI TASK =====================
void TaskBlink1(void *pvParameters);
void TaskBlink2(void *pvParameters);
void TaskBacaSensor(void *pvParameters);
// ===================== VARIABEL GLOBAL =====================
// Variabel delay dinamis
volatile int kecepatanDelay = 500;
void setup() {
  // Memulai serial monitor
  Serial.begin(9600);
  // ===================== MEMBUAT TASK =====================
  xTaskCreate(TaskBlink1, "TaskLED1", 128, NULL, 1, NULL);
  xTaskCreate(TaskBlink2, "TaskLED2", 128, NULL, 1, NULL);
  xTaskCreate(TaskBacaSensor, "TaskSensor", 128, NULL, 2, NULL);
  // ===================== MENJALANKAN SCHEDULER =====================
  vTaskStartScheduler();
}
void loop() {
  // Kosong karena menggunakan scheduler FreeRTOS
}
// ===================== TASK SENSOR =====================
void TaskBacaSensor(void *pvParameters) {
  pinMode(A0, INPUT);
  while(1) {
    // Membaca nilai potensiometer
    int nilaiSensor = analogRead(A0);
    // Mengubah nilai ADC menjadi delay
    kecepatanDelay = map(nilaiSensor, 0, 1023, 50, 1000);
    // Delay task sensor
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

// ===================== TASK LED 1 =====================
void TaskBlink1(void *pvParameters) {
  pinMode(8, OUTPUT);
  while(1) {
    digitalWrite(8, HIGH);
    vTaskDelay(kecepatanDelay / portTICK_PERIOD_MS);
    digitalWrite(8, LOW);
    vTaskDelay(kecepatanDelay / portTICK_PERIOD_MS);
  }
}
// ===================== TASK LED 2 =====================
void TaskBlink2(void *pvParameters) {
  pinMode(7, OUTPUT);
  while(1) {
    digitalWrite(7, HIGH);
    vTaskDelay(kecepatanDelay / portTICK_PERIOD_MS);
    digitalWrite(7, LOW);
    vTaskDelay(kecepatanDelay / portTICK_PERIOD_MS);
  }
}
```
# Penjelasan Program
- `#include <Arduino_FreeRTOS.h>`  
  Digunakan untuk memanggil library FreeRTOS pada Arduino.
- `xTaskCreate()`  
  Digunakan untuk membuat task baru pada sistem FreeRTOS.
- `vTaskStartScheduler()`  
  Digunakan untuk menjalankan scheduler FreeRTOS.
- `analogRead()`  
  Digunakan untuk membaca nilai analog dari potensiometer.
- `map()`  
  Digunakan untuk mengubah nilai ADC menjadi nilai delay.
- `vTaskDelay()`  
  Digunakan untuk memberikan jeda pada task tanpa menghentikan task lain.
- `digitalWrite()`  
  Digunakan untuk mengontrol LED.

# Penjelasan Modifikasi Program
- Program dimodifikasi dengan menambahkan task pembacaan sensor menggunakan potensiometer pada pin A0.
- Task `TaskBacaSensor` bertugas membaca nilai analog dari potensiometer kemudian mengubahnya menjadi nilai delay menggunakan fungsi `map()`.
- Nilai delay tersebut disimpan pada variabel global `kecepatanDelay` yang digunakan oleh `TaskBlink1` dan `TaskBlink2`.
Akibatnya:
- Jika potensiometer diputar kecil, LED berkedip lebih cepat
- Jika potensiometer diputar besar, LED berkedip lebih lambat

# Kesimpulan
Berdasarkan percobaan yang telah dilakukan, dapat disimpulkan bahwa:
1. FreeRTOS memungkinkan beberapa task berjalan secara concurrent menggunakan scheduler.
2. Task dapat dibuat dan dijalankan secara terpisah menggunakan `xTaskCreate()`.
3. Pembacaan sensor dan kontrol LED dapat berjalan secara real-time tanpa saling menghambat menggunakan konsep multitasking.
