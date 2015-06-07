/*
    fluroplot LCD
*/

#include <Adafruit_GFX.h>    // Core graphics library
#include "SWTFT.h" // Hardware-specific library
// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define BOXSIZE 70
SWTFT tft;
byte xpos=0;
byte xpos2=0;
word ypos=3;
int komut;
byte a;
union{
		int32_t value;
		uint8_t aa[4];
	} c ;


void printLCD(int32_t val){
   xpos=(val*230)/2097152;
  tft.drawLine(xpos2,ypos-3,xpos,ypos,RED);
    xpos2=xpos;
    ypos=ypos+3;

if(ypos>300){
  ypos=0;
tft.fillScreen(BLACK);}
tft.drawLine(240,300,240,320,BLUE);
tft.setCursor(220,300);
tft.setTextSize(1);
tft.print("5V");
tft.drawLine(160,300,160,320,BLUE);
tft.setCursor(140,300);
tft.print("3.3V");
tft.drawLine(120,300,120,320,BLUE);
tft.setCursor(100,300);
tft.print("2.5V");
tft.drawLine(60,300,60,320,BLUE);
tft.setCursor(40,300);
tft.print("1.25V");
tft.drawLine(0,300,0,320,BLUE);

}


void returnmenu(void);
void processing_data(void){
  Serial.write(1);
while(komut==10){
   while(Serial.available()<3){}
  c.aa[0]=Serial.read();
  c.aa[1]=Serial.read();
  c.aa[2]=Serial.read();
 
   printLCD(c.value);
                }
  
}

void menu1(void){
  komut=10;
 tft.setCursor(10,10);
      tft.fillScreen(BLACK);
    processing_data();

  }


void menu3(void){

komut=10;
       tft.fillScreen(BLUE);
Serial.write(3);
while(!Serial.available()){}
a=Serial.parseInt();
tft.setCursor(40,40);
tft.setTextSize(2);
tft.print(a);
while(!Serial.available()){}
a=Serial.parseInt();
tft.setCursor(60,40);
tft.setTextSize(2);
tft.print(a);
while(!Serial.available()){}
a=Serial.parseInt();
tft.setCursor(80,40);
tft.setTextSize(2);
tft.print(a);
while(!Serial.available()){}
a=Serial.parseInt();
tft.setCursor(100,40);
tft.setTextSize(2);
tft.print(a);
delay(2000);
returnmenu();
}


void komut_al(void){
while(!Serial.available()){}
 komut= Serial.parseInt();
  

//komut=character;
 
  tft.setCursor(10,290);
  tft.fillRect(0,270,40,40,BLACK);
  tft.setTextSize(2);
  tft.println(komut); 
}


void menu_sec(void){
 switch(komut){
 case 1:
       menu1();
        break;

case 3:
      menu3();
       break;

 case 10:
  
        break;
 }
 
}
void setup(void) {
  Serial.begin(115200);
  tft.reset();
  uint16_t identifier = tft.readID();


  tft.begin(identifier);
  returnmenu();
  
}

void loop(void){
  komut_al();
menu_sec();

 
}

void returnmenu(void){
  
tft.fillScreen(BLACK);
  tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
  tft.setCursor(10,10);
  tft.setTextSize(1);
  tft.print("Start ADC");
  tft.setCursor(10,40);
  tft.setTextSize(2);
  tft.print("1");
  tft.fillRect(80, 0, BOXSIZE, BOXSIZE, RED);
  tft.setCursor(80,10);
  tft.setTextSize(1);
  tft.print("nothing");
  tft.setCursor(80,40);
  tft.setTextSize(2);
  tft.print("2");
  tft.fillRect(160,0, BOXSIZE, BOXSIZE, RED);
  tft.setCursor(160,10);
  tft.setTextSize(1);
  tft.print("Set timer");
  tft.setCursor(160,40);
  tft.setTextSize(2);
  tft.print("3");
  //   SATIR 2
   tft.fillRect(0, 80, BOXSIZE, BOXSIZE, RED);
  tft.setCursor(10,90);
  tft.setTextSize(1);
  tft.println("set para-");
  tft.println("  meters");
  tft.setCursor(10,120);
  tft.setTextSize(2);
  tft.print("4");
  tft.fillRect(80, 80, BOXSIZE, BOXSIZE, RED);
  tft.setCursor(80,80);
  tft.setTextSize(1);
  tft.print("Show Data");
  tft.setCursor(80,120);
  tft.setTextSize(2);
  tft.print("5");
  tft.fillRect(160,80, BOXSIZE, BOXSIZE, RED);
  tft.setCursor(160,90);
  tft.setTextSize(1);
  tft.println("Return Menu");
  tft.setCursor(160,120);
  tft.setTextSize(2);
  tft.print("0");
   tft.setCursor(0,250);
  tft.setTextSize(3);
  tft.print("Enter number:");

}
