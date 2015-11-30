
#R2FX.ino

This software is used to control the auxilary functions in an astromech.  Control over compnonents like a panel or lighting system may be directly controlled through here, however more importantly the goal of this project is to expose the capability of creating new sequences and sharing them with other astromech builders. 


[**Hardware**](#r2fx-hardware) - A description of the hardware necessary to run R2FX.

[**R2FXConfig.h** ](#r2fx-configuration) - Contains all of the configurations used to build the project. This is the only file that **needs** be edited by end users.

[**R2FX Protocol**](#r2fx-protocol) - A description of the protocol used to communicate to the R2FX control system.

###<a name="r2fx-protocol"></a>R2FX Protocol
<i>Work in progress></i>

A R2FX command and its data parameters are refferred to as an R2FX message . The minimum size of a message is 2 bytes (one command byte, and a length paramter signed 8 bit integer (-1) with no parameter bytes). The maximum size of a R2FX message currently can be up to 16 bytes, however in practice this should rarely happen and in theory could be expanded to 129 bytes (CMD + LEN + 127 bytes). 

An R2FX message **always** starts with a command byte. The table below outlines the possible command types that may be used when using R2FX.

#### Reserved Commands
```

0x5B	Used to maintain backwards compatibility with R2FX v1 serial based protocol
0x5D	Used to maintain backwards compatibility with R2FX v1 serial based protocol

```

#### Dome Commands

#### Body Servos

| CMD | CMD Description | LEN | PARAM  <br>**0-14 bytes** 
:-----------------|:--------------|:---------------|:---
 0xF0             |    |      0    |        ...      
 
 
 


