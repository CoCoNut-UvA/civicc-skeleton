# CiviC Skeleton
This gives a base for your own civicc compiler.

## Getting started
First make sure you have all dependencies installed. The full dependencies of CoCoNut are listed on the main [GitHub](https://github.com/CoCoNut-UvA/coconut) repository. On
Ubuntu these can be installed using:
```bash
sudo apt update && sudo apt install build-essential cmake bison flex graphviz
```
For macOS, see [macOS dependencies](#macos-dependencies).

Now clone this repo:
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

## VS Code support
For syntax highlighting of the CoCoNut DSL files (e.g. the `main.ccn` file), you can install the [nutcracker](https://github.com/CoCoNut-UvA/nutcracker/) extension from the Visual Studio Marketplace [here](https://marketplace.visualstudio.com/items?itemName=CoCoNut-UvA.nutcracker).

We provide a Linux configuration file in [`.vscode/c_cpp_properties.json`](.vscode/c_cpp_properties.json) that helps IntelliSense to find the header files generated by cocogen.
VS code should pick this up automatically; if you open a C file you should see CoCoNut-Linux in the bottom-right corner.

## Creating an archive
You can quickly create an archive for submitting to canvas as follows
```bash
make dist
```
this gets everything in your git repo and combines it with the used coconut version in one archive.
This should contain everything needed to hand in your assignments.
**NOTE:** Always check the resulting archive if it contains everything and builds correctly.

## macOS dependencies
The following build dependencies are required on macOS:
```bash
brew install cmake coreutils binutils bison graphviz
```

You might also need to run the following for cmake to find Bison:
```bash
echo "export PATH=\"$(brew --prefix)/opt/bison/bin:\$PATH\"" >> ~/.zshrc
```

**Note:** Make sure to fully restart your terminal after adding this line to `.zshrc`, and also delete the folder `coconut/build` if it exists. Otherwise cmake will keep using the old unsupported Bison version that macOS ships with.
