
//Code for the QRE1113 Digital board
//Outputs via the serial terminal - Lower numbers mean more reflected
//3000 or more means nothing was reflected.

int IR1 = 4; //connected to digital 2
int IR2 = 5;
int IR3 = 6;
int IR4 = 7;
int LED1 = 12;  // move backwards   digital pin 12
int LED2 = 11;  // move fowards     digital pin 11
int LED3 = 10;  // move right       digital pin 10 
int LED4 = 9;   // move left        digital pin 9



void setup(){
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop()
{
  IR_Sensor_Mod();
}


void IR_Sensor_Mod()
{
  int LS1 = readQD(IR1);
  int LS2 = readQD(IR2);
  int RS1 = readQD(IR3);
  int RS2 = readQD(IR4);
  Serial.println(LS1); 

  if (LS1<2500 && RS1<2500)
  {
    // Move backwards if front sees white
      digitalWrite(LED1, HIGH);
      delay(80);
      digitalWrite(LED1, LOW);
   }

   else if (LS2<2500 && RS2<2500)
   {
   // Move fowards if back sees white
      digitalWrite(LED2, HIGH);
      delay(80);
      digitalWrite(LED2, LOW);
   }

   else if (LS1<2500 || LS2<2500)
   {
    // Turn right if any of the left sensors see white
     digitalWrite(LED4, HIGH);
     delay(80);
     digitalWrite(LED4, LOW);
   }

   else if (RS1<2500 || RS2<2500)
   {
   // Turn left if any of the right sensors see white
      digitalWrite(LED3, HIGH);
      delay(80);
      digitalWrite(LED3, LOW);
   }
} //end of the IR_Sensor_Mod 

int readQD(int sensor_number)
{
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
}  // end of readQD


  
