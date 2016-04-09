
#include <stdio.h>
#include <SoftwareSerial.h>
#include <SabertoothSimplified.h>

/*This code is from an experiment done in robotics. Author is unknown. Not our original work.
#include <SoftwareSerial.h>
#include <SabertoothSimplified.h> */
// motor pins
SoftwareSerial SWSerial1(NOT_A_PIN, 11); // RX on no pin (unused), TX on pin 11 (to S1).
SabertoothSimplified ST1(SWSerial1); // Use SWSerial as the serial port.
//SoftwareSerial SWSerial2(NOT_A_PIN, 10); // RX on no pin (unused), TX on pin 11 (to S1).
//SabertoothSimplified ST2(SWSerial2); // Use SWSerial as the serial port.
//ultrasonic pin
const int pingPin = 13;
int IR1 = 6; //connected to digital 6
int IR2 = 7;
int IR3 = 8;
int IR4 = 9;
/*int LED1 = 12;  // move backwards
int LED2 = 11;  // move fowards
int LED3 = 10;  // move right
int LED4 = 9;   // move left*/
int leftMotor = 10;//left port
int rightMotor = 11; //right port 


int Power = 0;  // Power going into motors
long cm;    // Distance in cm

void setup() {
  //some setup for the motor library
  SWSerial1.begin(9600);
  //SWSerial2.begin(9600);
  //start the serial output
  Serial.begin(9600);
  pinMode(leftMotor, OUTPUT);
  pinMode(rightMotor, OUTPUT);
  
  delay(5000);  // delays the robot for 5 seconds before moving as per competition rules
}

void loop() {

  cm=CheckDistance();

  if (cm<10)
  {
    // Robot will push opponent is less than 10cm
    // !!! NEED TO ADD A PUSHING MECAHNISM TO THIS
  int LS1 = readQD(IR1);
  int LS2 = readQD(IR2);
  int RS1 = readQD(IR3);
  int RS2 = readQD(IR4);
    if (Power != 127)
    // If power isn't the maximum
    {
      // Ramp from -127 to 127 (full reverse to full forward), waiting 20 ms (1/50th of a second) per value.
      for (int i = Power; i <= 127; i ++)
      {
        ST1.motor(1, i);
        ST1.motor(2, i);
        //ST2.motor(1, -1*i);
        //ST2.motor(2, -1*i);
        if (LS1<1000 || LS2<1000)
  {
    if (LS1<1000 && RS1<1000)
    // Move backwards if front sees white
    {
      digitalWrite(rightMotor, HIGH);
      //delay(80);
      digitalWrite(leftMotor, HIGH);
    }

    else if (LS2<1000 && RS2<1000)
    // Move foward if back sees white
    {
      digitalWrite(rigthMotor, HIGH);
      //delay(80);
      digitalWrite(leftMotor, HIGH);
    }

    else
    // Spin right if ONLY one of the front sensors see white
    if(RS1 < 1000 || RS2 < 1000)
    {
      digitalWrite(leftMotor, HIGH);
      delay(80);
      digitalWrite(rigthMotor, LOW);
    }
    else if(LS1 < 1000 || LS2 < 1000)//turn left 
    {
      digitalWrite(rightMotor, HIGH);
      delay(80);
      digitalWrite(leftMotor, LOW);
    }
    
  }
  

  else
  {
    if (RS1<1000 && LS1<1000)
    // Move foward if the BOTH front sensors see white
    {
      digitalWrite(rightMotor, HIGH);
      delay(80);
      digitalWrite(leftMotor, HIGH);
    }
  }
}

        delay(20);
      }
      Power=127;
    }
  }

 cm=CheckDistance();

  if (cm>10)
  // If robot is greater than 10cm away, start backing off.
  // POTENTIALLY TAKE THIS OUT.
  {
    if (Power != 0)
    {
      // Ramp from 127 to 0
      for (int i = Power; i >=0; i --)
      {
        ST1.motor(1, i);
        ST1.motor(2, i);
        //ST2.motor(1, -1*i);
        //ST2.motor(2, -1*i);
        delay(20);
      }
      Power=0;
    }
  } 
  
}

// Ultrasonic needs this for stuff
long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}
// Ultrasonic needs this for stuff
long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}


long CheckDistance(void) // checks distance from a near object to the robot 
{
  long duration,inches,cm;  
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(cm);
  Serial.print(" cm");
  Serial.println();
  
  return cm;
}
int readQD(int sensor_number){
  //Returns value from the QRE1113 
  //Lower numbers mean more refleacive
  //More than 3000 means nothing was reflected.
  pinMode( sensor_number, OUTPUT );
  digitalWrite( sensor_number, HIGH );  
  delayMicroseconds(10);
  pinMode( sensor_number, INPUT );

  long time = micros();

  //time how long the input is HIGH, but quit after 3ms as nothing happens after that
  while (digitalRead(sensor_number) == HIGH && micros() - time < 3000); 
  int diff = micros() - time;

  return diff;
}  
