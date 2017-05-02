# Installation guide

## Setup IQRF sensors and actuators

* Create IQRF network

Open the DS-IOT-01 set which is the part of your IoT Starter Kit.

	* Download Startup package from IQRF website which contains IQRF IDE application 
	  and all needed files: http://www.iqrf.org/support/how-to-start.

	* Watch tutorials about IQRF to simplify installation process to build your 
	  basic IQRF network.

	* How to upgrade IQRF OS:
		https://youtu.be/BMoUT_1_rDc?list=PLEQy1I01En98-Q68fH50l-yjtoeV48zKU

	* How to make a network with IQRF OS 4.0:
		https://youtu.be/x6Q8KsK5UB0?list=PLEQy1I01En98-Q68fH50l-yjtoeV48zKU

	* Build your IQRF network consisting of one IQRF coordinator and three IQRF nodes. 
	  The first node serves for sensor data receiving, the second one serves for relays 
	  control and the third one serves as an IQRF router for IQRF network extension.

* Configure IQRF network

There are prepared special Custom DPA Handler files in a Startup package. The first one 
for sensor kit to receive sensor data, the second one for relay control.

	* Watch tutorial video how to use Custom DPA Handlers.
	  Custom DPA Handlers for IoT Starter Kit:
	  https://youtu.be/ZbgEM7Z38zo?list=PLEQy1I01En98-Q68fH50l-yjtoeV48zKU.

	* Finally test your network to receive sensor data from the sensor kit and control 
	  relays on the relay kit.

	* There are prepared some special macros for the IoT Starter Kit 

	  - reading all sensor data from the sensor kit (temperature, light intensity, voltage) 
	  - FRC commands – reading specific sensor value from all devices in the IQRF network 
	    (temperature, light intensity, voltage), and switching relays on/off.

	* Macros for IoT Starter Kit
	  https://youtu.be/_skewBdWKnU

	  Tip: After UP board installation and IQRF Daemon configuration you can use UDP channel 
	  to connect IQRF IDE to UP board. The gateway must be in the accessible network from your 
	  computer. Fill in the IP address of the gateway and select User gateway in IQRF IDE. 
	  Then check if the communication is functional – refresh the network information of the 
	  coordinator and try to send some DPA command from the terminal.

	* How to connect IQRF IDE through UDP to UP
	  https://youtu.be/xyCJ9Cp2OWs

## Install Linux to your UP board and connect IQRF module

Follow the instructions on https://github.com/iqrfsdk/iot-starter-kit/tree/master/core/aaeon.com 
to install UbiLinux, Ubuntu or Yocto.

* Connect IQRF coordinator to the UP board

Follow the instructions here http://www.iqrf.org/weben/downloads.php?id=412 on how to attach
IQRF SPI board to UP board extension connector.

* Plug in prepared (by setup in IQRF IDE) IQRF coordinator to IQRF SPI board.

## Install ready IQRF daemon on the UP board

Follow the instructions [here](https://github.com/iqrfsdk/iqrf-daemon)

* Download public key to verify the packages from the repository
* Add repository to the source list
* Install or update the daemon
* Check the daemon service status
* Adjust your configuration

## Connect the UP to Azure cloud

* Start with dev essentials [program](https://www.visualstudio.com/cs/dev-essentials/) and activate azure package
* Create iothub in your Azure portal
* Create device in the iothub that will reprezent IQRF gw - UP board
* Use Device explorer app to connect to iothub
* Copy connection string from your Azure portal
* Generate sas token using Device explorer
* Update mqtt config in the iqrf-daemon
* Restart the daemon

## Learn about possible extensions

Check the content [here](https://github.com/iqrfsdk/iot-starter-kit/tree/master/extensions)
