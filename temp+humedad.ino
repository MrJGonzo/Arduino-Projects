//Libraries
#include <SD.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include <Servo.h>

#define DHTPIN 10 // set the DHT Pin
#define DHTTYPE DHT22 // set the sensor type between DHT11 or DHT22

#define I1 24  // Control pin 1 for motor 1
#define I2 26  // Control pin 2 for motor 1
#define E1 28  // Enable Pin for motor 1

//Objects
LiquidCrystal lcd(2,3,4,5,6,7);
DHT dht(DHTPIN, DHTTYPE);
Servo s1;

//Digital Sensor variables
const int maxHum = 60;
const int maxTemp = 40;
const int dryValue = 260;
const int wetValue = 680;
const int percentageDryValue = 100;
const int percentageWetValue = 0;
const int lapse = 3000;

//Relay variables
const int relay1 = 40;
const int relay2 = 42;

//Motor control variables
const int pulseForward = 53;     // the number of the pushbutton pin
const int pulseBackward = 51;      // the number of the LED pin
const int timer = 5000;
const int pause = 1000;

//Motor DC speed control
const int sL = 153;
const int sH = 255;

//motor
void setup() {
  
  // LCD 16x2
  lcd.begin(16, 2);
  lcd.print("HOLA");
  lcd.setCursor(0, 1);
  lcd.print("LUCIANA");
  delay(3000);
  lcd.clear();

  //Sensor DHT Humidity and temperature
  dht.begin();

  //Servor motor
  s1.attach(13,600,1500);

  //Serial monitor
  Serial.begin(9600);

  // DC Motor control Water pump
  pinMode(pulseForward, OUTPUT);
  pinMode(pulseBackward, OUTPUT);

  // Relay control - water supply
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  //Motor variable speed
  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);
  pinMode(E1, OUTPUT);
  
}

void loop() {
  
  delay(50);

  float h = dht.readHumidity();
  //read temperature in Celsius 
  float t = dht.readTemperature();
  
  //read temperature in Farenheit
  //float f = dht.readTemperature(true);

  //read soil sensor
  int rawValue = analogRead(A0);
  float s = map(rawValue, dryValue, wetValue, percentageDryValue, percentageWetValue);

  if (isnan(h) || isnan(t)) {
    lcd.print("ERROR");
    return;
  }
  
  //Serial monitor prints data
  Serial.print("Temperatura ambiente: ");
  Serial.print(t);
  Serial.print("° Celsius");
  Serial.print(" | ");
  Serial.print(" Humedad relativa :");
  Serial.print(h);
  Serial.print("%");
  Serial.print(" | ");
  Serial.print(" Humedad del suelo : ");
  Serial.print(s);
  Serial.print("%");
  Serial.println();
  
  //LCD prints environment temperature data
  lcd.print("Temp ambiente");
  lcd.setCursor(0,1);
  lcd.print(t);
  lcd.print((char)223);
  delay(lapse);
  lcd.clear();
  
  //LCD prints environment humidity data
  lcd.print("Humedad relativa");
  lcd.setCursor(0,1);
  lcd.print(h);
  lcd.print("%");
  delay(lapse); 
  lcd.clear(); 

  //LCD prints soil humidity data
  lcd.print("Humedad suelo");
  lcd.setCursor(0,1);
  lcd.print(s);
  lcd.print("%");
  delay(lapse); 
  lcd.clear();

  //Servo motor
  s1.write(0);
  delay(1000);
  s1.write(90);
  delay(500);
  s1.write(180);
  delay(1000);

  //Relay
  digitalWrite (relay1, HIGH);
  digitalWrite (relay2, LOW);
  delay(1000);
  digitalWrite (relay1, LOW);
  digitalWrite (relay2, HIGH);
  delay(1000);

  //Speed Control motor DC
  analogWrite(E1, sL); // Run in half speed
  digitalWrite(I1, HIGH);
  digitalWrite(I2, LOW);
  delay(10000);

  digitalWrite(E1, LOW);
  delay(200);

  analogWrite(E1, sH);  // Run in full speed
  digitalWrite(I1, LOW);
  digitalWrite(I2, HIGH);

  if(s<30) {
    
    lcd.print("Requires water");
    lcd.setCursor(0,1);
    lcd.print("Water pump on");
    
    // read the state of the pushbutton value:
    //buttonState = digitalRead(pulsePin);
    digitalWrite (pulseForward, HIGH);
  
  }
  else
    digitalWrite (pulseForward, LOW);
  
  
    
}
