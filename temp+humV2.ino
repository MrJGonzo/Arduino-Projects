  //Libraries
#include <SD.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include <Servo.h>

#define DHTPIN 53 // set the DHT Pin
#define DHTTYPE DHT22 // set the sensor type between DHT11 or DHT22

#define I1 24  // Control pin 1 for motor 1
#define I2 26  // Control pin 2 for motor 1
#define E1 28  // Enable Pin for motor 1

//Objects
//LiquidCrystal lcd(2,3,4,5,6,7);
LiquidCrystal lcd(33,31,29,27,25,23);
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

void soilHumidity() {

  int rawValue = 0;
  float soil = 0;

  rawValue = analogRead(A1);
  soil = map(rawValue, dryValue, wetValue, percentageDryValue, percentageWetValue);
  //LCD prints soil humidity data
  lcd.print("Humedad suelo");
  lcd.setCursor(0,1);
  lcd.print(soil);
  lcd.print("%");
  delay(lapse);
  lcd.clear();

  Serial.print(" Humedad del suelo : ");
  Serial.print(soil);
  Serial.print("%");
  Serial.println();

  if( soil < 30 ) {
    lcd.clear();
    lcd.print("Requires water");
    lcd.setCursor(0,1);
    lcd.print("Water pump on");
    lcd.clear();
    digitalWrite (pulseForward, LOW);

  }
  else
    Serial.println("Bomba iniciada ");

  // read the state of the pushbutton value:
  //buttonState = digitalRead(pulsePin);
  digitalWrite (pulseForward, HIGH);

}

void rainSensor() {

  int rainData = analogRead(A0);

  //LCD prints rain sensor data
  lcd.clear();
  lcd.print("Condicion lluvia");
  lcd.setCursor(0,1);
  lcd.print(rainData);
  delay(lapse);
  lcd.clear();

  // Serial data
  Serial.print(" Sensor de lluvia : ");
  Serial.print(rainData);
  Serial.print(" | ");

}

void environmentSensor(){

  float h = dht.readHumidity();
  //read temperature in Celsius
  float t = dht.readTemperature();
  //read temperature in Farenheit
  //float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t)) {
    lcd.print("ERROR");
    return;
  }

  Serial.print("Temperatura ambiente: ");
  Serial.print(t);
  Serial.print("° Celsius");
  Serial.print(" | ");
  Serial.print(" Humedad relativa :");
  Serial.print(h);
  Serial.print("%");
  Serial.print(" | ");

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

}

void setup() {

  // LCD 16x2
  lcd.begin(16, 2);
  lcd.print("AGRICULTURA");
  lcd.setCursor(0, 1);
  lcd.print("DE PRECISION");
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

void servoMotor(){
  //Servo motor
  s1.write(0);
  delay(100);
  s1.write(90);
  delay(100);
  s1.write(180);
  delay(100);

  //Relay
  digitalWrite (relay1, HIGH);
  digitalWrite (relay2, LOW);
  delay(100);
  digitalWrite (relay1, LOW);
  digitalWrite (relay2, HIGH);
  delay(100);

}

void motorControl(){
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

}

void loop() {

  rainSensor();
  environmentSensor();
  soilHumidity();

}
