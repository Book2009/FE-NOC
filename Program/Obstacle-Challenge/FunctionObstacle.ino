void handleIncomingData() {

  found_block = false;  // Reset found_block at the start
  signature = 0;
  while (Serial3.available()) {
    char incomingByte = Serial3.read();
    if (incomingByte != '\n') {
      receivedString += incomingByte;
    } else {
      receivedString.trim();  // Remove any leading or trailing whitespace

      // Parse the received data
      int commaIndex1 = receivedString.indexOf(',');
      int commaIndex2 = receivedString.indexOf(',', commaIndex1 + 1);
      int commaIndex3 = receivedString.indexOf(',', commaIndex2 + 1);
      int commaIndex4 = receivedString.indexOf(',', commaIndex3 + 1);

      if (commaIndex1 != -1 && commaIndex2 != -1 && commaIndex3 != -1 && commaIndex4 != -1) {
        int xValue = receivedString.substring(0, commaIndex1).toInt();
        int yValue = receivedString.substring(commaIndex1 + 1, commaIndex2).toInt();
        int widthValue = receivedString.substring(commaIndex2 + 1, commaIndex3).toInt();
        int heightValue = receivedString.substring(commaIndex3 + 1, commaIndex4).toInt();
        int blobType = receivedString.substring(commaIndex4 + 1).toInt();

        // Validate the coordinates and dimensions
        if (xValue >= 0 && xValue <= 320 && yValue >= 0 && yValue <= 240 && widthValue >= 0 && widthValue <= 320 && heightValue >= 0 && heightValue <= 240) {
          // Store the data of the received blob
          largestBlobX = xValue;
          largestBlobY = yValue;
          largestBlobWidth = widthValue;
          largestBlobHeight = heightValue;
          signature = (blobType == 1) ? 2 : 1;  // 2 for red, 1 for general

          found_block = true;  // A valid blob was received
          // Serial.println("Valid blob detected and stored.");
        } else {
          Serial.println("Received invalid coordinates or dimensions.");
          found_block = false;
        }
      } else {
        Serial.println("Data format error.");
        found_block = false;
      }
      receivedString = "";  // Clear the received string after processing
    }
  }

  if (found_block) {
    // Serial.print("Blob - X: ");
    // Serial.print(largestBlobX);
    // Serial.print(", Y: ");
    // Serial.print(largestBlobY);
    // Serial.print(", Width: ");
    // Serial.print(largestBlobWidth);
    // Serial.print(", Height: ");
    // Serial.print(largestBlobHeight);
    // Serial.print(", FoundBlock: ");
    // Serial.print(found_block);
    // Serial.print(", Signature: ");
    // Serial.println(signature);
  } else {
    Serial.println("No valid blob detected.");
  }
}

float degreesToRadians(double degrees) {
  return degrees * PI / 180.0;
}

float radiansToDegree(double raidans) {
  return raidans / PI * 180.0;
}

float calculate_avoidance() {
  // Check if a block is found
  if (signature != 0) {
    // Reset missed block count if a block is found
    missedBlockCount = 0;

    // Constants for OpenMV H7
    int targetHeight = 10;    // Height of the object in centimeters
    float focalLength = 3.6;  // Focal length of the OpenMV H7 camera lens in mm
    float cameraFOV = 60.0;   // Field of view of the OpenMV H7 camera in degrees

    // Use the largest blob data
    int objectHeight = largestBlobHeight;
    float distance = (targetHeight * focalLength * 100) / objectHeight;

    float blockCenterX = largestBlobX;
    float blockCenterY = largestBlobY;

    float deltaX = blockCenterX - (320 / 2);  // Assuming a 640x480 image resolution
    float deltaY = blockCenterY - (240 / 2);

    float detected_degree = -deltaX * cameraFOV / 320.0;  // Inverted deltaX to swap behavior

    float blockPositionX = distance * sin(degreesToRadians(detected_degree));
    float blockPositionY = distance * cos(degreesToRadians(detected_degree)) - 18;

    // Adjust avoidance degrees based on blob signature
    if (signature == 1) {
      avoidance_degree = max(radiansToDegree(atan2(blockPositionX + 9, blockPositionY)), 5) * -1.4;
      last_block = 'L';
      Blocks_TURN == 'L';
      before_last_block = 'L';
      //avoidance_degree = 0;
    } else if (signature == 2) {
      avoidance_degree = min(radiansToDegree(atan2(blockPositionX - 9, blockPositionY)), -5) * -1.7;
      last_block = 'R';
      Blocks_TURN == 'R';
      before_last_block = 'R';
      //avoidance_degree = 0;
    }
  } else {
    // Increment the missed block count if no block is found
    missedBlockCount++;

    // // If the block is missed three times in a row, set avoidance degree to zero
    if (missedBlockCount >= MAX_MISSED_BLOCKS) {
      avoidance_degree = 0;  // or some default value
    }
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

void motor(int speed) {
  if (speed > 0) {
    setMotorDirection(M1, Forward);
    setMotorSpeed(M1, speed);
  } else {
    setMotorDirection(M1, Backward);
    setMotorSpeed(M1, speed);
  }
}

void initMotor() {
  int i;
  for (i = 0; i < MotorNum; i++) {
    digitalWrite(MotorPin[i].enPin, LOW);

    pinMode(MotorPin[i].enPin, OUTPUT);
    pinMode(MotorPin[i].directionPin, OUTPUT);
  }
}

/**  motorNumber: M1, M2
direction:          Forward, Backward **/
void setMotorDirection(int motorNumber, int direction) {
  digitalWrite(MotorPin[motorNumber].directionPin, direction);
}

/** speed:  0-100   * */
inline void setMotorSpeed(int motorNumber, int speed) {
  analogWrite(MotorPin[motorNumber].enPin, 255.0 * (speed / 100.0));  //PWM
}

void zeroYaw() {
  Serial1.begin(115200);
  delay(100);
  // Sets data rate to 115200 bps
  Serial1.write(0XA5);
  delay(10);
  Serial1.write(0X54);
  delay(100);
  // pitch correction roll angle
  Serial1.write(0XA5);
  delay(10);
  Serial1.write(0X55);
  delay(100);
  // zero degree heading
  Serial1.write(0XA5);
  delay(10);
  Serial1.write(0X52);
  delay(100);
  // automatic mode
}

bool getIMU() {
  while (Serial1.available()) {
    rxBuf[rxCnt] = Serial1.read();
    if (rxCnt == 0 && rxBuf[0] != 0xAA) return;
    rxCnt++;
    if (rxCnt == 8) {  // package is complete
      rxCnt = 0;
      if (rxBuf[0] == 0xAA && rxBuf[7] == 0x55) {  // data package is correct
        pvYaw = (int16_t)(rxBuf[1] << 8 | rxBuf[2]) / 100.f;
        pvPitch = (int16_t)(rxBuf[3] << 8 | rxBuf[4]) / 100.f;
        pvRoll = (int16_t)(rxBuf[5] << 8 | rxBuf[6]) / 100.f;
        pvYaw = wrapValue(pvYaw + plus_degree, -179, 180);
        return true;
      }
    }
  }
  return false;
}

void Color_detection() {
  int blue_value = analogRead(BLUE_SEN);
  if (TURN == 'U') {
    int red_value = analogRead(RED_SEN);
    if (blue_value < 605 || red_value < 400) {
      int lowest_red_sen = red_value;
      long timer_line = millis();
      while (millis() - timer_line < 100) {
        int red_value = analogRead(RED_SEN);
        if (red_value < lowest_red_sen) {
          lowest_red_sen = red_value;
        }
      }
      if (lowest_red_sen > 400) {
        // Red
        TURN = 'L';
        plus_degree += 90;
      } else {
        // Blue
        TURN = 'R';
        plus_degree -= 90;
      }
      halt_detect_line_timer = millis();
      Line_Number++;
    }
  } else {
    if (millis() - halt_detect_line_timer > 1500) {
      Serial.println(pvYaw);
      if (blue_value < 605) {
        if (TURN == 'R') {
          plus_degree -= 90;
        } else {
          plus_degree += 90;
        }
        halt_detect_line_timer = millis();
        Line_Number++;
      }
    }
  }
}

void steering_servo(int degree) {
  myservo2.write((90 + max(min(degree, 45), -45)) / 2);
}

void motor_and_steer(int degree) {
  degree = max(min(degree, 52), -52);
  steering_servo(degree);
  // motor((map(abs(degree), 0, 45, 60, 70)));
  motor(0);
}

void ultra_servo(int degree, char mode_steer) {
  int middle_degree = 0;
  if (mode_steer == 'F') {
    middle_degree = 135;
  } else if (mode_steer == 'L') {
    middle_degree = 135 - 75;
  } else if (mode_steer == 'R' || mode_steer == 'U') {
    middle_degree = 135 + 95;
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
