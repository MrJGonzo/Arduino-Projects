/*
Version del prototipo matriz 8x8 multiplexada por 8 filas y 8 columnas, conectada directamente a los puertos del arduino
trabaja correctamente.
*/

const byte rowQty = 8;
const byte colQty = 8;

const byte buttonPin = 3;
int buttonState = 0;

byte ledCathode[colQty] = {38,40,42,44,46,48,50,52};
byte ledAnode[rowQty] = {39,41,43,45,47,49,51,53};

byte leds[rowQty][colQty] = {
  {0,0,0},
  {0,0,0},
  {0,0,0}
};

void setup() {

    Serial.begin(9600);
    pinMode(buttonPin, INPUT);


    for(int i=0; i<colQty; i++){

      pinMode(ledCathode[i], OUTPUT);

        for(int j=0; j<rowQty; j++){

          pinMode(ledAnode[j], OUTPUT);

        }

    }


}

void turnOn(){

  for(int i=0; i<colQty; i++){
    digitalWrite(ledCathode[i], LOW);
    delay(1);

      for(int j=0; j<colQty; j++){
        digitalWrite(ledAnode[j], HIGH);
        delay(1);
      }
  }


}

void turnOff(){

  for(int i=0; i<colQty; i++){
    digitalWrite(ledCathode[i], HIGH);
    delay(1);

      for(int j=0; j<colQty; j++){
        digitalWrite(ledAnode[j], LOW);
        delay(1);
      }
  }


}

void clearMatrix(){

  for(int i=0; i<colQty; i++){

    digitalWrite(ledCathode[i], LOW);
    delay(1);

      for(int j=0; j<colQty; j++){

        digitalWrite(ledAnode[j], LOW);
        delay(1);


      }

  }


}

void invertMatrix(){

  for(int j=0; j<colQty; j++){
        digitalWrite(ledAnode[j], HIGH);
        delay(1);
    for(int i=0; i<colQty; i++){
    digitalWrite(ledCathode[i], LOW);
    delay(1);

    }
  }

}



void printState(){
  for(byte i = 0; i<8; i++){
      for(byte j = 0; j<8; j++){
        Serial.print(leds[i][j]);
        digitalWrite(leds[i][j], LOW);
      }

    Serial.println(" ");
    }
  Serial.println("---");
}

void button(){

}


void loop() {

  buttonState = digitalRead(buttonPin);
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledCathode, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledCathode, LOW);
  }
  turnOn();
  printState();



}
