Running 2 iqrf-daemon as 2 docker containers servising 2 IQRF networks

- IQRF1 via /dev/spidev2.0 (configuration in iqrf-daemon-config1 folder)
- IQRF2 via /dev/ttyACM0 (configuration in iqrf-daemon-config2 folder)

```Bash
docker network create --subnet 10.1.0.0/16 --gateway 10.1.0.1 --ip-range=10.1.1.0/24 -driver=bridge --label=host1network bridge01
```

```Bash
docker run -d --name mqtt1broker -p 1883:1883 -p 9001:9001 --network=bridge01 --ip=10.1.1.1 --restart=always eclipse-mosquitto
```

```Bash
docker run -d --name iqrf1daemon --device /dev/spidev2.0:/dev/spidev2.0 --device /dev/ttyACM0:/dev/ttyACM0 --privileged --net bridge01 --ip 10.1.1.2 --restart=always -v iqrf-daemon-config1:/etc/iqrf-daemon iqrfsdk/iqrf-daemon
```

```Bash
docker run -d --name iqrf2daemon --device /dev/spidev2.0:/dev/spidev2.0 --device /dev/ttyACM0:/dev/ttyACM0 --privileged --net bridge01 --ip 10.1.1.3 --restart=always -v iqrf-daemon-config2:/etc/iqrf-daemon iqrfsdk/iqrf-daemon
```
