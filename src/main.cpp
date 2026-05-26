#include <Arduino.h>

#include <VarSpeedServo.h> 
VarSpeedServo BigServo;

#define INDUCTIVE_SENSOR_PIN 2
#define BIG_SERVO_PIN 4

#define SERVO_BOTTOM_ANGLE 30                      // angle of the bottom position
#define SERVO_TOP_ANGLE SERVO_BOTTOM_ANGLE + 120    // angle difference to the top position

#define SERVO_SPEED_RISE 75 // speed of the servo. between 1 and 255 (0 for max)
#define SERVO_SPEED_FALL 200 // speed of the servo. between 1 and 255 (0 for max)

#define DELAY_START 250 // how long to wait when a signal has come until we start rising
#define DELAY_RISE 750  // how long to wait for the servo to reach the top position
#define DELAY_FALL 500  // how long does the servo take to reach the bottom position

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  // Blink 3 times fast on start
  for(int i=0; i<3; i++) {
    digitalWrite(LED_BUILTIN, HIGH); delay(100);
    digitalWrite(LED_BUILTIN, LOW);  delay(100);
  }

  BigServo.attach(BIG_SERVO_PIN);
  pinMode(INDUCTIVE_SENSOR_PIN, INPUT);
  BigServo.write(SERVO_BOTTOM_ANGLE);
}
void loop() {
  if(!digitalRead(INDUCTIVE_SENSOR_PIN)){
    delay(DELAY_START);
    // ball has arrived, rise
    BigServo.write(SERVO_TOP_ANGLE, SERVO_SPEED_RISE);
    delay(DELAY_RISE);

    // we are on the top, go down again
    BigServo.write(SERVO_BOTTOM_ANGLE, SERVO_SPEED_FALL);
    delay(DELAY_FALL);
  }
}