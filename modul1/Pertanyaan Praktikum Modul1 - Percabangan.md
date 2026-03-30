

````markdown
# 📘 Praktikum Sistem Tertanam  
## Modul I: Percabangan

Repository ini berisi *source code* dan dokumentasi jawaban dari Pertanyaan Praktikum Modul I (Percabangan) pada mata kuliah **Sistem Tertanam dan Mikrokontroler**.

---

## 📌 Jawaban Pertanyaan Praktikum

### 1. Kondisi Masuk ke Blok `if`
Program akan mengeksekusi blok `if` ketika kondisi:

```cpp
timeDelay <= 100
````

bernilai **true**.

Artinya, program masuk ke blok ini saat jeda waktu kedipan LED telah mencapai batas tercepat, yaitu **100 milidetik atau kurang**.

---

### 2. Kondisi Masuk ke Blok `else`

Program akan mengeksekusi blok `else` ketika kondisi pada `if` bernilai **false**, yaitu saat:

```cpp
timeDelay > 100
```

Pada kondisi ini, nilai `timeDelay` akan terus dikurangi sebesar **100 ms setiap loop**, sehingga efek kedipan LED menjadi semakin cepat.

### 3. Fungsi `delay(timeDelay)`

Fungsi:

```cpp
delay(timeDelay);
```

digunakan untuk **menunda eksekusi program** selama durasi tertentu (dalam milidetik).

Fungsi ini berperan untuk:

* Menahan kondisi LED (nyala atau mati)
* Mengatur kecepatan kedipan LED
* Membuat perubahan status LED bisa terlihat oleh mata manusia

---

# Modifikasi Program

### Alur: Lambat → Cepat → Sedang → Mati

Program dimodifikasi agar LED:

1. Berkedip dari lambat ke cepat
2. Berubah ke kecepatan sedang
3. Mati secara permanen tanpa mengulang loop

# Source Code (`modul1_percabangan.ino`)

```cpp
const int ledPin = 12;    // Pin LED
int timeDelay = 1000;     // Delay awal (1 detik)

void setup() { 
  pinMode(ledPin, OUTPUT);
}

void loop() { 
  // --- Eksekusi LED ---
  digitalWrite(ledPin, HIGH); 
  delay(timeDelay);           

  digitalWrite(ledPin, LOW); 
  delay(timeDelay);           

  // --- Logika Percabangan ---
  if (timeDelay == 100) {     
    // Dari cepat → sedang
    timeDelay = 500;          

  } else if (timeDelay == 500) { 
    // Dari sedang → mati permanen
    digitalWrite(ledPin, LOW);

    while(true) {
      // Loop tak hingga (program berhenti di sini)
    }

  } else { 
    // Percepatan bertahap
    timeDelay -= 100;         
  }
}
```

# Penjelasan Alur Program

* **Inisialisasi (`timeDelay = 1000`)**
  LED mulai dengan kedipan lambat (1 detik).

* **Blok `else` (Percepatan)**
  Selama `timeDelay` belum 100 atau 500:

  ```cpp
  timeDelay -= 100;
  ```

  LED semakin cepat secara bertahap.

* **Blok `if (timeDelay == 100)`**
  Saat mencapai kecepatan maksimal, delay diubah ke:

  ```cpp
  timeDelay = 500;
  ```

  → Masuk fase sedang.

* **Blok `else if (timeDelay == 500)`**
  LED dimatikan:

  ```cpp
  digitalWrite(ledPin, LOW);
  ```

* **Penghentian Program (`while(true)`)**
  Program berhenti total dan tidak mengulang loop:

  ```cpp
  while(true) {}
  ```

# Kesimpulan

1. Percabangan `if-else` digunakan untuk mengatur perubahan kecepatan LED secara dinamis.
2. Variabel `timeDelay` menjadi pengontrol utama durasi nyala dan mati LED.
3. Program berhasil menghasilkan alur:
   **Lambat → Cepat → Sedang → Mati**
4. Penggunaan `while(true)` memastikan program berhenti permanen tanpa reset.
