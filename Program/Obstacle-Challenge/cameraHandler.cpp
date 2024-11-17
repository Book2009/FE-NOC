#include "CameraHandler.h"

CameraHandler::CameraHandler()
  : found_block(false), receivedString("") {
  blob = { 0, 0, 0, 0, 0 };
}
void CameraHandler::handleIncomingData() {
  while (Serial3.available() > 0) {
    char incomingByte = Serial3.read();
    if (incomingByte == '\n') {
      parseData(receivedString);
      receivedString = "";
    } else {
      receivedString += incomingByte;
    }
  }
}
void CameraHandler::parseData(const String &data) {
  int commaIndex1 = data.indexOf(',');
  int commaIndex2 = data.indexOf(',', commaIndex1 + 1);
  int commaIndex3 = data.indexOf(',', commaIndex2 + 1);
  int commaIndex4 = data.indexOf(',', commaIndex3 + 1);

  if (commaIndex1 != -1 && commaIndex2 != -1 && commaIndex3 != -1 && commaIndex4 != -1) {
    int xValue = data.substring(0, commaIndex1).toInt();
    int yValue = data.substring(commaIndex1 + 1, commaIndex2).toInt();
    int widthValue = data.substring(commaIndex2 + 1, commaIndex3).toInt();
    int heightValue = data.substring(commaIndex3 + 1, commaIndex4).toInt();
    int blobType = data.substring(commaIndex4 + 1).toInt();

    processBlobData(xValue, yValue, widthValue, heightValue, blobType);
  } else {
    found_block = false;
  }
}
void CameraHandler::processBlobData(int x, int y, int width, int height, int type) {
  if (type != 0) {

    found_block = true;

    blob.x = x;
    blob.y = y;
    blob.width = width;
    blob.height = height;
    blob.signature = type;
  } else {
    found_block = false;
  }
}

bool CameraHandler::isBlockFound() const {
  return found_block;
}

BlobData CameraHandler::getBlobData() const {
  return blob;
}
