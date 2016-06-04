
#include <SPI.h>
#include <SD.h>
#include <OneWire.h>
#include <Wire.h>
#define SensorPin 0          //pH meter Analog output to Arduino Analog Input 0
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;
int i=0;
String c;
OneWire  ds(4);
const int chipSelect = 10;
int led=7;

File dataFile;
char filename[]= "LOGGER00.txt";
void setup() {
  Wire.begin();
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
}
 
 for (uint8_t i = 0; i < 100; i++) {
    filename[6] = i/10 + '0';
    filename[7] = i%10 + '0';
    if (! SD.exists(filename)) {
      // only open a new file if it doesn't exist
      Serial.println(filename);
      break;  // leave the loop!
    }
  }
}
void loop() {
  digitalWrite(led,LOW);

 Wire.requestFrom(8,20);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    c = Wire.readString(); // receive a byte as character
       // print the character
  }

  delay(200);
  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue;                      //convert the millivolt into pH value


  byte data[12];
  byte addr[8];
 
  
  if ( !ds.search(addr)) {
    Serial.println("No more addresses.");
    Serial.println();
    ds.reset_search();
    delay(250);
    return;
  }
  
 
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  delay(759);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad


  for ( int i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  
  }

ds.reset_search();

byte MSB = data[1];
byte LSB = data[0];

float raw = ((MSB << 8) | LSB); // move MSB left for 8 spaces, join that with LSB
float celsius = raw / 16; // move decimal point left for 4 spaces, result our temperature
  String dataString =String(celsius);
String dataString1=String(phValue);


  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.

dataFile = SD.open(filename, FILE_WRITE);
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.print("temp:");
    dataFile.print(dataString);
    dataFile.print(";");
    dataFile.print("pH:");
    dataFile.print(dataString1);
    dataFile.print(";");
    dataFile.print("GPS:");
    dataFile.println(c);
    dataFile.close();
    // print to the serial port too:
    Serial.print(dataString);
    Serial.print(",");
    Serial.print(dataString1);
        Serial.print(",");
    Serial.println(c);
    digitalWrite(led,HIGH);
    delay(100);
    digitalWrite(led,LOW);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
    digitalWrite(led,HIGH);
    delay(2000);
    
  }
}


