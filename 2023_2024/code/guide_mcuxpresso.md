# GUIDE for MCUXpresso IDE
This document contain step by step guide to using MCUXpresso.

## Create a project
1. Open MCUXpresso IDE

2. Select this repository as workspace `insa-nxpcup\2023_2024\code` then hit `Launch`

3. Make sure you already installed the SDK for the FRDM-KL25Z. If not, check [here](#install-sdk-for-a-board) for how to do it

4. Select `Create a New Project` then `Go straight to the Wizard`

5. Chose FRDM-KL25Z board then click `Next`

6. In the **Configure the project** window, enter the project name

7. In the Components section, chose all the components you will 
need for the project. You can add them after by doing these
[steps](#add-other-sdk-components-to-project)

8. All other settings should be left as defaut unless you know what you are doing

9. Click `Finish` to generate project.

## Install SDK for a board
From the homepage of MCUXpresso (go to Home page by click on the House icon) :
1. Click on `Download and Install SDKs`
2. In Filter box on the right side, search the board you need (ex. FRDM-KL25Z)
3. Chose the right board then click `Install` then `Finish`

## Add PATH to project
1. Next, select `Project` window from the top then select `Properties` then `C/C++ General` then `Paths and Symbols`

2. In the includes window, add the PATH you desire

3. Select `Apply and Close` then `Rebuild Index`

## Add other SDK components to project