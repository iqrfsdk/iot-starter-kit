# Hands-On-Workshop for IQRF IOT Starter Kit

## Setup IQRF sensors and actuators

- Download IQRF Startup [package](http://www.iqrf.org/support/how-to-start)
- Install IQRF IDE software that is included in the package
- Upload DPA plugins, custom handlers and configurations
- Use IDE macros for IoT Starter Kit to test your IQRF mesh network

## Install Linux

- UbiLinux (It has been done for you already)
- Ubuntu 
- Yocto

## Connect IQRF module 

- [Connect](http://www.iqrf.org/weben/downloads.php?id=412) IQRF SPI board to the UP board extension connector
- Plug-in already prepared IQRF coordinator to IQRF SPI board 

## Install IQRF daemon

- Download [Putty](http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html) and connect to your UP board via SSH
- Follow the [instructions](https://github.com/iqrfsdk/iqrf-daemon/blob/master/README.md)
- Install MQTT mosquitto broker

```bash
sudo apt-get update
sudo apt-get install mosquitto
```

## Test MQTT channel

- Download MQTT Paho [client](https://eclipse.org/paho/clients/tool/) for Win/Linux
- Connect Paho client to your Mosquitto broker on the UP
- Use prepared JSON [examples](json-msgs) to communicate with IQRF sensors and actuators
- Try your own DPA [commands](http://www.iqrf.org/DpaTechGuide/)

## Test MQ channel

- Use Putty to connect to your UP board via SSH
- Use iqrfapp and prepared scripts to communicate via the daemon to IQRF network
- Try your own DPA [commands](http://www.iqrf.org/DpaTechGuide/)
- Switch the daemon to service mode

```bash
sudo iqrfapp conf service
```

## Test UDP channel

- Connect IQRF IDE to the UP board via UDP
- Run IQMesh Network Manager to control your IQRF network
- Switch the daemon back to operational mode by iqrfapp

```bash
sudo iqrfapp conf operational
```

## Use NodeRED to create your local dashboard

- Install [NodeRED](../extensions/jotio.cz/README.md)
- Import Jotio IQRF IoT [package](../extensions/jotio.cz/jotio_nodered.json)
- Run your local control dashboard

## Connect to Azure cloud

- Start with dev essentials [program](https://www.visualstudio.com/cs/dev-essentials/) and activate Azure package
- Create iothub in your Azure portal
- Create device in the iothub that will represent IQRF GW - UP board
- Use Device explorer [app](https://github.com/Azure/azure-iot-sdk-csharp/releases) to connect to iothub
- Copy connection string from your Azure portal
- Generate SAS token using Device explorer - is used as password in MQTT [config](daemon-config/MqttMessaging.json)
- Update MQTT [config](daemon-config/MqttMessaging.json) in the iqrf-daemon
- Setup [scheduler](daemon-config/Scheduler.json) for regural readings from DDC-SE
- Restart the daemon

```bash
sudo systemctl restart iqrf-daemon.service
```

- confirm receiving scheduled DDC-SE readings by Device explorer [app](https://github.com/Azure/azure-iot-sdk-csharp/releases)
- create stream analytics script
- create Power BI dashboard

## Try our mobile app

- Download our free IoT IQRF app to your Android device
- Setup MQTT connection to your broker
- Give a try
