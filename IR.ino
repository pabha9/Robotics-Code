
//Code for the QRE1113 Digital board
//Outputs via the serial terminal - Lower numbers mean more reflected
//3000 or more means nothing was reflected.
//Authors: Daniel and Huong

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

void setup(){
  Serial.begin(9600);
  pinMode(leftMotor, OUTPUT);
  pinMode(rightMotor, OUTPUT);
 // pinMode(LED3, OUTPUT);
  //pinMode(LED4, OUTPUT);
}


void loop(){
  int LS1 = readQD(IR1);
  int LS2 = readQD(IR2);
  int RS1 = readQD(IR3);
  int RS2 = readQD(IR4);
  Serial.println(LS1); 




  if (LS1<1000 || LS2<1000)
  {
    if (LS1<1000 && RS1<1000)
    // Move backwards if front sees white
    {
      digitalWrite(LED1, HIGH);
      delay(80);
      digitalWrite(LED1, LOW);
    }

    else if (LS2<1000 && RS2<1000)
    // Move foward if back sees white
    {
      digitalWrite(LED2, HIGH);
      delay(80);
      digitalWrite(LED2, LOW);
    }

    else
    // Spin right if ONLY one of the front sensors see white
    {
      digitalWrite(LED3, HIGH);
      delay(80);
      digitalWrite(LED3, LOW);
    }
  }
  

  else
  {
    if (RS1<1000 && LS1<1000)
    // Move foward if the BOTH front sensors see white
    {
      digitalWrite(LED2, HIGH);
      delay(80);
      digitalWrite(LED2, LOW);
    }
  }
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
