#include <Servo.h>

int degree=0;
Servo myservo;
int i = 1;

void setup() {
  myservo.attach(12);
}
void loop() {
  myservo.write(30);  //TURN a bit less than  half cycle
  delay(500);
  myservo.detach();
}
