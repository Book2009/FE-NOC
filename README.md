# Nocturnalist-Future-Engineers
### ***WE ARE TEAM Nocturnalist***

<p align="center">
  <img src="https://ybrobot.club/image/YB%20Robot%20logo.png" width="300"/>
</p>
<p align="center">
 by Yothinburana School

# **About Us.**

### **This is our team.**



  We are **Nocturnalist**. We are a team from Bangkok, Thailand. **Nocturnalist** is from our behavior. The word "Nocturnalist" refers to a person who thrives or operates during the night. It consists of the word "Nocturnal", which means animals or people active during nighttime, with the suffix "-ist" indicating someone who practices or specializes in something. Like us, we love to work during nighttime.  Our team consists of three members: Pawit Nateenantasawasd, Pongpapat Putongkam, and Thanyawut Krittikanon. Programmer, Designer, and Supporter respectively. We have been good friends for 4 years, so we know how to work together very well. In our first attempt at this WRO category last year, we earned the opportunity to compete in the international round. But we are not careful enough, our rookie mistake gets us only in 8th place. This year, we’re returning to correct the mistakes we made last year, confident that we’ll perform even better.

<p align="center">
    <img src="https://github.com/user-attachments/assets/0cc32271-a7d0-4db4-8669-6ef6ca3a210b"/>
</p>

Programmer: Pawit Nateenantasawasd </p>
Mechanic: Pongpapat Putongkam </p>
Support: Thanyawut Krittikanon </p>

</p>

  Our team has 3 major positions. Firstly, Pawit Nateenantasawasd (the middle person). He is the programmer of our team. He is quite introverted so he can focus for a very long time. On the other hand, Pongpapat Putongkam (the left person). He has a very short attention span, so he could come up with new ideas easily. He is the designer and builder of our robot. Lastly, Thanyawut Krittikanon (the right person). He is at the best of both worlds. He can program and design, so he is a supporter of the team. Our team name is YBR-BOK. 'YBR' stands for 'Yothinburana Robot Club', and 'BOK' comes from our nickname 'Book, O'ly, Kaopun'.

# Content
`3DModels` This folder includes the 3D design of the vehicle and the rendered model of the vehicle.

`FlowChart` This folder includes diagrams showing the logic and sequence of the robot's control program, highlighting how it processes inputs and controls movements during missions.

`Program` This folder includes all programming used to participate in the WRO 2024 Future Engineers Category and all the programming flowcharts.

`Robot-Photos` This folder contains photos of the vehicle from all perspectives, including side and bottom views.

`Schemes` This folder contains one or more schematic diagrams in JPEG, PNG, or PDF format that depict the electromechanical components of the vehicle. These diagrams illustrate all the elements, including electronic components and motors, and show how they are interconnected.

`Team-Photos` This folder includes photos of the team participating in the WRO 2024 Future Engineers Category.

`Videos` This folder contains YouTube links that show how the robot operates to complete both missions.

# **Part 1: MECHANICAL DEESIGN**

Last year, our design was based entirely on Lego. This year we decided to up our game and 3d print the whole thing with ABS and PLA plastic filament reinforced with metal parts and some Lego. Using 3d printed parts allows more flexibility to be implemented and makes it easy to acquire spare parts for an emergency.
Even with all of that, we will still use Lego parts to connect in a very precise area.


## Robot's Chassis

The chassis of our robot, primarily constructed from 3D-printed components, forms a robust foundation for all hardware and electronics. Each part is custom-designed to meet our specific requirements and interlocks seamlessly to create a lightweight yet resilient structure. The modular design of the 3D-printed chassis allows for straightforward customization and scalability. It is engineered to accommodate motors, electronics, and the battery, ensuring proper heat dissipation and balanced weight distribution for optimal performance. This approach not only enables rapid prototyping and iterative design but also simplifies part replacement and upgrades as the robot evolves. [All the 3D printable models can be found here](https://github.com/Book2009/Nocturnalist-Future-Engineers/tree/main/3D_Models).



## **Parts of our ROBOT**

<br>

   ### Movement Parts
   
- ## **Driving motor** : Power functions Large-motor made by LEGO™.
<image src="https://github.com/Snackels/FutureEngineer2024_YBR_AGO/blob/main/Robot/Parts/Motor.png" width = "400">
It's a simple motor, and we chose this motor because of its easy connection to our robot and its cost-effectiveness. This motor is small yet powerful. and it is the perfect size for our robot. The motor comes with a dedicated port for Lego. So, we modified it to make it able to connect to the board. 

### Electrical Specifications

| Specification     | Value    |
|-------------------|----------|
| Voltage           | 9 V      |

### Mechanical Specifications

| Specification     | Value    |
|-------------------|----------|
| Speed             | 390 rpm  |
| Maximum torque    | 40 Ncm   |

<br><br>

- ## **Servo** : GEEKSERVO 2kg 360 Degrees servo.
<image src="https://github.com/Snackels/FutureEngineer2024_YBR_AGO/blob/main/Robot/Parts/Servo%201.png" width = "400">
We use this servo for steering the robot and employ an ultrasonic sensor for rotation. This servo is compatible with LEGO, making it easy and convenient to build the robot by just putting studs in the hole on the side. We like how you can connect two axles to the dual outputs on this servo so you can power two wheels or gears, or mount the servo securely inside articulated limbs and other contraptions. Additionally, the gears inside these servos will 'slip' when the blocking load is too high instead of jamming, helping avoid damage to your servos and boards.

The wires are a standard servo pinout - 
-	Red - positive
-	Brown - negative
-	Yellow - data


### Electrical Specifications

| Specification     | Value    |
|-------------------|----------|
| Working voltage   | 3.3V~6V  |
| Rated voltage     | 4.8V     |
| Rated current     | 200mA    |
| Stall current     | 700mA    |
| Sliding current   | 450mA    |

- ## **Differential** : Technic, gear differential with inner tabs and closed center, 28 bevel teeth
<image src = "https://github.com/Snackels/FutureEngineer2024_YBR_AGO/blob/main/Robot/Parts/Gear_3%20(1).png" width = "400">
This part ensure that both wheels have the power from the motor, which makes the robot drive forward. This part has gear teeth on the side, which are connected to the gear we put on the motor earlier, and then we put 3 small gears inside the differential. The differential is attached to the main body using an axle from the wheel.

<br><br>

- ## **Wheel** : Lego 49.5 × 20 tire and 30 × 20 rim
<image src = "https://github.com/Snackels/FutureEngineer2024_YBR_AGO/blob/main/Robot/Parts/Wheel%20(1).png" width = "400">
There are a lot of wheels to select. We chose this one because of it's size. If the wheels are too small, it reduces the speed due to the lack of rotation. But if the wheels are too big, it makes the robot slower and harder to control. With the combination of the motor and the wheels, the robot can maintain the speed we can control.

<br><br>

 ### Controller
- ## **Microcontroller Board** : Arduino Mega 2560 R3
<img src = "https://github.com/Snackels/FutureEngineer2024_YBR_AGO/blob/main/Robot/Parts/Mega.png" width = "400">
This part is like a brain of our body. It's job is to store all the program of our robot from the computer, every components in the robot comes through here. We chose this board because of it's connection port, it contains tons of ports that we want such as 3 UART port. We used Arduino Uno last year, but the problem is there's not enough port for OpenMV and GY-25. But there's some disadvantage in this board. Because this board has a lot of connection port, it comes with weight and size. It's almost 2 times longer than the UNO. And that makes the robot long and heavy.

| Specification           | Value                                  |
|-------------------------|----------------------------------------|
| Microcontroller         | ATmega2560                             |
| Operating Voltage       | 5V                                     |
| Input Voltage (recommended) | 7-12V                               |
| Input Voltage (limit)   | 6-20V                                  |
| Digital I/O Pins        | 54 (15 provide PWM output)             |
| Analog Input Pins       | 16                                     |
| DC Current per I/O Pin  | 20 mA                                   |
| DC Current for 3.3V Pin | 50 mA                                   |
| Flash Memory            | 256 KB (8 KB used by bootloader)       |
| SRAM                    | 8 KB                                    |
| EEPROM                  | 4 KB                                    |
| Clock Speed             | 16 MHz                                  |
| LED_BUILTIN             | 13                                      |
| Length                  | 101.52 mm                               |
| Width                   | 53.3 mm                                 |
| Weight                  | 37 g                                    |

Additional information about UART:
UART operates by transmitting data as a series of bits, including a start bit, data bits, an optional parity bit, and stop bit(s). Unlike parallel communication, where multiple bits are transmitted simultaneously, UART sends data serially, one bit at a time. As the name reveals the protocol operates asynchronous which means that it doesn't rely on a shared clock signal. Instead, it uses predefined baud rates to determine the timing of data bits.

<img src = "https://github.com/Snackels/AGO/blob/main/Diagram_and_Electric_Circuit/UART.png" width = "400">

Our robot has serial1 and serial3, serial1 is connected to compass while serial3 is connected to OpenMV camera. They are connected to the UART port on the Arduino mega.

<br><br>

- ## **Sensor Shield** : Gravity IO Sensor Shield For Arduino Mega Due
<img src = "https://github.com/Snackels/FutureEngineer2024_YBR_AGO/blob/main/Robot/Parts/Sensor%20shield.png" width = "400">
This part is an extension of the board. It is where ultrasonic, light sensors, button sensors, camera, compass, and servos go. It has alot of connection pin which can be used for each components. But with that it also come with a very long design. Make it hard to design where to place it on robot.

| Specification                               | Value                                         |
|---------------------------------------------|-----------------------------------------------|
| Compatibility                               | Most Arduino shields                         |
| Compatible Boards                           | Arduino Mega boards, DFRobot megaADK, Arduino megaADK |
| Extended TTL Connection Pins                | Four Serial ports                            |
| Prototyping Area                            | DIP prototyping area for additional modules or components |
| Xbee Slots                                  | 3                                             |
| microSD Slot                                | 1                                             |
| Power Switch                                | Between Arduino Mega or external power       |
| Size                                        | 125 x 57 mm (4.92 x 2.24")                   |

<br><br>

- ## **Motor Shield** : Gravity 2x2A Motor Shield for Arduino Twin
<img src = "https://github.com/Snackels/FutureEngineer2024_YBR_AGO/blob/main/Robot/Parts/Motorshield.png" width = "400">
This part is also an extension of the board. It makes the connection between the board and motor easier. We connect the pin with the top of sensor shield.

| Specification            | Value                                  |
|--------------------------|----------------------------------------|
| Motor Driven Voltage    | 4.8V to 35V                            |
| Output Current          | Up to 2A/channel                       |
| Total Power Dissipation | 25W (T=75℃)                            |
| Driven Structure        | Dual full-bridge driver                |
| Driven Power Port       | External power terminal, or VIN from Arduino |
| Driven Output Port      | 2 channel screw terminals, or male PIN headers |
| Control Port            | 4 TTL compatible digital signals (Digital 10-13) |
| Operation Temperature   | -25℃ to 130℃                           |
| Shield Size             | 56x57mm (2.20x2.24")                   |

<br><br>

### Power Management And Inspection
- ## **Camera** : OpenMV H7 R1
<image src="https://github.com/Snackels/AGO/blob/main/Robot/Parts/OpenMV%20cam.png" width = "400">
This component is very important for avoiding obstacle. It can detect red and green obstacle from distance to avoid crashing into it. The OpenMV also comes with it's own microcontroller. Making the robot locate and think faster when see the obstacle. The OpenMV also comes with GLCD screen at the back of it to display what the camera see. This camera can be coded with MicroPython. Additionally, this camera wires are connected with the sensor shield.

#### STM32H743VI Specifications

| Specification             | Value                                           |
|---------------------------|-------------------------------------------------|
| **Processor**             | STM32H743VI ARM Cortex M7                       |
| **Clock Speed**           | 480 MHz                                         |
| **SRAM**                  | 1 MB                                             |
| **Flash Memory**          | 2 MB                                             |
| **I/O Voltage**           | 3.3V (5V tolerant)                              |
| **Number of I/O Pins**    | 10                                              |

#### Interfaces

| Specification             | Value                                           |
|---------------------------|-------------------------------------------------|
| **USB**                   | Full-speed USB (12 Mbps) interface             |
| **μSD Card Socket**       | Capable of 100 Mbps read/write                  |
| **SPI Bus**               | Up to 80 Mbps                                  |
| **I2C Bus**               | Up to 1 Mbps                                   |
| **CAN Bus**               | Up to 1 Mbps                                   |
| **Asynchronous Serial Bus** | Up to 7.5 Mbps                                |

#### Analog

| Specification             | Value                                           |
|---------------------------|-------------------------------------------------|
| **ADC**                   | 12-bit                                          |
| **DAC**                   | 12-bit                                          |

#### Control

| Specification             | Value                                           |
|---------------------------|-------------------------------------------------|
| **Servo Control Pins**    | 3 I/O pins                                      |
| **Interrupts and PWM**    | Available on all I/O pins                      |

#### LEDs

| Specification             | Value                                           |
|---------------------------|-------------------------------------------------|
| **RGB LED**               | Yes                                             |
| **High Power IR LEDs**    | Two 850nm                                      |

#### Camera Module

| Specification             | Value                                           |
|---------------------------|-------------------------------------------------|
| **Default Sensor**        | OV7725                                          |
| **Resolution**            | 640x480                                         |
| **Modes**                 | 8-bit Grayscale at 75 FPS, 16-bit RGB565 (75 FPS above 320x240, 150 FPS below 320x240) |
| **Lens**                  | 2.8mm, M12 mount                                |
| **Additional Modules**    | Global Shutter Camera, FLIR Lepton Adapter     |

#### Power

| Specification             | Value                                           |
|---------------------------|-------------------------------------------------|
| **Battery Connector**     | Compatible with 3.7V LiPo batteries             |


  <br><br>

- ## **Ultrasonic sensor** : Gravity URM 09 ultrasonic distance sensor.
<image src="https://github.com/Snackels/AGO/blob/main/Robot/Parts/Ultrasonic.png" width = "400">
The ultrasonic sensor plays a vital role in guiding the robot's navigation by accurately detecting distances between the robot and potential obstacles. Its precision in measuring distances ensures that the robot can maneuver and make informed decisions to navigate its path safely and effectively, avoiding collisions and maintaining its course.

### Electrical Specifications

| Specification                   | Value                  |
|---------------------------------|------------------------|
| Supply Voltage                  | 3.3~5.5V DC            |
| Operating Current               | 20mA                   |

### Performance Specifications

| Specification                   | Value                  |
|---------------------------------|------------------------|
| Operating Temperature Range      | -10°C to +70°C          |
| Measurement Range                | 2cm to 500cm (can be set) |
| Resolution                       | 1cm                    |
| Accuracy                         | 1%                     |
| Frequency                        | 50Hz Max               |

<br><br>

- ## **7.4 voltage Lipo-Battery** : 7.4 voltage 2 cell Lipo-Battery.
<image src="https://github.com/Snackels/AGO/blob/main/Robot/Parts/Battery.png" width = "400">
The battery provides the power for our robot. This battery is very lightweight and compact to fit into the robot since the robot is very small. And it is also able to connect to our controller board. We calculated the amount of mAh that is enough to power our robot for 1-2 hours before recharged.

### Specification

| Specification                   | Value                                        |
|---------------------------------|----------------------------------------------|
| 2 cells Voltage                  | 7.4V                                         |
| Capacity                         | 1100mAh 30C                                  |
| Charging Current                 | Up to 5 times the capacity (5C)             |
| Connectors                       | JST type, easily disconnectable              |

<br><br>

- ## **Light Sensor** : Virus III by Design By Sopon and ZX-03 By INEX
<image src = "https://github.com/Snackels/AGO/blob/main/Robot/Parts/Red%20sensor.png" width = "300">
Virus III
<image src = "https://github.com/Snackels/FutureEngineer2024_YBR_AGO/blob/main/Robot/Parts/Blue%20sensor.png" width = "300">
ZX-03

<br><br>

The color sensors play an important role in both rounds, as we use them for line detection. There are 2 lines with different colors in the corner of the race field, which is why we use 2 different colors of the color sensor, blue and red. The blue color sensor is used for detecting both colors, while the red color sensor is only used for the blue line.

<br><br>

- ## **GyroCompass** :GY-25
A gyro is a component that enables a robot to determine its orientation and turn in the appropriate direction. We chose this gyro sensor specifically because of how effective it is. It also comes in a very small
size to attach to our robot.

<image src = "https://github.com/Snackels/AGO/blob/main/Robot/Parts/GyroCompass.png" width = "400">

### Specification

#### Power and Communication

| Specification             | Value                                           |
|---------------------------|-------------------------------------------------|
| Power supply              | 3-5V (internal low dropout regulator)          |
| Used Chip                 | MCU+MPU6050                                     |
| Communication mode        | Serial communication (baud 9600, 115200), IIC communication |
| Operating Current         | 15 mA                                          |

#### Angular Measurement

| Specification             | Value                                           |
|---------------------------|-------------------------------------------------|
| Angular Resolution        | 0.01°                                           |
| Direct Data               | YAW ROLL PITCH                                 |
| Measuring range of axes   | -180 to +180 degrees                           |
| Resolution                | 0.01 degrees                                  |
| Frequency Response        | 100Hz (115200bps)                              |
| Operating Temperature     | -20 to 85°C                                    |

<br><br>

- ## **Touch Sensor** : ZX-Switch01 by INEX
This button gives us an easier way to start the robot. Since the controller board doesn't come with switches. So we found this button that could be attached to the frame outside the board using bolt. 

<img src = "https://github.com/Snackels/FutureEngineer2024_YBR_AGO/blob/main/Robot/Parts/ZX%20switch.png" width = "400">

<br><br>

- ## **On/Off Switch** : SPST ON/OFF Switch 2 Pin Rocker Switch DC 125/250V
This switch is for cutting the power from the battery to the robot. The regulation states that before starting the robot, the power must be cut off. That's when this switch came in. To use this switch we solder red wire(Positive pole) to the switch on 1 side for input. Then another solder red wire for output on the opposite side. You can put the black wire(Negative pole) straight into the step down. When the switch is turned on, the power from the battery will direct into the stepdown and then the robot. 

<img src = "https://github.com/Snackels/FutureEngineer2024_YBR_AGO/blob/main/Robot/Parts/On-off%20Switch.png" width = "400">

<br><br>

- ## **Step-down** : HW-360 V6.0
This is a step-down DC-DC module. It comes with a status indicator light, a display screen that shows the voltage meter, and self-calibration of the voltage meter. The electrical voltage has an error of 0.05 V, with a measuring range of 0–40 V. We need this step down to show us how long until we need to recharge the battery.

<img src = "https://github.com/Snackels/FutureEngineer2024_YBR_AGO/blob/main/Robot/Parts/Stepdown%20(1).png" width = "400">

<br><br>

### Specification

#### Input

| Specification           | Value                                  |
|-------------------------|----------------------------------------|
| Input voltage           | DC 4.0 ~ 38V                           |

#### Output

| Specification           | Value                                  |
|-------------------------|----------------------------------------|
| Output voltage          | DC 1.25V ~ 36V continuously adjustable |
| Output current          | Max 5A                                 |
| Output power            | Up to 75W                              |

#### Measurements

| Specification           | Value                                  |
|-------------------------|----------------------------------------|
| Voltmeter error         | ± 0.05V                               |
| Measure range           | 0 ~ 40V                               |

#### Performance

| Specification           | Value                                  |
|-------------------------|----------------------------------------|
| Conversion efficiency   | Up to 96%                              |
| Load regulation         | S (I) ≤ 0.8%                           |
| Voltage Regulation      | S (u) ≤ 0.8%                           |

<br><br>


# **Electric Circuit And Flowchart**


<img src = "https://github.com/Snackels/AGO/blob/main/Diagram_and_Electric_Circuit/Circuit%20Diagram.png?raw=true" width = "1000">

This is the electric diagram of our robot, showing where the wires go from the components to the board.

<br><br>

<img src = "https://github.com/Snackels/AGO/blob/main/Diagram_and_Electric_Circuit/OpenFlowchart.jpg" width = "1000">

Our robot open challenge flowchart. In this round, our robot must complete 3 laps around the track within 3 minutes.

<br><br>

<img src = "https://github.com/Snackels/AGO/blob/main/Diagram_and_Electric_Circuit/ObstacleFlowchart.jpg" width = "1000">

This flowchart shows how our robot works in obstacle challenge. 



