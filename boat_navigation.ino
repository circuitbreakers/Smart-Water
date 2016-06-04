
#define START_CMD_CHAR '>'
#define END_CMD_CHAR '\n'
#define DIV_CMD_CHAR ','

#define DEBUG 1 
String inText;
const int
PWM_A   = 5,
DIR_A   = 6,
BRAKE_A = 4,
PWM_B =9,
DIR_B=10,
BRAKE_B=8;
int state;
int flag=0;        
int stateStop=0;
int x,y;
float value0, value1, value2;
void setup() {
  // Configure the A output
  pinMode(BRAKE_A, OUTPUT);  
  pinMode(DIR_A, OUTPUT);    
  pinMode(BRAKE_B, OUTPUT); 
  pinMode(DIR_B, OUTPUT);    
  // Open Serial communication
  Serial.begin(9600);

}

void loop() {

  Serial.flush();
  int inCommand = 0;
  int sensorType = 0;
  unsigned long logCount = 0L;

  char getChar = ' '; 
  if (Serial.available() < 1) return; 
  getChar = Serial.read();
  if (getChar != START_CMD_CHAR) return; 

  // parse incoming pin# and value  
  sensorType = Serial.parseInt(); 
  logCount = Serial.parseInt(); 
  value0 = Serial.parseFloat(); 
  value1 = Serial.parseFloat();  
  value2 = Serial.parseFloat(); 

  }  
  
      Serial.print(x);
      Serial.print(' ');
            Serial.println(y);
    int f=map(x,153,255,0,255);
    int b=map(x,102,0,0,255);
    int r=map(y,114,0,0,255);
    int l=map(y,153,255,0,255);
     if(x>=153)
     {
      digitalWrite(BRAKE_A,LOW);
      digitalWrite(BRAKE_B,LOW);
      digitalWrite(DIR_A,HIGH);
      digitalWrite(DIR_B,HIGH);
      analogWrite(PWM_A,f);
      analogWrite(PWM_B,f);
     }
     else if(x<=102)
     {
      digitalWrite(BRAKE_A,LOW);
      digitalWrite(BRAKE_B,LOW);
      digitalWrite(DIR_A,LOW);
      digitalWrite(DIR_B,LOW);
      analogWrite(PWM_A,b);
      analogWrite(PWM_B,b);
     }
     else if(y>=153)
     {
      digitalWrite(BRAKE_A,LOW);
      digitalWrite(BRAKE_B,LOW);
      digitalWrite(DIR_A,LOW);
      digitalWrite(DIR_B,HIGH);
      analogWrite(PWM_A,0);
      analogWrite(PWM_B,l);
     }
     else if(y<=114)
     {
      digitalWrite(BRAKE_A,LOW);
      digitalWrite(BRAKE_B,LOW);
      digitalWrite(DIR_A,HIGH);
      digitalWrite(DIR_B,LOW);
      analogWrite(PWM_A,r);
      analogWrite(PWM_B,0);
     }
    else
    {
      digitalWrite(BRAKE_A,HIGH);
      digitalWrite(BRAKE_B,HIGH);
    }
  
}
    
  

