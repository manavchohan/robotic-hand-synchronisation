#include <Servo.h>
#define numOfvalsRec 5
#define digitsPervalRec 1

Servo servoThumb;
Servo servoIndex;
Servo servoMiddle;
Servo servoRing;
Servo servoPinky;

int valsRec[numOfvalsRec];
int stringLength = numOfvalsRec * digitsPervalRec + 1;
int counter = 0;
bool counterStart = false;
String receivedString;

void setup() {
  Serial.begin(2038);
  servoThumb.attach(9);
  servoIndex.attach(8);
  servoMiddle.attach(10);
  servoRing.attach(11);
  servoPinky.attach(12);
}

void receivedData() {
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '$') {
      counterStart = true;
    }
    if (counterStart) {
      if (counter < stringLength) {
        receivedString = String(receivedString + c);
        counter++;
      }
      if (counter >= stringLength) {
        for (int i = 0; i < numOfvalsRec; i++) {
          int num = (i * digitsPervalRec) + 1;
          valsRec[i] = receivedString.substring(num, num + digitsPervalRec).toInt();
        }
        receivedString = "";
        counter = 0;
        counterStart = false;
      }
    }
  }
}

void loop() {
  receivedData();
  if(valsRec[0]== 1){
    servoThumb.write(180);
  }
  else{
    servoThumb.write(0);
  }

  if(valsRec[1]== 1){
    servoIndex.write(180);
  }
  else{
    servoIndex.write(0);
  }

  if(valsRec[2]== 1){
    servoMiddle.write(180);
  }
  else{
    servoMiddle.write(0);
  }

  if(valsRec[3]== 1){
    servoRing.write(180);
  }
  else{
    servoRing.write(0);
  }

  if(valsRec[4]== 1){
    servoPinky.write(180);
  }
  else{
    servoPinky.write(0);
  }

}