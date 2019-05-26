# bio_impd

# Setup 
1. Connect the arduino usb cable to computer 
2. Connect the I2C cables from the bio-impedance chip to the arduino 
![Arduino Uno Pinout](https://www.theengineeringprojects.com/wp-content/uploads/2018/06/Introduction-to-Arduino-UNO.png)
This include the voltage to 5v, the ground, SDA, and SCL cables
3. Connect the Probes to sensor via the 3.5 mm connector
4. Apply black and red probes to intended surface
5. The Bioimpdeance sensor is now ready for use.

# Use
To use all that is necessary are the cpp and h files
The ino file is an exmaple of how to use the software.
In the sample file a scan a ran on the set frequencies.
1. Once the device is setup the code needs to be flashed on to the arduino this can be done by the arduino IDE
2. Then open the serial monitor to verfiy that the code is running properly
3. The results should be displayed on the monitor

# How to expand on Code 
Modify the Code to Display impedance with respect to frequency
