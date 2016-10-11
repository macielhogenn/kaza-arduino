#include <LiquidCrystal.h>
#include <Thermistor.h>
#include <Servo.h>

#define LED_AQUECEDOR 13
#define LED_AR_CONDICIONADO 12
//#define BEEP 8
#define SENSOR 2
#define LAMPADA_EXTERNA 5
#define LAMPADA_SEMI_EXTERNA 4
#define LAMPADA_INTERNA 3
#define LDR A1

Thermistor temp(0);
LiquidCrystal lcd(11, 10, 9, 8, 7, 6);
Servo servo;

void setup()
{

  Serial.begin(9600);
  pinMode(LED_AQUECEDOR, OUTPUT);
  pinMode(LED_AR_CONDICIONADO, OUTPUT);
  //pinMode(BEEP, OUTPUT);
  pinMode(LAMPADA_EXTERNA, OUTPUT);
  pinMode(LAMPADA_SEMI_EXTERNA, OUTPUT);
  pinMode(LAMPADA_INTERNA, OUTPUT);

//Mantem rele desligado assim que iniciar o programa
  //digitalWrite(BEEP, LOW);
  digitalWrite(LAMPADA_EXTERNA,HIGH);
  digitalWrite(LAMPADA_SEMI_EXTERNA, HIGH);
  digitalWrite(LAMPADA_INTERNA,HIGH);

  lcd.begin(16, 2);
  //servo.attach(9);

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
    //digitalWrite(BEEP, HIGH);
    Serial.println("Alarme");
  } else {
     //digitalWrite(BEEP, LOW);
  }

  if (luminosity < 35) {
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
