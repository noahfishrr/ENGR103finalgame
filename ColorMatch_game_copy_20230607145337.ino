///////////////////////////////////////////////////////////////////////////////
// Circuit Playground Total Acceleration
//
// Author: Carter Nelson
// MIT License (https://opensource.org/licenses/MIT)
///////////////////////////////////////////////////////////////////////////////
#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>
AsyncDelay delay_1s;

// button pins
int Lbutton = 4;
int Rbutton = 5;
int Switch = 7;

// interupt variables
int button;
bool leftButtonPressed;
bool rightButtonPressed;
bool slideSwitch;
volatile bool Lflag = 0;
volatile bool Rflag = 0;
volatile bool sFlag = 0;

// time that color is shown
int count = 0;

//beeps
float midi[127];
int A_four = 440;
int c_major[8] = { 60, 62, 64, 65, 67, 69, 71, 72 };

// color change
volatile int clear = 0;
int adjust = 10;
int r;
int b;
int g;

//shake to clear variables
float X, Y, Z, totalAccel;

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  randomSeed(analogRead(0));

  delay_1s.start(1000, AsyncDelay::MILLIS);
  generateMIDI();

  CircuitPlayground.begin();
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);
  attachInterrupt(digitalPinToInterrupt(Lbutton), LOnOff, RISING);
  attachInterrupt(digitalPinToInterrupt(Rbutton), ROnOff, RISING);


  print();
}

int colors[17] = { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160 };

int lvl1R = random(17);
int lvl1G = random(17);
int lvl1B = random(17);


void loop() {
  CircuitPlayground.setBrightness(30);
  slideSwitch = CircuitPlayground.slideSwitch();
  float rscore = abs((r / 10) - (lvl1R));
  float gscore = abs((g / 10) - (lvl1G));
  float bscore = abs((b / 10) - (lvl1B));
  float score = rscore + gscore + bscore;

  if (count <= 0) {
    print1();
  }
  if (delay_1s.isExpired() && count < 6) {
    delay_1s.start(1000, AsyncDelay::MILLIS);
    Serial.println("My counter value is ");
    Serial.println(count++);
    /*CircuitPlayground.playTone(midi[c_major[count]], 200);*/
    for (int o = 0; o < 10; o++) {

      CircuitPlayground.setPixelColor(o, colors[lvl1R], colors[lvl1G], colors[lvl1B]);
    }
  } else if (count >= 6) {
    for (int o = 0; o < 10; o++) {
      CircuitPlayground.setPixelColor(o, r, g, b);
    }
    X = 0;
    Y = 0;
    Z = 0;

    for (int i = 0; i < 10; i++) {
      X += CircuitPlayground.motionX();
      Y += CircuitPlayground.motionY();
      Z += CircuitPlayground.motionZ();
      delay(1);
    }
    X /= 10;
    Y /= 10;
    Z /= 10;

    totalAccel = sqrt(X * X + Y * Y + Z * Z);
    //print();
    for (int t = 0; t < 10; t++) {
      CircuitPlayground.setPixelColor(t, r, g, b);
    }
    if (slideSwitch) {
      if (Lflag && Rflag) {

        //un-comment to see user inputs
        // Serial.print("red: ");
        // Serial.println(r / 10);
        // Serial.print("green: ");
        // Serial.println(g / 10);
        // Serial.print("blue: ");
        // Serial.println(b / 10);
        g = g - 10;
        b = b - 10;
        Serial.print("score");
        Serial.println(score);
      }
      if (Lflag) {
        delay(10);
        b = b + adjust;
        if (b >= 171) { b = 0; }
        Lflag = 0;
      }

      for (int t = 0; t < 10; t++) {
        CircuitPlayground.setPixelColor(t, r, g, b);
      }
      sFlag = 0;

    } else {
      if (Lflag && Rflag) {
        // un-comment to see user inputs
        // Serial.print("red: ");
        // Serial.println(r / 10);
        // Serial.print("green: ");
        // Serial.println(g / 10);
        // Serial.print("blue: ");
        // Serial.println(b / 10);
        r = r - 10;
        g = g - 10;
        Serial.print("score");
        Serial.println(score);
      }
      if (Lflag) {
        delay(10);
        r = r + adjust;
        if (r >= 171) { r = 0; }
        Lflag = 0;
      }
      for (int t = 0; t < 10; t++) {
        CircuitPlayground.setPixelColor(t, r, g, b);
      }
      sFlag = 0;
    }
    if (Rflag) {
      delay(10);
      g = g + adjust;
      if (g >= 171) { g = 0; }
      Rflag = 0;
      for (int t = 0; t < 10; t++) {
        CircuitPlayground.setPixelColor(t, r, g, b);
      }
    }
    if (totalAccel > 45) {
      r = 0;
      g = 0;
      b = 0;
    }
  }
}

void print1() {

  Serial.println("Level 1");

  // Serial.print("lvl1R: ");
  // Serial.println(lvl1R);
  // Serial.print("lvl1G: ");
  // Serial.println(lvl1G);
  // Serial.print("lvl1B: ");
  // Serial.println(lvl1B);
  delay(200);
}

void print() {
  Serial.println(totalAccel);
  delay(200);
}

void LOnOff() {
  Lflag = 1;
}

void ROnOff() {
  Rflag = 1;
}
void generateMIDI() {
  for (int x = 0; x < 127; ++x) {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
  }
}
