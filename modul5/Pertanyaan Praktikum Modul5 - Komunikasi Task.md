#  Praktikum Sistem Tertanam  
# Modul V : Komunikasi Task

# Pertanyaan Praktikum

1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya! 
2. Apakah program ini berpotensi mengalami race condition? Jelaskan! 
3. Modifikasilah program dengan menggunakan sensor DHT sesungguhnya sehingga informasi yang ditampilkan dinamis. Bagaimana hasilnya? Jelaskan program pada file README.md.

# Jawaban Pertanyaan Praktikum

# 1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!
Kedua task berjalan secara bergantian (*concurrent*), bukan benar-benar paralel.
Arduino Uno menggunakan prosesor *single-core* sehingga instruksi hanya dapat dijalankan satu per satu. FreeRTOS menggunakan *scheduler* untuk mengatur pergantian eksekusi antar task.
Pada program ini:
- Task `read_data` mengirim data ke Queue
- Task `display` menunggu data masuk menggunakan `xQueueReceive()`
Ketika Queue terisi, scheduler akan menjalankan task `display` untuk menampilkan data, kemudian task kembali ke kondisi menunggu (*blocked state*).
Pergantian task yang sangat cepat membuat kedua task terlihat berjalan bersamaan.

# 2. Apakah program ini berpotensi mengalami race condition? Jelaskan!
Program ini tidak berpotensi mengalami *race condition* pada proses pengiriman data.
Hal ini karena komunikasi antar task menggunakan fitur Queue bawaan FreeRTOS:
- `xQueueCreate()`
- `xQueueSend()`
- `xQueueReceive()`
Queue pada FreeRTOS bersifat *thread-safe*, sehingga proses pengiriman dan pengambilan data diatur langsung oleh kernel RTOS agar tidak saling bertabrakan.
Dengan demikian:
- Data lebih aman
- Tidak terjadi konflik akses memori
- Data tidak mudah corrupt

# 3. Modifikasi Program Menggunakan Sensor DHT
# File Program: `modul5_queue_dht.ino`

```cpp
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include "DHT.h"
// ===================== KONFIGURASI SENSOR =====================
#define DHTPIN 2
#define DHTTYPE DHT11
// Inisialisasi sensor DHT
DHT dht(DHTPIN, DHTTYPE);
// ===================== STRUCT DATA =====================
struct readings {
  float temp;
  float h;
};
// ===================== QUEUE =====================
QueueHandle_t my_queue;
// ===================== DEKLARASI TASK =====================
void read_data(void *pvParameters);
void display(void *pvParameters);
void setup() {
  // Memulai serial monitor
  Serial.begin(9600);
  // Memulai sensor DHT
  dht.begin();
  // Membuat queue
  my_queue = xQueueCreate(1, sizeof(struct readings));
  // ===================== MEMBUAT TASK =====================
  xTaskCreate(read_data, "read sensors", 128, NULL, 1, NULL);
  xTaskCreate(display, "display", 128, NULL, 1, NULL);
  // ===================== MENJALANKAN SCHEDULER =====================
  vTaskStartScheduler();
}
void loop() {
  // Kosong karena menggunakan FreeRTOS
}
// ===================== TASK PEMBACA SENSOR =====================
void read_data(void *pvParameters) {
  struct readings x;
  for(;;) {
    // Membaca suhu
    x.temp = dht.readTemperature();
    // Membaca kelembapan
    x.h = dht.readHumidity();
    // Validasi sensor
    if (isnan(x.temp) || isnan(x.h)) {
      Serial.println("Gagal membaca sensor DHT!");
    } else {
      // Mengirim data ke queue
      xQueueSend(my_queue, &x, portMAX_DELAY);
    }
    // Delay pembacaan sensor
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}
// ===================== TASK DISPLAY =====================
void display(void *pvParameters) {
  struct readings x;
  for(;;) {
    // Menerima data dari queue
    if (xQueueReceive(my_queue, &x, portMAX_DELAY) == pdPASS) {
      Serial.print("temp = ");
      Serial.print(x.temp);
      Serial.println(" *C");
      Serial.print("humidity = ");
      Serial.print(x.h);
      Serial.println(" %");
    }
  }
}
```

# Penjelasan Program
- `#include <Arduino_FreeRTOS.h>`  
  Digunakan untuk memanggil library FreeRTOS.
- `#include <queue.h>`  
  Digunakan untuk fitur komunikasi Queue antar task.
- `#include "DHT.h"`  
  Digunakan untuk membaca sensor DHT.
- `xQueueCreate()`  
  Digunakan untuk membuat Queue.
- `xQueueSend()`  
  Digunakan untuk mengirim data ke Queue.
- `xQueueReceive()`  
  Digunakan untuk menerima data dari Queue.
- `xTaskCreate()`  
  Digunakan untuk membuat task baru.
- `vTaskDelay()`  
  Digunakan untuk memberikan delay pada task tanpa menghentikan task lain.

  # Penjelasan Modifikasi Program
Program dimodifikasi dengan menambahkan sensor DHT11 sebagai input data suhu dan kelembapan.
Task `read_data` bertugas membaca data sensor DHT setiap 2 detik kemudian mengirim data tersebut ke Queue menggunakan `xQueueSend()`.
Task `display` bertugas menerima data dari Queue menggunakan `xQueueReceive()` lalu menampilkannya pada Serial Monitor.
Dengan penggunaan Queue:
- Komunikasi antar task menjadi lebih aman
- Data dapat dikirim secara terstruktur menggunakan `struct`
- Task dapat berjalan secara concurrent tanpa konflik data


# Kesimpulan
Berdasarkan percobaan yang telah dilakukan, dapat disimpulkan bahwa:
1. FreeRTOS Queue dapat digunakan untuk komunikasi data antar task secara aman.
2. Queue membantu mencegah race condition pada pertukaran data.
3. Sensor DHT dapat diintegrasikan dengan FreeRTOS untuk menampilkan data suhu dan kelembapan secara real-time.
