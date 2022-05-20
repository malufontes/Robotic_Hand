#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int mappos;

void setup() {
  Serial.begin(115200);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  pos = analogRead(A5);
  mappos = map(pos,0,1023,0,180);
  myservo.write(mappos);              // tell servo to go to position in variable 'pos'
  Serial.println(mappos);
  delay(100);
}
