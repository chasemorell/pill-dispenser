# Automated Pill Dispenser
![Image of Pinball Machine](https://github.com/chasemorell/pill-dispenser/blob/master/BDB4E1B1-0CE5-42C6-918D-4770D2579AEC.png)

The goal of this project was to create a device that would make it easier for people to remember to take their medication. [Watch video](https://drive.google.com/file/d/1bFqZEF5VAqe_7O5_9LfIW5_Oe89VpvPF/view?usp=sharing)

## Construction 

The outer shell of the device is constructed from plastic. I designed the parts on Adobe Illustrator and sent the designs to Ponoko, an online laser cutting service. The plastic parts are assembled with screws and L brackets on the interior of the deivce. 

### Touch Screen

I ordered a 2.8 inch capacitive touchscreen for this project. It fits on the arduino like a shield. I used an Arduino Mega for this project. Because of differences in the SCL and SDA pins on the Mega versus the Uno, I had to solder two jumpers on the touchscreen's circuitboard. 

### Dispensing Mechanism

The device has a simple dispensing mechanism. I used a stepper motor mounted underneath a wood surface to turn a rod that allows the pills to fall into the tray below. 

## Interaction

Users interact with the touchscreen to recieve thier medication. The touchscreen alerts users when they need to take medication. Then the user can press a button on the screen to dispense the medication. After the medication is dispensed, the touchscreen will ask if the user took the medication. Once they press "yes," it will return to the home screen. 

## Electronics 

Components:
- Arduino Mega
- Stepper Motor
- Stepper Controller
- 2.8 inch Adafruit Capacative Touchscreen
- Wires

## Code 
The code for the automated pill dispenser can be [found here](https://github.com/chasemorell/pill-dispenser/blob/master/pillDispenser.ino).

![Image of Electronics of Machine](https://github.com/chasemorell/pill-dispenser/blob/master/insidepilldispenser.png)
## 3D Designed Part

I would have like to create a better storage mechanism for the pills. Here's a 3D model of it:
[Link to onShape file](https://cad.onshape.com/documents/4d53cef2c959949e67fda81e/w/4d736071720030c78e7785ca/e/d886c25de5ae0cb3e6f95560)

![Image of 3D Dispenser Part](https://github.com/chasemorell/pill-dispenser/blob/master/Screen%20Shot%202020-04-26%20at%205.46.25%20PM.png)

## Conclusion

This project was both exciting and challenging. With more time and resources, I would like to create a more sophisticated dispensing mechanism that allows for multiple pill types. 

## Video
[Watch video](https://drive.google.com/file/d/1bFqZEF5VAqe_7O5_9LfIW5_Oe89VpvPF/view?usp=sharing)



