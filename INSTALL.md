# Installation guide

## Setup IQRF sensors and actuators

* Create IQRF network
* Configure IQRF network

Follow the instructions in the iot-starter-kit guide in IQRF Startup Package. 

## Install Linux to your UP board and connect IQRF module

* Follow the [instructions](https://github.com/iqrfsdk/iot-starter-kit/tree/master/core/aaeon.com)
to install UbiLinux, Ubuntu or Yocto.
* Follow the instructions [here](http://www.iqrf.org/weben/downloads.php?id=412) on how to attach
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

* Start with dev essentials [program](https://www.visualstudio.com/cs/dev-essentials/) and activate Azure package
* Create iothub in your Azure portal
* Create device in the iothub that will represent IQRF GW - UP board
* Use Device explorer [app](https://github.com/Azure/azure-iot-sdk-csharp/releases) to connect to iothub
* Copy connection string from your Azure portal
* Generate SAS token using Device explorer - is used as password in MQTT [config](workshop/daemon-config/MqttMessaging.json)
* Update MQTT [config](workshop/daemon-config/MqttMessaging.json) in the iqrf-daemon
* Restart the daemon

## Learn about possible extensions

Check the content [here](https://github.com/iqrfsdk/iot-starter-kit/tree/master/extensions)
