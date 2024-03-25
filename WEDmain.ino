#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int diodePin1 = 6;
int diodePin2 = 7;
int signalPin = 8;
int buzzerPin1 = 9;
int buzzerPin2 = 10;
int inputDiode = 13;

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);

  pinMode(signalPin, INPUT);
  pinMode(diodePin1, OUTPUT);
  pinMode(diodePin2, OUTPUT);
  pinMode(buzzerPin1, OUTPUT);
  pinMode(buzzerPin2, OUTPUT);
  pinMode(inputDiode, INPUT_PULLUP);
}

void loop() {
  if(digitalRead(signalPin)) {
    printDisplay();
    buzzers();
    diodes();
  }
  else {
    reset();
  }
}

void printDisplay(){
  lcd.setCursor(3, 0);
  lcd.print("Earthquake");
  lcd.setCursor(3, 1);
  lcd.print("detected!!!");
}

void buzzers(){
  analogWrite(buzzerPin1, 64);
  analogWrite(buzzerPin2, 64);
}

void diodes(){
  digitalWrite(diodePin1, HIGH);
  digitalWrite(diodePin2, LOW);
  delay(200);
  digitalWrite(diodePin1, LOW);
  digitalWrite(diodepin2, HIGH);
  delay(200);
}

void reset(){
  lcd.clear();
  digitalWrite(diodePin1, LOW);
  digitalWrite(diodePin2, LOW);
  digitalWrite(buzzerPin1, LOW);
  digitalWrite(buzzerPin2, LOW);
}