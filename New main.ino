#include <stdio.h>
#include <SoftwareSerial.h>
#include <SabertoothSimplified.h>

/*This code is from an experiment done in robotics. Author is unknown. Not our original work.
#include <SoftwareSerial.h>
#include <SabertoothSimplified.h> */
// motor pins
SoftwareSerial SWSerial1(NOT_A_PIN, 11); // RX on no pin (unused), TX on pin 11 (to S1).
SabertoothSimplified ST1(SWSerial1); // Use SWSerial as the serial port.
SoftwareSerial SWSerial2(NOT_A_PIN, 9); // RX on no pin (unused), TX on pin 11 (to S1).
SabertoothSimplified ST2(SWSerial2); // Use SWSerial as the serial port.
//ultrasonic pin
const int pingPin = 10;
//const int LED = 8; // LED connected to digital pin 8
bool button_pressed=false;
int Power = 0;  // Power going into motors
long cm;    // Distance in cm

void setup() {
  //some setup for the motor library
  SWSerial1.begin(9600);
  //SWSerial2.begin(9600);
  //start the serial output
  Serial.begin(9600);
  //pinMode(LED, OUTPUT);
  pinMode(3,INPUT);
}

void loop() 
{
  if(digitalRead(3)==LOW)
  {
    button_pressed=true;
    delay(5000);
  }
  if (button_pressed)
  {
      cm=CheckDistance();
     // digitalWrite(LED,HIGH);
                                   /*if (cm>30)
                                   {
                                    Robot will push opponent is greater than 30cm
                                   !!! NEED TO ADD A PUSHING MECAHNISM TO THIS
                                  if (Power != 127)
                                  If power isn't the maximum
                                   {
                                    Ramp from -127 to 127 (full reverse to full forward), waiting 20 ms (1/50th of a second) per value. */
        while (cm > 30 && cm <200)
        {
          for (int i = Power; i <= 127; i=i+10)
          {
            ST1.motor(1, i);
            ST1.motor(2, i);
            ST2.motor(1, i);
            ST2.motor(2, i);
            delay(20);
          }
        Power=127;
        cm = CheckDistance();
        }// close bracket for while loop
  
        //
   
  
   cm=CheckDistance();
  
    if (cm == 0) // if opponent is not detected
    // If robot is greater than 10cm away, start backing off.
    // POTENTIALLY TAKE THIS OUT.
    {
      if (Power != 0)
      {
        // Ramp from 127 to 0
        for (int i = Power; i >=0; i = i-10)
        {
          ST1.motor(1, i);
          ST1.motor(2, i);
          ST2.motor(1, -1*i);
          ST2.motor(2, -1*i);
          delay(20);
        }
        Power=0;
      }
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
