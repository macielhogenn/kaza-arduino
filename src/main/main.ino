#include <Thermistor.h>

#define LED_AQUECEDOR 13
#define LED_AR_CONDICIONADO 12 
#define BEEP 8
#define SENSOR 2

Thermistor temp(0); 

void setup() {      
  Serial.begin(9600);
  pinMode(LED_AQUECEDOR, OUTPUT);
  pinMode(LED_AR_CONDICIONADO, OUTPUT);  
  pinMode(BEEP, OUTPUT);  
  digitalWrite(BEEP, LOW); 
} 

void loop() {      
  int temperature = temp.getTemp();
  
  if (temperature < 25) { //TODO temperature do turn on AQUECEDOR is 15º, but 25 was used for tests.
    digitalWrite(LED_AR_CONDICIONADO, LOW); 
    digitalWrite(LED_AQUECEDOR, HIGH); 
  } else if (temperature >= 25) {
    digitalWrite(LED_AQUECEDOR, LOW); 
    digitalWrite(LED_AR_CONDICIONADO, HIGH); 
  }
  
  if (digitalRead(SENSOR)) {
    digitalWrite(BEEP, HIGH);
  } else {
    digitalWrite(BEEP, LOW); 
  }
  
  Serial.print("Temperature: ");       
  Serial.print(temperature);       
  Serial.println(" *C\n"); 
  
  delay(1000);

}
