int incomingByte = 49;
// function for ultrasonic
int ultrasonic(int trigPin, int echoPin) {
  long duration;
  // setup trigger and echo pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // send out trigger signal
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);
  // wait for a pulse on the echo pin
  duration = pulseIn(echoPin, HIGH);
  // take the pulse and scale it to cm
  duration = duration / 59;
  // if duration is less than two or greater than 300, something is wrong.  Return an error.
  if ((duration < 2) || (duration > 300)) return false;
  return duration;
}
void setup() {
  // put your setup code here, to run once:
  //2-3 is EW sensor
  //4 is NS switch
  //5 is EW *    *
  //6-8=NS red-green
  //9-11=EW red-green
  //12-13=NS sensor
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  for (int i = 6; i <= 11; i++) {
    digitalWrite(i, LOW);
  }
  digitalWrite(6, HIGH);
  digitalWrite(9, HIGH);
  Serial.begin(9600);
}
void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read(); // read the incoming byte:
    Serial.print(" I received:");
    Serial.println(incomingByte);
  }
  if (incomingByte == 49) {
    Serial.println("Using mode 1, Normal");
    int NoSo = digitalRead(4);
    int EaWe = digitalRead(5);
    if (NoSo == LOW || ultrasonic(12, 13) <= 10) {
      digitalWrite(11, LOW);
      if (digitalRead(9) == LOW) {
        digitalWrite(10, HIGH);
      }
      delay(750);
      digitalWrite(10, LOW);
      digitalWrite(9, HIGH);
      delay(1000);
      digitalWrite(6, LOW);
      digitalWrite(8, HIGH);
    }
    delay(5000);
    if (EaWe == LOW || ultrasonic(2, 3) <= 10) {
      digitalWrite(8, LOW);
      if (digitalRead(6) == LOW) {
        digitalWrite(7, HIGH);
      }
      delay(750);
      digitalWrite(7, LOW);
      digitalWrite(6, HIGH);
      delay(1000);
      digitalWrite(9, LOW);
      digitalWrite(11, HIGH);
    }
    delay(5000);
  }
  if (incomingByte == 50) {
    Serial.println("Using mode 2, timed");
    for (int i = 6; i <= 11; i++) {
      digitalWrite(i, LOW);
    }
    digitalWrite(6, HIGH);
    digitalWrite(9, HIGH);
    delay(100);
    digitalWrite(6, LOW);
    digitalWrite(8, HIGH);
    delay(10000);
    digitalWrite(8, LOW);
    digitalWrite(7, HIGH);
    delay(700);
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH);
    delay(1000);
    digitalWrite(9, LOW);
    digitalWrite(11, HIGH);
    delay(10000);
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);
    delay(700);
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);
    delay(1000);
  }
  if (incomingByte == 51) {
    Serial.println("Using mode 3, danger/blinking yellow");
    for (int i = 6; i <= 11; i++) {
      digitalWrite(i, LOW);
    }
    digitalWrite(7, HIGH);
    digitalWrite(10, HIGH);
    delay(1000);
    digitalWrite(7, LOW);
    digitalWrite(10, LOW);
    delay(500);
  }
  if (incomingByte == 52) {
    Serial.println("Using mode 4, broken/blinking red");
    for (int i = 6; i <= 11; i++) {
      digitalWrite(i, LOW);
    }
    digitalWrite(6, HIGH);
    digitalWrite(9, HIGH);
    delay(1000);
    digitalWrite(6, LOW);
    digitalWrite(9, LOW);
    delay(500);
  }
  int NoSo = digitalRead(4);
  int EaWe = digitalRead(5);
  Serial.println("Ultrasounds:");
  Serial.println(ultrasonic(0, 1));
  Serial.println(ultrasonic(2, 3));
  Serial.println("Buttons:");
  Serial.println(NoSo);
  Serial.println(EaWe);
}
