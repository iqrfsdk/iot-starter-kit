# IoT Starter Kit - Part 2: IQRF GW

## Step 1 - Insert IQRF coordinator

![IQRF SPI board](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/iqrf-spi-board.png)

* Attach [IQRF SPI board](http://www.iqrf.org/weben/downloads.php?id=412)
* Insert prepared IQRF Coordinator to the IQRF SPI board

## Step 2 - Install OS Linux

* Download [UbiLinux 4.0](https://emutex.com/products/ubilinux)
* Burn UbiLinux 4.0 iso image to USB flash by [Etcher](https://etcher.io/)
* default login: user=ubilinux; pass=ubilinux

## Step 3 - Update UbiLinux 4.0

```bash
sudo apt-get update && sudo apt-get -y full-upgrade
```

## Step 4A - Install MQTT broker

```bash
sudo apt-get install -y mosquitto mosquitto-clients
```

### Step 4B - Confirm MQTT broker is running

```bash
systemctl status mosquitto.service
```
```bash
ubilinux@ubilinux:~$ systemctl status mosquitto.service
â mosquitto.service - LSB: mosquitto MQTT v3.1 message broker
   Loaded: loaded (/etc/init.d/mosquitto; generated; vendor preset: enabled)
   Active: active (running) since Wed 2017-11-22 17:24:13 UTC; 1min 59s ago
     Docs: man:systemd-sysv-generator(8)
   CGroup: /system.slice/mosquitto.service
           ââ14253 /usr/sbin/mosquitto -c /etc/mosquitto/mosquitto.conf
```

### Step 4C (optional) - Static password and ACL file

These steps describe how to setup Mosquitto with a static password and ACL file.

Using the mosquitto_passwd command, it is possible to create a password file for authentication.

#### Create password for <user_name> (ubilinux)

Example to create a password file and add add an username (use the -c only the first time as it will create a new file):

```bash
sudo mosquitto_passwd -c /etc/mosquitto/passwd <user_name>
```

#### Create ACL file

* Add [ACL file](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/up-board/mosquitto/acls) 
to your /etc/mosquitto folder

#### Modify mosquitto configuration

* Include lines to enable authorization as in [configuration file](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/up-board/mosquitto/mosquitto.conf) to your /etc/mosquitto/mosquitto.conf file

* Restart MQTT broker

```bash
sudo systemctl restart mosquitto.service
```

### Step 4D (optional) - Enable websockets

#### Modify mosquitto configuration

* Include lines to enable websocket as in [configuration file](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/up-board/mosquitto/mosquitto.conf) to your /etc/mosquitto/mosquitto.conf file

* Restart MQTT broker

```bash
sudo systemctl restart mosquitto.service
```

## Step 5A - Install IQRF Gateway Daemon

```bash
sudo apt-get install -y dirmngr
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 9C076FCC7AB8F2E43C2AB0E73241B9B7B4BD8F8E
echo "deb http://repos.iqrfsdk.org/debian stretch stable" | sudo tee -a /etc/apt/sources.list.d/iqrf-daemon.list
sudo apt-get update && sudo apt-get install -y iqrf-daemon
```

### Step 5B - Confirm IQRF Gateway Daemon is running

```bash
systemctl status iqrf-daemon.service
```
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

## Step 6A - Install IQRF Gateway Daemon WebApp

```bash
cd /home/ubilinux
git clone https://github.com/iqrfsdk/iqrf-daemon-webapp.git
cd iqrf-daemon-webapp/install/
sudo python3 install.py -d debian -v 9
```

### Step 6B - Confirm IQRF Gateway Daemon WebApp is running

```bash
http://localhost/en
```
![IQRF Gateway Daemon WebApp dashboard](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/iqrf-daemon-webapp.png "IQRF Gateway Daemon WebApp dashboard")

* Login using: user=admin; pass=iqrf

## Step 7A - Configure IQRF SPI interface

```bash
http://localhost/en/config/iqrf
```
![Select spidev2.0 interface](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/iqrf-daemon-webapp-config-iqrf.png "Select spidev2.0 interface")

* Select available interface!
* Save new configuration!

### Step 7B - Restart IQRF Gateway Daemon

```bash
http://localhost/en/service
```
![Restart IQRF Gateway Daemon](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/iqrf-daemon-webapp-service-restart.png "Restart IQRF Gateway Daemon")

* Hit Restart!

## Step 8A - Install Node.js

```bash
cd /home/ubilinux
git clone https://github.com/iqrfsdk/iot-starter-kit.git
cd iot-starter-kit/install
sudo cp etc/lsb-release-debian /etc/lsb-release
sudo apt-get install curl
curl -sL https://deb.nodesource.com/setup_6.x | sudo -E bash -
sudo apt-get install nodejs
sudo cp etc/lsb-release-ubilinux /etc/lsb-release
```

## Step 9A - Install Node-RED

```bash
sudo npm install -g --unsafe-perm node-red
sudo npm install -g pm2
```

### Step 9B - Start Node-RED

```bash
cd /home/ubilinux
pm2 start /usr/bin/node-red
```

### Step 9C - Add Node-RED dashboard

```bash
http://localhost:1880
```
![Manage palete](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/node-red-add-dashboard-1.png "Manage palete")
![Install node-red-dashboard](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/node-red-add-dashboard-2.png "Install node-red-dashboard")

### Step 9D - Run IoT-Starter-Kit flow

```bash
cd /home/ubilinux/iot-starter-kit/install
cp up-board/node-red/* /home/ubilinux/.node-red
pm2 restart node-red
```

### Step 9E - Allow Node-RED to run after reboot

```bash
pm2 save
```
```bash
[PM2] Saving current process list...
[PM2] Successfully saved in /home/ubilinux/.pm2/dump.pm2
```

```bash
pm2 startup
```
```bash
[PM2] Init System found: systemd
[PM2] To setup the Startup Script, copy/paste the following command:
sudo env PATH=$PATH:/usr/bin /usr/lib/node_modules/pm2/bin/pm2 startup systemd -u ubilinux --hp /home/ubilinux
```

```bash
sudo env PATH=$PATH:/usr/bin /usr/lib/node_modules/pm2/bin/pm2 startup systemd -u ubilinux --hp /home/ubilinux
```

### Step 9F - Confirm Node-RED is running

```bash
systemctl status pm2-ubilinux
```
```bash
â pm2-ubilinux.service - PM2 process manager
   Loaded: loaded (/etc/systemd/system/pm2-ubilinux.service; enabled; vendor preset: enabled)
   Active: active (running) since Thu 2017-11-23 01:20:09 UTC; 1min 10s ago
     Docs: https://pm2.keymetrics.io/
 Main PID: 21952 (PM2 v2.7.2: God)
   CGroup: /system.slice/pm2-ubilinux.service
           âŁ 21952 PM2 v2.7.2: God Daemon (/home/ubilinux/.pm2)
```

## Step 10A - Check Node-RED dashboard

```bash
http://localhost:1880/ui
```
![IQRF Gateway App dashboard](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/node-red-ui.png "IQRF App Dashboard")

### Step 10B - Check Node-RED flow

```bash
http://localhost:1880
```
![IQRF Gateway App flow](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/node-red-flows.png "IQRF App Flow")

### Step 10C - Blink coordinator LEDR from IQRF Gateway Daemon WebAPP

```bash
http://localhost/en/iqrfnet/send-raw
```
![IQRF Send DPA packet](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/iqrf-daemon-webapp-pulse-ledr.png "IQRF Send DPA packet")

* Select macro Pulse LEDR and send it!

![IQRF JSON DPA RAW structure](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/iqrf-daemon-webapp-pulse-ledr-json-raw.png "IQRF JSON DPA RAW structure")

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
cd /home/ubilinux
git clone https://github.com/iqrfsdk/iqrf-daemon-examples.git
cd iqrf-daemon-examples
```

* Contribution to the examples very much appreciated!

Enjoy and spred the joy!
