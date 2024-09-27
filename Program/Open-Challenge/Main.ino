#include "Mapf.h"
#include "Servo.h"
#include <PID_v2.h>

Servo myservo1;
Servo myservo2;

//  Compass Variables
float pvYaw, pvRoll, pvPitch;
uint8_t rxCnt = 0, rxBuf[8];

//  Motor B
const int E1Pin = 10;
const int M1Pin = 12;
const int E2Pin = 11;
const int M2Pin = 13;

/**inner definition**/
typedef struct {
  byte enPin;
  byte directionPin;
} MotorContrl;

const int M1 = 0;
const int MotorNum = 1  ;

const MotorContrl MotorPin[] = { {E1Pin, M1Pin}, {E2Pin, M2Pin} } ;

const int Forward = LOW;
const int Backward = HIGH;

//  Servos
int const STEER_SRV = 23;
int const ULTRA_SRV = 16;

//  Ultrasonic Sensor
int const ULTRA_PIN = A9;

//  Light Sensors
int const RED_SEN = A6;
int const GEEN_SEN = A7;

//  Button
int const BUTTON = A8;

char TURN = 'U';
int compass_offset = 0;
long halt_detect_line_timer;
bool found_block = false;
int Servo_Value;
int x = 1;
int Y = 20;
int count = 0;

// Specify the links and initial tuning parameters
PID_v2 compassPID(0.4, 0.0001, 0.025, PID::Direct);

void setup() {
  compassPID.Start(0, 0, 0);
  compassPID.SetOutputLimits(-180, 180);
  compassPID.SetSampleTime(10);
  pinMode(E1Pin, OUTPUT);
  pinMode(M1Pin, OUTPUT);
  pinMode(STEER_SRV, OUTPUT);
  pinMode(ULTRA_SRV, OUTPUT);
  pinMode(ULTRA_PIN, INPUT);
  pinMode(RED_SEN, INPUT);
  pinMode(GEEN_SEN, INPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
  initMotor();
  myservo1.attach(STEER_SRV, 600, 2400);
  myservo2.attach(ULTRA_SRV, 600, 2400);
  steering_servo(0);
  ultra_servo(0, 'L');
  // check_leds();
  while (analogRead(BUTTON) > 500)
    ;
  zeroYaw();
  while (analogRead(BUTTON) <= 500)
    ;
}

void loop() {
  // getIMU();
  // Serial.println(pvYaw);
  // //(❁´◡`❁);
  

  while (analogRead(BUTTON) > 500) {
    getIMU();
    line_detection();
    int wall_distance = getDistance();
    motor_and_steer((1 * x) * compassPID.Run((x * pvYaw) + ((wall_distance - Y)) * ((float(TURN == 'TURN') - 0.5) * 2)) * -1);
    ultra_servo(pvYaw,TURN);
    if (count >= 12) {
      long timer01 = millis();
      while (millis() - timer01 < 850) {
        getIMU();
        line_detection();
        motor_and_steer((1 * x) * compassPID.Run((x * pvYaw) + ((wall_distance - Y)) * ((float(TURN == 'TURN') - 0.5) * 2)) * -1);
        ultra_servo(pvYaw,TURN);
      }
      setMotorSpeed( M1 , 0 );
      while (true) {
      }
    }
  }
    setMotorSpeed( M1 , 0 );
  while (analogRead(BUTTON) <= 500)
    ;
  while (analogRead(BUTTON) > 500)
    ;
  while (analogRead(BUTTON) <= 500)
    ;
}
