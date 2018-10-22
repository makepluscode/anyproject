
# TELLO CONTROL with WEMOS LOLIN EP1
This example is about how to takeoff and land Tello with WemosㆍLolin D1 Mini.
It is EP1 for Tello Joystick project.

![p006-tello-joystick-ep01 00_00_09_04 001](https://user-images.githubusercontent.com/39910774/47289628-93242e00-d636-11e8-9b73-dbff194070ea.png)

## Before Start
Firstly, install Visual Code and a plug-in for Wemos or Lolin. Please See [Youtube](https://youtu.be/V6bG-UvD54Q?sub_confirmation=1) to install IDEs.

## Build
### STEP1. Download the main.cpp
 1. Execute Visual Code with sudo privilege
 ```
 sudo code --user-data-dir
 ```
 2. Go to platformIO's home and create a new project.
 3. Make sure set the Baudrate to 74880 not text on terminal to be broken on platformio.ini.
  ```
 monitor_speed = 74880
 ```
 4. Copy downloaded code to main.cpp and change information of SSID of tello.

## Run
 1. Compile the code created with the Build button at the bottom
 2. Upload the executable file to the board with the upload button at the bottom
 3. Run the program.
 4. Turn on your Tello.
 
## Video Tutorial 
 [![Watch the video](https://user-images.githubusercontent.com/39910774/47252575-f0c34980-d481-11e8-9c30-5b2543b722e5.png)](https://youtu.be/92QhbKA3VbQ?sub_confirmation=1)
