# IQRF in Docker

Docker installation [guideline](https://github.com/iqrfsdk/iqrf-daemon/blob/master/DOCKER.md)

## Running 2 IQRF daemons as 2 docker containers servising 2 IQRF networks

![Block schema](../schema/workshop-schema-docker.png "Schema for IQRF GWs in Docker")

- IQRF Mesh network1 via IQRF SPI (configuration in [iqrf-daemon-config1](iqrf-daemon-config1) folder)
- IQRF Mesh network2 via CDC IQRF (configuration in [iqrf-daemon-config2](iqrf-daemon-config2) folder)

### Dedicated network for our containers
```Bash
docker network create --subnet 10.1.0.0/16 --gateway 10.1.0.1 --ip-range=10.1.1.0/24 -driver=bridge --label=host1network bridge01
```

### MQTT broker

- Runs Mosquitto broker as docker daemon
- Maps ports to the host system
- Assigns dedicated IP address 10.1.1.2

```Bash
docker run -d --name mqtt1broker -p 1883:1883 -p 9001:9001 --network=bridge01 --ip=10.1.1.1 --restart=always eclipse-mosquitto
```

### IQRF Mesh network1

- Runs first IQRF daemon as docker daemon
- Maps devices(SPI, CDC) into container
- Assigns dedicated IP address 10.1.1.2
- Takes configuration from host folder iqrf-daemon-config1 

```Bash
docker run -d --name iqrf1daemon --device /dev/spidev2.0:/dev/spidev2.0 --device /dev/ttyACM0:/dev/ttyACM0 --privileged --net bridge01 --ip 10.1.1.2 --restart=always -v iqrf-daemon-config1:/etc/iqrf-daemon iqrfsdk/iqrf-daemon
```

### IQRF Mesh network2

- Runs second IQRF daemon as docker daemon
- Maps devices(SPI, CDC) into container
- Assigns dedicated IP address 10.1.1.3
- Takes configuration from host folder iqrf-daemon-config2

```Bash
docker run -d --name iqrf2daemon --device /dev/spidev2.0:/dev/spidev2.0 --device /dev/ttyACM0:/dev/ttyACM0 --privileged --net bridge01 --ip 10.1.1.3 --restart=always -v iqrf-daemon-config2:/etc/iqrf-daemon iqrfsdk/iqrf-daemon
```

Enjoy and spread the joy!
