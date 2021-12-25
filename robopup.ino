#include <Servo.h>
#include <Ultrasonic.h>
#include <IRremote.h>

#define TRIGGER_PIN  8
#define ECHO_PIN     9

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
Servo servoFL;  // create servo object to control a servo
Servo servoFR;
Servo servoBL;
Servo servoBR;

int RECPin = 11;
IRrecv irrecv(RECPin);
decode_results results;

int pos = 0;
int fl = 0;
int del = 10;
String cursig;
int pose;

/*
 * pose = 0 : sitting
 * pose = 1 : standing
 * 
 */

void setup() {
  irrecv.enableIRIn();
  //Serial.begin(9600);
  servoFL.attach(5);
  servoFR.attach(3);
  servoBL.attach(4);
  servoBR.attach(2);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  if (irrecv.decode(&results)) {
    
    cursig = String(results.value, HEX);
    //Serial.println(cursig);
    if (cursig == "ff5aa5") {
      stand();
      pose = 1;
    }
    else if (cursig == "ff02fd") {
      stepforward();
      pose = 1;
    }
    else if (cursig == "ff38c7") {
      sit();
      pos = 0;
    }
    irrecv.resume(); // Receive the next value
  }
  
  if (!fl){

    fl = 1;
    
  }

}

int stand() {
    if (pos == 0){
      for (pos = 30; pos >= 0; pos -= 1){
        servoBR.write(90 + pos);
        servoBL.write(90 - pos);
        delay(del);
        servoFR.write(90 - int(pos/2));
        servoFL.write(90 + int(pos/2));
        delay(del);
      }     
    }
    servoFL.write(90);
    servoFR.write(90);
    servoBL.write(90);
    servoBR.write(90);
    //delay(del*100);
}

int sit() {
  if (pose == 0){
    return 0;
  }
  else if (pose == 1){
    for (pos = 0; pos <= 30; pos += 1){
      servoBR.write(90 + pos);
      servoBL.write(90 - pos);
      delay(del);
      servoFR.write(90 - int(pos/2));
      servoFL.write(90 + int(pos/2));
      delay(del);
    }
    pose = 0;
  }
}

int stepforward() {
    if (pose != 1){
      stand();
    }
    for (pos = 90; pos >= 75; pos -= 1){
      servoBL.write(pos);
      delay(del);
    }
    delay(del*2);
    
    for (pos = 90; pos <= 120; pos += 1){
      servoFR.write(pos);
      delay(del);
    }
    delay(del*2);
    
    for (pos = 75; pos <= 90; pos += 1){
      servoBL.write(pos);
      delay(del);
    }
    delay(del*2);
    // First half ends
    for (pos = 90; pos <= 105; pos += 1){
      servoBR.write(pos);
      delay(del);
    }
    delay(del*2);
    
    for (pos = 90; pos >= 60; pos -= 1){
      servoFL.write(pos);
      delay(del);
    }
    delay(del*2);
    for (pos = 105; pos >= 90; pos -= 1){
      servoBR.write(pos);
      delay(del);
    }
    delay(del*2);

    
    for (pos = 0; pos <= 30; pos += 1){
      servoFR.write(120 - pos);
      servoBR.write(int(90 - pos));
      delay(del);
      servoFL.write(60 + pos);
      servoBL.write(int(90 + pos));
      delay(del);
    }
    // robot is halfway
    /*
    for (pos = 90; pos <= 120; pos += 1){
      servoFL.write(pos);
      delay(del);
    }
    delay(del*2);
    */
    for (pos = 60; pos <= 90; pos += 1){
      servoBR.write(pos);
      delay(del);
    }
    delay(del*2);
    /*
    for (pos = 120; pos >= 90; pos -= 1){
      servoFL.write(pos);
      delay(del);
    }
    delay(del*2);
    
    // First half ends
    for (pos = 90; pos >= 60; pos -= 1){
      servoFR.write(pos);
      delay(del);
    }
    delay(del*2);
    */
    for (pos = 120; pos >= 90; pos -= 1){
      servoBL.write(pos);
      delay(del);
    }
    delay(del*2);
    /*
    for (pos = 60; pos <= 90; pos += 1){
      servoFR.write(pos);
      delay(del);
    }
    
    //delay(del*2);
    */
  }
