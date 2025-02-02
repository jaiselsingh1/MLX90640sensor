#include <Servo.h>

const int ch1 = A0; // Connect to receiver channel 1 (pin 8)
const int ch2 = A1; // Connect to receiver channel 2 (pin 7)
const int ch3 = A2; // Connect to receiver channel 3 (pin 5)
const int ch4 = A3; // Connect to receiver channel 4 (pin 4)
const int ch5 = A4; // Connect to receiver channel 5 (pin 3)
const int ch6 = A5; // Connect to receiver channel 6 (pin 2)

// Variables to store control values
int roll;
int pitch;
int throttle;
int yaw;
int auto_manual;
int kill;


Servo motor1, motor2, motor3, motor4;
const int MIN_THROTTLE = 1000;
const int MAX_THROTTLE = 2000;

int pwm1;
int pwm2;
int pwm3;
int pwm4;
int pwm5;
int pwm6;

void setup() {
Serial.begin(9600); // Start serial communication
pinMode(ch1, INPUT);
pinMode(ch2, INPUT);
pinMode(ch3, INPUT);
pinMode(ch4, INPUT);
pinMode(ch5, INPUT);
pinMode(ch6, INPUT);
motor1.attach(11);
 // motor2.attach(9);
 // motor3.attach(10);
 // motor4.attach(11);
 delay(5000);
 
}

void loop() {
// Read raw microsecond values

pwm1 = pulseIn(ch1, HIGH);
pwm2 = pulseIn(ch2, HIGH);
pwm3 = pulseIn(ch3, HIGH);
pwm4 = pulseIn(ch4, HIGH);
pwm5 = pulseIn(ch5, HIGH);
pwm6 = pulseIn(ch6, HIGH);
// Map values from microseconds (995-1991) to 0-255 range
roll = map(pwm1, 995, 1991, 1000, 2000);
pitch = map(pwm2, 995, 1991, 1000, 2000);
throttle = map(pwm3, 998, 1989, 1000, 2000);
yaw = map(pwm4, 995, 1991, 1000, 2000);
auto_manual = map(pwm5, 995, 1991, 0, 100);
kill = map(pwm6, 995, 1991, 0, 100);

    if (kill>70){
      kill = 1;
    }else{
      kill = 0;
    }

    if (auto_manual>50){
      auto_manual = 1;
    }else{
      auto_manual = 0;
    }

    if (kill){
      stopAllMotors();
    }else{
      if (!auto_manual ) {
        setAllMotors(throttle);
      } else {
        setMotorSpeed(1, throttle);
      }
    }



// Print mapped values

Serial.print("CH1: "); Serial.print(roll);
Serial.print(" | CH2: "); Serial.print(pitch);
Serial.print(" | CH3: "); Serial.print(throttle);
Serial.print(" | CH4: "); Serial.print(yaw);
Serial.print(" | CH5: "); Serial.print(auto_manual);
Serial.print(" | CH6: "); Serial.println(kill);
Serial.println("");
delay(100);
}

void setMotorSpeed(int motorNumber, int value) {
  value = constrain(value, MIN_THROTTLE, MAX_THROTTLE);
  switch(motorNumber) {
    case 1: motor1.writeMicroseconds(value); break;
    case 2: motor2.writeMicroseconds(value); break;
    case 3: motor3.writeMicroseconds(value); break;
    case 4: motor4.writeMicroseconds(value); break;
  }
  Serial.print("Motor ");
  Serial.print(motorNumber);
  Serial.print(" set to ");
  Serial.println(value);
}


void setAllMotors(int value) {
  value = constrain(value, MIN_THROTTLE, MAX_THROTTLE);
  motor1.writeMicroseconds(value);
  motor2.writeMicroseconds(value);
  motor3.writeMicroseconds(value);
  motor4.writeMicroseconds(value);
  Serial.print("All motors set to ");
  Serial.println(value);
}


void stopAllMotors() {
  setAllMotors(MIN_THROTTLE);
  Serial.println("All motors stopped");
}
