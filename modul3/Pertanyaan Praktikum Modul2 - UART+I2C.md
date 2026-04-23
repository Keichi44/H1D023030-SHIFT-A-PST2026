#  Praktikum Sistem Tertanam  
# Modul II: Auto Seven Segment

# Pertanyaan Praktikum

1. Sebutkan dan jelaskan keuntungan dan kerugian menggunakan UART dan I2C! 
2. Bagaimana peran alamat I2C pada LCD (misalnya 0x27 vs 0x20)? Berikan penjelasan! 
3. Jika UART dan I2C digabung dalam satu sistem (misalnya input dari Serial Monitor, output ke LCD), bagaimana alur kerja sistem tersebut? Bagaimana Arduino mengelola dua protokol sekaligus?

# Jawaban Pertanyaan Praktikum

# 1. Sebutkan dan jelaskan keuntungan dan kerugian menggunakan UART dan I2C!
- UART (Serial):
   Keuntungan: Sangat sederhana, murah, dan mudah diimplementasikan karena hanya butuh 2 jalur (RX dan TX) untuk pertukaran data dua arah.
   Kerugian: Komunikasi asinkron mengharuskan baud rate pengirim dan penerima harus persis sama. Selain itu, hanya terbatas untuk komunikasi point-to-point (satu perangkat ke satu perangkat).
- I2C:
   Keuntungan: Menghemat jumlah pin. Bisa menghubungkan sangat banyak perangkat (sensor, layar) sekaligus menggunakan "Bus" yang sama (hanya 2 kabel: SDA dan SCL).
   Kerugian: Memiliki zona rawan konflik alamat; jika ada perangkat dengan alamat default yang sama dalam satu rangkaian, akan terjadi bentrok (harus diubah secara manual via solder pad).

# 2. Bagaimana peran alamat I2C pada LCD (misalnya 0x27 vs 0x20)? Berikan penjelasan!
Karena protokol I2C menempatkan semua perangkat slave pada kabel (jalur) yang sama persis , alamat I2C (seperti 0x27) bertindak layaknya sebuah "Nomor Kursi" yang unik. Peran alamat ini adalah untuk memberitahu Arduino, "Kirimkan instruksi tampilkan teks ini ke alamat 0x27 saja". Hal ini mencegah komponen I2C lain ikut menyahut atau memproses data yang bukan haknya. Alamat ini biasanya berbeda tergantung pabrik pembuat chip pada modul backpack LCD tersebut (misalnya buatan NXP memakai 0x27

# 3. Jika UART dan I2C digabung dalam satu sistem, bagaimana alur kerja sistem tersebut? Bagaimana Arduino mengelola dua protokol sekaligus?
- Alur Sistem: Input pertama masuk via keyboard ke USB. Chip UART pada Arduino akan menerima input tersebut. Lalu, source code Arduino mengolah data input tadi. Hasil olahan tersebut (misalnya instruksi menyalakan LCD), akan dikirim keluar (Output) oleh Arduino melalui pin SDA/SCL menggunakan antarmuka protokol I2C ke layar.
- Cara Pengelolaan: Arduino Uno dapat mengelola keduanya secara mulus karena kedua protokol tersebut memiliki modul perangkat keras (hardware register) dan pin fisik yang terpisah di mikrokontroler ATMega328P. UART menggunakan pin internal (Pin digital 0/RX dan 1/TX), sementara I2C menggunakan pin khusus I2C (A4 dan A5). Program menjalankannya secara sequential (berurutan dengan sangat cepat) di dalam void loop().
