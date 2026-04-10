const int SENSOR_PIN = A0;

int readWaterSensor() {
  delay(30);                 // krátka stabilizácia
  int v = analogRead(SENSOR_PIN);
  return v;
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  // 10 meraní pre jednu hladinu
  for (int i = 0; i < 10; i++) {
    int v = readWaterSensor();
    Serial.println(v);
    delay(300);
  }

  Serial.println("---");     // oddeľovač série
  delay(5000);
}