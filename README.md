# Spidercam With Live Camera Stream

[This project was done as part of the EEE318 Control Systems Laboratory of Level 3, Term 2]  
The project features a spidercam system with live streaming camera with a web interface. For the spidercam 3D maneuver, 2 Arduinos have been used as the microcontroller to precisely control 4 stepper motors. ESP32 camera module has been used for live streaming and an asynchronous TCP web server has been programmed into the ESP32 controller. An HTML/JavaScript based web interface has been made for wireless live stream of the camera feed.

## Theory
### Controlling an object's coordinate in 3D with 4 strings
![image](https://github.com/touhid314/Spidercam-with-live-camera-stream/assets/69526008/17d4c6ad-9dbc-43ee-8156-1994bca40f6e)

4 strings are attached to 4 poles of height h. A specific value of the set {l1, l2, l3, l4} corresponds to a unique (x,y,z) coordinate of the tied point on the tip of the strings. 


