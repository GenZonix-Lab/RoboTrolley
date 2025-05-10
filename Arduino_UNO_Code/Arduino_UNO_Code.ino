#include <Servo.h>
#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

String inputData;
int x, y, width, height;
String label;

void setup() {
  Serial.begin(9600); 
  
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(2000);
  Serial.println("rendering");
}

void loop() {
  while(!Serial.available()){
    delay(10);
  }

  if (Serial.available()) {
    inputData = Serial.readStringUntil('\n');  // Read a line of serial data

    // Check if string contains rectangle data
    if (inputData.indexOf("x:") >= 0 && inputData.indexOf("y:") >= 0) {
      parseData(inputData);
      classifyX(x);  // Assign label based on x

      Serial.print("x: "); Serial.print(x);
      Serial.print(", y: "); Serial.print(y);
      Serial.print(", label: "); Serial.println(label);
    }
  }
  Serial.flush();
}

void parseData(String data) {
  int xIndex = data.indexOf("x:");
  int yIndex = data.indexOf("y:");
  int wIndex = data.indexOf("width:");
  int hIndex = data.indexOf("height:");

  x = data.substring(xIndex + 2, data.indexOf(",", xIndex)).toInt();
  y = data.substring(yIndex + 2, data.indexOf(",", yIndex)).toInt();
  width = data.substring(wIndex + 6, data.indexOf(",", wIndex)).toInt();
  height = data.substring(hIndex + 7, data.indexOf("]", hIndex)).toInt();
}

void classifyX(int xpos) {
  if (xpos < 18) {
    left();
  } else if (xpos < 70) {
    forward();
  } else {
    right();
  }
  delay(100);
  stop();
}

void forward(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void left(){
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}
void right(){
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}
void stop(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}