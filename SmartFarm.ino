#include <SoftwareSerial.h>
#include <Servo.h>
#include <stdlib.h>
#define DEBUG true

//soil moisture sensor
int SENSE= 0; // Soil Sensor input at Analog PIN A0
int value= 0;
String apiKey = "7JJJ2SL0384EN9PB"; // Ubah dengan API Key ente bro!
SoftwareSerial ser(10,11); // RX, TX
int moist = 0;
int prevmoist = 1;

//servo
Servo myservo;
int pos;

void setup() {
  Serial.begin(115200);
  ser.begin(115200);
  connectWifi();
  myservo.attach(9);
  Serial.println("SOIL MOISTURE SENSOR");
  Serial.println("-----------------------------");
}

void loop() {
   value= analogRead(SENSE);
   value= value/10;
   Serial.println("VALUE: ");
   Serial.println(value);
   if(value<50)
   {
      moist = 1;
      Serial.println ("MOIST");
      if (prevmoist == 0) {
         tutup();
      }
   }
   else
   {
      moist = 0;
      Serial.println ("NOT MOIST");
      if (prevmoist == 1) {
        buka();
      }
   }
  char buf[16];
  String strM = dtostrf(moist, 1, 1, buf);
  sendData(strM);
  prevmoist = moist;
  delay(5000);
    if (Serial.available() > 0) 
      {
        char ch = ser.read();
        ser.print(ch);
      }
      if (ser.available() > 0) 
      {
        char ch = ser.read();
        Serial.print(ch);
      }
      delay(1000); //gaboleh diilangin!
}

//-------------------------------------------------------------------------------------------------
 
  void connectWifi()
  {
    //Set-wifi
  Serial.print("Restart Module...\n");
  sendCommand("AT+RST\r\n",2000,DEBUG); // reset module
  delay(5000);
  Serial.print("Set wifi mode : STA...\n");
  sendCommand("AT+CWMODE=1\r\n",1000,DEBUG); // configure as access point
  delay(5000);
  Serial.print("Connect to access point...\n");
  sendCommand("AT+CWJAP=\"Alicia\",\"cfjr6533\"\r\n",3000,DEBUG);
  delay(5000);
  Serial.print("Check IP Address...\n");
  sendCommand("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  delay(5000);
   // sendCommand("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
   // sendCommand("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80

  /*  String cmd = "AT+CIPSTART=\"TCP\",\"";
  
    cmd += HOST;
    cmd += "\",80\r\n";
     sendCommand(cmd,1000,DEBUG);*/
     delay(2000);
  }

//-------------------------------------------------------------------------------------------------
 
  String sendCommand(String command, const int timeout, boolean debug)
  {
      String response = "";
             
      ser.print(command); // send the read character to the esp8266
      
      long int time = millis();
      
      while( (time+timeout) > millis())
      {
        while(ser.available())
        {
          
          // The esp has data so display its output to the serial window 
          char c = ser.read(); // read the next character.
          response+=c;
        }  
      }
      
      if(debug)
      {
        Serial.print(response);
      }
      
      return response;
  }
  
//-------------------------------------------------------------------------------------------------
 
    void sendData(String data)
    {
    //if (Serial1.find("CLOSE") )
    {
    String cmd = "AT+CIPSTART=\"TCP\",\"";
  
    cmd += "184.106.153.149";
    cmd += "\",80\r\n";
     sendCommand(cmd,1000,DEBUG);
     delay(2000);
    }
    
    String cmd2 = "GET /update?api_key="; // Link ke alamat server
    cmd2 += apiKey;  
    cmd2 +="&field1=";
    cmd2 += data;
    cmd2 += "\r\n\r\n\r\n";
    String pjg="AT+CIPSEND=";
    pjg += cmd2.length();
    pjg += "\r\n";
    
    sendCommand(pjg,1000,DEBUG);
    delay(500);
    sendCommand(cmd2,1000,DEBUG);
    delay(5000);
    }
//-------------------------------------------------------------------------------------------------
void buka() {
   for (pos = 0; pos <90; pos+= 1) {
     myservo.write(pos);
     delay(15);
   }
}

//-------------------------------------------------------------------------------------------------
void tutup() {
   for (pos = 90; pos >=1; pos-= 1) {
     myservo.write(pos);
     delay(15);
   }
}
