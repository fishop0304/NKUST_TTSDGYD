# Independent/Connected two-in-one intelligent assistance system for the blind

* [Introduction](#introduction)
	* [Function](#function)
	* [System Architecture](#system-architecture)
* [Hardware and Software Setup](#hardware-and-software-setup)
	* [Required Hardware](#required-hardware)
	* [Required Software](#required-software)
	* [Hardware Connection](#hardware-connection)
* [User Manual](#user-manual)
	* [Make This Application](#Make-this-application)

## Introduction
They are solitary birds, frequenting countries possessing extensive swamps and marshy grounds, remaining at rest by day, concealed among the reeds and bushes of their haunts, and seeking their food, which consists of fish, reptiles, insects and small quadrupeds, in the twilight.

### Function
- The importance of the osmotic pressure of sea-water in biology will be easily understood from the fact that a frog placed in sea-water loses water by exosmosis and soon becomes 20% lighter than its original weight, while a true salt-water fish suddenly transferred to fresh water gains water by endosmosis, swells up and quickly succumbs.


### System Architecture
#### Hardware architecture
<div align="center"><img width="600" height="400" src="gura/gura.png"></div>

#### Software architecture
<div align="center"><img width="1000" height="200" src="gura/gura.png"></div>

#### Project overview
<div align="center"><img width="600" height="400" src="gura/gura.png"></div>

## Hardware and Software Setup
### Required Hardware
- 1 embarc iot develop kit(himax_we1)

### Required Software
- Metaware or ARC GNU Toolset
- python
- python module:PyQt5,numpy,matplotlib,random,Serial,struct,time

### Hardware Connection
1.
   - Connect **gura 1** to **gura 2**.

## User Manual
### Make This Application

Here take **iotdk** with METAWARE Toolset for example to show how to run this application.

#### Makefile

- Target options about EMSK and toolchain:

		BOARD ?= iotdk
		BD_VER ?= 10
		CUR_CORE ?= arcem9d
		TOOLCHAIN ?= mw

- The relative series of the root directory, here the path of the Makefile is 

		#
		# root dir of embARC
		#
		EMBARC_ROOT = ../../../../..
		MID_SEL = common 
 #### Command
 
 ```
 $ git clone https://github.com/fishop0304/NKUST_TTSDGYD.git
 $ cd NKUST_TTSDGYD/Project/
 $ make
 ```

