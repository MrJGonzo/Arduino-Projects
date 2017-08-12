#include "LiquidCrystal.h"

LiquidCrystal lcd(2,3,4,5,6,7);

const int button1 = 10;    
const int button2 = 11;
const int button3 = 12;

const int led1 = 22;       
const int led2 = 24;       
const int led3 = 26;       

int buttonPushCounter = 0;   
String count = String();

int button1State = 0;         
int button2State = 0;
int button3State = 0;

int lastStateButton1 = 0;     
int lastStateButton2 = 0;     
int lastStateButton3 = 0;

void setup() 
   {
       lcd.begin(16, 2);           
       lcd.print("GAME");  
     
        pinMode(button1, INPUT);
        pinMode(button2, INPUT);
        pinMode(led1, OUTPUT);
        pinMode(led2, OUTPUT);
        Serial.begin(9600);
   }

void loop()
   {

       lcd.setCursor(0, 1);    
       lcd.print("Active: ");

        button1State = digitalRead(button1);
        button2State = digitalRead(button2);
        button3State = digitalRead(button3);
      
        if (button1State != lastStateButton1) {
          
          if (button1State == HIGH) {
            
            buttonPushCounter++;
            String count = String(buttonPushCounter);
            lcd.clear();
            lcd.setCursor(0, 0);    
            lcd.print("LETS PLAY ");
            lcd.setCursor(8, 1); 
            lcd.print(count);
            Serial.print("number of pushed buttons: ");
            Serial.println(buttonPushCounter);
          }
          else if(button1State != lastStateButton1){
            
            buttonPushCounter--;
            String count = String(buttonPushCounter);
            lcd.clear();
            lcd.setCursor(0, 0);    
            lcd.print("LETS PLAY ");
            lcd.setCursor(8, 1);
            lcd.print(count);
            Serial.print("number of pushed buttons: ");
            Serial.println(buttonPushCounter);
            }
          else {
            Serial.println("off");
          }
          delay(1);
        }

        lastStateButton1 = button1State;
      
        if (buttonPushCounter % 2 == 0) {
          digitalWrite(led1, HIGH);
        } else {
          digitalWrite(led1, LOW);
        }

        if (button2State != lastStateButton2) {

          if (button2State == HIGH) {
            buttonPushCounter++;
            String count = String(buttonPushCounter);
            lcd.clear();
            lcd.setCursor(0, 0);    
            lcd.print("LETS PLAY ");
            lcd.setCursor(8, 1);
            lcd.print(count);
            Serial.print("number of pushed buttons: ");
            Serial.println(buttonPushCounter);
          }
          else if(button2State != lastStateButton2){
            buttonPushCounter--;
            String count = String(buttonPushCounter);
            lcd.clear();
            lcd.setCursor(0, 0);    
            lcd.print("LETS PLAY ");
            lcd.setCursor(8, 1);
            lcd.print(count);
            Serial.print("number of pushed buttons: ");
            Serial.println(buttonPushCounter);
            }
          else {
            Serial.println("off");
          }
          delay(1);
        }
        lastStateButton2 = button2State;
      
        if (buttonPushCounter % 2 == 0) {
          digitalWrite(led2, HIGH);
        } else {
          digitalWrite(led2, LOW);
        }

        if (button3State != lastStateButton3) {
          if (button3State == HIGH) {
            buttonPushCounter++;
            String count = String(buttonPushCounter);
            lcd.clear();
            lcd.setCursor(0, 0);   
            lcd.print("LETS PLAY ");
            lcd.setCursor(8, 1);
            lcd.print(count);
            Serial.print("number of pushed buttons: ");
            Serial.println(buttonPushCounter);
          }
          else if(button3State != lastStateButton3){
            buttonPushCounter--;
            String count = String(buttonPushCounter);
            lcd.clear();
            lcd.setCursor(0, 0);    
            lcd.print("LETS PLAY ");
            lcd.setCursor(8, 1);
            lcd.print(count);
            Serial.print("number of pushed buttons: ");
            Serial.println(buttonPushCounter);
            }
          else {
            Serial.println("off");
          }
          delay(1);
        }
        lastStateButton3 = button3State;

        if (buttonPushCounter % 2 == 0) {
          digitalWrite(led3, HIGH);
        } else {
          digitalWrite(led3, LOW);
        }
   }
