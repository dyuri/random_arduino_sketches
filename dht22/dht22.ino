#include <DHT.h>

const int ledPin = 11;   // Teensy has LED on 11, Teensy++ on 6

const int redPin =  12;
const int greenPin =  15;
const int bluePin =  14;
const int dhtPin = 8;

const int lightPin = 0;
const int tempPin = 1;

#define DHTPIN 19
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// the setup() method runs once, when the sketch starts

void setup() {
  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(19, INPUT);
  Serial.begin(38400);
  
  dht.begin();
}

int redI = 0;
int greenI = 0;
int blueI = 0;

void loop() {
  int i;
  int l;
  float temp;
  float dht_temp;
  float dht_hum;

  dht_temp = dht.readTemperature();
  dht_hum = dht.readHumidity();  
 
  analogRead(lightPin);
  delay(10);
  l = map(analogRead(lightPin), 400, 1000, 0, 255);
  
  analogRead(tempPin);
  delay(10);
  temp = 0;
  for (i=0;i<8;i++) {
    temp += analogRead(tempPin) * 0.48828125; // (VCC * 1000 / 1024) / 10; VCC = 5  
    // temp = analogRead(tempPin);
  }
  temp = temp / 8;
  
  Serial.println(">");
  Serial.print("light: ");
  Serial.println(l);
  Serial.print("temperature: ");
  Serial.println(temp);
  Serial.print("DHT_temp: ");
  Serial.println(dht_temp);
  Serial.print("DHT_hum: ");
  Serial.println(dht_hum);  
  Serial.println("<");
 
  if (temp > 25) {
    analogWrite(bluePin, 128);  
  } else {
    analogWrite(bluePin, 0);
  }
  
  if (l > 127) {
    analogWrite(redPin, l);
    analogWrite(greenPin, 0);
  } else {
    analogWrite(greenPin, l);
    analogWrite(redPin, 0);
  }

  delay(500);
  
}
