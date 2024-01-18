# GUIDE for MCUXpresso IDE
This document contains step by step guide for different problems of MCUXpresso.
#### Authors: Triet NGUYEN (Github: trietngh)
## Create a project
1. Open MCUXpresso IDE

2. Select this repository as workspace your workspace then hit `Launch`

3. Make sure you already installed the SDK for the FRDM-KL25Z. If not, check [here](#install-sdk-for-a-board) for how to do it

4. Select `Create a New Project` then `Go straight to the Wizard`

5. Chose FRDM-KL25Z board then click `Next`

6. In the **Configure the project** window, enter the project name

7. In the Components section, choose all the components you will 
need for the project. You can add them after by doing these
[steps](#add-other-sdk-components-to-project)

8. All other settings should be left as default unless you know what you are doing

9. Click `Finish` to generate a project.

## Reopen an existing project in your workspace
1. Open MCUXpresso and choose your workspace

2. From the Home page, click on IDE (it should be on the right side)

3. In the Project Explorer on the left, select `Import Projects...`

4. Select `General` then `Existing Projects into Workspace`

5. Select your project's folder as the root folder

6. In the project window, make sure the checkbox of your project is checked

7. Click `Finish`

## Install SDK for a board
From the homepage of MCUXpresso (go to the Home page by clicking on the House icon) :
1. Click on `Download and Install SDKs`
2. In the Filter box on the right side, search for the board you need (ex. FRDM-KL25Z)
3. Choose the right board and click `Install` then `Finish`

## Add PATH to your project
1. Next, select the `Project` window from the top then select `Properties` then `C/C++ General` then `Paths and Symbols`

2. In the includes window, click on `GNU C` and add the PATH you desire

3. Select `Apply and Close` then `Rebuild Index`

## Add other SDK components to your project
1. In Project Explorer (on the left side), click on your project.

2. Also in the Project Explorer window, find a brown square and click on it (`Manage SDK components`)

3. Choose the drivers you want to add (mostly in the Driver section)

4. Then hit `OK`