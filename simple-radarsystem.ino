#include <Servo.h>

Servo myservo;

const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 6;
const int ledPin = 5;

int angle = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(7);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);
}

long readDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // 30 ms timeout

  long distance = duration * 0.034 / 2;
  if (duration == 0) distance = 999;

  return distance;
}

void loop() {
  for (angle = 0; angle <= 180; angle += 2) {
    myservo.write(angle);
    delay(20);

    long distance = readDistanceCM();

    Serial.print(angle);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");

    if (distance > 0 && distance < 40) {
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(buzzerPin, LOW);
      digitalWrite(ledPin, LOW);
    }
  }
  for (angle = 180; angle >= 0; angle -= 2) {
    myservo.write(angle);
    delay(20);

    long distance = readDistanceCM();

    Serial.print(angle);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");

    if (distance > 0 && distance < 40) {
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(buzzerPin, LOW);
      digitalWrite(ledPin, LOW);
    }
  }
}
