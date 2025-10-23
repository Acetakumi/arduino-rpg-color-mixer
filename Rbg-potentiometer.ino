#include <Wire.h>
#include "rgb_lcd.h"
#include "Adafruit_NeoPixel.h"

#ifdef __AVR__
  #include <avr/power.h>
#endif

rgb_lcd lcd;


const int buttonPin = 6;
int buttonState = 0;
int rotaryPin = A0; 
int rotaryValue = 0; 


#define PIN        3
#define NUMPIXELS  10
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


String state = "red";
int red = 0;
int blue = 0;
int green = 0;

void setup() {
  pinMode(buttonPin, INPUT);   
  pinMode(rotaryPin, INPUT);

  #ifdef __AVR__
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif

  pixels.setBrightness(50);
  pixels.begin(); 

  lcd.begin(16, 2);
    
    lcd.setRGB(0, 50 , 50);
    
 
}

void setRgb(String state, int value) {   
  int v = map(value, 0, 1023, 0, 255);  

  if (state == "red") {
    red = v;           
    for (int i = 0; i < NUMPIXELS; i++) pixels.setPixelColor(i, pixels.Color(red, green, blue));
  } 
  else if (state == "green") {   
    green = v;         
    for (int i = 0; i < NUMPIXELS; i++) pixels.setPixelColor(i, pixels.Color(red, green, blue));
  } 
  else {
    blue = v;          
    for (int i = 0; i < NUMPIXELS; i++) pixels.setPixelColor(i, pixels.Color(red, green, blue));
  }

}



int previousedge = 0;
    int edge = 0;
void loop() {
  buttonState = digitalRead(buttonPin);
  rotaryValue = analogRead(rotaryPin);




  if (buttonState == HIGH && previousedge == LOW) {

        if (state == "red")       state = "green";
        
        else if (state == "green") state = "blue";
      
        else                       state = "red";
    

  } previousedge = buttonState;

  setRgb(state, rotaryValue);
  pixels.show();


  lcd.setCursor(0, 0);
  lcd.print("State: ");
  lcd.print(state);
  lcd.print("      ");  


  lcd.setCursor(0, 1);
  lcd.print("Val: ");
  lcd.print(rotaryValue * 0.249266862);     
  lcd.print("      ");

 

  delay(100);
}
