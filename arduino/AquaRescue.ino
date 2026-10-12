/* AquaRescue SDG 6 - Arduino Uno sensor transmitter
   Leak sensor module: digital OUT -> D2, VCC -> 5V, GND -> GND
   HC-SR04: TRIG -> D9, ECHO -> D10, VCC -> 5V, GND -> GND

   Serial output is one JSON object per line, at 9600 baud.
   Many leak sensor modules output LOW when wet. If yours works the
   opposite way, change LEAK_ACTIVE_LOW below to false.
*/

const byte LEAK_PIN = 2;
const byte TRIG_PIN = 9;
const byte ECHO_PIN = 10;
const bool LEAK_ACTIVE_LOW = true;

unsigned long lastSend = 0;
const unsigned long SEND_INTERVAL_MS = 500;

float readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(3);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);
  if (duration == 0) return -1.0; // no echo / out of range
  return duration * 0.0343f / 2.0f;
}

void setup() {
  pinMode(LEAK_PIN, INPUT_PULLUP);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
  Serial.begin(9600);
}

void loop() {
  if (millis() - lastSend >= SEND_INTERVAL_MS) {
    lastSend = millis();
    int rawLeak = digitalRead(LEAK_PIN);
    bool leakDetected = LEAK_ACTIVE_LOW ? (rawLeak == LOW) : (rawLeak == HIGH);
    float distanceCm = readDistanceCm();

    Serial.print("{\"leak\":");
    Serial.print(leakDetected ? "true" : "false");
    Serial.print(",\"distance_cm\":");
    if (distanceCm < 0) Serial.print("null");
    else Serial.print(distanceCm, 1);
    Serial.println("}");
  }
}
