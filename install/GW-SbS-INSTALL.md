# IoT Starter Kit - Part 2: IQRF GW

## Step 1 - Insert IQRF coordinator

![IQRF SPI board](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/iqrf-spi-board.png)

* Attach [IQRF SPI board](http://www.iqrf.org/weben/downloads.php?id=412)
* Insert prepared IQRF Coordinator to the IQRF SPI board

## Step 2 - Install OS Linux

* Install [UbiLinux 4.0](https://up-community.org/downloads/download/44-ubilinux/90-ubilinux-installer-4-0)

## Step 3 - Update UbiLinux 4.0

```bash
sudo apt-get update && sudo apt-get full-upgrade -y
```

## Step 4A - Install MQTT broker

```bash
sudo apt-get install -y mosquitto mosquitto-clients
```

### Step 4B - Confirm MQTT broker is running

```bash
ubilinux@ubilinux:~$ systemctl status mosquitto.service
â mosquitto.service - LSB: mosquitto MQTT v3.1 message broker
   Loaded: loaded (/etc/init.d/mosquitto; generated; vendor preset: enabled)
   Active: active (running) since Wed 2017-11-22 17:24:13 UTC; 1min 59s ago
     Docs: man:systemd-sysv-generator(8)
   CGroup: /system.slice/mosquitto.service
           ââ14253 /usr/sbin/mosquitto -c /etc/mosquitto/mosquitto.conf
```

## Step 5A - Install IQRF daemon

```bash
echo "deb http://repos.iqrfsdk.org/debian stretch testing" | sudo tee -a /etc/apt/sources.list.d/iqrf-daemon.list
sudo apt-get install -y dirmngr
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys F973CFCE6B3BE25C
sudo apt-get update && sudo apt-get install -y iqrf-daemon
```

### Step 5B - Confirm IQRF daemon is running

```bash
ubilinux@ubilinux:~$ systemctl status iqrf-daemon.service
â iqrf-daemon.service - IQRF daemon iqrf_startup
   Loaded: loaded (/lib/systemd/system/iqrf-daemon.service; enabled; vendor preset: enabled)
   Active: active (running) since Wed 2017-11-22 17:31:01 UTC; 52s ago
 Main PID: 15905 (iqrf_startup)
    Tasks: 11 (limit: 4915)
   CGroup: /system.slice/iqrf-daemon.service
           ââ15905 /usr/bin/iqrf_startup /etc/iqrf-daemon/config.json
```

## Step 6A - Install IQRF WebAPP

```bash
cd /home/ubilinux
git clone https://github.com/iqrfsdk/iqrf-daemon-webapp.git
cd iqrf-daemon-webapp/install/
sudo python3 install.py -d debian -v 9
```

### Step 6B - Confirm IQRF WebAPP is running

```bash
http://localhost/en
```
![IQRF daemon WebAPP dashboard](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/iqrf-daemon-webapp.png "IQRF daemon WebAPP dashboard")

* Login using: user=admin; pass=iqrf

## Step 7A - Configure IQRF SPI interface

```bash
http://localhost/en/config/iqrf
```
![Select spidev2.0 interface](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/iqrf-daemon-webapp-config-iqrf.png "Select spidev2.0 interface")

* Save new configuration!

## Step 7B - Restart IQRF daemon

```bash
http://localhost/en/service
```
![Restart IQRF daemon](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/iqrf-daemon-webapp-service-restart.png "Restart IQRF daemon")

* Hit Restart!

## Step 8A - Install Nodejs

```bash
cd /home/ubilinux
git clone https://github.com/iqrfsdk/iot-starter-kit.git
cd iot-starter-kit/install
sudo cp lsb-release-debian /etc/lsb-release
sudo apt-get install curl libssl-dev
curl -sL https://deb.nodesource.com/setup_6.x | sudo -E bash -
sudo apt-get install nodejs
sudo cp lsb-release-ubilinux /etc/lsb-release
```

## Step 9A - Install Node-RED

```bash
sudo npm install -g --unsafe-perm node-red
sudo npm install -g pm2
```

* Have patience with commands!

### Step 9B - Start Node-RED

```bash
pm2 start /usr/bin/node-red -- -v
```

### Step 9C - Add Node-RED dashboard

```bash
http://localhost:1880
```

### Step 9D - Run IoT-Starter-Kit flow

```bash
cd /home/ubilinux/iot-starter-kit/install
cp node-red/* /home/ubilinux/.node-red
pm2 restart node-red
```

### Step 9E - Allow Node-RED to run after reboot

```bash
pm2 save
pm2 startup
```

## Step 10A - Check Node-RED dashboard

```bash
http://localhost:1880/ui
```
![IQRF App dashboard](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/node-red-ui.png "IQRF App Dashboard")

### Step 10B - Check Node-RED flow

```bash
http://localhost:1880
```
![IQRF App flow](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/node-red-flows.png "IQRF App Flow")

### Step 10C - Blink coordinator LEDR from IQRF WebAPP

```bash
http://localhost/en/iqrfnet/send-raw
```
![IQRF Send DPA packet](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/iqrf-daemon-webapp-pulse-ledr.png "IQRF Send DPA packet")

* Select macro Pulse LEDR and send it!

![IQRF JSON DPA RAW structure](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/iqrf-daemon-webapp-pulse-ledr-json-raw.png.png "IQRF JSON DPA RAW structure")

* Learn JSON DPA RAW structure!

### Step 10D - Inspect JSON messages between Node-RED and IQRF daemon

* Listen for all JSON DPA RAW-HDP Requests

```bash
mosquitto_sub -t Iqrf/DpaRequest
```

* Listen for all JSON DPA RAW-HDP Responses

```bash
mosquitto_sub -t Iqrf/DpaResponse
```

### Step 10E - Check our examples

```bash
cd /home/ubilinux
git clone https://github.com/iqrfsdk/iqrf-daemon-examples.git
cd iqrf-daemon-examples
```

* Contribution to the examples very much appreciated!

Enjoy and spred the joy!
