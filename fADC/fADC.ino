/*
    fluroplot ADC
    pins:
    cs=10
    sdo/rdy=12
    sck=13
    keypad=2-9
*/
#include <SPI.h>
#include <Keypad.h>
#define F_CPU 16000000UL
unsigned char sspin=10; //cs pin
uint16_t timer=10;
byte a;
union{
		int32_t value;
		uint8_t aa[4];
	} c ;
	
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
 byte rowPins[4] = {9,8,7,6}; //Rows 0 to 3
byte colPins[4]= {5,4,3,2}; //Columns 0 to 3
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},  
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
unsigned int command=0;
void perform_command(unsigned int task);
void send_adc(void);
void set_timer(void);

void setup(){
pinMode(12,INPUT);  //to check ready pin
pinMode(sspin,OUTPUT);
digitalWrite(sspin,HIGH);//for single conversion
SPI.begin();
SPI.setBitOrder(MSBFIRST);
SPI.setDataMode(SPI_MODE3);
SPI.setClockDivider(SPI_CLOCK_DIV16);//max. speed of chip is 5 Mhz
Serial.begin(9600);  

}

void loop(){
char customKey = customKeypad.getKey();
 
if (customKey){
    Serial.print(customKey);
              }
  
if(Serial.available()){
    command=Serial.read();
 //   Serial.print(11); // connection established, command received 
    perform_command(command);                 
                      }
  
  
}


void perform_command(unsigned int task){
switch(task){
    case 1:
          send_adc();
            break;
  
    case 3: 
          set_timer();
            break;

       
           }

}

 void send_adc(void){
  //char customKey = customKeypad.getKey();

  while(command==1){
  
  digitalWrite(sspin,LOW);

while(digitalRead(12)){
  
  digitalWrite(sspin,LOW);
                    
                    }
  c.aa[2]=SPI.transfer(0x00);
  c.aa[1]=SPI.transfer(0x00);
  c.aa[0]=SPI.transfer(0x00);
  c.aa[3]=0x00;
  digitalWrite(sspin,HIGH);
  //check if overflow has occured
  if((c.aa[2]&(1<<6))|(c.aa[2]&(1<<7))){
    c.aa[2]&=~(1<<6);
    Serial.write(c.aa[0]);  
     Serial.write(c.aa[1]);
    Serial.write(c.aa[2]);  
                                      }
//check if sign bit is affected. if so, since it is two's compliment,
// substract it from 2^N
  else if(c.aa[2]&(1<<5)){
    c.value=0x400000-c.value;
   Serial.write(c.aa[0]);
     Serial.write(c.aa[1]);
    Serial.write(c.aa[2]);  
                          }

  else{
   Serial.write(c.aa[0]);
     Serial.write(c.aa[1]);
    Serial.write(c.aa[2]);  
      }  
  delay(timer);
  
  }
  
  /*if(customKey){
  command=2;
  Serial.print(2);}*/
                
  
                    }
void set_timer(void){
    char customKey = customKeypad.getKey();

while(!customKey){}
  a=customKey;
  Serial.parseInt(a);
while(!customKey){}
  timer=1000*a;
  a=customKey;
  timer+=(100*a);
  Serial.parseInt(a);
while(!customKey){}
  a=customKey;
  timer+=(10*a);
  Serial.parseInt(a);               
while(!customKey){}
  a=customKey;
  timer+=a;
  Serial.parseInt(a);  
                  }


