#  Praktikum Sistem Tertanam  
# Modul IV: ADC dan PWM

# Pertanyaan Praktikum
1. Bagaimana proses konversi sinyal analog menjadi digital pada Arduino? Jelaskan! 
2. Faktor apa saja yang dapat mempengaruhi keakuratan pembacaan ADC? 
3. Apa kendala yang mungkin terjadi saat mengintegrasikan ADC dan PWM dalam satu sistem?

# Jawaban Pertanyaan Praktikum

# 1. Bagaimana proses konversi sinyal analog menjadi digital pada Arduino? Jelaskan!
Arduino menggunakan fitur internal bernama *Analog to Digital Converter* (ADC) untuk mengubah sinyal analog menjadi data digital. ADC pada Arduino Uno memiliki resolusi 10-bit, sehingga tegangan analog 0-5V akan dikonversi menjadi nilai digital 0-1023. Saat tegangan analog masuk ke pin analog, mikrokontroler akan membaca tegangan tersebut lalu mengubahnya menjadi data digital secara linier. Tegangan 0V akan bernilai 0, sedangkan 5V akan bernilai 1023.

# Faktor apa saja yang dapat mempengaruhi keakuratan pembacaan ADC?
Beberapa faktor yang mempengaruhi keakuratan ADC antara lain:
- Tegangan referensi yang tidak stabil
- Noise atau gangguan listrik pada rangkaian
- Kabel jumper yang terlalu panjang
- Nilai resistansi komponen yang terlalu tinggi
- Pembacaan ADC yang terlalu cepat tanpa jeda
Faktor-faktor tersebut dapat menyebabkan nilai ADC menjadi tidak stabil atau berubah-ubah.

# 3. Apa kendala yang mungkin terjadi saat mengintegrasikan ADC dan PWM dalam satu sistem?
Beberapa kendala yang dapat terjadi antara lain:
- Noise dari sinyal PWM dapat mempengaruhi pembacaan ADC sehingga data menjadi fluktuatif
- Perbedaan resolusi ADC (0-1023) dan PWM (0-255) dapat membuat output kurang halus
- Output seperti LED atau servo dapat mengalami jitter atau getaran akibat perubahan data yang terlalu cepat
