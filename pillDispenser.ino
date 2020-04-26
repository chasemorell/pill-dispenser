
#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>       // this is needed for display
#include <Adafruit_ILI9341.h>
#include <Wire.h>      // this is needed for FT6206
#include <Adafruit_FT6206.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include <Stepper.h>
#include <Servo.h>


// The FT6206 uses hardware I2C (SCL/SDA)
Adafruit_FT6206 ctp = Adafruit_FT6206();

// The display also uses hardware SPI, plus #9 & #10
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// Size of the color selection boxes and the paintbrush size
#define BOXSIZE 40
#define PENRADIUS 3
int oldcolor, currentcolor;

//tft.setRotation(180);

#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)
Stepper stepper(STEPS, 31, 35, 39, 43);
int stepperSpeed = 6;
int stepperRevolution = 2038;

Servo myservo;  // create servo object to control a servo
int pos = 0;

int state = 0;
//0 = no meds need to be taken
//1 = user alerted of medicine
//2 = dispensing medicine...
//3 = medicine dispensed. Confirm medicine as been taken.

long prevTime = 0;
long buzzTime = 0;
boolean isBuzzing = false;
int buzzer = 41;

void alertTakePills() {
  tft.fillScreen(ILI9341_WHITE);
  tft.setCursor(40, 50);
  tft.setFont(&FreeSansBold24pt7b);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(1);
  tft.println("PillBird");

  tft.setCursor(10, 100);
  tft.setFont(&FreeSans12pt7b);
  tft.setTextColor(ILI9341_BLACK);  tft.setTextSize(1.2);
  tft.println("John, it's time to take your medication:");
  tft.setTextSize(1);
  tft.setCursor(10, 160);
  tft.println("1 acetaminophen pills");
  tft.setCursor(10, 180);
  tft.println("3 loratadine pills");
  tft.fillRoundRect(20, 210, 200, 90, 20, ILI9341_RED);
  tft.setCursor(50, 260);
  tft.setTextSize(1.2);
  tft.setTextColor(ILI9341_WHITE);
  tft.println("Get Medicine");
}

void standbyMode() {
  tft.fillScreen(ILI9341_WHITE);
  tft.setCursor(40, 50);
  tft.setFont(&FreeSansBold24pt7b);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(1);
  tft.println("PillBird");
  tft.setFont(&FreeSans12pt7b);
  tft.setTextColor(ILI9341_BLACK);
  tft.setCursor(0, 150);
  tft.println("     It's not time for \n     your next dose yet.");
}
void setup(void) {
  while (!Serial);     // used for leonardo debugging

  Serial.begin(9600);
  Serial.println(F("Cap Touch Paint!"));
  pinMode(buzzer, OUTPUT);

  tft.begin();

  if (! ctp.begin(40)) {  // pass in 'sensitivity' coefficient
    Serial.println("Couldn't start FT6206 touchscreen controller");
    while (1);
  }

  tft.fillScreen(ILI9341_WHITE);

  standbyMode();
  Serial.println("Capacitive touchscreen started");

  myservo.attach(45);
  myservo.write(0); 
  stepper.setSpeed(stepperSpeed);

  // select the current color 'red'
  currentcolor = ILI9341_RED;
}


void dispenseMedication() {
  tft.fillScreen(ILI9341_WHITE);
  tft.setCursor(40, 50);
  tft.setFont(&FreeSansBold24pt7b);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(1);
  tft.println("PillBird");

  tft.setFont(&FreeSans12pt7b);
  tft.setTextColor(ILI9341_BLACK);
  tft.setCursor(0, 150);
  tft.println("     Dispensing your \n     Medicine...");

}

void confirmPillsTaken() {
  tft.fillScreen(ILI9341_WHITE);
  tft.setCursor(40, 50);
  tft.setFont(&FreeSansBold24pt7b);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(1);
  tft.println("PillBird");

  tft.setCursor(10, 100);
  tft.setFont(&FreeSans12pt7b);
  tft.setTextColor(ILI9341_BLACK);  tft.setTextSize(1.2);
  tft.println("Did you take ALL the pills?");
  tft.setTextSize(1);
  tft.setCursor(10, 160);
  tft.println("1 acetaminophen pills");
  tft.setCursor(10, 180);
  tft.println("3 loratadine pills");
  tft.fillRoundRect(20, 210, 200, 90, 20, ILI9341_RED);
  tft.setCursor(50, 250);
  tft.setTextSize(1.2);
  tft.setTextColor(ILI9341_WHITE);
  tft.println("  Yes, I took \n           EVERY pill.");
}

void thankyouPage() {
  tft.fillScreen(ILI9341_WHITE);
  tft.setCursor(40, 50);
  tft.setFont(&FreeSansBold24pt7b);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(1);
  tft.println("PillBird");

  tft.setFont(&FreeSans12pt7b);
  tft.setTextSize(1.5);
  tft.setTextColor(ILI9341_BLACK);
  tft.setCursor(0, 150);
  tft.println("     Thank you for\n     taking your\n     medicine!");
}

void loop() {
           //stepper.step(stepperRevolution);

  if (! ctp.touched()) {
    //noTone(29);  
     noTone(29);
  } else{
   
    if(isBuzzing == false){
    //tone(29, 1500);
    isBuzzing = true;
    buzzTime = millis();
    }
    
  }

  if(millis() - buzzTime > 200){
   
    isBuzzing = false;
  }

  switch (state) {
    case 0: //no pills need to be taken now. After 5s, alert user to take pills.
      if (millis() - prevTime > 5000) {
        alertTakePills();
        state = 1;
      }
      break;
    case 1: //user has been alerted in this stage. When
      if (! ctp.touched()) {
        return;
      } else {
        dispenseMedication();
        stepper.step(stepperRevolution);
        tone(buzzer, 500);
        myservo.write(pos+100);              // tell servo to go to position in variable 'pos'
        delay(1000);
        myservo.write(pos-100);
        noTone(buzzer);
        prevTime = millis();
        state = 2;
        return;
      }
      break;
    case 2:
      if (millis() - prevTime > 1000) {
        confirmPillsTaken();
        prevTime = millis();
        state = 3;
      }
      break;
    case 3:
      if (! ctp.touched()) {
        return;
      } else {

        thankyouPage();
        prevTime = millis();
        state = 4;
        return;
      }
      break;
    case 4:
      if (millis() - prevTime > 5000) {
        standbyMode();
        prevTime = millis();
        state = 0;
      }
      break;
    default:

      break;
  }

  // Retrieve a point
  TS_Point p = ctp.getPoint();

  /*
    // Print out raw data from screen touch controller
    Serial.print("X = "); Serial.print(p.x);
    Serial.print("\tY = "); Serial.print(p.y);
    Serial.print(" -> ");
  */

  // flip it around to match the screen.
  p.x = map(p.x, 0, 240, 240, 0);
  p.y = map(p.y, 0, 320, 320, 0);

  // Print out the remapped (rotated) coordinates
  Serial.print("("); Serial.print(p.x);
  Serial.print(", "); Serial.print(p.y);
  Serial.println(")");


   
}
