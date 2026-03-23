# NXP Application Code Hub

[<img src="https://mcuxpresso.nxp.com/static/icon/nxp-logo-color.svg" width="100"/>](https://www.nxp.com)

## Using SmartDMA to implement camera interface in MCXN236

Using SmartDMA to implement camera interface in MCXN236.
This demo introduces a parallel interface for the camera solution for MCXN236.

The camera interface can be used as important part of camera usage as below:

• Object detection

• Gesture recognition

• Color recognition

• QR code scanning, and so on.

Supported formats (8-bit): RGB565

• Maximum image transfer rate: 30 fps for QVGA(320 × 240). For small RAM parts, reduce the size of image and frame
rate.

• Camera module tested: OV7670

• Other camera modules can be supported as long as they provide the same signal timing.

#### Boards: FRDM-MCXN236

#### Categories: HMI, Graphics

#### Peripherals: GPIO, VIDEO

#### Toolchains: MCUXpresso IDE

## Table of Contents

1. [Software](#step1)
2. [Hardware](#step2)
3. [Setup](#step3)
4. [Results](#step4)
5. [Support](#step5)
7. [Release Notes](#step6)

## 1. Software<a name="step1"></a>

- [MCUXpresso IDE V11.9.0 or later](https://www.nxp.com/design/design-center/software/development-software/mcuxpresso-software-and-tools-/mcuxpresso-integrated-development-environment-ide:MCUXpresso-IDE).
- SDK_2_14_0_FRDM-MCXN236
- MCUXpresso for Visual Studio Code: This example supports MCUXpresso for Visual Studio Code, for more information about how to use Visual Studio Code please refer [here](https://www.nxp.com/design/training/getting-started-with-mcuxpresso-for-visual-studio-code:TIP-GETTING-STARTED-WITH-MCUXPRESSO-FOR-VS-CODE).

## 2. Hardware<a name="step2"></a>

- USB Type-C cable
- FRDM-MCXN236
- Personal Computer
- OV7670 camera module
- LCD-PAR-S035

## 3. Setup<a name="step3"></a>

### 3.1 Step 1

Connect the LCD-PAR-S035 with FRDM-MCXN236, connect OV7670 camera module with FRDM-MCXN236, as shown below:

![hardware](./images/hardware.jpg)

### 3.2 Step 2

- Import the project to MCUXpresso IDE.

1. Open MCUXpresso IDE, in the Quick Start Panel, choose **Import from Application Code Hub**.

   ​	![](./images/import_project_1.png)

2. Enter the demo name in the search bar.

   ![](./images/import_project_2.png) 

3. Click **Copy GitHub link**, MCUXpresso IDE will automatically retrieve project attributes, then click **Next>**.

   ​	![](./images/import_project_3.png)

4. Select **main** branch and then click **Next>**, Select the MCUXpresso project, click **Finish** button to complete import.

   ​	![](./images/import_project_4.png)

- Connect the micro USB cable between the PC host and the USB port (J10) on the board.
- Compile and download to the board.
- Reset and run.

## 4. Results<a name="step4"></a>

The demo result as below:

​	![](./images/result.jpg)

## 5. Support<a name="step5"></a>

#### Project Metadata

<!----- Boards ----->
[![Board badge](https://img.shields.io/badge/Board-FRDM&ndash;MCXN236-blue)](https://github.com/search?q=org%3Anxp-appcodehub+FRDM-MCXN236+in%3Areadme&type=Repositories)

<!----- Categories ----->
[![Category badge](https://img.shields.io/badge/Category-HMI-yellowgreen)](https://github.com/search?q=org%3Anxp-appcodehub+hmi+in%3Areadme&type=Repositories) [![Category badge](https://img.shields.io/badge/Category-GRAPHICS-yellowgreen)](https://github.com/search?q=org%3Anxp-appcodehub+graphics+in%3Areadme&type=Repositories)

<!----- Peripherals ----->
[![Peripheral badge](https://img.shields.io/badge/Peripheral-GPIO-yellow)](https://github.com/search?q=org%3Anxp-appcodehub+gpio+in%3Areadme&type=Repositories) [![Peripheral badge](https://img.shields.io/badge/Peripheral-VIDEO-yellow)](https://github.com/search?q=org%3Anxp-appcodehub+video+in%3Areadme&type=Repositories)

<!----- Toolchains ----->
[![Toolchain badge](https://img.shields.io/badge/Toolchain-MCUXPRESSO%20IDE-orange)](https://github.com/search?q=org%3Anxp-appcodehub+mcux+in%3Areadme&type=Repositories)

Questions regarding the content/correctness of this example can be entered as Issues within this GitHub repository.

> **Warning**: For more general technical questions regarding NXP Microcontrollers and the difference in expected funcionality, enter your questions on the [NXP Community Forum](https://community.nxp.com/)

[![Follow us on Youtube](https://img.shields.io/badge/Youtube-Follow%20us%20on%20Youtube-red.svg)](https://www.youtube.com/@NXP_Semiconductors)
[![Follow us on LinkedIn](https://img.shields.io/badge/LinkedIn-Follow%20us%20on%20LinkedIn-blue.svg)](https://www.linkedin.com/company/nxp-semiconductors)
[![Follow us on Facebook](https://img.shields.io/badge/Facebook-Follow%20us%20on%20Facebook-blue.svg)](https://www.facebook.com/nxpsemi/)
[![Follow us on Twitter](https://img.shields.io/badge/Twitter-Follow%20us%20on%20Twitter-white.svg)](https://twitter.com/NXP)

## 6. Release Notes<a name="step6"></a>

| Version | Description / Update                    |                          Date |
| :-----: | --------------------------------------- | ----------------------------: |
|   1.0   | Initial release on Application Code Hub | February 26<sup>th</sup> 2024 |

