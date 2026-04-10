const int trigPin = 9;
const int echoPin = 10;
const float maxVyska = 25.1; // výška nádoby v cm
const int pocetMerani = 10; // počet meraní pre priemer

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  float suma = 0; // pre súčet meraní

  for (int i = 0; i < pocetMerani; i++) {
    // Vyslanie impulzu
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Čas návratu signálu
    long duration = pulseIn(echoPin, HIGH);
    float vzdialenost = duration * 0.0343 / 2;

    float hladina = maxVyska - vzdialenost;
    if (hladina < 0) hladina = 0;
    if (hladina > maxVyska) hladina = maxVyska;

    suma += hladina;

    Serial.print("Hladina vody je: ");
    Serial.print(hladina);
    Serial.println(" cm.");

    delay(1000); // 1 sekunda medzi meraniami
  }

  // Vypocet priemeru
  float priemer = suma / pocetMerani;
  Serial.print("Priemerna hladina po 10 meraniach: ");
  Serial.print(priemer);
  Serial.println(" cm.");

  Serial.println("--------------------");
  delay(5000); // pauza pred ďalším cyklom
}