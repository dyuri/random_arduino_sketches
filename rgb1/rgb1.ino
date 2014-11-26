
const int ledPin = 11;   // Teensy has LED on 11, Teensy++ on 6

const int redPin =  12;
const int greenPin =  15;
const int bluePin =  14;
const int button1Pin = 8;

const int lightPin = 0;
const int tempPin = 1;

// the setup() method runs once, when the sketch starts

void setup() {
  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(button1Pin, INPUT_PULLUP);
  Serial.begin(38400);
}

int redI = 0;
int greenI = 0;
int blueI = 0;

void loop() {
  int i;
  int l;
  float temp;

  // lila, Beanak
  /*
  for (redI=0; redI<128; redI++) {
    if (digitalRead(button1Pin) != LOW) {
      analogWrite(redPin, redI);
      analogWrite(bluePin, redI*2);
    } else {
      analogWrite(redPin, 0);
      analogWrite(bluePin, 0);
    }
    delay(5);
  }

  delay(1000);

  for (redI=127; redI>=0; redI--) {
    if (digitalRead(button1Pin) != LOW) {
      analogWrite(redPin, redI);
      analogWrite(bluePin, redI*2);
    } else {
      analogWrite(redPin, 0);
      analogWrite(bluePin, 0);
    }
    delay(5);
  }  
  */
  
  analogRead(lightPin);
  delay(10);
  l = map(analogRead(lightPin), 400, 1000, 0, 255);
  
  analogRead(tempPin);
  delay(10);
  temp = analogRead(tempPin) * 0.48828125; // (VCC * 1000 / 1024) / 10; VCC = 5  
  // temp = analogRead(tempPin);
  
  Serial.println(l);
  Serial.println(temp);
  Serial.println(""); 
 
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
