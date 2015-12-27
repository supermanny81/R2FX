#<a name="r2fx"></a> R2FX 
#####  supermanny on [R2 Builders Group](http://www.astromech.net) | Build Log [Facebook](https://www.facebook.com/supermannys.artoo.detoo/)


This system is designed to be used as a visual effects system for astromechs.  Sequences can be built by builders and uploaded to the R2FX system.  Other control systems can then integrate and call sequences or specific features using a serial connection, I2C or by connecting sequences to unused digital pins.  In conjunction with the software, serveral hardware components have been designed. 

### Hardware _[..](#r2fx)_
Open source hardware and designed to recreate R2-D2's doors throughout the body using HS-55|65 servos with mini splines.  Original source files as well as STL exports are available to use for printing parts. 

![](Media/body_servo_system.png)

In addition to servo mounts for the body doors, a mounting system has also been designed.  This system was created to be minimal in space usgae while very strong.  The mounts are designed for the HS-55|65 series servo.

![](Media/hp_servo_mounts.png)

### Software  _[..](#r2fx)_
```
                  ~~~
                 \_0_/
                  | | ___---___
                ____  ____  _______  __
               |  _ \|___ \|  ___\ \/ /
             / | |_) | __) | |_   \  / \
           /   |  _ < / __/|  _|  /  \   \
          |    |_| \_\_____|_|   /_/\_\   |
     ___  |-------------------------------|  ___
     |  |_| Visual effects control system |_|  |
     |          =====================          |

```

Using off the shelf hardware like an Arduino Uno, Adafruit PWM modules, and Bluefruit module, and FRAM chips.  You can control all of your astromechs dome panels, doors and more.  

