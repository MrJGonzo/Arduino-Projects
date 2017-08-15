int dryValue = 260;
int wetValue = 680;
int friendlyDryValue = 100;
int friendlyWetValue = 0;
void setup() {
  Serial.begin(9600);
}
void loop() {
  int rawValue = analogRead(A0);
  Serial.print("Raw Value: ");
  Serial.print(rawValue);
  Serial.print(" | ");
  
  int friendlyValue = map(rawValue, dryValue, wetValue, friendlyDryValue, friendlyWetValue);
  
  Serial.print("Humedad del suelo: ");
  Serial.print(friendlyValue);
  Serial.println("%");
  
  delay(2000);
}
