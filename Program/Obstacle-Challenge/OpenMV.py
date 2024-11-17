import time
import sensor
import display
from pyb import UART

# Initialize sensor
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)  # 320x240 resolution

sensor.skip_frames(time=2000)  # Wait for settings to take effect.

# Lock auto-exposure and auto-white-balance to prevent drift across reboots.
sensor.set_auto_gain(False)  # Disable auto gain.
sensor.set_auto_whitebal(False)  # Disable auto white balance.

# Lock exposure to prevent fluctuations in lighting conditions.
sensor.set_auto_exposure(False, exposure_us=7000)  # Adjust exposure manually.


sensor.set_contrast(3)
sensor.set_brightness(0)
sensor.set_saturation(0)

sensor.skip_frames(time=1000)

#sensor.__write_reg(0x0E, 0b00000000)  # Disable night mode
#sensor.__write_reg(0x3E, 0b00000000)  # Disable BLC

# Color thresholds
GREEN_THRESHOLDS = [(22, 48, -52, -21, 17, 49)]
RED_THRESHOLDS = [(0, 52, 13, 37, -3, 25)]
PURPLE_THRESHOLDS = [(33, 70, -25, 14, 42, 76)]

# Region of Interest (ROI)
ROI = (0, 160, 320, 240)

# Initialize UART
uart = UART(3, 19200, timeout_char = 2000)
clock = time.clock()

def send_blob_data(blob, blob_type, color):
    """Send blob data over UART and draw rectangle on the image."""
    img.draw_rectangle(blob.rect(), color=color)
    img.draw_cross(blob.cx(), blob.cy(), color=color)
    data = f"{blob.cx()},{blob.cy()},{blob.w()},{blob.h()},{blob_type}\n"
    uart.write(data)
    print(data)  # Optional: Log sent data for debugging

def send_no_blob_data():
    """Send default data when no red or green blob is found."""
    data = "0,0,0,0,0\n"  # No blob detected
    uart.write(data)
#    print(data)  # Optional: Log for debugging

while True:
    clock.tick()
    img = sensor.snapshot()

    # Detect red and green blobs
    green_blobs = img.find_blobs(GREEN_THRESHOLDS, roi=ROI, area_threshold=30, pixels_threshold=30, merge=True)
    red_blobs = img.find_blobs(RED_THRESHOLDS, roi=ROI, area_threshold=30, pixels_threshold=30, merge=True)

    # Find the largest blob between red and green blobs
    largest_green = max(green_blobs, key=lambda b: b.area(), default=None)
    largest_red = max(red_blobs, key=lambda b: b.area(), default=None)

    # Determine the largest blob between red and green
    largest_blob = None
    if largest_green and largest_red:
        largest_blob = largest_green if largest_green.area() > largest_red.area() else largest_red
    elif largest_green:
        largest_blob = largest_green
    elif largest_red:
        largest_blob = largest_red

    # Send data for the largest red or green blob (if found), else send '0'
    if largest_blob:
        blob_type = 2 if largest_blob in green_blobs else 1  # Green = 2, Red = 1
        color = (0, 255, 0) if blob_type == 2 else (200, 0, 0)
        send_blob_data(largest_blob, blob_type, color)
    else:
        send_no_blob_data()  # Send 0 when no red or green blobs are found

    # Detect and send data for all purple blobs
    purple_blobs = img.find_blobs(PURPLE_THRESHOLDS, roi=ROI, area_threshold=30, pixels_threshold=30, merge=True)
    purple_blobs = sorted(purple_blobs, key=lambda b: b.cx())

    if purple_blobs:
        for i, purple_blob in enumerate(purple_blobs):
            color = (255, 0, 255) if i == 0 else (252, 244, 3)  # Alternate colors for blobs
            send_blob_data(purple_blob, 3 + i, color)  # Different blob types for each purple blob
    cropped_img = img.crop(roi=ROI)  # Crop to exclude the top 120 pixels
    # Optional: Read and print incoming UART data
    if uart.any():
        data = uart.readline()
        print("Received:", data)
