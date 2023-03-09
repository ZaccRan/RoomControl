/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/Nemo/Documents/IoT/RoomControl/Room/src/Room.ino"
/*
 * Project Doggo Room
 * Description:MidTerm Attempt
 * Author:Zacc 
 * Date:2/6/23
 */
#include <neoPixel.h>
void setup();
void loop();
#line 8 "c:/Users/Nemo/Documents/IoT/RoomControl/Room/src/Room.ino"
const int PIXPIN=D2;
const int PIXCT=1;
Adafruit_NeoPixel pix(1,D2,WS2812B);

const int W=A5; // Water Sensor
int water;

#include <Adafruit_BMP280.h>
bool status;
int tempF;
int tempC;
Adafruit_BMP280 bmp;

#include "ioTClassroom_CNM.h"
SYSTEM_MODE(MANUAL);

const int NUMBULBS=6;
const int BULB=1;          //Room Lights, make sure to tell all 6 bulb not just on 2
int color;


#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#define OLED_RESET D4
Adafruit_SSD1306 display(OLED_RESET);
#define XPOS 0
#define YPOS 1
#define DELTAY 2                      //OLED

Button buttonB(A0),buttonR(A1);
bool b,r;

int bb,rr,dd;
int x=0;         // more delay creates more button "lag"

void roomDark();         //list of functions
void roomRed();
void roomBlue();

void setup() {
  Wire.begin();
  status=bmp.begin(0x76);
  // if(status==false){
  //     Serial.printf("BMP280 at address 0x%02X failed to start\n", 0x76);
  //   }
  pix.begin();
  
  pinMode(W,INPUT);

  pinMode(D10,OUTPUT);   //Blue's

  pinMode(D9,OUTPUT);       //Red's

  pinMode(PIXPIN,OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  // Serial.begin(9600);
  // waitFor(Serial.isConnected,15000);

  WiFi.on();
  WiFi.setCredentials("IoTNetwork");

  WiFi.connect();
  // while(WiFi.connecting()) {
  //   Serial.printf(".");
  // }
  // Serial.printf("\n\n");
}

void loop() {
  display.setRotation(1);                //temp oled display
  bmp.readTemperature();                 //using tempf to automatically control wemo1&2 and 
  tempC=bmp.readTemperature();
  tempF=(tempC*1.8)+32;
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.printf("%iC\n",tempC);
  display.printf("%iF\n",tempF);
  display.display();
  // Serial.printf("%iC\n",tempC);
  // Serial.printf("%iF\n",tempF);
  display.clearDisplay();
  if(water<=50){
      display.printf("Water\nNeeded");     //set by water sensor
    }
  display.display();
  water=analogRead(W);
  // Serial.printf("%i\n\n",water);
  int blind;
  blind=map(water,0,955,255,0);  //little to no water, neopixel max brightness
  pix.setBrightness(blind);
  pix.setPixelColor(0,0x008000);
  pix.show();

  if(buttonB.isClicked()){
      b=!b;
    }
  if(b){
      digitalWrite(D10,HIGH);
      switchON(3);
      roomBlue();
    }
  else{
      digitalWrite(D10,LOW);
      roomDark();
      switchOFF(3);
    }
  if(buttonR.isClicked()){
      r=!r;
    }
  if(r){
      digitalWrite(D9,HIGH);
      switchON(1);
      roomRed();
    }
  else{
      digitalWrite(D9,LOW);
      roomDark();
      switchOFF(1);
    }
  if(tempF=60){
    digitalWrite(D10,LOW);
    digitalWrite(D9,LOW);
    roomDark();
    switchOFF(1);
    switchOFF(3);

  }
  if((tempF>=65)&&(!r)){                 // automatic function
      digitalWrite(D10,HIGH);
      switchON(3);
      roomBlue();
    }
  if((tempF<=75)&&(!b)){
      digitalWrite(D9,HIGH);
      switchON(1);
      roomRed();
    }
}
//Functions to clean code
void roomDark() {
  for(dd=1;dd=6;dd++){
      setHue(dd,false,0,0,0);
    }
}
void roomRed(){
  for(rr=1;rr=6;rr++){
      setHue(rr,true,HueRed,255,255);
    }
}
void roomBlue(){
  for(bb=1;bb=6;bb++){
      setHue(bb,true,HueBlue,255,255);
    }
}

// for(bb=1;bb=6;bb++){
//   setHue(bb,true,HueBlue,255,255)
// };
// for(rr=1;rr=6;rr++){
//   setHue(rr,true,HueRed,255,255)
// };

// example code
  // delay(x);
  // setHue(1,true,HueRed,255,255);
  // delay(x);
  // setHue(2,true,HueRed,255,255);
  // delay(x);
  // setHue(3,true,HueRed,255,255);
  // delay(x);
  // setHue(4,true,HueRed,255,255);
  // delay(x);
  // setHue(5,true,HueRed,255,255);
  // delay(x);
  // setHue(6,true,HueRed,255,255);

  // delay(x);
  // setHue(1,true,HueBlue,255,255);
  // delay(x);
  // setHue(2,true,HueBlue,255,255);
  // delay(x);
  // setHue(3,true,HueBlue,255,255);
  // delay(x);
  // setHue(4,true,HueBlue,255,255);
  // delay(x);
  // setHue(5,true,HueBlue,255,255);
  // delay(x);
  // setHue(6,true,HueBlue,255,255);

// HueRed
// HueBlue
// bool setHue(int lightNum, bool HueOn, int HueColor, int HueBright, int HueSat)
// setHue(BULB,true,HueRainbow[color%7],random(32,255),255);
  // Serial.printf("Setting color of bulb %i to color %06i\n",BULB,HueRainbow[color%7]);
  // setHue(BULB,true,HueRainbow[color%7],random(32,255),255);
  // color++;
  // delay(10000);


// Blue and red buttons and led's toggling
// if(buttonB.isClicked()){
//   b=!b;
// }
// if(b){
//   digitalWrite(D10,HIGH);
// }
// else{
//   digitalWrite(D10,LOW);
// }
// if(buttonR.isClicked()){
//   r=!r;
// }
// if(r){
//   digitalWrite(D9,HIGH);
// }
// else{
//   digitalWrite(D9,LOW);
// }

// Manual button control
// if(buttonB.isClicked()){
//   b=!b;
// }
// if(b){
//   digitalWrite(D10,HIGH);
//   delay(x);
//   switchON(3);
//   setHue(1,true,HueBlue,255,255);
//   delay(x);
//   setHue(2,true,HueBlue,255,255);
//   delay(x);
//   setHue(3,true,HueBlue,255,255);
//   delay(x);
//   setHue(4,true,HueBlue,255,255);
//   delay(x);
//   setHue(5,true,HueBlue,255,255);
//   delay(x);
//   setHue(6,true,HueBlue,255,255);
// }
// else{
//   digitalWrite(D10,LOW);
//   setHue(1,false,0,0,0);
//   setHue(2,false,0,0,0);
//   setHue(3,false,0,0,0);
//   setHue(4,false,0,0,0);
//   setHue(5,false,0,0,0);
//   setHue(6,false,0,0,0);
//   switchOFF(2);
// }

// if(buttonR.isClicked()){
//   r=!r;
// }
// if(r){
//   digitalWrite(D9,HIGH);
//   delay(x);
//   switchON(1);
//   setHue(1,true,HueRed,255,255);
//   delay(x);
//   setHue(2,true,HueRed,255,255);
//   delay(x);
//   setHue(3,true,HueRed,255,255);
//   delay(x);
//   setHue(4,true,HueRed,255,255);
//   delay(x);
//   setHue(5,true,HueRed,255,255);
//   delay(x);
//   setHue(6,true,HueRed,255,255);
// }
// else{
//   digitalWrite(D9,LOW);
//   setHue(1,false,0,0,0);
//   setHue(2,false,0,0,0);
//   setHue(3,false,0,0,0);
//   setHue(4,false,0,0,0);
//   setHue(5,false,0,0,0);
//   setHue(6,false,0,0,0);
//   switchOFF(1);
// }
//water sensor,bmp280,neopixel,oled working
  // display.setRotation(1);                //temp oled display
  // bmp.readTemperature();                 //using tempf to automatic control wemo1&2
  // tempC=bmp.readTemperature();
  // tempF=(tempC*1.8)+32;
  // display.setTextSize(1);
  // display.setTextColor(WHITE);
  // display.setCursor(0,0);
  // display.printf("%iC\n",tempC);
  // display.printf("%iF\n",tempF);
  // display.display();
  // Serial.printf("%iC\n",tempC);
  // Serial.printf("%iF\n",tempF);
  // delay(x);                              //DELAY causes extra button delay
  // display.clearDisplay();
  // if(water<=50){
  //   display.printf("Water\nNeeded");     //set by water sensor
  // }
  // display.display();
  
  // water=analogRead(W);
  // Serial.printf("%i\n\n",water);
  // int blind;
  // blind=map(water,0,955,255,0);  //little to no water, neopixel max brightness
  // pix.setBrightness(blind);
  // pix.setPixelColor(0,0x008000);
  // pix.show();