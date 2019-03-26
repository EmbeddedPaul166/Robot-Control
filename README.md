Robot-Control is an application targeted at Raspberry Pi 3B+, to control the semi-autonomous three-wheeled robot (two wheeled drive, third for support) with camera and vision feedback.
It was made specifically for my engineering thesis. Technologies used were C++ 11, Qt and OpenCV.

The ability to use the app was given by VNC viewer-server mechanism of working with remote desktops (Wi-Fi), hence the app was run on the RPI itself.
Robot was suited for work in two modes, first being manual, in which you could calibrate it's speed and movement, and second was autonomous in which it detected circular objects and followed them (also with speed calibration).

Raspberry Pi 3B+ was only used as upper level control centre. There was also an ATmega8A with implemented PID controller steering the DC motors and it received orders from RPI through UART. It's code is not a part of this repository though.

