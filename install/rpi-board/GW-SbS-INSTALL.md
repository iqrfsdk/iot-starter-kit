# IoT Starter Kit - Part 2: IQRF Gateway RPI

## Step 1 - Insert IQRF coordinator

![IQRF SPI board](../pics/iqrf-spi-board.png)

* Attach [IQRF SPI board](http://www.iqrf.org/weben/downloads.php?id=412)
* Insert prepared IQRF Coordinator to the IQRF SPI board

## Step 2 - Install OS Linux

* Download [Raspbian Lite](https://downloads.raspberrypi.org/raspbian_lite_latest)
* Burn Raspbian Lite iso image to SD card or USB flash by [Etcher](https://etcher.io/)
* default login: user=pi; pass=raspberry

## Step 3A - Update Raspbian Lite

```bash
sudo apt-get update && sudo apt-get -y full-upgrade
```

## Step 3B - Install SSH server and start it

```bash
sudo apt-get install -y ssh
sudo systemctl enable ssh.service && sudo systemctl start ssh.service
```

Now you can connect to Raspberry via SSH client from your PC e.g. using [Putty](http://www.putty.org/) client.

```bash
sudo ifconfig
```

Ifconfig tells you the IP address of your Raspberry. Use it in your Putty client. Login is default, see above.

## Step 3C - Enable SPI on Raspberry

Edit config.txt

```bash
sudo nano /boot/config.txt
```

and uncomment dtparam=spi=on and reboot Raspberry by:

```bash
sudo reboot
```

After reboot login again using Putty client.

## Step 4A - Install MQTT broker

```bash
sudo apt-get install -y mosquitto mosquitto-clients
```

### Step 4B - Confirm MQTT broker is running

```bash
systemctl status mosquitto.service
```
```bash
pi@raspberrypi:~ $ systemctl status mosquitto.service
â mosquitto.service - LSB: mosquitto MQTT v3.1 message broker
   Loaded: loaded (/etc/init.d/mosquitto; generated; vendor preset: enabled)
   Active: active (running) since Tue 2017-12-12 23:37:19 UTC; 6min ago
     Docs: man:systemd-sysv-generator(8)
   CGroup: /system.slice/mosquitto.service
           ââ15266 /usr/sbin/mosquitto -c /etc/mosquitto/mosquitto.conf

Dec 12 23:37:19 raspberrypi systemd[1]: Starting LSB: mosquitto MQTT v3.1 message broker...
Dec 12 23:37:19 raspberrypi mosquitto[15260]: Starting network daemon:: mosquitto.
Dec 12 23:37:19 raspberrypi systemd[1]: Started LSB: mosquitto MQTT v3.1 message broker.
```

## Step 5A - Install IQRF Gateway Daemon

```bash
sudo apt-get install -y dirmngr apt-transport-https lsb-release ca-certificates
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 9C076FCC7AB8F2E43C2AB0E73241B9B7B4BD8F8E
echo "deb http://repos.iqrf.org/debian buster stable testing" | sudo tee -a /etc/apt/sources.list.d/iqrf-gateway.list
sudo apt-get update && sudo apt-get install -y iqrf-gateway-daemon
```

### Step 5B - Confirm IQRF Gateway Daemon is running

```bash
systemctl status iqrf-gateway-daemon.service
```

## Step 6A - Install IQRF Gateway Daemon WebApp

```bash
sudo apt-get install -y iqrf-gateway-webapp
```

### Step 6B - Confirm IQRF Gateway Daemon WebApp is running

```bash
http://localhost/
```
![IQRF Gateway Daemon WebApp dashboard](../pics/iqrf-daemon-webapp.png "IQRF Gateway Daemon WebApp dashboard")

* Create your own login credentials

## Step 7A - Configure IQRF SPI interface

```bash
http://localhost/config/iqrf-spi/
```
![Select spidev0.0 interface](../pics/iqrf-daemon-webapp-config-iqrf.png "Select spidev0.0 interface")

* Select available interface!
* Save new configuration!

### Step 7B - Restart IQRF Gateway Daemon

```bash
http://localhost/service
```
![Restart IQRF Gateway Daemon](../pics/iqrf-daemon-webapp-service-restart.png "Restart IQRF Gateway Daemon")

* Hit Restart!

## Step 8A - Install Node.js and Node-RED

```bash
sudo apt-get install -y curl
bash <(curl -sL https://raw.githubusercontent.com/node-red/linux-installers/master/deb/update-nodejs-and-nodered)
```

### Step 9A - Start Node-RED

```bash
sudo systemctl enable nodered.service
sudo systemctl start nodered.service
```

### Step 9B - Add Node-RED dashboard

```bash
http://your-rpi-ip:1880
```
![Manage palete](../pics/node-red-add-dashboard-1.png "Manage palete")
![Install node-red-dashboard](../pics/node-red-add-dashboard-2.png "Install node-red-dashboard")

### Step 9C - Run IoT-Starter-Kit flow

```bash
cd /home/pi
git clone https://gitlab.iqrf.org/alliance/iot-starter-kit.git
cd iot-starter-kit/install
cp rpi-board/node-red/* /home/pi/.node-red
sudo systemctl restart nodered.service
```

### Step 9D - Confirm Node-RED is running

```bash
systemctl status nodered.service
```
```bash
â nodered.service - Node-RED graphical event wiring tool
   Loaded: loaded (/etc/systemd/system/nodered.service; enabled; vendor preset: enabled)
   Active: active (running) since Thu 2019-11-29 01:20:09 UTC; 1min 10s ago
     Docs: http://nodered.org/docs/hardware/raspberrypi.html
 Main PID: 20773 (node-red)
   CGroup: /system.slice/nodered.service
           âŁ 20773 node-red
```

## Step 10A - Check Node-RED dashboard

```bash
http://localhost:1880/ui
```
![IQRF Gateway App dashboard](../pics/node-red-ui.png "IQRF Gateway App Dashboard")

### Step 10B - Check Node-RED flow

```bash
http://localhost:1880
```
![IQRF Gateway App flow](../pics/node-red-flows.png "IQRF Gateway App Flow")

### Step 10C - Blink coordinator LEDR from IQRF Gateway Daemon WebApp

```bash
http://localhost/iqrfnet/send-raw
```
![IQRF Send DPA packet](../pics/iqrf-daemon-webapp-pulse-ledr.png "IQRF Send DPA packet")

* Select macro Pulse LEDR and send it!

![IQRF JSON DPA RAW structure](../pics/iqrf-daemon-webapp-pulse-ledr-json-raw.png "IQRF JSON DPA RAW structure")

* Learn JSON DPA RAW structure!

### Step 10D - Inspect JSON messages between Node-RED and IQRF Gateway Daemon

* Listen for all JSON DPA RAW Requests

```bash
mosquitto_sub -t Iqrf/DpaRequest
```

* Listen for all JSON DPA RAW Responses

```bash
mosquitto_sub -t Iqrf/DpaResponse
```

### Step 10E - Check our examples

```bash
cd /home/pi
git clone https://gitlab.iqrf.org/open-source/iqrf-gateway-daemon.git
cd iqrf-gateway-daemon/examples
```

* Contribution to the examples very much appreciated!

Enjoy and spred the joy!
