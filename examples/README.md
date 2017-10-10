# Demo Apps

## Get ready for the Docker ride

Follow our [guide](https://github.com/iqrfsdk/iqrf-daemon/blob/master/docker/README.md)

## Node-RED app

### Build it for the UP board

```Bash
git clone https://github.com/iqrfsdk/iot-starter-kit.git
cd apps/nodered
docker build -f Dockerfile.amd64 -t iot-iqrf-nodered-app .
```

### Build it for the RPI board

```Bash
git clone https://github.com/iqrfsdk/iot-starter-kit.git
cd apps/nodered
docker build -f Dockerfile.rpi -t iot-iqrf-nodered-app .
```

### Run it

```Bash
docker container run -d -p 1880:1880 --name iot-iqrf-nodered-app --net bridge01 \ 
--ip 10.1.1.3 --restart=always iot-iqrf-nodered-app
```
