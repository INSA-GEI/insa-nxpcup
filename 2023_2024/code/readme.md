# Embedded code for Buggy 1 & 2
## Target board: NXP FRDM-KL25Z

This folder stores the code for Buggy 1 & 2, which uses the FRDM-KL25Z board.

### This document explains how to work with this project using MCUXpresso.
#### Authors: Triet NGUYEN (Github: trietngh)
Feel free to contribute to this document and other guides included in this repo.

> Please refer to this guide for more detail on MCUXpresso : [Guide for MCUXpresso](guide_mcuxpresso.md)

> It is highly recommended to using Git when you work. Check out this guide for all the useful Git commands : [Guide for Git](guide_git.md)

## Important notes
1. **Please read the [WORKFLOW](#workflow) below before starting.**

2. Every sub-repository in this repo is ignored by Git except for the `buggy` repo to ignores all MCU projects.

3. Drivers for all the components with their test code can be found in the folder `buggy/peripherals`.

4. Your code should be well **documented**.

5. The peripheral configuration tool of MCUXpresso **doesn't support** the FRDM-25Z. 

**Hence we have chosen to configure "by hand" the Pins, Clocks, and Peripherals.** (Although the Pins and clock configuration tool is supported)

> All the configuration for a component such as a DC motor including Pins, clock and board peripheral can be found within the driver for that component.

See [this part](#configure-pins-clock-and-peripheral) for more details.



## Workflow
First, **pull from git** to update the project:

`git pull origin`

Then, you need an MCUXpresso project.
1. Extract the project template zip file named `frdmkl25z_nxp_cup.zip` included in this repo.

2. Make sure you already installed the SDK for the FRDM-KL25Z. If not, check [here](guide_mcuxpresso.md/#install-sdk-for-a-board) for how to do it

3. Follow these [steps](guide_mcuxpresso.md/#reopen-an-existing-project-in-your-workspace) to open the project in MCUXpresso.

4. If you have done it correctly, the project is ready to build. In the top bar, click on the `Build` icon (a hammer icon) and make sure it doesn't have any errors.

The template already includes all the source code of the buggy and the FSL drivers necessary for the buggy.

**YOU CAN START WORKING NOW.**

**Attention!!! USE the FSL library**  
> Direct access to the board's registers is NOT needed, there is a function for that.

From now on, depending on what you want to do, please refer to the corresponding section. 

- [Create a new component](#create-source-code-for-a-new-component) for the buggy (let's say you want to add an ultrasonic sensor to the buggy)

- [Test or use existing components](#testuse-an-existing-components-source-code) (the DC motor driver for example)

- [Configure Pins, Clocks, and Peripherals](#configure-pins-clock-and-peripheral) for the board

- [Add an FSL driver to your project](#fsl-library) if it's missing

- [Build and flash code](#build-and-flash-code)  to your board

## FSL library
> This library provide all functions needed to work with the FRDM board.

**Direct access to the board's registers is NOT needed, there is a function for that.**

When you want to work with a peripheral of the FRDM board (ex. TPM - Timer / PWM Module), you will need the `fsl_tpm.h` source code in your project.

Often, these source codes can be found in the `Drivers` directory.

If that's not the case, you can add it to your project by following this [guide](guide_mcuxpresso.md/#add-other-sdk-components-to-project).

## Create source code for a new component
1. In Project Explorer (on the left side), right-click and choose `New` and `Folder`

2. Select the `frdmkl25z_nxp_cup/buggy` as the parent folder

3. Enter your component name as folder name (for example dc_motor)

4. Repeat those steps to create a header `.h`, source `.c` file for your component.

5. Also, remember to write a test `.h` and `.c` for your component.

6. Make sure the FSL driver needed for your component is presented in the project (for ex. dc_motor needs the `fsl_tpm.h` driver to use the PWM timer). If that is not the case, please refer to this [guide](guide_mcuxpresso.md/#add-other-sdk-components-to-your-project).

7. You should configure all the peripherals needed for your component in your component's code. When someone uses your driver, it should take care of all the board configuration necessary. See this [part](#configure-pins-clock-and-peripheral) on how to do it.

8. That's all, you can start adding more functions to your component' code.

**May the force be with you.**

## Test/Use an existing component's source code
1. A component's code should include a header, source, and test file. You can find it in the `buggy` folder.

2. To test an existing component, go to your main source.

3. Include the test code of the component with this syntax: 

`#include your_component/test_your_component.h`

4. All the board's configuration should already be done in the component's source code. You have nothing to configure (check the source code for all the configuration that has been done).

5. Call the test function in your main function and you're good to go.

**Good luck!**

## Configure Pins, Clock, and Peripheral
This is the hard part. The FRMD KL25Z isn't supported for auto-configuration of its peripherals (it is too old). So you have to do it on your once. 

But there is a trick. In this repo, another project zip named `example_config.zip` is included. This is a project of the FRDM-K32L3A6 board, a newer one used in the Buggy 3. This board supports all the auto-config tools that make life so much easier.

The trick is to use the tool to configure the K32L3A6 board, then copy it to your old K25Z board (it's long and frustrating but at least it works).

> **Important note**: the configuration isn't 100% identical. It give you an example on how to configure the perpheral. Refer to the KL25Z manual reference to make sure that you done the configuration correctly.

1. First, you need to extract the `example_config.zip` and open it in your workspace. [Here is the guide](guide_mcuxpresso.md/#reopen-an-existing-project-in-your-workspace) for that.

Now let's see how to configure a peripheral using the Peripheral auto-config tool.

On the top bar, click on the `ConfigTool`. There are 3 things that you need to configure:

### Pin

1. Select Pins in ConfigTool and on the top left, make sure the project `example_config` is chosen (not the kl25z project)

2. In the center window, select the `Expansion Header` tab

3. Select the Pin you want to configure and assign a function for it.

4. On the bottom window (`Routing Detail` window), you can specify the function of that Pin.

5. Make sure to configure the GPIO clock !!! 

6. Click on `Update code` (you can do it when you finish all the configuration)

### Clock
1. Select Clocks in ConfigTool and on the top left, make sure the project `example_config` is chosen (not the kl25z project)

2. Select the clock you want to active, double-click on it

3. On the right side, in the first field (ex. ClockName_SEL), choose the clock for your peripheral

4. In the second field, configure a frequency for the clock

5. Click on `Update code` (you can do it when you finish all the configuration)

### Peripheral
1. Select Peripherals in ConfigTool and on the top left, make sure the project `example_config` is chosen (not the kl25z project)

2. Click on  the `+` sign in the Peripheral Drivers section

3. Add the peripheral you want (the warning sign on the left means that you need to add an FSL driver for that peripheral to your project)

4. Configure your peripheral and REMEMBER to configure the clock for it!!!

5. Click on `Update code` (you can do it when you finish all the configuration)

### How to transfer the configuration to the KL25Z board
A configuration of a peripheral always contains a configuration structure (stores all the configurations) and a configuration structure (writes those configurations to the board's registers).

These 2 elements will show you which structure and function you need to use to configure the KL25Z board. 

**Use them wisely!** 


## Build and Flash code
### Build
It's easy. Find the `hammer` icon in the top bar and click on it.

### Flash
It's not that easy. 

Normally, you can flash by clicking on the `GUI Flash Tool` (micro-processor icon) in the middle of the top bar then a few `Ok/Next`.

If the `GUI Flash Tool` doesn't illuminate, you can try :

- Clean the project (broom icon in QuickStart Panel)
- Rebuild it
- Click on Run (green arrow), an error should appear, close it
- Check if you can click on the `GUI Flash Tool` 
- If not, repeat these steps. LOL (I will find another method later)

