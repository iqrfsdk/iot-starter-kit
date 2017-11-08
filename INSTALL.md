# Installation guide

## IoT Starter Kit - Part1: IQRF Network

* Download IQRF-Startup package
* Install IQRF IDE
* Upload HWP profiles and IQRF standard handlers
* Bond and discover IQRF sensors and actuators

[![IoT Starter Kit - Part1: IQRF Network](https://img.youtube.com/vi/zOiRGo4ZIyo/0.jpg)](https://www.youtube.com/watch?v=zOiRGo4ZIyo "IoT Starter Kit - Part1: IQRF Network")

## IoT Starter Kit - Part2: IQRF GW

### Install OS Linux

* Install [UbiLinux](https://up-community.org/wiki/Ubilinux)
* Post-install tips

```bash
sudo apt update && sudo apt full-upgrade -y
```

### Install Docker CE

* Install [Docker](https://github.com/iqrfsdk/iqrf-daemon/blob/master/docker/INSTALL.md)

### Insert IQRF Coordinator

* Attach [IQRF SPI board](http://www.iqrf.org/weben/downloads.php?id=412)
* Insert prepared IQRF Coordinator to the IQRF SPI board

### Install IQRF GW Docker image

* Ready to go IQRF GW docker [image](https://hub.docker.com/r/iqrfsdk/iqrf-gateway-debian/)

```bash
git clone https://github.com/iqrfsdk/iqrf-gateway.git
...
```

## Learn about possible extensions

Check the extensions [here](https://github.com/iqrfsdk/iot-starter-kit/tree/master/extensions)
