# insa-nxpcup

Repository for INSA NXP cup : C0R3 DUMP. Its current members are Alex, Valentin and Vincent
As of today, this repo is used by INSA's three teams.

# Where do I find/place the source code ?
Every folder titled `source_[...]` is a version of the code. One should only put the \*.c and the \*.h of the project, not the entire folder !

[...] Is a keyword or a_small_sentence describing this version in particular (e.g. "`source_dangerously_fast`" or "`source_safest`").

# Quick HowTo
Small survival kit for everyone : 
## Installing git (the clean way)
[Get here](https://git-scm.com/downloads) and follow the installer's instructions. One should avoid using github desktop client ;)

## Downloading the code
```bash
git clone https://github.com/INSA-GEI/insa-nxpcup-1.git
cd insa-nxpcup-1
```

## Update before you start working !
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
git commit -a #Prepare a commit with all updated files, ignoring new files.
git push #Sends the previous commit on this repo
```
**NB :** While commiting, use `Esc :wq Enter`. A good commit message is brief, and completes the following statement : *This commit will ...*.


# Branches management
**Do not use branches yet !**
Your are in branch master, nothing should be done here
Select a valid branch:

	git checkout stable    : stable branch
	git checkout dev       : work in progress
	

