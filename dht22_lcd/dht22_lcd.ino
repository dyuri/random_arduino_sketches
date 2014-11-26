#include <Wire.h>
#include <LiquidCrystal_I2C.h>
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

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

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
  
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.home();
  lcd.print("Hello!");  
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
 
  lcd.home();
  lcd.print("Temp: ");
  lcd.print(dht_temp);
  lcd.setCursor(0, 1);
  lcd.print("Hum%: ");
  lcd.print(dht_hum);
 
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
