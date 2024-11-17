#include <Mapf.h>
#include <PID_v2.h>
#include <Wire.h>
#include <Servo.h>
#include "CameraHandler.h"

// SETUP OPENMV CAMERA
CameraHandler camera;
BlobData blob;
BlobData purple_blob1;
BlobData purple_blob2;

// SETUP SERVO
Servo myservo;
Servo myservo2;
int const STEER_SRV = 27;  //16
int const ULTRA_SRV = 25;  //23

// SETUP MOTORS
const int E1Pin = 10;
const int M1Pin = 12;
const int E2Pin = 11;
const int M2Pin = 13;

typedef struct {
  byte enPin;
  byte directionPin;
} MotorContrl;

const int M1 = 0;
const int M2 = 1;
const int MotorNum = 2;

const MotorContrl MotorPin[] = { { E1Pin, M1Pin }, { E2Pin, M2Pin } };

const int Forward = LOW;
const int Backward = HIGH;

//Button
int BUTTON = A8;

//PID
PID_v2 compassPID(0.69, 0, 0, PID::Direct);

//Ultra
int const ULTRA_PIN = A9;
int const ULTRA_PIN_II = A10;


//INEX Gyro
float pvYaw;
uint8_t rxCnt = 0, rxBuf[8];

//  Light Sensors
int const RED_SEN = A6;
int const BLUE_SEN = A7;

//Others
char TURN = 'U';  // L = left, R = Right, U = undefined
char ULTRA_DIR = 'R';
int last_found_signature;
int plus_degree = 0;
double halt_detect_line_timer = 0;
double halt_detect_mok = 0;
double MV_timer = 0;
int count_line = 0;
int parking_step = 0;
int parkingsection = -1;
bool fame = false;
bool parking = false;
bool next = false;
bool foundpark = false;
float found_parkAngle = 0;
char lastblock;
char MOK = 'U';
int side = 1;
float Kaopun;
float Sin;
float Gain;
bool neab = false;
float avoidance_degree;
int hi = 0;
char currentBlock = 'N';
char previousBlock = 'N';
int angle = 80;
int ignore_line = -1;
int INT;

void setup() {
  initialize_everything();
  while (analogRead(BUTTON) > 500)
    ;
  zeroYaw();
}

void loop() {
  // Calculate camera errors
  camera.handleIncomingData();
  BlobData tempBlob = camera.getBlobData();
  int desiredDistance = parking_step == 0 ? (camera.isBlockFound() ? 20 : 40) : 15;
  if (tempBlob.signature == 1) {
    // RED
    last_found_signature = 1;
    blob = tempBlob;

  } else if (tempBlob.signature == 2) {
    // GREEN
    last_found_signature = 2;
    blob = tempBlob;

  } else if (tempBlob.signature == 3) {
    purple_blob1 = tempBlob;
  } else if (tempBlob.signature == 4) {
    purple_blob2 = tempBlob;
  }

  float distanceError = getDistance() - desiredDistance;
  float frontDistance = getDistanceII();
  float avoidance_degree = 0;
  if (tempBlob.signature == 3 && tempBlob.width / 3.9 > blob.width) {
    avoidance_degree = calculate_avoidance(tempBlob.signature, tempBlob.width, tempBlob.x, tempBlob.y);
  } else {
    avoidance_degree = calculate_avoidance(blob.signature, blob.width, blob.x, blob.y);
  }


  // Calculate distance errors
  float deadband = 2.0;
  if (abs(distanceError) < deadband) {
    distanceError = 0.0;
  }
  if (parking_step == 1) {
    ULTRA_DIR = TURN == 'R' ? 'L' : 'R';
  }
  float directionFactor = (ULTRA_DIR == 'R') ? -1.0 : 1.0;
  float adjustedYaw = pvYaw - clamp(distanceError * directionFactor, -20, 20);
  float pidOutput = compassPID.Run(adjustedYaw);

  // Calculate Compass errors
  getIMU();
  color_detection();

  // TEST PARKING

  if (count_line >= 8 && count_line < 12 && tempBlob.signature == 3 && parkingsection == -1) {
    parkingsection = count_line % 4;
  } else if (count_line > 12) {
    if (parkingsection == 0) {
      parkingsection = 4;
    }
  }
  int parking_degree = ((purple_blob1.x + purple_blob2.x) / 2 - 160) * -0.5;
  int final_degree = camera.isBlockFound() ? mapf(min(max(getDistance(), 15), desiredDistance), 15, desiredDistance, pidOutput, avoidance_degree) : pidOutput;

  switch (parking_step) {
    case 1:

      if (!fame) {
        halt_detect_mok = millis();
        fame = true;
      }
      if (tempBlob.signature != 3 || tempBlob.width < 70) {
        steering_servo(pidOutput * 1.3);
        ultra_servo(pvYaw, ULTRA_DIR);
        motor(40);
      } else {
        parking_step = 2;
        fame = false;
      }
      break;
    case 2:
      halt_detect_line_timer = millis();
      if (!fame) {
        halt_detect_mok = millis();
        fame = true;
      }
      if (millis() - halt_detect_mok < 1400) {
        steering_servo(final_degree);
        ultra_servo(0, ULTRA_DIR);
        motor(40);
        // Serial.println("1");
      } else {
        parking_step = 3;
        fame = false;
        if (TURN == 'L') {
          plus_degree += 90;
        } else {
          plus_degree -= 90;
        }
      }

      break;

    case 3:

      if (!fame) {
        halt_detect_mok = millis();
        fame = true;
      }
      if (millis() - halt_detect_mok < 2000) {
        steering_servo(pvYaw);
        ultra_servo(0, ULTRA_DIR);
        motor(-40);
      } else {
        parking_step = 4;
        fame = false;
      }

      break;

    case 4:
      if (frontDistance > 10) {
        steering_servo(mapf(clamp(frontDistance, 10, 20), 20, 10, parking_degree, 0));
        motor(mapf(clamp(frontDistance, 10, 20), 20, 10, 50, 40));
      } else {
        motor(30);
        delay(500);
        motor(0);
        while (true)
          ;
      }
      break;

    case 5:
      if (count_line >= 13 && count_line < 12 + parkingsection) {
        motor_and_steer(pidOutput);
        ultra_servo(pvYaw, TURN);
      } else {
        parking_step = 1;
      }
      break;

    default:
      motor_and_steer(final_degree);
      ultra_servo(pvYaw, ULTRA_DIR);
      if (count_line > 12 && parkingsection != -1) {
        parking_step = 5;
      }
      break;
  }
  uTurn();
}
