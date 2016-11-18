#include <LiquidCrystal.h>
#include <Thermistor.h>
#include <Servo.h>

#define LED_AQUECEDOR 2
#define LED_AR_CONDICIONADO 3
#define BEEP A2
#define SENSOR 10
#define LAMPADA_EXTERNA 11
#define LAMPADA_SEMI_EXTERNA 12
#define LAMPADA_INTERNA 13
#define LDR A1

Thermistor temp(0);
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

void setup()
{

  Serial.begin(9600);
  pinMode(LED_AQUECEDOR, OUTPUT);
  pinMode(LED_AR_CONDICIONADO, OUTPUT);
  pinMode(BEEP, OUTPUT);
  pinMode(LAMPADA_EXTERNA, OUTPUT);
  pinMode(LAMPADA_SEMI_EXTERNA, OUTPUT);
  pinMode(LAMPADA_INTERNA, OUTPUT);

  digitalWrite(BEEP, LOW);
  digitalWrite(LAMPADA_EXTERNA,HIGH);
  digitalWrite(LAMPADA_SEMI_EXTERNA, HIGH);
  digitalWrite(LAMPADA_INTERNA,HIGH);

  lcd.begin(16, 2);

}

void loop()
{
  int temperature = temp.getTemp();
  float luminosity = analogRead(LDR);
  luminosity = (luminosity / 1024) * 100;

  if (temperature < 25) {
    digitalWrite(LED_AR_CONDICIONADO, LOW);
     digitalWrite(LED_AQUECEDOR, HIGH);
  } else if (temperature >= 25) {
     digitalWrite(LED_AQUECEDOR, LOW);
     digitalWrite(LED_AR_CONDICIONADO, HIGH);
  }

  if (digitalRead(SENSOR)){
    digitalWrite(BEEP, HIGH);
    Serial.println("Alarme");
  } else {
    digitalWrite(BEEP, LOW);
  }

  if (luminosity < 40) {
      digitalWrite(LAMPADA_EXTERNA,HIGH);
  } else {
      digitalWrite(LAMPADA_EXTERNA, LOW);
  }

  lcd.setCursor(0,0);
  lcd.print("Temperature: ");
  lcd.print(temperature);
  lcd.print("C");

  lcd.setCursor(0,1);
  lcd.print("Luminosity: ");
  lcd.print(luminosity);
  lcd.print("%");

  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" *C\n");

  Serial.print("Luminosidade: ");
  Serial.print(luminosity);
  Serial.println(" %\n");

  delay(1000);

}
