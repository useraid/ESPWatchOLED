# ESPWatchOLED
ESP12F based NTP-sync Watch

### Contents
- [Schematics](#schematics)
- [Hardware](#hardware)
- [Software](#software)
- [Download Gerber Files for PCB](https://github.com/useraid/ESPWatchOLED/releases/)

## Schematics
**Circuit Schematic Diagram**

![ESPWatchOLEDV2_SCH](https://github.com/useraid/ESPWatchOLED/assets/93074700/f5cb6720-096a-40e9-9652-c50f3e128761)
<!--
**Routed PCB Layers**

![PCB_PCB_ESPWatchOLED](https://github.com/useraid/ESPWatchOLED/assets/93074700/7d066b5f-e17a-463b-bb14-ff1017b00c68)
![PCB_PCB_ESPWatchOLEDIMG](https://github.com/useraid/ESPWatchOLED/assets/93074700/8b2d7882-b4bd-42da-ad8b-c3db881437d3)
 ![ESPWatchOLED Back](https://github.com/useraid/ESPWatchOLED/assets/93074700/ff764ece-8e84-445a-837d-7a4d2b41800e)
![ESPWatchOLEDFront](https://github.com/useraid/ESPWatchOLED/assets/93074700/0dc9b770-f2c9-4a92-b51a-fc377053ee2c) 
**3D Render**

<img src="https://github.com/useraid/ESPWatchOLED/assets/93074700/0dc9b770-f2c9-4a92-b51a-fc377053ee2c" width="200" height="200">
<img src="https://github.com/useraid/ESPWatchOLED/assets/93074700/ff764ece-8e84-445a-837d-7a4d2b41800e" width="200" height="200">
-->
## Hardware

Watch can be made on a prototype board or using the PCB Gerber Files(You will need to source SMD Components for that though)

### Components Required
- ESP12F - Microprocessor for WiFi and Smart Features
- SPX3819 3.3V - Voltage Regulator
- CH340C IC - USB to Serial IC
- Tactile Buttons - 4
- SPDT Slide Switch - Power Off
- Connection Wires - Enamel Coated or Jumpers
- 0.96" SSD1306 OLED Display - Watch Screen
- TP4056 IC - Battery Charging
- Type C Female Port - USB to Serial and Battery Charging Input
- Lipo Battery

## Software
***Due to the complex nature of the software, it'll be spinned off into a new project [UOS](https://github.com/useraid/UOS)***

The Code is written in Arduino IDE(WIP). The ESP8266 libraries need to be added using the board manager

### Prerequisites 
- Arduino IDE
- Drivers for whatever ISP Programmers you are using. (I'll be using a NODEMCU board to write the code to the ESP12F so CP2102 Drivers needed)

### Currently WIP 🚧

If you have any problems in the implementation or just ever need general help with this project, make an issue regarding the same.
