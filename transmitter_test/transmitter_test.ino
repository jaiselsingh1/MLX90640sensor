const int ch1 = 8; // Connect to receiver channel 1 (pin 8)
const int ch2 = 7; // Connect to receiver channel 2 (pin 7)
const int ch3 = 5; // Connect to receiver channel 3 (pin 5)
const int ch4 = 4; // Connect to receiver channel 4 (pin 4)
const int ch5 = 3; // Connect to receiver channel 5 (pin 3)
const int ch6 = 2; // Connect to receiver channel 6 (pin 2)

// Variables to store control values
int roll;
int pitch;
int throttle;
int yaw;
int auto_manual;
int kill;

void setup() {
Serial.begin(115200); // Start serial communication
pinMode(ch1, INPUT);
pinMode(ch2, INPUT);
pinMode(ch3, INPUT);
pinMode(ch4, INPUT);
pinMode(ch5, INPUT);
pinMode(ch6, INPUT);
}

void loop() {
// Read raw microsecond values
int pwm1 = pulseIn(ch1, HIGH);
int pwm2 = pulseIn(ch2, HIGH);
int pwm3 = pulseIn(ch3, HIGH);
int pwm4 = pulseIn(ch4, HIGH);
int pwm5 = pulseIn(ch5, HIGH);
int pwm6 = pulseIn(ch6, HIGH);

// Map values from microseconds (995-1991) to 0-255 range
roll = map(pwm1, 995, 1991, 0, 255);
pitch = map(pwm2, 995, 1991, 0, 255);
throttle = map(pwm3, 995, 1991, 0, 255);
yaw = map(pwm4, 995, 1991, 0, 255);
auto_manual = map(pwm5, 995, 1991, 0, 255);
kill = map(pwm6, 995, 1991, 0, 255);

// Print mapped values
Serial.print("CH1: "); Serial.print(roll);
Serial.print(" | CH2: "); Serial.print(pitch);
Serial.print(" | CH3: "); Serial.print(throttle);
Serial.print(" | CH4: "); Serial.print(yaw);
Serial.print(" | CH5: "); Serial.print(auto_manual);
Serial.print(" | CH6: "); Serial.println(kill);
delay(5);
}