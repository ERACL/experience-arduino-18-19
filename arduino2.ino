#include <Servo.h>

Servo myservo;  // create servo object to control a servo
bool active = false;
int SonarPin=A0;
int sensorValue;
int n = 0;
void setup(){
pinMode(SonarPin,INPUT);
pinMode(13, OUTPUT);
Serial.begin(9600);
myservo.attach(10);  // attaches the servo on pin 10 to the servo object
}

void loop(){
sensorValue=analogRead(SonarPin);
delay(50);
Serial.println(sensorValue);
if (sensorValue < 20) {
    n++;
  } else {
    // turn LED off:
    n=0;
  }
  if (n > 10) {
    myservo.write(90);
    active = true;
    
  } else {
    // turn LED off:
    myservo.write(0);
  }
  if (active) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);     

  }
  }
