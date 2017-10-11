# Demo Apps

## Get ready for the Docker ride

Follow our [guide](https://github.com/iqrfsdk/iqrf-daemon/blob/master/docker/README.md)

## Node-RED app

Custom flow has been develop by our partner [JoTio](http://jotio.cz/).

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

### Check that all is good

#### See all containers running

```Bash
ubilinux@ubilinux:~/iot-starter-kit/apps/nodered$ docker container ls
CONTAINER ID        IMAGE                  COMMAND                  CREATED             STATUS              PORTS                                            NAMES
4a9cb85e0819        iot-iqrf-nodered-app   "npm start -- --us..."   22 minutes ago      Up 22 minutes       0.0.0.0:1880->1880/tcp                           iot-iqrf-nodered-app
91bef707acc9        iqrf-daemon            "/usr/bin/entry.sh..."   7 hours ago         Up 7 hours                                                           iqrf1daemon
01eda0695d7f        eclipse-mosquitto      "/docker-entrypoin..."   7 hours ago         Up 7 hours          0.0.0.0:1883->1883/tcp, 0.0.0.0:9001->9001/tcp   mqtt1broker
```

#### See the dashboard

http://your-host-ip-address:1880/ui

### Feedback

Please, let us know if we miss anything!
Enjoy & spread the joy!
