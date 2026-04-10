#include <Wire.h>   // Knižnica pre I2C komunikáciu

// I2C adresy pre dve časti senzora
#define ADDR_LOW  0x77   // spodná časť (8 sekcií)
#define ADDR_HIGH 0x78   // horná časť (12 sekcií)

// Prahová hodnota
#define THRESHOLD 60

// Polia na uloženie dát zo senzora
uint8_t low_data[8], high_data[12];


// Funkcia na načítanie dát zo senzora cez I2C
void readBlock(uint8_t addr, uint8_t *buf, uint8_t len) {
  Wire.requestFrom(addr, len); 
  uint8_t i = 0;
  
  // čítame dostupné bajty a ukladáme do poľa
  while (Wire.available() && i < len) {
    buf[i++] = Wire.read();
  }
}


// Funkcia vytvorí 32-bitové číslo,
uint32_t buildTouchBits() {
  uint32_t bits = 0;

  // Spracovanie spodných 8 sekcií
  for (int i = 0; i < 8; i++) {
    if (low_data[i] > THRESHOLD) 
      bits |= (1UL << i);   // nastav bit, ak je sekcia "mokrá"
  }

  // Spracovanie horných 12 sekcií
  for (int i = 0; i < 12; i++) {
    if (high_data[i] > THRESHOLD) 
      bits |= (1UL << (8 + i)); // pokračujeme od bitu 8
  }

  return bits; // výsledok: 20 bitov = 20 sekcií
}


// Funkcia nájde najvyššiu mokrú sekciu
int highestWetIndex(uint32_t bits) {
  for (int i = 19; i >= 0; i--) {
    if (bits & (1UL << i))          // ak je bit zapnutý
      return i;                     // vrátime index sekcie
  }
  return -1; // ak nič nie je mokré
}


void setup() {
  Serial.begin(115200); 
  Wire.begin();
  
  Serial.println("Grove Water Level Sensor -> cm");
}


void loop() {
  readBlock(ADDR_LOW, low_data, 8);
  readBlock(ADDR_HIGH, high_data, 12);

  // premena dát na bitové pole
  uint32_t bits = buildTouchBits();

  // zistenie najvyššej mokrej sekcie
  int hi = highestWetIndex(bits);

  // 20 sekcií = 10 cm → 1 sekcia = 0.5 cm
  float level_cm = (hi < 0) ? 0.0 : (hi + 1) * 0.5;

  // výpis do Serial Monitoru
  Serial.print("Water level: ");
  Serial.print(level_cm, 1); 
  Serial.println(" cm");

  delay(300);