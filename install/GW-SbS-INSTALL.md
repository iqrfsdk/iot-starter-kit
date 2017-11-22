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

## Step 4B - Confirm MQTT broker is running

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

## Step 5B - Confirm IQRF daemon is running

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

## Step 6A - Install IQRF daemon webapp

```bash
cd /home/ubilinux
git clone https://github.com/iqrfsdk/iqrf-daemon-webapp.git
cd iqrf-daemon-webapp/install/
sudo python3 install.py -d debian -v 9
```

## Step 6B - Confirm IQRF daemon webapp is running

```bash
http://localhost
```

![IQRF daemon WebAPP dashboard](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/iqrf-daemon-webapp-gateway.png "IQRF daemon WebAPP dashboard")

* Login using: user=admin; pass=iqrf

## Step 7A - Configure IQRF SPI interface

```bash
http://localhost/en/config/iqrf
```

![Select spidev2.0 interface](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/iqrf-daemon-webapp-config-iqrf.png "Select spidev2.0 interface")

## Step 7B - Restart IQRF daemon

```bash
http://localhost/en/service
```

![Restart IQRF daemon](https://github.com/iqrfsdk/iot-starter-kit/blob/master/install/pics/iqrf-daemon-webapp-service-restart.png "Restart IQRF daemon")

## Step 8A - Install Nodejs

```bash
cd /home/ubilinux
git clone https://github.com/iqrfsdk/iot-starter-kit.git
cd iot-starter-kit/install
sudo cp lsb-release-debian /etc/lsb-release
curl -sL https://deb.nodesource.com/setup_6.x | sudo -E bash -
sudo apt-get install nodejs
```

TBC
