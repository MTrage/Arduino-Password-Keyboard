/*
  Arduino Password Keyboard 
  This little code shows you how easy you can use a Pro Micro as a Password-Keyboard.
  Freely usable for all with the exception of military and other anti-social activities.
  Created 12.9.2015 by Marc-André Tragé
  
  Pinout for Arduino Pro Micro
  
  DISPALY Binding
  GND = GND
  5V  = 5V  (VCC)
  SDA = 2   (SDA)
  SCK = 3   (SCL)
    
  If you have any useful changes or improvements please let me know.
  (Not a wish (but a command)) have fun (NOW (and for the rest of your life))!
*/


// Keyboard output
#include <Keyboard.h>

// OLED-Display
//#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


int countsz = 5; // Number of Passwords
int b3 = 4;  // OK - Button
int b1 = 10; // DW - Button
int b2 = 8;  // UP - Button

int b4 = 5;  // MENU 1 Button
int b5 = 6;  // MENU 2 Button
int b6 = 9;  // MENU 3 Button
int b7 = 7;  // MENU 4 Button

//             PW-Name     Password
String TN1  = "Title 1";   String PW1  = "Password1";
String TN2  = "Title 2";   String PW2  = "Password2";
String TN3  = "Title 3";   String PW3  = "Password3";
String TN4  = "Title 4";   String PW4  = "Password4";
String TN5  = "Title 5";   String PW5  = "Password5";

String MPW1 = "Direct Password Button 1"; 
String MPW2 = "Direct Password Button 2";  
String MPW3 = "Direct Password Button 3";
String MPW4 = "Direct Password Button 4";

int rstimer = 0, counter = 0;
String PWA = "";

// Login STOP Password °)
int ulb1, ulb2, ulb3, ulb4;
int STOP       = 1;  // 1 = Login Question itc press Menu Button 1 2 3 4 and hold OK Button or use 0 = without Login Question
int STOP_count = 0;
int STOP_ok    = 0;

void setup() {
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);
  pinMode(b4, INPUT_PULLUP);
  pinMode(b5, INPUT_PULLUP);
  pinMode(b6, INPUT_PULLUP); 
  pinMode(b7, INPUT_PULLUP);
  // Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  delay(250);
  display.clearDisplay();
}

// Clear Display 
int Reset() {
  rstimer = 0;
  counter = 0;
  display.clearDisplay();
  display.display();
  delay(250);
  display.clearDisplay();
}

// Write Information
int writeR() {
  display.display();
  display.clearDisplay();
  display.setRotation(2);                   // 180° Rotation
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Select Password NOW");
  display.setCursor(0,8);
  display.setTextSize(2);
  display.drawLine(0,25,127,25,  WHITE);
  display.drawLine(0,25,0,30,    WHITE);
  display.drawLine(127,25,127,30,WHITE);
  display.drawLine(0,31,127,31,  WHITE);

  if (counter == 1){display.println(TN1);}
  if (counter == 2){display.println(TN2);}
  if (counter == 3){display.println(TN3);}
  if (counter == 4){display.println(TN4);}
  if (counter == 5){display.println(TN5);}
    
  delay(250);
}

// Start output 
int Run() {

  if (counter == 0){return true;} delay(10); // Arduino Vacation Position

  if (counter == 100){PWA = MPW1;} delay(10);
  if (counter == 200){PWA = MPW2;} delay(10);
  if (counter == 300){PWA = MPW3;} delay(10);
  if (counter == 400){PWA = MPW4;} delay(10);

  if (counter == 1){PWA = PW1;} delay(10);
  if (counter == 2){PWA = PW2;} delay(10);
  if (counter == 3){PWA = PW3;} delay(10);
  if (counter == 4){PWA = PW4;} delay(10);
  if (counter == 5){PWA = PW5;} delay(10);

  // USB-Keyboard write the selected Password with write-delay.
  int PWL = PWA.length();
   for (int i=0; i <= PWL; i++){
      Keyboard.print(PWA[i]);
      delay(5);
   }
  delay(10);
  Keyboard.print("\n"); // Return
  rstimer = 0;
  counter = 0;
  display.clearDisplay();
  display.display();
  display.clearDisplay();
  delay(250);
}


void loop() {

  STOP_ok = STOP_ok+1;
  if (STOP == 1){

      display.display();
      display.clearDisplay();
      display.setRotation(2);                   // 180° Rotation
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.print("YOU ARE NOT SEXY");
      display.setTextSize(2);
      display.setCursor(0, 8);
      display.print("BLOCKED");
      display.display();
      if (digitalRead(b3) == LOW){STOP_count = STOP_count+1;}
      if (digitalRead(b4) == LOW){ulb1=1;STOP_count=0;}
      if (digitalRead(b5) == LOW){ulb2=1;STOP_count=0;}
      if (digitalRead(b6) == LOW){ulb3=1;STOP_count=0;}
      if (digitalRead(b7) == LOW){ulb4=1;STOP_count=0;}
      if (STOP_ok>300){
        ulb1=0;
        ulb2=0;
        ulb3=0;
        ulb4=0;
        STOP_count=0;
        }
      if (ulb3==1 & ulb4==1 & STOP_count>50){
        display.display();
        display.clearDisplay();
        display.display();
        STOP=0;
      }
      }
    else{
      // Check Menu 1-4 MENU1Button 
      //if (digitalRead(b4) == LOW){counter=100; Run();}
      //if (digitalRead(b5) == LOW){counter=200; Run();}
      if (digitalRead(b6) == LOW){counter=300; Run();}
      if (digitalRead(b7) == LOW){counter=400; Run();}

  // Check OK-Button 
  if (digitalRead(b3) == LOW) {Run();}

  // Check DOWN-Button
  if (digitalRead(b1) == LOW) {
    rstimer = 0;
    if (countsz >= counter + 1) {
      counter = counter + 1;
    }
    else {
      counter = 1;
    }
    writeR();
    return;
  }

  // Check UP-Button
  if (digitalRead(b2) == LOW) {
    rstimer = 0;
    if (2 <= counter) {
      counter = counter - 1;
    }
    else {
      counter = countsz;
    }
    writeR();
    return;
  }

// Countdown-Bar
if(counter!=0){
  rstimer = rstimer + 1;
  if (rstimer <= 227) { 
      int setb = rstimer-100;
      display.display();
      display.drawLine(0,26,setb,26,WHITE);
      display.drawLine(0,27,setb,27,WHITE);  
      display.drawLine(0,28,setb,28,WHITE);
      display.drawLine(0,29,setb,29,WHITE);
      display.drawLine(0,30,setb,30,WHITE);   
    }
  else{
      rstimer = 0;
      counter = 0;
      display.clearDisplay();
      display.display();
      display.clearDisplay();
      delay(100);
    }
  }
      }
  //delay(1);
}

