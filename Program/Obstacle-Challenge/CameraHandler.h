#ifndef CAMERAHANDLER_H
#define CAMERAHANDLER_H

#include <Arduino.h>

struct BlobData {
    int x;
    int y;
    int width;
    int height;
    int signature;
};

class CameraHandler {
  public:
    CameraHandler();

    void handleIncomingData();
    bool isBlockFound() const;
    BlobData getBlobData() const;

  private:
    bool found_block;
    BlobData blob;
    String receivedString;

    void parseData(const String &data);
    void processBlobData(int x, int y, int width, int height, int type);
};

#endif
