#  Praktikum Sistem Tertanam  
# Modul V : Komunikasi Task dan Multitasking

# Pertanyaan Praktikum

1. Jelaskan perbedaan antara loop() pada Arduino biasa dengan sistem yang menggunakan RTOS! 
2. Mengapa fungsi loop() dibiarkan kosong?  
3. Apa insight utama yang Anda pelajari dari praktikum ini?

# Jawaban Pertanyaan Praktikum

# 1. Jelaskan perbedaan antara `loop()` pada Arduino biasa dengan sistem yang menggunakan RTOS!
## Arduino Biasa (Non-OS)
Pada Arduino biasa, program berjalan secara berurutan di dalam fungsi `loop()` yang terus diulang tanpa henti.
Jika terdapat instruksi yang membutuhkan waktu lama, seperti `delay()`, maka seluruh program akan berhenti sementara (*blocking*) hingga proses tersebut selesai.
Akibatnya:
- Program menjadi kurang responsif
- Instruksi lain harus menunggu giliran eksekusi


## Arduino dengan RTOS
Pada sistem RTOS, program dibagi menjadi beberapa *task* yang berjalan secara *concurrent*.
Eksekusi task diatur oleh *scheduler* FreeRTOS sehingga setiap task mendapatkan giliran pemrosesan CPU.
Dengan sistem ini:
- Task dapat berjalan secara independen
- Delay pada satu task tidak menghentikan task lainnya
- Sistem menjadi lebih responsif dan efisien

# 2. Mengapa fungsi `loop()` dibiarkan kosong?
Fungsi `loop()` dibiarkan kosong karena kontrol program sudah diambil alih oleh *scheduler* dari FreeRTOS.
Setelah fungsi:

```cpp
vTaskStartScheduler();
```
dijalankan, seluruh eksekusi program akan berpindah ke task-task yang telah dibuat menggunakan `xTaskCreate()`.
Perulangan utama tidak lagi berada di `loop()`, tetapi berada di masing-masing task menggunakan:

```cpp
while(1)
```
Karena itu, fungsi `loop()` tidak lagi digunakan.

# 3. Apa insight utama yang Anda pelajari dari praktikum ini?
Insight utama dari praktikum ini adalah mikrokontroler seperti Arduino Uno dapat menjalankan beberapa proses secara *concurrent* menggunakan RTOS meskipun hanya memiliki prosesor *single-core*.
Saya juga memahami bahwa:
- Scheduler berperan penting dalam pengaturan task
- Queue dapat digunakan untuk komunikasi data antar task
- Sistem multitasking membuat program lebih responsif
- RTOS membantu mengurangi blocking dan race condition
