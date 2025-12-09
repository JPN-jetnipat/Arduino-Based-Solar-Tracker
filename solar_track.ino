#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD 16x2

const int ldrLeft = A0;
const int ldrRight = A1;
const int servoPin = 9;
const int dustSensorPin = A2;
const int vibrationMotorPin = 6;
const int buzzerPin = 7;
const int buttonPin = 8;

const int redLEDPin = 5;
const int yellowLEDPin = 4;
const int greenLEDPin = 3;

Servo servo;
int pos = 90;
bool manualVibrate = false;

// New variables for manual dust override
int fixedDustValue = 0;
bool useFixedDust = false;

void setup() {
  servo.attach(servoPin);
  servo.write(pos);

  pinMode(greenLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(vibrationMotorPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // button uses pull-up resistor

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Solar Tracker Init");
  delay(1500);
  lcd.clear();

  Serial.begin(9600);
  Serial.println("Type dust value (or 0 to use sensor):");
}

void loop() {
  int leftLDR = analogRead(ldrLeft) + 228;
  int rightLDR = analogRead(ldrRight);
  int dustValue;

  // Check if input available from Serial
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    int inputVal = input.toInt();

    if (inputVal == 0) {
      useFixedDust = false;
      Serial.println("Using sensor dust value.");
    } else {
      useFixedDust = true;
      fixedDustValue = inputVal;
      Serial.print("Manual dust value set to: ");
      Serial.println(fixedDustValue);
    }
  }

  // Use fixed or sensor dust value
  if (useFixedDust) {
    dustValue = fixedDustValue;
  } else {
    dustValue = analogRead(dustSensorPin);
  }

  // Servo control
  if (abs(leftLDR - rightLDR) > 30) {
    if (leftLDR > rightLDR) pos -= 6;
    else pos += 6;
  }

  pos = constrain(pos, 0, 180);
  servo.write(pos);

  // LCD display
  lcd.setCursor(0, 0);
  lcd.print("Dust: ");
  lcd.print(dustValue);
  lcd.print("   ");

  lcd.setCursor(0, 1);
  if (leftLDR > rightLDR) {
    lcd.print("Move Left: ");
  } else if (rightLDR > leftLDR) {
    lcd.print("Move Right:");
  } else {
    lcd.print("Balanced     ");
  }
  lcd.print(pos);
  lcd.print("  ");

  // LEDs for dust levels
  if (dustValue > 800) {
    digitalWrite(redLEDPin, HIGH);
    digitalWrite(yellowLEDPin, LOW);
    digitalWrite(greenLEDPin, LOW);
  } else if (dustValue > 400) {
    digitalWrite(redLEDPin, LOW);
    digitalWrite(yellowLEDPin, HIGH);
    digitalWrite(greenLEDPin, LOW);
  } else {
    digitalWrite(redLEDPin, LOW);

    digitalWrite(yellowLEDPin, LOW);
    digitalWrite(greenLEDPin, HIGH);
  }

  // Vibration and buzzer
  manualVibrate = digitalRead(buttonPin) == LOW;

  if (dustValue > 800 || manualVibrate) {
    digitalWrite(vibrationMotorPin, LOW);
    digitalWrite(buzzerPin, LOW);
  } else {
    digitalWrite(vibrationMotorPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
  }

  Serial.print("Dust: ");
  Serial.print(dustValue);
  Serial.print(" | LDR L:");
  Serial.print(leftLDR);
  Serial.print(" R:");
  Serial.println(rightLDR);

  delay(500);
}
