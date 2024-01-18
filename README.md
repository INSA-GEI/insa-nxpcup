# insa-nxpcup

Repository for INSA NXP cup 

# File organization
- 2023-2024: contain code, documentation, and hardware design of the Buggy 1 & 2 
- archive: all the work before 2023

# How can I navigate this project?
Each buggy has a dedicated directory with all the code and hardware files.

The source code for a specific buggy can be found at `buggy_name/code/buggy`

It contains the source code for each component and also the main source code of the buggy. 

**There is a README.md in the `code` folder that describes how to work with the code. Please refer to that document.**

# Quick HowTo
Small survival kit for everyone : 
## Installing git (the clean way)
[Get here](https://git-scm.com/downloads) and follow the installer's instructions. One should avoid using the GitHub desktop client

## Downloading the code
```bash
git clone https://github.com/INSA-GEI/insa-nxpcup.git
cd insa-nxpcup
```

## Update before you start working!
```bash
git pull 
```
If it doesn't work, save your changes elsewhere, and retry with
```bash
git stash	#Cancels all your changes in the repo
git pull	#Try pulling again
```

## Uploading your work
Upload as often as possible. Most errors here appear when working un un-updated code.

```bash
git add .
git commit -m "Message to describe commit"
git push #Sends the previous commit on this repo
```

**NB:** A good commit message is brief, and completes the following statement: *This commit will ...*.


# Branches management
**Do not use the master branch!**

You are in branch master, nothing should be done here

Select a valid branch:
```bash
git checkout branch_name
```

Teamwork should use a main branch and integrate inside every stable work. 

**Create new branches derive from the team's main branch for your work in progress.**



	


