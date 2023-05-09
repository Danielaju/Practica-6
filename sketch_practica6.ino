#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>
#include <RTClib.h>



#define lcdAddress 0x27  
#define filas 2
#define columnas 16
LiquidCrystal_I2C pantallalcd(lcdAddress, columnas, filas);

OneWire ourWire(5);
DallasTemperature sensors(&ourWire);

RTC_DS3231 RTC;

#define buzzer 6
#define salidabuzzer() pinMode(buzzer,OUTPUT)
#define encendidobuzzer() tone(buzzer,1000)
#define apagadobuzzer() noTone(buzzer)

#define bomba 7
#define salidabomba() pinMode(bomba,OUTPUT)
#define encedidobomba() digitalWrite(bomba,HIGH)
#define apagdidobomba() digitalWrite(bomba,LOW)



void setup() {
  pantallalcd.init();
  pantallalcd.backlight();
  sensors.begin();
  RTC.begin();
  RTC.adjust(DateTime(__DATE__, __TIME__));
  salidabuzzer();
  salidabomba();

}

void loop() {
  sensors.requestTemperatures();
  float temp1 = sensors.getTempFByIndex(0);
  pantallalcd.setCursor(0,1);
  pantallalcd.print(temp1);
  pantallalcd.print("F  ");
  

  DateTime fecha = RTC.now();
  Serial.print(fecha.hour());
  Serial.print(":");
  Serial.print(fecha.minute());
  Serial.print(":");
  Serial.println(fecha.second());
  pantallalcd.print(fecha.hour());
  pantallalcd.print(":");				
  pantallalcd.print(fecha.minute());
  delay(100);


  if (fecha.hour() ==10 && fecha.minute() == 1 && fecha.second() == 0){
    encendidobuzzer();
    delay(100);
    delay(5000);
  } else {
    apagadobuzzer();
  }

  if (fecha.hour() ==10 && fecha.minute() == 1 && fecha.second() == 10){
    encendidobuzzer();
    delay(100);
    delay(5000);
  } else {
    apagadobuzzer();
  }

  if (fecha.hour() ==10 && fecha.minute() == 1 && fecha.second() == 15){
    encendidobuzzer();
    delay(100);
    delay(5000);
  } else {
    apagadobuzzer();
  }
  
  if (fecha.hour() == 22 && fecha.minute() == 1 && fecha.second() == 20) {
  pantallalcd.setCursor(0,0);
  pantallalcd.print("hora de regar");
  delay(20000);
  pantallalcd.clear();
  } else{
    encedidobomba();
  }

}