const int floatPin = 7;

void setup() {
  Serial.begin(9600);
  pinMode(floatPin, INPUT_PULLUP);
}

void loop() {
  int stav = digitalRead(floatPin);

  if (stav == LOW) {                    
    Serial.println("Hladina pod senzorom"); //Ak nie je zopnutý 
  } 
  else {
    Serial.println("Hladina dosiahnutá");   // Ak je zopnutý
  }

  delay(500);
}