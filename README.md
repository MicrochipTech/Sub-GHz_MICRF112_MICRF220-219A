# MICRF112-433-EV AND MICRF220/219A-433-EV

<img src="docs/IoT-Made-Easy-Logo.png" width=100>


> "IOT Made Easy!" 

Devices: **| PIC16F1619 | PIC18F47K40 | MICRF112 | MICRF220 | MICRF219A|**<br>
Features: **|Sub-GHz|**


## ⚠ Disclaimer

<p><span style="color:red"><b>
THE SOFTWARE ARE PROVIDED "AS IS" AND GIVE A PATH FOR SELF-SUPPORT AND SELF-MAINTENANCE. This repository contains example code intended to help accelerate client product development. </br>

For additional Microchip repos, see: <a href="https://github.com/Microchip-MPLAB-Harmony" target="_blank">https://github.com/Microchip-MPLAB-Harmony</a>

Checkout the <a href="https://microchipsupport.force.com/s/" target="_blank">Technical support portal</a> to access our knowledge base, community forums or submit support ticket requests.
</span></p></b>





## Contents

1. [Introduction](#step1)
1. [Bill of materials](#step2)
1. [Hardware Setup](#step3)
1. [Software Setup](#step4)
1. [Harmony MCC Configuration](#step5)
1. [Board Programming](#step6)
1. [Run the demo](#step7)


## 1. Introduction<a name="step1">

This Application demonstrates the working of MICRF112-433-EV with PIC16F1619 and MICRF220/219A-433-EV with PIC18F47K40 using ASK Modulation.

![](docs/app.png)

## 2. Bill of materials<a name="step2">


| Hardware Required       | Description  | Quantity |
|:- |:- |:- |
| DM164137                | Curiosity Development Board.  | 1 |
| PIC16F1619              | Change MCU on DM164137 for MICRF112-433-EV.| 1 |
| MICRF112-433-EV         | ASK/FSK Transmitter (433Mhz).    | 1 |
| DM160228                | Explorer 8 Development Kit.       |   1 |
| PIC18F47K40             | Change MCU on DM160228 for MICRF220/219A-433-EV.   | 1 |
| MICRF219A-433-EV        | ASK/OOK Receiver (433Mhz).        | 1 |
| ICD3                    | In-Circuit Debugging for DM160228    | 1 |

## 3. Hardware Setup<a name="step3">

### MICRF112-433-EV with PIC16F1619(MCU) on Curiosity Development Board.


**Step 1** - Replace the default MCU of Curiosity Development Board with PIC16F1619.

**Step 2** - Connect the Jumper J12 to 3.3V/5V based on the MCU(here PIC16F1619 has Operating voltage range 2.3V to 5.5V).

**Step 3** - The MICRF112 Dev Board Connects to the Curiosity Board by straddling the Mikro Bus GND pins.

| MICRF112 | Curiosity     | Description |
|----------|---------------|-------------|
| J1-1     |    3.3V       |     VDD     |
| J1-2     | Mikro Bus GND |     GND     |
| J1-3     |  J33-8(RC2)   | PIC Data Out|
| J2-1     |  J34-8(RC5)   |   Enable    |
| J2-2     | Mikro Bus GND |     GND     |
| J2-3     |    N/C        |    N/C      |


![](docs/MICRF112.JPG)

### MICRF220/219A-433-EV with PIC18F47K40(MCU) on Explorer 8 Development Kit.


**Step 1** - Replace the default MCU of CExplorer 8 Development Kit with PIC18F47K40.

**Step 2** - Connect the MICRF220/219A-433-EV Board directly into J17(**face down**) as shown below. J3-8 of the MICRF220 connects to the Explorer 8 J17-1 and Make sure jumper 15 is tied to 3.3V.

| Note MICRF220 Pin1 does NOT connect to Pin 1 on J17! |
| --- |

**Step 3** - Power Explorer 8 from J1, the 9V power adapter, not from USB.

![](docs/explore1.png)

**Step 4** - Verify all the Jumper connection of the Explorer 8 Development Kit as shown below.

![](docs/explore2.png)

## 4. Software Setup<a name="step4">

- [MPLAB X IDE ](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide#tabs)

    - Version: 6.00
	- XC32 Compiler v4.10
	- MPLAB® Code Configurator v5.1.17
	- PIC32CX-BZ_DFP v1.0.107
	- MCC Harmony
	  - csp version: v3.13.1
	  - core version: v3.11.1
	  - CMSIS-FreeRTOS: v10.4.6
	  - wireless_pic32cxbz_wbz: v1.0.0
	  - wireless_ble: v1.0.0	  
	  - dev_packs: v3.13.1
	  - wolfssl version: v4.7.0
	  - crypto version: v3.7.6
	    



- [MPLAB X IPE v6.00](https://microchipdeveloper.com/ipe:installation)


**Step 4** - Connect the USB and Program the (MICRF112) application to the Device from MPLAB X IDE.

**Step 5** - Verify the MCC configuration as shown below.

![](docs/tx1.png)
![](docs/tx2.png)

![](docs/tx3.png)
![](docs/tx4.png)




**Step 5** - Connect the IDC 3 In-Circuit Debugger to program the device..

**Step 6** - Verify the MCC configuration as shown below.

![](docs/rx1.png)
![](docs/rx2.png)

![](docs/rx3.png)
![](docs/rx4.png)

![](docs/rx5.png)
![](docs/rx6.png)

![](docs/rx7.png)
![](docs/rx8.png)

![](docs/rx9.png)
![](docs/rx10.png)
