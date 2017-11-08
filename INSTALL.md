# Installation guide

## IoT Starter Kit - Part 1: IQRF Network

* Download IQRF-Startup package
* Install IQRF IDE
* Upload HWP profiles and IQRF standard handlers
* Bond and discover IQRF sensors and actuators

[![IoT Starter Kit - Part1: IQRF Network](https://img.youtube.com/vi/zOiRGo4ZIyo/0.jpg)](https://www.youtube.com/watch?v=zOiRGo4ZIyo "IoT Starter Kit - Part1: IQRF Network")

## IoT Starter Kit - Part 2: IQRF GW

### Step 1 - Insert IQRF Coordinator

* Attach [IQRF SPI board](http://www.iqrf.org/weben/downloads.php?id=412)
* Insert prepared IQRF Coordinator to the IQRF SPI board

### Step 2 - Install OS Linux

* Install [UbiLinux](https://up-community.org/wiki/Ubilinux)
* Post-install tips

```bash
sudo apt update && sudo apt full-upgrade -y
```

### Step 3 - Install Docker CE

* Install [Docker](https://github.com/iqrfsdk/iqrf-daemon/blob/master/docker/INSTALL.md)

### Step 4 - Run Docker image

* Ready IQRF GW [image](https://hub.docker.com/r/iqrfsdk/iqrf-gateway-debian/)

```bash
docker container run -d -p 80:80 -p 1883:1883 -p 8080:8080 -p 9001:9001 --device /dev/spidev2.0:/dev/spidev2.0 --privileged --name iqrf-gateway --restart=always iqrf-gateway:latest
```

#### Check Node-RED Dashboard

```bash
http://localhost/ui
```

#### Check IQRF WebAPP Dashboard

```bash
http://localhost:8080
```

#### Check Supervisor Service Dashboard

```bash
http://localhost:9001
```

## IoT Starter Kit - Part 3: Possible extensions

* Learn more about kit [extensions](https://github.com/iqrfsdk/iot-starter-kit/tree/master/extensions)
