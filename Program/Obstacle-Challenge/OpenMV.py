import sensor, image, time, math
from pyb import UART

# Initialize the sensor
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time=2000)
clock = time.clock()

# Initialize UART (change 3 to 1 if using UART1)
uart = UART(3, 19200)

# Color thresholds
red_threshold = (22, 34, 44, 92, -128, 127)
green_threshold = (0, 58, -128, -25, -128, 127)

focalLength = 2.3
targetHeight = 10
cameraFOV = 80.0
frameWidth = 320
frameHeight = 240

avoidance_degree = 0
Blocks_TURN = None

def calculate_avoidance():
    global avoidance_degree, Blocks_TURN
    found_block = False

    img = sensor.snapshot()

    red_blobs = img.find_blobs([red_threshold], pixels_threshold=100, area_threshold=100, merge=True)
    green_blobs = img.find_blobs([green_threshold], pixels_threshold=100, area_threshold=100, merge=True)

    largest_blob = None
    largest_blob_area = 0
    signature = None

    all_blobs = [(1, blob) for blob in red_blobs] + [(2, blob) for blob in green_blobs]

    for sig, blob in all_blobs:
        if blob.h() > 1.33 * blob.w():
            object_area = blob.w() * blob.h()
            found_block = True
            if object_area > largest_blob_area:
                largest_blob = blob
                largest_blob_area = object_area
                signature = sig

    if signature is not None and largest_blob:
        object_height = largest_blob.h()
        distance = (targetHeight * focalLength * 100) / object_height

        block_center_x = largest_blob.cx()
        block_center_y = largest_blob.cy()

        delta_x = block_center_x - frameWidth / 2
        detected_degree = delta_x * (cameraFOV / frameWidth)

        block_position_x = distance * math.sin(math.radians(detected_degree))
        block_position_y = distance * math.cos(math.radians(detected_degree)) - 17

        if signature == 1:  # Red object
            avoidance_degree = max(math.degrees(math.atan2(block_position_x + 9, block_position_y)), 5)
            Blocks_TURN = 'R'
        else:  # Green object
            avoidance_degree = min(math.degrees(math.atan2(block_position_x - 9, block_position_y)), -5)
            Blocks_TURN = 'L'

        uart.write("%f\n" % avoidance_degree)  # Send avoidance degree to Arduino

    return avoidance_degree

while True:

    img = sensor.snapshot()
    img.draw_rectangle(red_blobs.rect(), color=(255, 0, 0))
    img.draw_cross(red_blobs.cx(), red_blobs.cy(), color=(255, 0, 0))
    avoidance_degree = calculate_avoidance()
    print("Avoidance Degree: ", avoidance_degree)
    print("Turn Direction: ", Blocks_TURN)
