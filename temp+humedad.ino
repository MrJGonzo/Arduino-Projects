#include "DHT.h"
#include "LiquidCrystal.h"

#define DHTPIN 10     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define fan 4

LiquidCrystal lcd(2,3,4,5,6,7);

int maxHum = 60;
int maxTemp = 40;
int dryValue = 260;
int wetValue = 680;
int friendlyDryValue = 100;
int friendlyWetValue = 0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(fan, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);           
  lcd.print("ESTADO PLANTA"); 
  dht.begin();
}

void loop() {

  int rawValue = analogRead(A0);
  int tempValue = analogRead(A1);
  int friendlyValue = map(rawValue, dryValue, wetValue, friendlyDryValue, friendlyWetValue);
 
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  int t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  if(h > maxHum || t > maxTemp) {
      digitalWrite(fan, HIGH);
  } else {
     digitalWrite(fan, LOW); 
  }

  lcd.setCursor(0, 1);    
  lcd.print("Humedad: ");
  Serial.print("Raw Value: ");
  Serial.print(rawValue);
  Serial.print(" | ");
  Serial.print("Humedad del suelo: ");
  lcd.clear();
  lcd.print("Humedad: ");
  lcd.print(friendlyValue);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.println("Temp:");
  lcd.println(t);
  Serial.print(friendlyValue);
  Serial.println("%");
  
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");

}
