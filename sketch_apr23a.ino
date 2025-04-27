#include <LiquidCrystal.h>

LiquidCrystal lcd(22, 23, 24, 25, 26, 27);


const int motorButton = 37;
const int seatbeltButton = 38;
const int doorSwitch = 39;
const int tempSensor = A1;
const int lightSensor = A0;
const int fuelSensor = A2;

const int redLED = 42;
const int blueLED = 43;
const int yellowLED = 44;
const int rgbRed = 33;
const int rgbGreen = 34;
const int rgbBlue = 35;
const int buzzer = 36;
const int fanMotor = 12;
const int driveMotor = 13;

volatile bool motorRunning = false;


volatile bool motorBtnPressed, seatbeltOn, doorClosed;
volatile float temperature;
volatile int lightValue, fuelPercent;

void setup() {
  lcd.begin(16, 2);

  pinMode(motorButton, INPUT_PULLUP);
  pinMode(seatbeltButton, INPUT_PULLUP);
  pinMode(doorSwitch, INPUT_PULLUP);

  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(rgbRed, OUTPUT);
  pinMode(rgbGreen, OUTPUT);
  pinMode(rgbBlue, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(fanMotor, OUTPUT);
  pinMode(driveMotor, OUTPUT);
}

void loop() {
  readInputs();
  checkDoor();
  handleSeatbeltAndStart();
  controlTemperature();
  controlLights();
  controlFuel();
  controlDriveMotor();
}



void readInputs() {
  motorBtnPressed = digitalRead(motorButton) == LOW;
  if (!motorBtnPressed)  motorRunning = false;
  seatbeltOn = digitalRead(seatbeltButton) == LOW;
  doorClosed = digitalRead(doorSwitch) == LOW;

  int tempValue = analogRead(tempSensor);
  float voltage = tempValue * (5.0 / 1023.0);
  temperature = voltage * 100;

  lightValue = analogRead(lightSensor);
  int fuelValue = analogRead(fuelSensor);
  fuelPercent = map(fuelValue, 0, 1023, 0, 100);
}

void checkDoor() {
  if (!doorClosed) {
    digitalWrite(rgbRed, HIGH);
    digitalWrite(rgbGreen, LOW);
    digitalWrite(rgbBlue, HIGH);
    lcd.clear();
    lcd.print("Uyari: Kapi Acik");
    lcd.setCursor(0, 1);
    lcd.print("Motor Calismaz");
    motorRunning = false;
    delay(500);

  } else {
    digitalWrite(rgbRed, LOW);
    digitalWrite(rgbGreen, LOW);
    digitalWrite(rgbBlue, LOW);
    lcd.clear();

  }
}

void handleSeatbeltAndStart() {
  if (motorBtnPressed && !motorRunning && doorClosed) {
    if (fuelPercent > 0) motorRunning = true;

    if (!seatbeltOn) {
      digitalWrite(buzzer, HIGH);
      digitalWrite(redLED, HIGH);
      lcd.clear();
      lcd.print("Emniyet Kemeri");
      lcd.setCursor(0, 1);
      lcd.print("Takili Degil!");
      motorRunning = false;
      delay(200);
    } else {
      digitalWrite(buzzer, LOW);
      digitalWrite(redLED, LOW);
    }
  }else {
      digitalWrite(buzzer, LOW);
      digitalWrite(redLED, LOW);    
  }

  if (seatbeltOn){
      digitalWrite(buzzer, LOW);
      digitalWrite(redLED, LOW);
  }
}

void controlTemperature() {
  if (temperature > 25 && motorRunning) {
    digitalWrite(fanMotor, HIGH);
    lcd.clear();
    lcd.print("Sicaklik: ");
    lcd.print(temperature);
    lcd.setCursor(0, 1);
    lcd.print("Klima Acildi");
    delay(300);
  } else {
    digitalWrite(fanMotor, LOW);
  }
}

void controlLights() {
  if (lightValue <= 250 && motorRunning) {
    digitalWrite(blueLED, HIGH);
    lcd.clear();
    lcd.print("Farlar Acik");
    delay(300);
  } else {
    if (digitalRead(blueLED)==HIGH){
    lcd.clear();
    lcd.print("Farlar Kapandi");
    delay(750);
    }
    digitalWrite(blueLED, LOW);
  }
}

void controlFuel() {
  if (fuelPercent <= 0) {
    motorRunning = false;
    digitalWrite(driveMotor, LOW);
    lcd.clear();
    lcd.print("Yakit Bitti");
    lcd.setCursor(0, 1);
    lcd.print("Motor Durdu");
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, LOW);
    digitalWrite(yellowLED, LOW);
    delay(250);
  } else if (fuelPercent < 5 && motorRunning) {
    digitalWrite(yellowLED, millis() / 500 % 2);
    lcd.clear();
    lcd.print("Kritik Yakit: ");
    lcd.print(fuelPercent);
    lcd.print("%");
    delay(300);
  } else if (fuelPercent < 10 && motorRunning) {
    digitalWrite(yellowLED, HIGH);
    lcd.clear();
    lcd.print("Yakit Az: ");
    lcd.print(fuelPercent);
    lcd.print("%");
    delay(300);
  } else {
    digitalWrite(yellowLED, LOW);
  }
}

void controlDriveMotor() {
  if (motorRunning && fuelPercent > 0 && doorClosed && seatbeltOn && motorBtnPressed ) {
    digitalWrite(driveMotor, HIGH);
  } else {
    digitalWrite(driveMotor, LOW);
  }
}