# Hands-On-Workshop for IQRF IOT

## Setup IQRF sensors and actuators

- Download Startup package
- Install IQRF IDE software
- Upload DPA plugins, custom handlers and configurations
- Use IDE macros for IoT Starter Kit to test your IQRF mesh network

## Install Linux &+ to your UP board (has been done for you already)

- UbiLinux 
- Ubuntu 
- Yocto

## Connect IQRF module 

- Connect IQRF SPI board to the UP board extension connector
- Plug-in prepared IQRF coordinator to IQRF SPI board 

## Install IQRF daemon on the UP board

- Download Putty and connect to your UP board via ssh
- Download public key to verify the packages from the repository
- Add repository to the source list
- Install or update the daemon
- Check the daemon service status
- Setup your configuration
- Install mosquitto broker

## Test MQTT channel

- Download MQTT Paho client for Win
- Connect Paho client to your Mosquitto broker on the UP
- Use prepared json examples to communicate with IQRF sensors and actuators
- Try your own DPA commands

## Test MQ channel

- Use putty to connect to your UP board via ssh
- Use iqrfapp and prepared examples to communicate via the daemon to IQRF network
- Try your own DPA commands
- Switch the daemon to service mode

## Test UDP channel

- Connect IQRF IDE to the UP board
- Run IQMesh Network Manager to control your IQRF network
- Switch the daemon back to operational mode by iqrfapp using putty

## Use NodeRED to create your local dashboard

- Install NodeRED
- Import Jotio IQRF IoT package
- Run your local control dashboard

## Connect to Azure cloud

- Start with dev essentials [program](https://www.visualstudio.com/cs/dev-essentials/) and activate azure package
- Create iothub in your Azure portal
- Create device in the iothub that will reprezent IQRF gw - UP board
- Use Device explorer app to connect to iothub
- Copy connection string from your Azure portal
- Generate sas token using Device explorer
- Update mqtt config in the iqrf-daemon
- Restart the daemon

## Try our mobile app

- Download our free iot iqrf app to your android device
- Setup mqtt connection
- Experiment with it
