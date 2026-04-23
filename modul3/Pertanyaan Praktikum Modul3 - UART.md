#  Praktikum Sistem Tertanam  
# Modul III: Protokol Komunikasi

# Pertanyaan Praktikum 

1) Jelaskan proses dari input keyboard hingga LED menyala/mati! 
2) Mengapa digunakan Serial.available() sebelum membaca data? Apa yang terjadi jika baris tersebut dihilangkan? 
3) Modifikasi program agar LED berkedip (blink) ketika menerima input '2' dengan kondisi jika ‘2’ aktif maka LED akan terus berkedip sampai perintah selanjutnya diberikan dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md! 
4) Tentukan apakah menggunakan delay() atau milis()! Jelaskan pengaruhnya terhadap sistem 

# Jawaban Pertanyaan Praktikum

# 1. Proses dari Input Keyboard hingga LED Menyala/MatiAlur komunikasinya adalah sebagai berikut:
   - Input: Karakter diketik di keyboard melalui Serial Monitor pada komputer.
   - Transmisi: Data dikirim bit demi bit secara serial melalui kabel USB menggunakan protokol UART.
   - Penerimaan: Bit data diterima oleh pin RX Arduino dan disimpan sementara di dalam buffer serial.
   - Eksekusi: Fungsi Serial.read() mengambil data dari buffer ke variabel data. Jika variabel berisi '1', instruksi digitalWrite(PIN_LED, HIGH) dikirim ke hardware sehingga LED menyala. Jika '0', instruksi LOW dikirim dan LED mati.

# 2. Penggunaan Serial.available()
   - Fungsi: Untuk memastikan bahwa ada data yang sudah masuk ke buffer sebelum program mencoba membacanya.
   - Jika dihilangkan: Program akan terus mengeksekusi Serial.read() di setiap putaran loop(). Karena kecepatan loop() jauh lebih cepat dari ketikan manusia, fungsi tersebut akan sering membaca nilai kosong (-1). Hal ini mengakibatkan Serial Monitor akan terus menampilkan pesan "Perintah tidak dikenal" secara berulang-ulang tanpa henti.

# 3. Modifikasi Program (Mode Blink)
Berikut adalah kode program agar LED berkedip saat menerima input '2':
```cpp
const int PIN_LED = 12;
char mode = '0'; // Status mode: '0'=mati, '1'=nyala, '2'=blink
unsigned long prevMillis = 0;
const long interval = 500; // Kecepatan kedip (ms)
bool ledState = LOW;

void setup() {
  Serial.begin(9600);
  Serial.println("1: ON, 0: OFF, 2: BLINK");
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  // 1. Cek input baru tanpa menghentikan program
  if (Serial.available() > 0) {
    char input = Serial.read();
    if (input == '1' || input == '0' || input == '2') {
      mode = input; // Update mode
      if (mode == '1') { digitalWrite(PIN_LED, HIGH); Serial.println("LED ON"); }
      if (mode == '0') { digitalWrite(PIN_LED, LOW); Serial.println("LED OFF"); }
      if (mode == '2') { Serial.println("LED BLINKING..."); }
    } else if (input != '\n' && input != '\r') {
      Serial.println("Perintah tidak dikenal");
    }
  }

  // 2. Jalankan logika blink jika mode adalah '2'
  if (mode == '2') {
    unsigned long currentMillis = millis();
    if (currentMillis - prevMillis >= interval) {
      prevMillis = currentMillis;
      ledState = !ledState; // Balikkan status LED
      digitalWrite(PIN_LED, ledState);
    }
  }
}
```
Penjelasan
- mode: Variabel untuk menyimpan kondisi perintah terakhir agar program tahu kapan harus diam, nyala, atau kedip.
- millis(): Digunakan untuk menghitung waktu internal Arduino agar proses kedip tidak menghentikan pengecekan data serial.
- ledState = !ledState: Membalikkan kondisi LED (dari mati ke nyala atau sebaliknya) setiap interval waktu tercapai.

# 4. Penggunaan delay() atau millis()
- Pilihan: Sangat disarankan menggunakan millis() untuk sistem ini.
- Pengaruh terhadap sistem: * Jika menggunakan delay(), seluruh aktivitas program akan berhenti (pause) selama waktu delay tersebut. Akibatnya, Arduino tidak bisa membaca input baru dari Serial Monitor sampai delay selesai (sistem menjadi tidak responsif).
- Jika menggunakan millis(), program tetap berjalan (non-blocking). Arduino bisa melakukan pengecekan input serial sekaligus mengontrol kedipan LED secara bersamaan.

# Kesimpulan:
Penggunaan millis() memungkinkan Arduino melakukan multitasking sederhana, menjaga komunikasi serial tetap lancar dan responsif terhadap perintah user meskipun sistem sedang menjalankan tugas berulang seperti mode blink.
