// include the EduIntro library
#include <EduIntro.h>

DHT11 dht11(D4);  // creating the object sensor on pin 'D4'

int water = 12;
int fan = 11;
int light = 10;

int time = 0;
int DC = 0;
int C;   // temperature C readings are integers

void setup() {
  Serial.begin (9600);
  
  pinMode (fan, OUTPUT);
  digitalWrite (fan, HIGH); //fan turn off

  pinMode (water, OUTPUT);
  digitalWrite (water, HIGH);  //water pump turn off

  pinMode (light, OUTPUT);
  digitalWrite (light, HIGH); //light turn off
}

void loop() {
  //time
  delay(1000);
  time = time + 1;
  Serial.print ("time: ");
  Serial.println (time);
  
  //temperature
  if (time%300 == 0) { //300s = 5mins
    dht11.update();
    C = dht11.readCelsius();
    Serial.print ("temperature:");
    Serial.println (C);
    if (C > 25) {
      digitalWrite (fan, LOW);
      Serial.println ("fan is on");
    } else if (22 > C) {
      digitalWrite (fan, HIGH);
      Serial.println ("fan is off");
    }
  }

  //light
  digitalWrite (light, LOW);
  Serial.println ("light is on");

  //dirt
  if (time%18000 == 0) { //18000s = 5hrs
    int sensorReading = analogRead(A0);
    Serial.print ("moisture value: ");
    Serial.println (sensorReading);
    if (sensorReading > 250) {
      digitalWrite (water, LOW);
      Serial.println ("water pump is on");
      DC = time;
    }
  }
  
  if (DC + 6 > time && time > DC + 4) {
    digitalWrite (water, HIGH);
    Serial.println ("water pump is off");
  }
  Serial.print ("DC: ");
  Serial.println (DC);
}
