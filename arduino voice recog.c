
/////////////////////////////////////////////////////////////////////////////
//////library built in in arduino  
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

/*
  Connection
  Arduino    VoiceRecognitionModule
   2   ------->     TX
   3   ------->     RX
*/
VR myVR(2,3);    // 2:RX 3:TX, you can choose your favourite pins.


/////////////////////////////////////////////////////////////////////////////
//////declaration of pin to be used
const int buttonleft = 8; 
const int buttonright = 9; 
const int buttoncenter = 11; 
int ledleft = 6;
int ledright = 7;









/////////////////////////////////////////////////////////////////////////////
////// system variables
 int buttonlefts = 0;  
 int buttonrights = 0; 
 int buttoncenters = 0; 

int counter=0;

int statusled=0;




/////////////////////////////////////////////////////////////////////////////
///////number of save records
uint8_t records[9]; 
uint8_t buf[64];



/////////////////////////////////////////////////////////////////////////////
///////definition if command name
#define offRecord   (0)
#define rightrec  (1) 
#define leftrec  (2) 
#define hazzardrec  (3) 
#define close1  (4) 
#define kaliwa (5)
#define kanan (6)
#define hinto (7)



 
/**
  @brief   Print signature, if the character is invisible, 
           print hexible value instead.
  @param   buf     --> command length
           len     --> number of parameters
*/
void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){


/////////////////////////////////////////////////////////////////////////////
//////print sa serial port
      Serial.write(buf[i]);
    }
    else{

/////////////////////////////////////////////////////////////////////////////
//////print sa serial port      
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}

/**
  @brief   Print signature, if the character is invisible, 
           print hexible value instead.
  @param   buf  -->  VR module return value when voice is recognized.
             buf[0]  -->  Group mode(FF: None Group, 0x8n: User, 0x0n:System
             buf[1]  -->  number of record which is recognized. 
             buf[2]  -->  Recognizer index(position) value of the recognized record.
             buf[3]  -->  Signature length
             buf[4]~buf[n] --> Signature
*/
void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if(buf[0] == 0xFF){
    Serial.print("NONE");
  }
  else if(buf[0]&0x80){
    Serial.print("UG ");
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}

void setup()
{
  /** initialize */

/////////////////////////////////////////////////////////////////////////////
//////initialize input
    pinMode(buttonleft, INPUT_PULLUP);
    pinMode(buttonright, INPUT_PULLUP);
    pinMode(buttoncenter, INPUT_PULLUP);

/////////////////////////////////////////////////////////////////////////////
////// initialize serial port for voice recognition
    myVR.begin(9600);


/////////////////////////////////////////////////////////////////////////////
////initialize output 
    pinMode(ledleft, OUTPUT);
    pinMode(ledright, OUTPUT);

/////////////////////////////////////////////////////////////////////////////
//// assign led ouput  
    digitalWrite(ledleft, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(ledright, LOW);    // turn the LED off by making the voltage LOW

/////////////////////////////////////////////////////////////////////////////
//// initialize serial port for communication
 
  Serial.begin(115200);
  Serial.println("Elechouse Voice Recognition V3 Module\r\nControl LED sample");

/////////////////////////////////////////////////////////////////////////////
//// check voice recognition module
    
  if(myVR.clear() == 0){
    Serial.println("Recognizer cleared.");
  }else{
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while(1);
  }
  
/////////////////////////////////////////////////////////////////////////////
//// load voice recognition module records
    
  if(myVR.load((uint8_t)leftrec) >= 0){
    Serial.println("onRecord loaded");
  }
  
  if(myVR.load((uint8_t)rightrec) >= 0){
    Serial.println("onRecord loaded");
  }

  
  if(myVR.load((uint8_t)hazzardrec) >= 0){
    Serial.println("onRecord loaded");
  }
    
  if(myVR.load((uint8_t)kaliwa) >= 0){
    Serial.println("offRecord loaded");
  }  


  if(myVR.load((uint8_t)kanan) >= 0){
    Serial.println("offRecord loaded");
  }  

  if(myVR.load((uint8_t)hinto) >= 0){
    Serial.println("offRecord loaded");
  }  
  
  if(myVR.load((uint8_t)close1) >= 0){
    Serial.println("offRecord loaded");
  }
  
  if(myVR.load((uint8_t)offRecord) >= 0){
    Serial.println("offRecord loaded");
  }
}
/////////////////////////////////////////////////////////////////////////////
////main loop programs
void loop()
{
/////////////////////////////////////////////////////////////////////////////
////switch checking
buttonlefts = digitalRead(buttonleft);
buttonrights = digitalRead(buttonright);
buttoncenters = digitalRead(buttoncenter);
 
  
  if (buttonlefts == LOW) {       statusled=2; } 
  if (buttonrights == LOW) {   statusled=3;} 
  if (buttonlefts == LOW and buttonrights == LOW) {   statusled=1;} 
 
  
  // logic if switch is low
  
  if (buttoncenters == LOW) {
      statusled=0;
        /** turn on LED */
        Serial.println("off");
          digitalWrite(ledleft, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(ledright, LOW);    // turn the LED off by making the voltage LOW
 } 







/////////////////////////////////////////////////////////////////////////////
//// check for voice recognition output
  
  int ret;
  ret = myVR.recognize(buf, 50);
  if(ret>0){
    switch(buf[1]){
      case hazzardrec:
        /** turn on LED */
        statusled=1;
         Serial.println("hazzard");
        break;
      case leftrec:
        /** turn on LED */

        statusled=2;
         Serial.println("left");
        break;

      case rightrec:
        /** turn on LED */
 statusled=3;

        Serial.println("right");
        break;

      case close1:
      statusled=0;
        /** turn on LED */
        Serial.println("off");
          digitalWrite(ledleft, LOW);    // turn the LED off by making the voltage LOW
 
    digitalWrite(ledright, LOW);    // turn the LED off by making the voltage LOW
 
        
        break;


 case kaliwa:
        /** turn on LED */

        statusled=2;
         Serial.println("left");
        break;

      case kanan:
        /** turn on LED */
 statusled=3;

        Serial.println("right");
        break;


      case hinto:
      statusled=0;
        /** turn on LED */
        Serial.println("stop");
       digitalWrite(ledleft, LOW);    // turn the LED off by making the voltage LOW
 
    digitalWrite(ledright, LOW);    // turn the LED off by making the voltage LOW
    
        break;



     
      default:
        Serial.println("Record function undefined");
        break;
    }
    /** voice recognized */
  



  
  }


/////////////////////////////////////////////////////////////////////////////
//// led output logic



   // printVR(buf);
   delay(1);
  counter++;
   //Serial.println(  counter);
  if (counter>20){counter=0;}
  if (statusled==1)
  { if (counter<10){
          digitalWrite(ledleft, HIGH);    // turn the LED off by making the voltage LOW
 
    digitalWrite(ledright, HIGH);    // turn the LED off by making the voltage LOW
    Serial.println(  counter);
    }
    if (counter>10){
      
             digitalWrite(ledleft, LOW);    // turn the LED off by making the voltage LOW
 
    digitalWrite(ledright, LOW);    // turn the LED off by making the voltage LOW
 Serial.println("off");
        
      }
   }


  if (statusled==2)
  { if (counter<10){
          digitalWrite(ledleft, HIGH);    // turn the LED off by making the voltage LOW
 
    digitalWrite(ledright,LOW);    // turn the LED off by making the voltage LOW
    
    }
    if (counter>10){
      
             digitalWrite(ledleft, LOW);    // turn the LED off by making the voltage LOW
 
    digitalWrite(ledright, LOW);    // turn the LED off by making the voltage LOW
 
        
      }
   }
  if (statusled==3)
  { if (counter<10){
          digitalWrite(ledleft, LOW);    // turn the LED off by making the voltage LOW
 
    digitalWrite(ledright, HIGH);    // turn the LED off by making the voltage LOW
    
    }
    if (counter>10){
      
             digitalWrite(ledleft, LOW);    // turn the LED off by making the voltage LOW
 
    digitalWrite(ledright, LOW);    // turn the LED off by making the voltage LOW
 
        
      }
   }




}

