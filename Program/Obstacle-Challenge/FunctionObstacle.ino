void initialize_everything() {
  Serial.begin(19200);
  Serial1.begin(19200);
  Serial2.begin(19200);
  Serial3.begin(19200);

  compassPID.Start(0, 0, 0);
  compassPID.SetOutputLimits(-180, 180);
  compassPID.SetSampleTime(10);

  pinMode(STEER_SRV, OUTPUT);
  pinMode(ULTRA_SRV, OUTPUT);
  pinMode(ULTRA_PIN, INPUT);
  pinMode(RED_SEN, INPUT);
  pinMode(BLUE_SEN, INPUT);
  pinMode(BUTTON, INPUT);

  initMotor();
  while (!Serial)
    ;
  myservo.attach(ULTRA_SRV, 500, 2400);
  myservo2.attach(STEER_SRV, 500, 2500);
  steering_servo(0);
  ultra_servo(0, 'U');
}

float degreesToRadians(double degrees) {
  return degrees * PI / 180.0;
}

float radiansToDegree(double raidans) {
  return raidans / PI * 180.0;
}

float _cal_avoidance(char mode, int targetWidth, int objectWidth, int blockCenterX, int blockCenterY) {
  float focalLength = 2.8;
  float cameraFOV = 70;

  float distance = (targetWidth * focalLength * 100) / objectWidth;

  float deltaX = blockCenterX - (320 / 2);
  float deltaY = blockCenterY - (240 / 2);

  float detected_degree = -deltaX * cameraFOV / 320.0;

  float blockPositionX = distance * sin(degreesToRadians(detected_degree));
  float blockPositionY = distance * cos(degreesToRadians(detected_degree)) - 10;

  ULTRA_DIR = mode;

  if (mode == 'L') {
    return max(radiansToDegree(atan2(blockPositionX + (targetWidth / 2 + 10), blockPositionY)), 5) * 0.85;
  } else if (mode == 'R') {
    return min(radiansToDegree(atan2(blockPositionX - (targetWidth / 2 + 10), blockPositionY)), -5) * 1;
  } else {
    return 0;
  }
}

float calculate_avoidance(int signature, int objectWidth, int blockCenterX, int blockCenterY) {
  int avoidance_degree = 0;

  if (signature == 2) {
    avoidance_degree = _cal_avoidance('L', 5, objectWidth, blockCenterX, blockCenterY);
  } else if (signature == 1) {
    avoidance_degree = _cal_avoidance('R', 5, objectWidth, blockCenterX, blockCenterY);
  } else if (signature == 3 || signature == 4) {
    avoidance_degree = _cal_avoidance(TURN, 20, objectWidth, blockCenterX, blockCenterY);
    Serial.println(avoidance_degree);
  }
  return avoidance_degree;
}

int wrapValue(int value, int minValue, int maxValue) {
  int range = maxValue - minValue + 1;
  if (value < minValue) {
    value += range * ((minValue - value) / range + 1);
  }
  return minValue + (value - minValue) % range;
}

void initMotor() {
  int i;
  for (i = 0; i < MotorNum; i++) {
    digitalWrite(MotorPin[i].enPin, LOW);

    pinMode(MotorPin[i].enPin, OUTPUT);
    pinMode(MotorPin[i].directionPin, OUTPUT);
  }
}

void motor(int speed) {
  if (speed > 0) {
    setMotorDirection(M1, Forward);
    setMotorSpeed(M1, speed);
  } else {
    setMotorDirection(M1, Backward);
    setMotorSpeed(M1, speed);
  }
}

void setMotorDirection(int motorNumber, int direction) {
  digitalWrite(MotorPin[motorNumber].directionPin, direction);
}

inline void setMotorSpeed(int motorNumber, int speed) {
  analogWrite(MotorPin[motorNumber].enPin, 255.0 * (speed / 100.0));
}

void color_detection() {
  int blue_value = analogRead(BLUE_SEN);
  if (TURN == 'U') {
    int red_value = analogRead(RED_SEN);
    if (blue_value < 600 || red_value < 600) {
      int lowest_red_sen = red_value;
      long timer_line = millis();
      while (millis() - timer_line < 100) {
        int red_value = analogRead(RED_SEN);
        if (red_value < lowest_red_sen) {
          lowest_red_sen = red_value;
        }
      }
      if (lowest_red_sen > 600) {
        // Red
        TURN = 'R';
        plus_degree += 90;
      } else {
        // Blue
        TURN = 'L';
        plus_degree -= 90;
      }
      halt_detect_line_timer = millis();
      count_line++;
    }
  } else {
    if (millis() - halt_detect_line_timer > 1800) {
      if (blue_value < 600) {
        if (TURN == 'L') {
          plus_degree -= 90;
        } else {
          plus_degree += 90;
        }
        halt_detect_line_timer = millis();
        count_line++;
      }
    }
  }
}

void steering_servo(int degree) {
  myservo2.write((90 + max(min(degree, 50), -50)) / 2);
}

void ultra_servo(int degree, char mode_steer) {
  int middle_degree = 0;
  if (mode_steer == 'F') {
    middle_degree = 150;
  } else if (mode_steer == 'R') {
    middle_degree = 225;
  } else if (mode_steer == 'L' || mode_steer == 'U') {
    middle_degree = 80;
  } else {
  }
  myservo.write(mapf(max(min(middle_degree + degree, 225), 45), 0, 270, 0, 180));
}


float getDistance() {
  float raw_distance = mapf(analogRead(ULTRA_PIN), 0, 1023, 0, 500);
  if (TURN == 'L') {
    raw_distance += 0;
  } else if (TURN == 'R') {
    raw_distance -= 0;
  }
  return min(raw_distance, 50);
}

float getDistanceII() {
  float raw_distance = mapf(analogRead(ULTRA_PIN_II), 0, 1023, 0, 500);
  if (TURN == 'L') {
    raw_distance += 0;
  } else if (TURN == 'R') {
    raw_distance -= 0;
  }
  return min(raw_distance, 50);
}

bool getIMU() {
  while (Serial1.available()) {
    rxBuf[rxCnt] = Serial1.read();
    if (rxCnt == 0 && rxBuf[0] != 0xAA) return;
    rxCnt++;
    if (rxCnt == 8) {
      rxCnt = 0;
      if (rxBuf[0] == 0xAA && rxBuf[7] == 0x55) {
        pvYaw = (int16_t)(rxBuf[1] << 8 | rxBuf[2]) / 100.f;
        pvYaw = wrapValue(pvYaw + plus_degree, -179, 180);
        return true;
      }
    }
  }
  return false;
}

void zeroYaw() {
  Serial1.begin(115200);
  delay(100);
  Serial1.write(0XA5);
  delay(10);
  Serial1.write(0X54);
  delay(100);
  Serial1.write(0XA5);
  delay(10);
  Serial1.write(0X55);
  delay(100);
  Serial1.write(0XA5);
  delay(10);
  Serial1.write(0X52);
  delay(100);
}

void motor_and_steer(int degree) {
  degree = clamp(degree, -52, 52);
  steering_servo(degree);
  motor((map(abs(degree), 0, 30, 49, 49)));
}

float clamp(float value, float minVal, float maxVal) {
  if (value < minVal) return minVal;
  if (value > maxVal) return maxVal;
  return value;
}


void check_leds() {
  while (true) {
    Serial.print("Geen: ");
    Serial.print(analogRead(BLUE_SEN));
    Serial.print("   Red: ");
    Serial.println(analogRead(RED_SEN));
  }
}

void uTurn() {
  camera.handleIncomingData();
  BlobData tempBlob = camera.getBlobData();

  if ((count_line == 3 && count_line < 4) || (count_line == 7 && count_line < 8)) {
    if (tempBlob.signature == 1) {
      currentBlock = 'R';
    } else if (tempBlob.signature == 2) {
      currentBlock = 'G';
    } else {
      currentBlock = 'N';
    }
    if (currentBlock != 'N') {
      if (currentBlock != lastblock) {
        previousBlock = lastblock;
      } else {
        previousBlock = currentBlock;
      }
    }
  }
  lastblock = currentBlock;
  Serial.print(currentBlock);
  Serial.print("lastblock");
  Serial.println(lastblock);

  if (count_line == 8) {
    if (analogRead(BLUE_SEN) > 600) {
      ignore_line = 1;
    }
    if (analogRead(BLUE_SEN) < 600 && ignore_line == 1) {
      if (lastblock == 'R') {
        count_line++;
        if (TURN == 'R') {
          TURN = 'L';
          plus_degree += 90;
        } else {
          TURN = 'R';
          plus_degree -= 90;
        }
        unsigned long timer = millis();
        while (millis() - timer <= 8000) {
          getIMU();
          steering_servo(pvYaw);
          motor(-50);
        }
        halt_detect_line_timer = millis();
      }
    } else {
      if (tempBlob.signature == 1) {
        currentBlock = 'R';
      } else if (tempBlob.signature == 2) {
        currentBlock = 'G';
      } else {
        currentBlock = 'N';
      }
      if (currentBlock != 'N') {
        if (currentBlock != lastblock) {
          previousBlock = lastblock;
        } else {
          previousBlock = currentBlock;
        }
      }
    }
  }
}


float angleDiff(float a, float b) {
  float diff = a - b;
  while (diff > 180) diff -= 360;
  while (diff <= -180) diff += 360;
  return diff;
}
