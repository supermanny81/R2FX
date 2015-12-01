
#R2FX.ino

This software is used to control the auxilary functions in an astromech.  Control over compnonents like a panel or lighting system may be directly controlled through here, however more importantly the goal of this project is to expose the capability of creating new sequences and sharing them with other astromech builders. 


[**Hardware**](#r2fx-hardware) - A description of the hardware necessary to run R2FX.

[**R2FXConfig.h** ](#r2fx-configuration) - Contains all of the configurations used to build the project. This is the only file that **needs** be edited by end users.

[**R2FX ASCII Protocol**](#r2fx-ascii-protocol) | [**R2FX Byte Protocol**](#r2fx-byte-protocol) - A description of the protocol used to communicate to the R2FX control system.

###<a name="r2fx-ascii-protocol"></a>R2FX ASCII Protocol

An ASCII based protocol to interact with the R2FX system.  While this protocol provides an 'simpler and easier' way of issuing commands, it will only ever exist for testing and demo purposes and most likely will never be a complete implementation of the prefferred byte based protocol which is more robust, concise and allows for 'sequences' of commands to be stored in FRAM.

R2FX serial messages contain a command, followed by any possible parameters and can total up to 16 bytes in length.  (Keep in mind, the messages use 2 bytes each to START and END a message.) Theorectically, the mininum length of message is 3 bytes, in practice it's much more.

An example of it's usage can be found below, here we are closing the center pie panel while opening up the PP1 to it's fullest setting.

```

[PPC0][PP180]

```
In addition to sending messages, the protocol also returns reponses.  A R2FX ASCII response will contain one or more lines, followed by an exit message of either `OK` or `ERR`.  If entered into a terminal, these are some of the responses you may get.

```
// close the center panel
> [PPC0]
PPC
OK

// move to 80 degrees
> [PP180]
PP1
OK

// Unmapped command
> [FOO-BAR]
ERR
```

#### Dome Commands
Command          | Description                         | Parameters                   | Example
:----------------|:------------------------------------|:-----------------------------|---------
`PPC`            | center pie panel                    | `null` or `0-180` (null == 0)| `[PPC90]`
`PP(1,2,5,6)`    | pie panels #1,2,3,5,6               | ...                          | `[PP1]`
`PP(1-4)|(7,8,A)`| panel #1-4, or 7, 8, A (Hex for 10) | ...                          | `[PA0]`

#### Body Commands
Command          | Description                         | Parameters                   | Example
:----------------|:------------------------------------|:-----------------------------|---------
`U(T|B)`         | controls the position of the utility arms T=top, B=bottom | `null` or `0-180` (null == 0)| `[UT145]`
                                                       
###<a name="r2fx-byte-protocol"></a>R2FX Byte Protocol
<i>Work in progress</i>

A R2FX command and its data parameters are refferred to as an R2FX message . The minimum size of a message is 2 bytes (one command byte, and a length paramter signed 8 bit integer (-1) with no parameter bytes). The maximum size of a R2FX message currently can be up to 16 bytes, however in practice this should rarely happen and in theory could be expanded to 129 bytes (CMD + LEN + 127 bytes). 

An R2FX message **always** starts with a command byte. The table below outlines the possible command types that may be used when using R2FX.

#### Reserved Commands
```

0x5B	Reserved to maintain compatibility with R2FX serial based protocol
0x5D	Reserved to maintain compatibility with R2FX serial based protocol

```

#### Dome Commands

#### Body Servos

| Command | Description | Length | Parameters  <br>**0-14 bytes** 
:-----------------|:--------------|:---------------|:---
 0xF0             |    |      0    |        ...      
 
 
 


