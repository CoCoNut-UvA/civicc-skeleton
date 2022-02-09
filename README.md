# CoCo

This gives a base for your own civicc compiler.
Clone this repo: 
```bash
git clone git@github.com:CoCoNut-UvA/civicc-skeleton.git civicc
cd civicc
./configure.sh
```
If everything went correctly, a build-debug directory is created. 
Run
```bash
make -C build-debug
```
to build your compiler.

**IMPORTANT**: After cloning, you should change the remote to point to a **private** repo you control.
You can **not** achieve this via forking, because GitHub does not allow changing the visibility of a forked repo.

# Creating an archive
You can quickly create an archive for submitting to canvas as follows
```
make dist
```
this gets everything in your git repo and combines it with the used coconut version in one archive.
This should contain everything needed to hand in your assignments.
**NOTE** Always check the resulting archive if it contains everything and builds correctly.