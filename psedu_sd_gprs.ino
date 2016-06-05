#include <SoftwareSerial.h>
#include <String.h>
SoftwareSerial mySerial(10, 11);                                                      //your pins to serial communication

//-------------------------------------------------------------
//---------------------Ubidots Configuration-------------------
//-------------------------------------------------------------
String token = "odraNN8HGIPNuPmpwdFAQC3wlqTs6e";      //your token to post value
String idvariable = "56fea5e57625422eb1b8bc93";                                     //ID of your variable
String idvariable2 = "56fea5ef7625423fa0bf5f1c";    

#include <SPI.h>
#include <SD.h>

File myFile;
String tempMsg;
String e;
String b;
String c;String d;

void setup()
{
pinMode(46,OUTPUT);
digitalWrite(46,HIGH);

  mySerial.begin(9600);                                                            //the GPRS baud rate
  Serial.begin(9600);                                                              //the serial communication baud rate

 while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

 

  

  
}

void loop()
{
myFile = SD.open("DATA1.txt");
  if (myFile) {
   

    // read from the file until there's nothing else in it:
   for(float a=0;a<1500;a++)
   { if (myFile.available()) {
      

 String tempMsg = myFile.readStringUntil('\n');
    
      
    
 e = tempMsg.substring(0, 5);
    b = tempMsg.substring(6, 10);
    c = tempMsg.substring(11, 20);
    d = tempMsg.substring(22);
    
Serial.println(e);
Serial.println(b);
Serial.println(c);
Serial.println(d);

save_value(e);                                                      //call the save_value function
save_value2(b);

      
    }}
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

                                                         
     
    
    if (mySerial.available())
    Serial.write(mySerial.read());
}
//this function is to send the sensor data to Ubidots, you should see the new value in Ubidots after executing this function






void save_value(String value)
{//temperature block
  int num;
  String le;
  String var;
  String Location = "";
   
  Location = "{\"lat\":" + c + ",\"lng\":" + d + "}";// c and d are lat and lon
var="{\"value\":"+ value + ", \"context\":"+ Location + "}";
num=var.length();
  le=String(num);
  for(int i = 0;i<4;i++)
  {
    mySerial.println("AT+CGATT?");                                                   //this is made repeatedly because it is unstable
    delay(1000);
    ShowSerialData();
  }

  mySerial.println("AT+CIFSR");                                                      //get local IP adress
  delay(2000);
  ShowSerialData();
  mySerial.println("AT+CIPSPRT=0");
  delay(2000);
  ShowSerialData();
  mySerial.println("AT+CIPSTART=\"tcp\",\"things.ubidots.com\",\"80\"");             //start up the connection
  delay(2000);
  ShowSerialData();
  mySerial.println("AT+CIPSEND");                                                    //begin send data to remote server
  delay(2000);
  ShowSerialData();
  ShowSerialData();
  mySerial.print("POST /api/v1.6/variables/"+idvariable);
  delay(100);
  ShowSerialData();
  mySerial.println("/values HTTP/1.1");
  delay(100);
  ShowSerialData();
  mySerial.println("Content-Type: application/json");
  delay(100);
  ShowSerialData();
  mySerial.println("Content-Length: "+le);
  delay(100);
  ShowSerialData();
  mySerial.print("X-Auth-Token: ");
  delay(100);
  ShowSerialData();
  mySerial.println(token);
  delay(100);
  ShowSerialData();
  mySerial.println("Host: things.ubidots.com");
  delay(100);
  ShowSerialData();
  mySerial.println();
  delay(100);
  ShowSerialData();
  mySerial.println(var);
  delay(100);
  ShowSerialData();
  mySerial.println();
  delay(100);
  ShowSerialData();
  mySerial.println((char)26);
  delay(1000);
  mySerial.println();
  ShowSerialData();
  mySerial.println("AT+CIPCLOSE");                                                //close the communication
  delay(1000);
  ShowSerialData();
}



void save_value2(String value)
{//temperature block
  int num;
  String le;
  String var;
  String Location = "";
   
  Location = "{\"lat\":" + c + ",\"lng\":" + d + "}";// c and d are lat and lon
var="{\"value\":"+ value + ", \"context\":"+ Location + "}";
num=var.length();
  le=String(num);
 
  ShowSerialData();
  mySerial.println("AT+CIPSTART=\"tcp\",\"things.ubidots.com\",\"80\"");             //start up the connection
  delay(2000);
  ShowSerialData();
  mySerial.println("AT+CIPSEND");                                                    //begin send data to remote server
  delay(2000);
  ShowSerialData();
  ShowSerialData();
  mySerial.print("POST /api/v1.6/variables/"+idvariable2);
  delay(100);
  ShowSerialData();
  mySerial.println("/values HTTP/1.1");
  delay(100);
  ShowSerialData();
  mySerial.println("Content-Type: application/json");
  delay(100);
  ShowSerialData();
  mySerial.println("Content-Length: "+le);
  delay(100);
  ShowSerialData();
  mySerial.print("X-Auth-Token: ");
  delay(100);
  ShowSerialData();
  mySerial.println(token);
  delay(100);
  ShowSerialData();
  mySerial.println("Host: things.ubidots.com");
  delay(100);
  ShowSerialData();
  mySerial.println();
  delay(100);
  ShowSerialData();
  mySerial.println(var);
  delay(100);
  ShowSerialData();
  mySerial.println();
  delay(100);
  ShowSerialData();
  mySerial.println((char)26);
  delay(1000);
  mySerial.println();
  ShowSerialData();
  mySerial.println("AT+CIPCLOSE");                                                //close the communication
  delay(1000);
  ShowSerialData();
}




void ShowSerialData()
{
  while(mySerial.available()!=0)
  Serial.write(mySerial.read());
}


