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
