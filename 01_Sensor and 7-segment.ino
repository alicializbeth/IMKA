//Project - Sensor IMKA
int aPin = 8;  
int bPin = 9;  
int cPin = 10; 
int dPin = 11; 
int ePin = 12;
int fPin = 13;  
int gPin = A0;
int ledPin = A1; 
int ledPin2 = A2;
int ledPin3 = A3;
// Value read from LDR 
int lightVal = 0;
int score;
int puluhan;
int satuan;
int ratusan = 0;

//Sensor Jarak   
#define echoPin 2 // Echo Pin yang dekat ground
#define trigPin 3 // Trigger Pin
int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance


void setup() 
{
// Set both pins as outputs
Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(aPin, OUTPUT);
 pinMode(bPin, OUTPUT);
 pinMode(cPin, OUTPUT);
 pinMode(dPin, OUTPUT);
 pinMode(ePin, OUTPUT);
 pinMode(fPin, OUTPUT);
 pinMode(gPin, OUTPUT);
 Serial.begin(9600);
 analogReference(INTERNAL);
 pinMode(ledPin, OUTPUT); 
 pinMode(ledPin2, OUTPUT); 
 pinMode(ledPin3, OUTPUT); 
}     

  void loop() {
/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
 


 if (distance >= maximumRange || distance <= minimumRange){
 /* Send a negative number to computer and Turn LED ON 
 to indicate "out of range" */
 Serial.println("-1");
 }
 else {
 /* Send the distance to the computer using Serial protocol, and
 turn LED OFF to indicate successful reading. */
       Serial.println(distance);
       satuan = distance % 10;
       Serial.println(satuan);
       pickNumber(satuan);
       digitalWrite(ledPin, LOW);
       digitalWrite(ledPin2, HIGH); //A2 ledpin 7 segmen kiri
       digitalWrite(ledPin3, HIGH);
       delay(10);
       
       
       puluhan = (distance %100)/10;
       Serial.println(puluhan);
       pickNumber(puluhan); 
       digitalWrite(ledPin2, LOW);
       digitalWrite(ledPin, HIGH); //A1 ledpin 7 segmen kanan
       digitalWrite(ledPin3, HIGH);
       delay(10);

       ratusan = distance / 100;
       Serial.println(ratusan);
       pickNumber(ratusan);
       digitalWrite(ledPin3, LOW);
       digitalWrite(ledPin2, HIGH); //A2 ledpin 7 segmen kiri
       digitalWrite(ledPin, HIGH);
       delay(10);
 }
 
 //Delay 50ms before next reading.
 delay(50);
}

     


void pickNumber(int x){
   switch(x){
     case 1: one(); break;
     case 2: two(); break;
     case 3: three(); break;
     case 4: four(); break;
     case 5: five(); break;
     case 6: six(); break;
     case 7: seven(); break;
     case 8: eight(); break;
     case 9: nine(); break;
     default: zero(); break;
   } 
}

void one()
{
  digitalWrite(aPin, 0);
  digitalWrite(bPin, 1);
  digitalWrite(cPin, 1);
  digitalWrite(dPin, 0);
  digitalWrite(ePin, 0);
  digitalWrite(fPin, 0);
  digitalWrite(gPin, 0);
}

void two()
{
  digitalWrite(aPin, 1);
  digitalWrite(bPin, 1);
  digitalWrite(cPin, 0);
  digitalWrite(dPin, 1);
  digitalWrite(ePin, 1);
  digitalWrite(fPin, 0);
  digitalWrite(gPin, 1); 
}

void three()
{
  digitalWrite(aPin, 1);
  digitalWrite(bPin, 1);
  digitalWrite(cPin, 1);
  digitalWrite(dPin, 1);
  digitalWrite(ePin, 0);
  digitalWrite(fPin, 0);
  digitalWrite(gPin, 1); 
}

void four()
{
  digitalWrite(aPin, 0);
  digitalWrite(bPin, 1);
  digitalWrite(cPin, 1);
  digitalWrite(dPin, 0);
  digitalWrite(ePin, 0);
  digitalWrite(fPin, 1);
  digitalWrite(gPin, 1); 
}

void five()
{
  digitalWrite(aPin, 1);
  digitalWrite(bPin, 0);
  digitalWrite(cPin, 1);
  digitalWrite(dPin, 1);
  digitalWrite(ePin, 0);
  digitalWrite(fPin, 1);
  digitalWrite(gPin, 1); 
}

void six()
{
  digitalWrite(aPin, 1);
  digitalWrite(bPin, 0);
  digitalWrite(cPin, 1);
  digitalWrite(dPin, 1);
  digitalWrite(ePin, 1);
  digitalWrite(fPin, 1);
  digitalWrite(gPin, 1); 
}

void seven()
{
  digitalWrite(aPin, 1);
  digitalWrite(bPin, 1);
  digitalWrite(cPin, 1);
  digitalWrite(dPin, 0);
  digitalWrite(ePin, 0);
  digitalWrite(fPin, 0);
  digitalWrite(gPin, 0); 
}

void eight()
{
  digitalWrite(aPin, 1);
  digitalWrite(bPin, 1);
  digitalWrite(cPin, 1);
  digitalWrite(dPin, 1);
  digitalWrite(ePin, 1);
  digitalWrite(fPin, 1);
  digitalWrite(gPin, 1); 
}

void nine()
{
  digitalWrite(aPin, 1);
  digitalWrite(bPin, 1);
  digitalWrite(cPin, 1);
  digitalWrite(dPin, 1);
  digitalWrite(ePin, 0);
  digitalWrite(fPin, 1);
  digitalWrite(gPin, 1); 
}

void zero()
{
  digitalWrite(aPin, 1);
  digitalWrite(bPin, 1);
  digitalWrite(cPin, 1);
  digitalWrite(dPin, 1);
  digitalWrite(ePin, 1);
  digitalWrite(fPin, 1);
  digitalWrite(gPin, 0); 
}
