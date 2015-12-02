
#<a name="r2fx-ino"></a>R2FX.ino

This software is used to control the auxilary functions in an astromech.  Control over compnonents like a panel or lighting system may be directly controlled through here, however more importantly the goal of this project is to expose the capability of creating new sequences and sharing them with other astromech builders. 


[**Hardware**](#r2fx-hardware) - A description of the hardware necessary to run R2FX.

[**R2FXConfig.h** ](#r2fx-configuration) - Contains all of the configurations used to build the project. This is the only file that **needs** be edited by end users.

[**R2FX ASCII Protocol**](#r2fx-ascii-protocol), [**R2FX Byte Protocol**](#r2fx-byte-protocol) - A description of the protocols used to communicate to the R2FX control system.

###<a name="r2fx-ascii-protocol"></a>R2FX ASCII Protocol _[(top)](#r2fx-ino)_

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

##### Dome Systems _[(ascii protocol)](#r2fx-ascii-protocol)_
Command          | Description                         | Parameters                   | Example
:----------------|:------------------------------------|:-----------------------------|---------
`PPC`            | center pie panel                    | `null` or `0-180` (null == 0)| `[PPC90]`
`PP(1,2,5,6)`    | pie panels #1,2,3,5,6               | ...                          | `[PP1]`
`PP(1-4)|(7,8,A)`| panel #1-4, or 7, 8, A (Hex for 10) | ...                          | `[PA0]`

##### Body Systems _[(ascii protocol](#r2fx-ascii-protocol)_
Command          | Description                         | Parameters                   | Example
:----------------|:------------------------------------|:-----------------------------|---------
`U(T|B)`         | controls the position of the utility arms T=top, B=bottom | `null` or `0-180` (null == 0)| `[UT145]`
`CB`             | enables or disables the charge bay panel , returns it's enabled state| `null` to toggle, or boolean `0|1` | `[CB]`
`DP`				 | enables or disables the data port logics, returns it's state | ... | `[DP]`


##### System Commands _[(ascii protocol](#r2fx-ascii-protocol)_
Command          | Description                         | Parameters                   | Example
:----------------|:------------------------------------|:-----------------------------|---------
`V(P|D)`         | prints the current voltage level in decimal (D) or percent (P) | `null` | `[VP]`
                                                       
###<a name="r2fx-byte-protocol"></a>R2FX Byte Protocol _[(top)](#r2fx-ino)_
---<i>Work in progress</i>----

A R2FX command and its data parameters are refferred to as an R2FX message . The minimum size of a message is 3 bytes *(one command byte, a length parameter signed 8 bit integer (-1) with no parameter (data) bytes), and a CRC field*. The maximum size of a R2FX message currently can be up to 16 bytes, however in practice this should rarely happen and in theory could be expanded to 130 bytes (CMD + LEN + 127 bytes + CRC). 

An R2FX message **always** starts with a command byte. The table below outlines the possible command types that may be used when using R2FX.

##### R2FX Message Format _[(byte protocol)](#r2fx-byte-protocol)_
```

         CMD.,  LEN.,  DATA..............,  CRC
         0xF0,  0x03,  0xA1,  0xC1,  0xF7,  0xCC
         |_______________________________|
                       | |
       CRC computed from the complete packet.    
            
```

##### R2FX CRC _[(byte protocol)](#r2fx-byte-protocol)_

```
const byte CRC_INIT = 0xF0;
const byte CRC_POLY = 0x07;

unsigned byte crc_calc(unsigned byte buffer[], byte size) {
  unsigned long i;
  unsigned byte crc;

  crc = CRC_INIT;

  for (i=0;i<size * 8;i++) {
    crc = (crc << 1) | (crc >> (7));
    if (buffer[i/8] & (0x80 >> (i%8))) {
      crc ^= CRC_POLY;
    }
  }
  return crc;
}
```


##### Reserved Command Ranges _[(byte protocol)](#r2fx-byte-protocol)_
The ranges in the command space are reserved or restricted for groups of systems, compatibility reasons, or future expansion.

Range (HEX) | Range (DEC) | Purpose
:-----------|:-----------:|:----------
`0x00-0x5A` |    0-90     | TBD
`0x5B`      |     91      | Restricted to maintain compatibility with R2FX serial based protocol
`0x5C`      |     92      | Restricted
`0x5D`      |     93      | Restricted to maintain compatibility with R2FX serial based protocol
`0x5E-0x79` |    94-126   | TBD
`0x80-0xB2` |   127-178   | Reserved for Dome FX Systems
`0xB3-0xDA` |   179-219   | Reserved for Body FX Systems
`0xDB-0xEF` |   220-239   | Reserved for Audio FX Systems
`0xF0-0xFF` |   240-255   | Reserved for R2FX managment and telemetry


##### Dome Systems _[(byte protocol)](#r2fx-byte-protocol)_

| Command | Description | Length | Parameters  <br>*0-13 bytes* 
:---------|:------------|:-------|:-----------------------------
 `0x80`   |             |   0    |        ...     
 
##### Body Systems _[(byte protocol)](#r2fx-byte-protocol)_

| Command | Description | Length | Parameters  <br>*0-13 bytes* 
:---------|:------------|:-------|:-----------------------------
 `0xB3`   |             |   0    |        ...     
 
 
 


