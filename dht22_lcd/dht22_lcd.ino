#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

const int ledPin = 11;   // Teensy has LED on 11, Teensy++ on 6

const int redPin =  12;
const int greenPin =  15;
const int bluePin =  14;
const int buttonPin = 8;
const int PIRPin = 9;

const int lightPin = 0;
const int tempPin = 1;

#define DHTPIN 19
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// the setup() method runs once, when the sketch starts

void setup() {
  Wire.begin();
  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(DHTPIN, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(PIRPin, INPUT);
  Serial.begin(9600);
  
  dht.begin();
  
  lcd.begin(16, 2);
  lcd.noBacklight();
  lcd.home();
  lcd.print("Hello!");  
}

int redI = 0;
int greenI = 0;
int blueI = 255;
int lastButton = LOW;

void loop() {
  int i;
  int l;
  int light;
  float temp;
  float dht_temp;
  float dht_hum;
  int pir;
  int button;
 
  button = digitalRead(buttonPin);
  pir = digitalRead(PIRPin);

  dht_temp = dht.readTemperature();
  dht_hum = dht.readHumidity();  
 
  analogRead(lightPin);
  delay(10);
  light = analogRead(lightPin);
  l = map(light, 400, 1000, 0, 255);
  
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
 
  if (lastButton != button) {
    lcd.clear();
    lastButton = button;
  }
 
  lcd.home();
  if (pir == HIGH) {
    lcd.backlight();
  } else {
    lcd.noBacklight();
  }
  if (button == HIGH) {
    lcd.print("Temp: ");
    lcd.print(dht_temp);
    lcd.setCursor(0, 1);
    lcd.print("Hum%: ");
    lcd.print(dht_hum);
    Wire.beginTransmission(9);
    Wire.send(200);
    Wire.endTransmission();
  } else {
    lcd.print("Temp (a): ");
    lcd.print(temp);
    lcd.setCursor(0, 1);
    lcd.print("Light: ");
    lcd.print(light);
    Wire.beginTransmission(9);
    Wire.send(0);
    Wire.endTransmission();
  }
 
  if (blueI == 255 && redI < 255 && greenI == 0) {
    redI++;
  }
  if (redI == 255 && blueI > 0) {
    blueI--;
  }
  if (redI == 255 && blueI == 0 && greenI < 255) {
    greenI++;
  }
  if (greenI == 255 && redI > 0) {
    redI--;
  }
  if (greenI == 255 && redI == 0 && blueI < 255) {
    blueI++;
  }
  if (blueI == 255 && greenI > 0) {
    greenI--;
  }
 
  analogWrite(bluePin, blueI);  
  analogWrite(redPin, redI);
  analogWrite(greenPin, greenI);
 
  delay(500);
  
}
