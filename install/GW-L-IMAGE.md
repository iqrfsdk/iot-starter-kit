# IoT Starter Kit - Part 2: IQRF GW

## Step 1 - Download IoT Starter Kit installer image

[IoT Starter Kit installer](https://dl.iqrfsdk.org/iot-starter-kit-v080-installer.img.bz2)

Installer burns complete image right after the boot without any user interaction, just wait:

* Ubilinux 4.0
* IQRF daemon
* IQRF daemon webapp
* Mosquitto broker
* Nodejs
* Node-RED
* Node-RED IoT Starter Kit dashboard
* Gparted

Burning is signalled by blinking of the GREEN led on the UP board. When we are done blinking stops.

## Step 2 - Install 7-Zip and Rufus tools

* Download and install [7-Zip](http://www.7-zip.org/)
* Download and install [Rufus](https://rufus.akeo.ie/)

## Step 3 - Extract image and burn it to 8G(16G) USB disk

* Extract image using 7-Zip
* Burn image to USB disk using Rufus

![Burn installer to 8G(16G) USB disk](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/rufus-burn-installer.png)

## Step 4 - Plug 8G(16G) USB installer to the UP board

* Plug 8G(16G) USB installer to the UP board
* Let the UP board boot from USB (Press F7 and select UEFI disk to boot from)
* Wait till blinking of GREEN led is stopped
* Power-off the UP board
* Unplug USB installer

## Step 5 - Insert IQRF coordinator

![IQRF SPI board](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/iqrf-spi-board.png)

* Attach [IQRF SPI board](http://www.iqrf.org/weben/downloads.php?id=412)
* Insert prepared IQRF Coordinator to the IQRF SPI board

## Step 6 - Boot installed image

* Power-on the UP board and boot normally
* Login using: user=ubilinux; pass=ubilinux
* Run Gparted and extend UP board flash to 32GB

Enjoy, your are done! 
Now, check all is fine!

## Step 7 - Check IQRF daemon WebAPP dashboard

```bash
http://localhost
```
![IQRF daemon WebAPP dashboard](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/iqrf-daemon-webapp-gateway.png "IQRF daemon WebAPP dashboard")

* Login using: user=admin; pass=iqrf

## Step 8 - Check Node-RED dashboard

```bash
http://localhost:1880/ui
```
![IQRF App dashboard](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/node-red-ui.png "IQRF App Dashboard")

## Step 9 - Check Node-RED flow

```bash
http://localhost:1880
```
![IQRF App flow](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/node-red-flows.png "IQRF App Flow")
