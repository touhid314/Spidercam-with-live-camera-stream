# Spidercam With Live Camera Stream

[This project was done as part of the EEE318 Control Systems Laboratory of Level 3, Term 2 of BUET]  
The project features a spidercam system with live streaming camera with a web interface. For the spidercam 3D maneuver, 2 Arduinos have been used as the microcontroller to precisely control 4 stepper motors. ESP32 camera module has been used for live streaming and an asynchronous TCP web server has been programmed into the ESP32 controller. An HTML/JavaScript based web interface has been made for wireless live stream of the camera feed.

## Theory
### Controlling an object's coordinate in 3D with 4 strings
<img src='https://github.com/touhid314/Spidercam-with-live-camera-stream/assets/69526008/44209f62-56f1-4b10-a64d-5a62f8ad0d2e' width='500'>

4 strings of length `l1`, `l2`, `l3`, `l4` are attached to 4 poles of height `h`. The base area has dimensions `a*b`. A specific value of the set `{l1, l2, l3, l4}` corresponds to a unique `(x,y,z)` coordinate of the tied point on the tip of the strings. 

The relation between `{l1, l2, l3, l4}` and `(x,y,z)` can be found from 3D coordinate geometry as:  
  
$`l_1 = \sqrt{(x-0)^2 + (y-b)^2 + (z-h)^2}`$  
$`l_2 = \sqrt{(x-a)^2 + (y-b)^2 + (z-h)^2}`$  
$`l_3 = \sqrt{(x-0)^2 + (y-0)^2 + (z-h)^2}`$  
$`l_4 = \sqrt{(x-a)^2 + (y-0)^2 + (z-h)^2}`$  

Considering the string is attached with a cylinder of radius `r`, to change a string length by $`\Delta l`$, the cylinder has to be rotated by an angle.  

$`\Theta = \frac{\Delta l}{r}`$  
  
By rotating the stepper motor with the proper angle, each wire length can be adjusted to achieve a desired `(x,y,z)` coordinate. 

## Implementation
### 3D Coordinate Control
### Live Camera Stream on Web Interface



