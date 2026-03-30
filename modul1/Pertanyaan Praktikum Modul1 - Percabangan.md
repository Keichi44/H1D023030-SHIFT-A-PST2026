Siapp Kei! Berhubung lu mau *push* tugas ini ke GitHub, format `README.md` emang harus dibikin serapi dan seprofesional mungkin biar asisten praktikumnya seneng pas *review* kodingan lu. 

Gue udah susunin ulang teks yang lu kasih ke dalam format Markdown yang cakep, lengkap dengan hierarki *heading*, *syntax highlighting* buat kode C++, dan *bullet points* biar gampang dibaca.

Lu tinggal *copy* teks di dalam blok abu-abu di bawah ini, terus *paste* langsung ke file `README.md` di *repository* GitHub lu:

```markdown
# 📘 Praktikum Sistem Tertanam - Modul I: Percabangan

Repository ini berisi *source code* dan dokumentasi jawaban dari Pertanyaan Praktikum Modul I (Percabangan) untuk mata kuliah Sistem Tertanam dan Mikrokontroler.

---

## 📌 Jawaban Pertanyaan Praktikum

### 1. Kondisi Masuk ke Blok `if`
Program akan mengeksekusi perintah di dalam blok `if` pada saat evaluasi kondisi `timeDelay <= 100` bernilai **benar (true)**. 
Artinya, program masuk ke blok ini ketika jeda waktu kedipan LED sudah mencapai batas tercepatnya, yaitu 100 milidetik atau kurang.

### 2. Kondisi Masuk ke Blok `else`
Program akan melompat ke blok `else` apabila kondisi pada blok `if` bernilai **salah (false)**, alias saat nilai variabel `timeDelay` masih di atas 100 milidetik. 
Pada fase ini, program rutin mengurangi nilai *delay* sebesar 100ms setiap siklusnya untuk menciptakan efek kedipan yang semakin cepat.

### 3. Fungsi Perintah `delay(timeDelay)`
Fungsi utama dari `delay(timeDelay);` adalah untuk menghentikan sementara proses eksekusi mikrokontroler selama durasi yang ditentukan oleh nilai variabel `timeDelay` (dalam satuan milidetik). 
Perintah ini bertugas menahan status terakhir dari pin digital, baik saat sedang menyala (`HIGH`) maupun saat sedang mati (`LOW`), sehingga mata kita bisa melihat efek kedipannya.

---

## 💻 Modifikasi Kode: Alur Lambat → Cepat → Sedang → Mati
Bagian ini berisi modifikasi *source code* agar LED mengalami transisi dari lambat ke cepat, lalu turun ke kecepatan sedang, dan akhirnya mati secara permanen tanpa mengulang dari awal.

### Source Code (`modul1_percabangan.ino`)

```cpp
const int ledPin = 12;    // Menggunakan pin 12 sesuai topologi rangkaian
int timeDelay = 1000;     // Inisialisasi awal: jeda 1 detik (lambat)

void setup() { 
  pinMode(ledPin, OUTPUT); // Konfigurasi pin 12 sebagai jalur output
}

void loop() { 
  // --- Fase Eksekusi LED ---
  digitalWrite(ledPin, HIGH); 
  delay(timeDelay);           

  digitalWrite(ledPin, LOW); 
  delay(timeDelay);           

  // --- Fase Logika Percabangan ---
  if (timeDelay == 100) {     
    // Transisi 1: Dari kecepatan maksimal (cepat) diturunkan ke sedang
    timeDelay = 500;          

  } else if (timeDelay == 500) { 
    // Transisi 2: Dari kecepatan sedang menuju fase mati permanen
    digitalWrite(ledPin, LOW); // Memastikan lampu dalam kondisi padam
    while(true) {
      // Infinite loop kosong untuk menahan program agar tidak kembali ke awal
    }

  } else { 
    // Default: Percepatan bertahap dari lambat menuju cepat
    timeDelay -= 100;         
  }
}
```

### 🔍 Penjelasan Baris Kode (Alur Logika)

* **Inisialisasi (`timeDelay = 1000`)**: Program dimulai dengan *delay* 1000ms. Lampu berkedip lambat.
* **Blok `else` (Percepatan)**: Karena nilai awal belum 100 atau 500, program masuk ke `else`. Nilai `timeDelay` dikurangi 100ms di setiap putaran *loop* (`timeDelay -= 100;`). Lampu berangsur-angsur berkedip makin cepat.
* **Blok `if (timeDelay == 100)` (Fase Cepat ke Sedang)**: Ketika pengurangan terus terjadi dan nilai `timeDelay` menyentuh 100ms (fase sangat cepat), blok ini dieksekusi. Nilai *delay* langsung diubah menjadi 500 ms.
* **Blok `else if (timeDelay == 500)` (Fase Sedang ke Mati)**: Pada putaran berikutnya, karena `timeDelay` sekarang bernilai 500ms, blok logika ini yang dieksekusi.
* **Penghentian Permanen (`while(true)`)**: Di dalam blok nilai 500ms, lampu dipastikan mati dengan perintah `digitalWrite(ledPin, LOW);`, kemudian program dijebak ke dalam perulangan `while(true)` yang tidak ada jalan keluarnya. Ini mencegah fungsi `void loop()` mengulang dari awal, sehingga LED mati total tanpa perlu mencabut daya mikrokontroler.

---

## 🎯 Kesimpulan

1. Struktur kontrol percabangan `if-else` sangat efektif digunakan untuk mengatur perubahan fase kecepatan kedipan LED secara dinamis berdasarkan kondisi tertentu.
2. Variabel `timeDelay` berperan sebagai pengontrol utama durasi nyala (`HIGH`) dan mati (`LOW`) pada komponen LED.
3. Modifikasi program dengan menyisipkan beberapa kondisi `if` dan `else if` berhasil menciptakan alur transisi yang lebih halus dan bertahap, yaitu: **Lambat → Cepat → Sedang → Mati**.
4. Penggunaan perulangan tak terbatas `while(true)` pada fase akhir terbukti berhasil menjebak program agar berhenti secara permanen di kondisi mati tanpa melakukan *reset* atau mengulang *looping* dari awal.
```

Tinggal *commit* dan *push* ke *repository* lu. Sukses terus buat laporannya, Kei!
