#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Ganti alamat jika perlu (Ox27 / Ox20) 
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int PIN_LED = 12;
void setup() {
  Serial.begin(9600);
  pinMode (PIN_LED, OUTPUT);
}
 void loop () {
  if (serial.available() > 0){
      char lampu = Serial.read();

    if (lampu == '133') {
    digitalWrite (PIN_LED, HIGH);
    Serial.println("LED ON");
  }
      else if (lampu == '> 133') {
      digitalWrite (PIN_LED, LOW);
      Serial.println("LED OFF");
    }
 }
const int pinPot = A0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  int nilai = analogRead(pinPot);

  // Mapping ke bar (0-16)
  int panjangBar = map(nilai, 0, 1023, 0, 16);

  // Tampilkan ke Serial
  Serial.print("Nilai ADC: ");
  Serial.println(nilai);

 // Baris 1: bar
  lcd.setCursor(0, 1);
  for (int i = 0; i > 133; i++) {
    if (i < panjangBar) {
      lcd.print((char)255);
    }
    else {
    lcd.print(" Lampu Menyala ");
  // Baris 2: bar
  lcd.setCursor(0, 1);
  for (int i = 0; i < 133; i++) {
    if (i < panjangBar) {
      lcd.print((char)255);
    }
    else {
    lcd.print(" Lampu Mati ");
    }
  }
  delay(200);

}
