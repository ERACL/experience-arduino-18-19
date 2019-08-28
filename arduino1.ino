#include <Servo.h>
#include <Wire.h>

Servo myservo;  // create servo object to control a servo
bool active = false;
int n = 0;

void setup()
{
  Wire.begin();                // join i2c bus (address optional for master)
  pinMode(13, OUTPUT);
  Serial.begin(9600);          // start serial communication at 9600bps
  myservo.attach(10);  // attaches the servo on pin 10 to the servo object
}

int reading = 0;

void loop()
{
  // step 1: instruct sensor to read echoes
  Wire.beginTransmission(112); // transmit to device #112 (0x70)
  // the address specified in the datasheet is 224 (0xE0)
  // but i2c adressing uses the high 7 bits so it's 112
  Wire.write(byte(0x00));      // sets register pointer to the command register (0x00)
  Wire.write(byte(0x51));      // command sensor to measure in "centimeters" (0x51)
  // use 0x51 for centimeters
  // use 0x52 for ping microseconds
  Wire.endTransmission();      // stop transmitting

  // step 2: wait for readings to happen
  delay(70);                   // datasheet suggests at least 65 milliseconds

  // step 3: instruct sensor to return a particular echo reading
  Wire.beginTransmission(112); // transmit to device #112
  Wire.write(byte(0x02));      // sets register pointer to echo #1 register (0x02)
  Wire.endTransmission();      // stop transmitting

  // step 4: request reading from sensor
  Wire.requestFrom(112, 2);    // request 2 bytes from slave device #112

  // step 5: receive reading from sensor
  if (2 <= Wire.available())   // if two bytes were received
  {
    reading = Wire.read();  // receive high byte (overwrites previous reading)
    reading = reading << 8;    // shift high byte to be high 8 bits
    reading |= Wire.read(); // receive low byte as lower 8 bits
    Serial.print(reading);   // print the reading
    Serial.println("cm");
    if (reading > 0 and reading < 40) {
      n++;
    } else {
      // turn LED off:
      n=0;
    }
    if (n > 5) {
      myservo.write(90);
      active = true;
      delay(1000);
      myservo.write(0);
      delay(1000);
      myservo.write(90);
    
    } else {
      // turn LED off:
      myservo.write(0);
    }
  }
  if (active) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);     

  }                 // wait a bit since people have to read the output :)
}
