const int PIN = A0;

// Referenčné napätie Arduina
const float VCC = 5.0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Načítanie analógovej hodnoty (0–1023)
  int adc = analogRead(PIN);

  // Prepočet ADC hodnoty na napätie (V)
  float v = adc * VCC / 1023.0;

  // Výpis ADC hodnoty
  Serial.print("ADC=");
  Serial.print(adc);

  // Výpis vypočítaného napätia
  Serial.print("  V=");
  Serial.println(v, 3);

  delay(300);
}
