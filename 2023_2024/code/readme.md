# Embedded code for Buggy 1 & 2
## Target board : NXP FRDM-KL25Z
This folder store the code for the Buggy 1 & 2, which using the FRDM-KL25Z board.

**This readme explain how to work with this project using MCUXpresso.**


> Please refer to this guide for more detail on how to start with MCUXpresso : [Guide for MCUXpresso](guide_mcuxpresso.md)

> It is highly recommended to using Git when you work. Check out this guide for all the useful Git commands : [Guide for Git](guide_git.md)

## Importants notes
1. The peripheral configuration tool of MCUXpresso **doesn't support** the FRDM-25Z. 

**Hence we have chosen to configure "by hand" the Pins, Clocks and Peripherals.** (Althrought the Pins and clock configuration tool is supported)

> All the configuration for a component such as a DC motor including Pins, clock and board peripheral can be found within the driver for that component.

See [this part](#configure-pins-clock-and-peripheral) for more details.

2. Drivers for all the component with their test code can be found in the folder `frdmkl25z_nxp_cup/buggy_peripherals`

## Workflow
1. Open MCUXpresso and chose this folder `insa-nxpcup/2023-2024/code` as workspace then `Launch`

2. Reopen the project by create a new project in MCUXpresso  ***with the same name `frdmkl25z_nxp_cup`***. [This guide](guide_mcuxpresso.md/#create-a-project) can help you.

> Every time you start working on a new component, create new Git branch for it. 


## Build and Flash code

## Configure Pins, Clock and Peripheral
